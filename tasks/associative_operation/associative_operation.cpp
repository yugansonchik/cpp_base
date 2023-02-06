#include "associative_operation.h"
#include <iostream>
#include <vector>
bool IsAssociative(const std::vector<std::vector<size_t>>& table) {
    int32_t cnt_of_rows = table.size();
    for (size_t i = 0; i < cnt_of_rows; ++i) {
        for (size_t j = 0; j < i; ++j) {
            for(size_t k = 0; k < j; ++k) {
                if (table[table[i][j]][k] != table[i][table[j][k]]) {
                    return false;
                }
            }
        }
    }
    return true;
}
int main() {
    int32_t n = 0;
    std::cin >> n;
    std::vector<std::vector<size_t>> table;
    for (size_t i = 0; i < n; ++i) {
        std::vector<size_t> v(n, 0);
        table.push_back(v);
    }
    if (IsAssociative(table)) {
        std::cout << "Associative\n";
    } else {
        std::cout << "NotAssociative\n";
    }
    return 0;
}