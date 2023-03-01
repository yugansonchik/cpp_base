#pragma once

#include <map>
#include <set>
#include <string>
#include <vector>
#include <unordered_map>

using StudentName = std::string;
using TaskName = std::string;

using ScoreTable = std::map<StudentName, std::set<TaskName>>;

struct InfoAboutTask {
    bool check_success = false;
    bool merge_closed = true;
};

class Scorer {
public:
    void OnCheckFailed(const StudentName& student_name, const TaskName& task_name);
    void OnCheckSuccess(const StudentName& student_name, const TaskName& task_name);
    void OnMergeRequestOpen(const StudentName& student_name, const TaskName& task_name);
    void OnMergeRequestClosed(const StudentName& student_name, const TaskName& task_name);
    void Reset();
    void AddToScoreTable(const StudentName& student_name, const TaskName& task_name);

    ScoreTable GetScoreTable() const;

private:
    ScoreTable score_table_;
    std::unordered_map<std::string, std::unordered_map<std::string, InfoAboutTask>> student_task_;
};