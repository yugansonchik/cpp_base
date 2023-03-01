#include "scorer.h"

void Scorer::AddToScoreTable(const StudentName& student_name, const TaskName& task_name) {
    if (!student_task_[student_name][task_name].check_success || !student_task_[student_name][task_name].merge_closed) {
        score_table_[student_name].erase(task_name);
        if (score_table_[student_name].empty()) {
            score_table_.erase(student_name);
        }
    } else {
        score_table_[student_name].insert(task_name);
    }
}

void Scorer::OnCheckFailed(const StudentName& student_name, const TaskName& task_name) {
    student_task_[student_name][task_name].check_success = false;
    AddToScoreTable(student_name, task_name);
}

void Scorer::OnCheckSuccess(const StudentName& student_name, const TaskName& task_name) {
    student_task_[student_name][task_name].check_success = true;
    AddToScoreTable(student_name, task_name);
}

void Scorer::OnMergeRequestOpen(const StudentName& student_name, const TaskName& task_name) {
    student_task_[student_name][task_name].merge_closed = false;
    AddToScoreTable(student_name, task_name);
}

void Scorer::OnMergeRequestClosed(const StudentName& student_name, const TaskName& task_name) {
    student_task_[student_name][task_name].merge_closed = true;
    AddToScoreTable(student_name, task_name);
}

void Scorer::Reset() {
    score_table_.clear();
    student_task_.clear();
}

ScoreTable Scorer::GetScoreTable() const {
    return score_table_;
}