#include "unixpath.h"

UnixPath::UnixPath(std::string_view initial_dir) {
    ChangeDirectory(initial_dir);
    initial_dir_ = current_dir_;
}

std::string UnixPath::GetAbsolutePath() const {
    std::string result;
    for (auto it = current_dir_.begin(); it != current_dir_.end(); ++it) {
        result += "/" + *it;
    }
    return result.empty() ? "/" : result;
}

std::string UnixPath::GetRelativePath() const {
    auto it1 = initial_dir_.begin();
    auto it2 = current_dir_.begin();
    while (it1 != initial_dir_.end() && it2 != current_dir_.end() && *it1 == *it2) {
        ++it1;
        ++it2;
    }
    std::string result;
    for (size_t i = std::distance(it1, initial_dir_.end()); i > 0; --i) {
        result += "../";
    }
    if (result.empty()) {
        result = ".";
    } else {
        result.pop_back();
    }
    for (; it2 != current_dir_.end(); ++it2) {
        result += "/" + *it2;
    }
    return result;
}

void UnixPath::ChangeDirectory(std::string_view path) {
    current_dir_.clear();
    std::istringstream ss(std::string(path));
    std::string dir;
    while (std::getline(ss, dir, '/')) {
        if (dir.empty() || dir == ".") {
            continue;
        }
        if (dir == "..") {
            if (!current_dir_.empty()) {
                current_dir_.pop_back();
            }
        } else {
            current_dir_.push_back(dir);
        }
    }
}
