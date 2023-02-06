#include "associative_operation.h"
#include <vector>
bool IsAssociative(const std::vector<std::vector<size_t>>& table) {
    int32_t cnt_of_rows = static_cast<int>(table.size());
    for (size_t i = 0; i < cnt_of_rows; ++i) {
        for (size_t j = 0; j < cnt_of_rows; ++j) {
            for(size_t k = 0; k < cnt_of_rows; ++k) {
                if (table[table[i][j]][k] != table[i][table[j][k]]) {
                    return false;
                }
            }
        }
    }
    return true;