#include "word2vec.h"

#include <vector>

int64_t Distance(const std::vector<int>& vector1, const std::vector<int>& vector2) {
    int64_t dist = 0;
    for (size_t i = 0; i < vector1.size(); ++i) {
        dist += static_cast<int64_t>(vector1[i]) * vector2[i];
    }
    return dist;
}
std::vector<std::string> FindClosestWords(const std::vector<std::string>& words,
                                          const std::vector<std::vector<int>>& vectors) {
    int64_t length = static_cast<int64_t>(words.size());

    if (length <= 1) {
        return {};
    }

    int64_t max_dist = Distance(vectors[0], vectors[1]);
    std::vector<std::string> result;

    for (int64_t i = 1; i != length; ++i) {
        if (Distance(vectors[0], vectors[i]) > max_dist) {
            max_dist = Distance(vectors[0], vectors[i]);
            result.clear();
            result.push_back(words[i]);
        } else if (Distance(vectors[0], vectors[i]) == max_dist) {
            result.push_back(words[i]);
        }
    }
    return result;
}
