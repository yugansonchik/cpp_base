#include "palindrome.h"
#include <algorithm>
#include <iostream>
#include <string>

bool IsPalindrome(const std::string& str) {
    std::string str_copy = str;
    std::getline(std::cin, str_copy);
    str_copy.erase(std::remove(str_copy.begin(), str_copy.end(), ' '), str_copy.end());
    return std::equal(str_copy.begin(), str_copy.begin() + static_cast<int>(str_copy.size()) / 2, str_copy.rbegin());
}