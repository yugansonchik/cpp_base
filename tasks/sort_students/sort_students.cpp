#include "sort_students.h"
#include <tuple>

bool CompareDates(const Date& left, const Date& right) {
    return (left.year < right.year)
           && (left.month < right.month)
           && (left.day < right.day);
    }
bool ComparatorByName(const Student& left, const Student& right){
    if (std::tie(left.last_name, left.name) == std::tie(right.last_name, right.name)){
        return CompareDates(left.birth_date, right.birth_date);
    }
    return (left.last_name < right.last_name)
           && (left.name < right.name);
}
bool ComporatorByDate(const Student& left, const Student& right) {
    if (std::tie(left.birth_date.year, left.birth_date.month, left.birth_date.day) == std::tie(right.birth_date.year, right.birth_date.month, right.birth_date.day)) {
        return (left.last_name < right.last_name)
               && (left.name < right.name);
    }
    return CompareDates(left.birth_date, right.birth_date);
}
void SortStudents(std::vector<Student>& students, SortKind sortKind) {
    switch (sortKind) {
        case SortKind::Date:
            return std::sort(students.begin(), students.end(), ComporatorByDate);
        case SortKind::Name:
            return std::sort(students.begin(), students.end(), ComparatorByName);
    }
}