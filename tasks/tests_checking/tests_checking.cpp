#include "tests_checking.h"
#include <deque>
#include <vector>

std::vector<std::string> StudentsOrder(const std::vector<StudentAction>& student_actions,
                                       const std::vector<size_t>& queries) {
    std::deque<std::string> list_of_names;
    std::vector<std::string> answer;

    for (const auto& actions : student_actions) {
        if (actions.side == Side::Top) {
            list_of_names.push_front(actions.name);
        } else {
            list_of_names.push_back(actions.name);
        }
    }

    for (size_t i = 0; i < queries.size(); ++i) {
        answer.push_back(list_of_names[queries[i] - 1]);
    }
    return answer;
}
