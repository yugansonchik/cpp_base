#include "search.h"
#include <iostream>
#include <cmath>
#include <tuple>

std::string GetLowercase(const std::string_view s) {
    std::string lowercase_string;
    for (const char c : s) {
        lowercase_string += static_cast<char>(std::tolower(c));
    }
    return lowercase_string;
}

size_t CaseInsensitiveStringHash::operator()(const std::string_view input) const {
    std::hash<std::string> hash;
    auto lowercase_string = GetLowercase(input);
    return hash(lowercase_string);
}

bool CaseInsensitiveStringComparator::operator()(const std::string_view str1, const std::string_view str2) const {
    if (str1.size() != str2.size()) {
        return false;
    }

    for (size_t i = 0; i < str1.size(); ++i) {
        if (std::tolower(str1[i]) != std::tolower(str2[i])) {
            return false;
        }
    }
    return true;
}

std::vector<std::string_view> SearchEngine::Split(const std::string_view text, bool by_lines) const {
    size_t lb = 0;
    size_t rb = 0;
    std::vector<std::string_view> result;

    const auto text_size = text.size();
    while (rb < text_size) {
        const bool flag = by_lines ? (text[rb] == '\n') : (!std::isalpha(text[rb]));
        if (flag) {
            if (rb != lb) {
                result.emplace_back(text.data() + lb, rb - lb);
            }
            lb = rb + 1;
        }
        rb++;
    }

    if (rb == text_size && lb != text_size) {
        result.emplace_back(text.data() + lb, rb - lb);
    }

    return result;
}

void SearchEngine::BuildIndex(std::string_view text) {
    total_lines = 0;
    word_info_.clear();
    line_word_count_.clear();
    inputLines = Split(text, true);

    for (const auto& line : inputLines) {
        line_word_count_.push_back(0);
        for (const auto& word : Split(line, false)) {
            line_word_count_[total_lines]++;
            auto& word_info_ref = word_info_[word];
            if (word_info_ref.amount_in_line[total_lines]++ == 0) {
                word_info_ref.lines_count++;
            }
        }
        total_lines++;
    }
}

std::vector<std::string_view> SearchEngine::Search(std::string_view query, size_t results_count) const {
    std::unordered_set<std::string_view, CaseInsensitiveStringHash, CaseInsensitiveStringComparator> query_term_set;
    std::vector<std::pair<double, size_t>> scored_lines(total_lines);
    for (const auto& search_term : Split(query, false)) {
        bool is_new_word = false;
        std::tie(std::ignore, is_new_word) = query_term_set.emplace(search_term);
        if (is_new_word) {
            auto word_info_iter = word_info_.find(search_term);
            for (size_t i = 0; i < total_lines; ++i) {
                scored_lines[i].second = i;
                auto amount_in_line_iter = word_info_iter->second.amount_in_line.find(i);
                size_t amount_in_line = (amount_in_line_iter == word_info_iter->second.amount_in_line.end()) ? 0 : amount_in_line_iter->second;
                double tf = static_cast<double>(amount_in_line) / static_cast<double>(line_word_count_[i]);
                double idf = std::log(static_cast<double>(total_lines) / static_cast<double>(word_info_iter->second.lines_count));
                scored_lines[i].first += tf * idf;
            }
        }
    }
    std::sort(scored_lines.begin(), scored_lines.end(),
              [](const std::pair<double, size_t>& a, const std::pair<double, size_t>& b) {
                  return std::tuple(-a.first, a.second) < std::tuple(-b.first, b.second);
              });

    std::vector<std::string_view> substrings;
    for (const auto& [relevanceScore, line_index] : scored_lines) {
        if (substrings.size() == results_count || relevanceScore <= 0) {
            break;
        }
        substrings.push_back(inputLines[line_index]);
    }

    return substrings;
}
