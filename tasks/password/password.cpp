#include "password.h"
#include <cctype>
#include <iostream>
#include <string>

const int32_t MIN_LENGTH = 8;
const int32_t MAX_LENGTH = 14;
const int32_t MIN_ASCII = 33;
const int32_t MAX_ASCII = 126;
bool ValidatePassword(const std::string& password) {
    int len_of_password = password.length();
    if (len_of_password < MIN_LENGTH || password.size() > MAX_LENGTH) {
        return false;
    }
    bool digit = false;
    bool upper = false;
    bool lower = false;
    bool other = false;
    for (char p : password) {
        if (p < MIN_ASCII || p > MAX_ASCII) {
            return false;
        } else if (std::isdigit(p) && !digit) {
            digit = true;
        } else if (std::isupper(p) && !upper) {
            upper = true;
        } else if (std::islower(p) && !lower) {
            lower = true;
        } else {
            other = true;
        }
    }
    return digit + upper + lower + other >= 3;
}