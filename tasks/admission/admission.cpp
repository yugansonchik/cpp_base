#include "admission.h"

auto TieStudentDate(const Student* student) {
    return std::tie(student->birth_date.year, student->birth_date.month, student->birth_date.day);
}

bool CompareStudents(const Student* student_1, const Student* student_2) {
    if (student_1->name != student_2->name) {
        return student_1->name < student_2->name;
    } else {
        return TieStudentDate(student_1) < TieStudentDate(student_2);
    }
}

bool CompareApplicants(const Applicant* applicant_1, const Applicant* applicant_2) {
    if (applicant_1->points != applicant_2->points) {
        return applicant_1->points >= applicant_2->points;
    } else if (TieStudentDate(&applicant_1->student) != TieStudentDate(&applicant_2->student)) {
        return TieStudentDate(&applicant_1->student) < TieStudentDate(&applicant_2->student);
    } else {
        return applicant_1->student.name < applicant_2->student.name;
    }
}

AdmissionTable FillUniversities(const std::vector<University>& universities, const std::vector<Applicant>& applicants) {
    std::unordered_map<std::string, int> university_places_left;

    std::unordered_map<std::string, int> max_students;

    for (const auto& university : universities) {
        university_places_left[university.name] = static_cast<int>(university.max_students);
    }

    std::vector<const Applicant*> sorted_applicants;
    for (const auto& applicant : applicants) {
        sorted_applicants.push_back(&applicant);
    }

    sort(sorted_applicants.begin(), sorted_applicants.end(), CompareApplicants);

    AdmissionTable resulting_table;

    for (const Applicant* applicant : sorted_applicants) {
        for (const std::string& university_name : (*applicant).wish_list) {
            auto it = university_places_left.find(university_name);
            if (it->second > 0) {
                --(it->second);
                resulting_table[university_name].push_back(&(applicant->student));
                break;
            }
        }
    }

    for (auto& pair : resulting_table) {
        std::sort(pair.second.begin(), pair.second.end(), CompareStudents);
    }
    return resulting_table;
}
