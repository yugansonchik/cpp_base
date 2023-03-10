#pragma once

#include <deque>
#include <string>
#include <string_view>
#include <vector>

class UnixPath {
public:
    explicit UnixPath(std::string_view initial_dir);

    void ChangeDirectory(std::string_view path);

    std::string GetAbsolutePath() const;
    std::string GetRelativePath() const;

private:
    std::vector<std::string_view> initial_deq_;
    std::vector<std::string_view> abs_deq_;
    void Split(std::string_view str, std::vector<std::string_view>& result);
    void Normalize(std::vector<std::string_view>& dirs) const;
};