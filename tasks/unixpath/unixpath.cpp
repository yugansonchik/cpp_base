#include "unixpath.h"
#include <vector>

std::string NormalizePath(std::string_view current_working_dir, std::string_view path) {
    std::string absolute_path;
    if (path[0] == '/') {
        for (const auto &letter : path) {
            absolute_path += letter;
        }
    } else {
        for (const auto &letter : current_working_dir) {
            absolute_path += letter;
        }

        absolute_path += '/';

        for (const auto &letter : path) {
            absolute_path += letter;
        }
    }
    std::vector<std::string> additional_vector;
    std::string answer;

    for (size_t index = 0; index < absolute_path.length(); index++) {
        std::string current_dir;
        while (index < absolute_path.length() && absolute_path[index] != '/') {
            current_dir += absolute_path[index];
            index++;
        }
        if (current_dir == "..") {
            if (!additional_vector.empty()) {
                additional_vector.pop_back();
            }
        } else if (current_dir != "." && !current_dir.empty()) {
            additional_vector.push_back(current_dir);
        }
    }
    for (const auto& i : additional_vector) {
        answer += "/" + i;
    }
    if (answer.empty()) {
        return "/";
    }
    return answer;
}