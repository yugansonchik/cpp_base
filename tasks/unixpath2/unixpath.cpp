#include "unixpath.h"

#include <deque>

UnixPath::UnixPath(std::string_view initial_dir) {
    Split(initial_dir, initial_deq_);
    Normalize(initial_deq_);
    abs_deq_ = initial_deq_;
}

void UnixPath::ChangeDirectory(std::string_view path) {
    if (path.starts_with("/")) {
        abs_deq_.clear();
    }
    Split(path, abs_deq_);
    Normalize(abs_deq_);
}

std::string UnixPath::GetAbsolutePath() const {
    std::string result;
    for (const auto& dir : abs_deq_) {
        result += "/";
        result += dir;
    }
    return result;
}

std::string UnixPath::GetRelativePath() const {
    std::vector<std::string_view> rel_path;
    size_t last_eq_idx = -1;
    for (size_t i = initial_deq_.size(); i > 0; --i) {
        if (i - 1 >= abs_deq_.size()) {
            rel_path.push_back("..");
            continue;
        }
        if (initial_deq_[i - 1] == abs_deq_[i - 1]) {
            if (rel_path.empty()) {
                rel_path.push_back(".");
            }
            last_eq_idx = i - 1;
            break;
        } else {
            rel_path.push_back("..");
            continue;
        }
    }
    for (size_t i = last_eq_idx + 1; i < abs_deq_.size(); ++i) {
        rel_path.push_back(abs_deq_[i]);
    }
    std::string result;
    for (const auto& dir : rel_path) {
        result += dir;
        result += "/";
    }
    result.erase(result.size() - 1);
    return result;
}

void UnixPath::Split(std::string_view str, std::vector<std::string_view>& result) {
    while (!str.empty()) {
        if (str.starts_with("/")) {
            str.remove_prefix(1);
            continue;
        }
        size_t sl_idx = str.find("/");
        if (sl_idx == std::string_view::npos) {
            result.push_back(str);
            break;
        } else {
            result.push_back(str.substr(0, sl_idx));
        }
        str.remove_prefix(sl_idx);
    }
}

void UnixPath::Normalize(std::vector<std::string_view>& dirs) const {
    for (size_t i = 0; i < dirs.size();) {
        if (dirs[i] == ".") {
            dirs.erase(dirs.begin() + static_cast<int64_t>(i));
        } else if (dirs[i] == "..") {
            if (i == 0) {
                dirs.erase(dirs.begin());
            } else {
                dirs.erase(dirs.begin() + static_cast<int64_t>(i) - 1, dirs.begin() + static_cast<int64_t>(i) + 1);
                i--;
            }
        } else {
            i++;
        }
    }
}