#include "search.h"
#include "math.h"
#include <cctype>
#include <string>

std::vector<std::string_view> SearchEngine::Search(std::string_view query, size_t results_count) const {
    if (!build_called_) {
        return {};
    }

    std::vector<std::string_view> found_rows;
    std::string buffer;
    std::set<std::string> unique_words;
    std::unordered_map<std::string, size_t> row_words_local_counter;
    std::unordered_map<std::string, size_t> word_rows_total_counter;

    for (const auto& letter : query) {
        if (std::isalpha(letter)) {
            buffer.push_back(static_cast<char>(std::tolower(letter)));
        } else if (!buffer.empty()) {
            unique_words.insert(buffer);
            buffer.clear();
        }
    }
    if (!buffer.empty()) {
        unique_words.insert(buffer);
        buffer.clear();
    }

    const auto get_word = [](std::string_view text, size_t start, size_t end) -> std::string {
        return std::string(text.substr(start + 1, end - start - 1));
    };

    const auto get_tf_idf = [&](const std::vector<std::pair<size_t, size_t>>& row,
                                                                 const std::set<std::string>& words) -> double {
        size_t words_count = row.size();
        double sum_of_tf_idf = 0;
        for (const auto& [start, end] : row) {
            std::string word = get_word(text_, start, end);
            std::transform(word.begin(), word.end(), word.begin(), ::tolower);
            if (words.find(word) != words.end()) {
                ++row_words_local_counter[word];
            }
        }
        for (const auto& word : words) {
            if (row_words_local_counter[word] > 0 && word_rows_total_counter[word] > 0) {
                double tf = static_cast<double>(row_words_local_counter[word]) /
                                                         static_cast<double>(static_cast<float>(words_count));
                double idf = std::log(static_cast<double>(words_indexes_.size()) /
                                                                             static_cast<double>(word_rows_total_counter[word]));
                sum_of_tf_idf += tf * idf;
                row_words_local_counter[word] = 0;
            }
        }
        return sum_of_tf_idf;
    };

    std::vector<Row> rows_relevance;
    rows_relevance.reserve(words_indexes_.size());
    for (size_t i = 0; i < words_indexes_.size(); ++i) {
        auto& row = words_indexes_[i];
        for (const auto& [start, end] : row) {
            std::string word = get_word(text_, start, end);
            std::transform(word.begin(), word.end(), word.begin(), ::tolower);
            if (unique_words.find(word) != unique_words.end()) {
                ++word_rows_total_counter[word];
            }
        }
        double tf_idf = get_tf_idf(row, unique_words);
        if (tf_idf > 0) {
            rows_relevance.emplace_back(tf_idf, rows_ind_len_[i].first, rows_ind_len_[i].second);
        }
    }

    std::stable_sort(rows_relevance.rbegin(), rows_relevance.rend());
    found_rows.reserve(std::min(rows_relevance.size(), results_count));
    for (size_t i = 0; i < std::min(rows_relevance.size(), results_count); ++i) {
        found_rows.push_back(text_.substr(rows_relevance[i].begin_index, rows_relevance[i].length));
    }

    return found_rows;
}

void SearchEngine::BuildIndex(std::string_view text) {
    build_called_ = true;

    text_ = text;

    // Clear the data structures used to store the index
    words_indexes_.clear();
    rows_ind_len_.clear();

    // Initialize variables for tracking the current word and row
    size_t word_start = 0;
    size_t row_start = 0;

    // Iterate over each character in the input text, looking for word and row boundaries
    for (size_t i = 0; i <= text_.size(); ++i) {
        if (i == text_.size() || !std::isalpha(text_[i])) {
            // If we've found a word boundary, add the previous word to the current row
            if (i > word_start) {
                words_indexes_.back().emplace_back(word_start, i - word_start);
            }
            word_start = i;

            // If we've found a row boundary, add the current row to the index
            if (i == text_.size() || text_[i] == '\n') {
                if (!words_indexes_.empty()) {
                    rows_ind_len_.emplace_back(row_start, i - row_start + 1);
                }
                words_indexes_.emplace_back();
                row_start = i + 1;
            }
        }
    }
}
