#include "search.h"
#include <cctype>
#include <string_view>
#include <cmath>
#include <map>
#include <tuple>

std::map<std::string, double> Mapping(std::string_view words) {

    std::map<std::string, double> result;
    int64_t start_of_word = 0;
    int64_t length_of_word = 0;
    int64_t words_size = static_cast<int64_t>(words.size());
    for (int64_t index = 0; index != words_size; ++index) {
        if ((index == 0) || (std::isalpha(words[index]) && std::isalpha(words[index - 1]))) {
            length_of_word += 1;
        } else if (std::isalpha(words[index])) {
            start_of_word = index;
            length_of_word = 1;
        } else if (std::isalpha(words[index - 1])) {
            std::string_view word = words.substr(start_of_word, length_of_word);
            std::string word1;
            for (const auto &letter : word) {
                word1 += letter;
            }
            result[word1] = 0;
        }
    }
    std::string_view word = words.substr(start_of_word, length_of_word);
    std::string word1;
    for (const auto &letter : word) {
        word1 += letter;
    }
    result[word1] = 0;
    return result;
}

bool CompareByRelevance(std::pair<std::pair<int, int>, double> string1,
                        std::pair<std::pair<int, int>, double> string2) {
    return std::tie(string1.second) > std::tie(string2.second);
}

std::vector<std::string_view> Search(std::string_view text, std::string_view query, size_t results_count) {

    int64_t number_of_strings = 0;
    std::map<std::string, double> idf = Mapping(query);

    std::vector<std::pair<std::pair<int, int>, std::map<std::string, double>>> additional_vector;

    std::vector<std::pair<std::pair<int, int>, double>> measures_for_strings;
    std::vector<std::string_view> result;

    int64_t begin_word = 0;
    int64_t length_of_word = 0;

    char end = '\n';
    int64_t begin_string = 0;
    int64_t length_of_string = 0;
    int64_t number_of_words = 0;
    std::map<std::string, double> tf_for_string;
    int64_t size_of_text = static_cast<int64_t>(text.size());
    for (int64_t index = 0; index != size_of_text; ++index) {

        if (text[index] == end) {

            for (const auto &word : tf_for_string) {
                if (tf_for_string[word.first] > 0) {
                    tf_for_string[word.first] /= static_cast<double>(number_of_words);
                    idf[word.first] += 1;
                }
            }
            auto begin_length = std::make_pair(begin_string, length_of_string);
            auto string_tf_pair = std::make_pair(begin_length, tf_for_string);
            additional_vector.push_back(string_tf_pair);
            tf_for_string.clear();

            number_of_strings += 1;
            begin_string = index + 1;
            length_of_string = 0;
            begin_word = index + 1;
            length_of_word = 0;
            number_of_words = 0;
        } else if ((index == 0) || (std::isalpha(text[index]) && std::isalpha(text[index - 1]))) {
            length_of_word += 1;
            length_of_string += 1;
        } else if (std::isalpha(text[index])) {
            number_of_words += 1;
            begin_word = index;
            length_of_word = 1;
            length_of_string += 1;
        } else if (std::isalpha(text[index - 1])) {
            length_of_string += 1;

            std::string_view word = text.substr(begin_word, length_of_word);
            std::string word1;
            for (const auto &letter : word) {
                word1 += letter;
            }
            std::transform(word1.begin(), word1.end(), word1.begin(), tolower);
            if (idf.count(word1) > 0) {
                tf_for_string[word1] += 1;
            }
        } else {
            length_of_string += 1;
        }
    }
    for (const auto &word : tf_for_string) {
        if (tf_for_string[word.first] > 0) {
            tf_for_string[word.first] /= static_cast<double>(number_of_words);
            idf[word.first] += 1;
        }
    }
    number_of_strings += 1;
    auto begin_length = std::make_pair(begin_string, length_of_string);
    auto string_tf_pair = std::make_pair(begin_length, tf_for_string);
    additional_vector.push_back(string_tf_pair);

    for (const auto &word : idf) {
        idf[word.first] = static_cast<double>(number_of_strings) / idf[word.first];
    }

    for (int64_t index = 0; index != static_cast<int64_t>(additional_vector.size()); ++index) {
        double relevance_measure = 0;
        for (const auto &word : additional_vector[index].second) {
            relevance_measure += static_cast<double>(word.second) * log(idf[word.first]);
        }
        auto string_measure = std::make_pair(additional_vector[index].first, relevance_measure);
        measures_for_strings.push_back(string_measure);
    }

    std::sort(measures_for_strings.begin(), measures_for_strings.end(), CompareByRelevance);

    for (size_t index = 0; static_cast<double>(index) !=
                           fmin(static_cast<double>(results_count), static_cast<double>(measures_for_strings.size()));
         ++index) {
        if (measures_for_strings[index].second > 0) {
            result.push_back(
                text.substr(measures_for_strings[index].first.first, measures_for_strings[index].first.second));
        }
    }
    return result;
}