#include "unixpath.h"

UnixPath::UnixPath(std::string_view initial_dir) {
    ChangeDirectory(initial_dir);
    this->initial_dir_ = current_dir_;
}

std::string UnixPath::GetAbsolutePath() const {
    std::string result;
    for (const auto& dir : current_dir_) {
        result += "/";
        result += dir;
    }
    return result.empty() ? "/" : result;
}

std::string UnixPath::GetRelativePath() const {
    auto it1 = initial_dir_.begin();
    auto it2 = current_dir_.begin();
    while (it1 != initial_dir_.end() && it2 != current_dir_.end() && *it1 == *it2) {
        it1++;
        it2++;
    }

    std::string result;
    for (size_t i = 0; i < static_cast<size_t>(initial_dir_.end() - it1); ++i) {
        result += "../";
    }

    if (result.empty()) {
        result = ".";
    } else {
        result.pop_back();
    }

    while (it2 != current_dir_.end()) {
        result += "/";
        result += *it2;
        it2++;
    }

    return result;
}

void UnixPath::ChangeDirectory(std::string_view path) {
    if (path.starts_with("/")) {
        current_dir_.clear();
    }
    while (!path.empty()) {
        if (path.starts_with("/")) {
            path.remove_prefix(1);
            continue;
        }
        size_t index = path.find("/");
        if (index == std::string_view::npos) {
            current_dir_.push_back(path);
            break;
        } else {
            current_dir_.push_back(path.substr(0, index));
        }
        path.remove_prefix(index);
    }
    for (size_t i = 0; i < current_dir_.size();) {
        if (current_dir_[i] == ".") {
            current_dir_.erase(current_dir_.begin() + static_cast<int64_t>(i));
        } else if (current_dir_[i] == "..") {
            current_dir_.erase(current_dir_.begin());
        }
    }
}