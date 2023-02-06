#include "password.h"
#include <cctype>
#include <iostream>
#include <string>

bool ValidatePassword(const std::string& password) {

    const int32_t min_length = 8;
    const int32_t max_length = 14;
    const char min_ascii = 33;
    const char max_ascii = 126;

    if (password.size() < min_length || password.size() > max_length) {
        return false;
    }
    int digit = 0;
    int upper = 0;
    int lower = 0;
    int other = 0;
    for (char p : password) {
        if (p < min_ascii || p > max_ascii) {
            return false;
        } else if (std::isdigit(p) && !digit) {
            digit = 1;
        } else if (std::isupper(p) && !upper) {
            upper = 1;
        } else if (std::islower(p) && !lower) {
            lower = 1;
        } else {
            other = 1;
        }
    }
    return digit + upper + lower + other >= 3;
}