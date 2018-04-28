//
// Created by sebastian on 10.04.18.
//

#include <set>
#include <regex>
#include "StudentRepository.h"

academia::StudyYear academia::StudyYear::operator++() {
    m_year++;
    return *this;
}

academia::StudyYear academia::StudyYear::operator--() {
    m_year--;
    return  *this;
}

bool academia::StudyYear::operator==(const academia::StudyYear &other) const{
    return m_year == other.m_year;
}

academia::StudyYear::StudyYear(int year) {
    m_year = year;
}

academia::StudyYear::StudyYear() {
    m_year = 1;
}

bool academia::StudyYear::operator<(StudyYear other) const {
    return m_year < other.m_year;
}

academia::StudyYear::operator int() const {
    return m_year;
}

string academia::Student::Id() {
    return m_id;
}

string academia::Student::FirstName() {
    return m_first_name;
}

string academia::Student::LastName() {
    return m_last_name;
}

string academia::Student::Program() {
    return m_program;
}

academia::StudyYear academia::Student::Year() {
    return m_year;
}

void academia::Student::ChangeLastName(const string &new_last_name) {
    m_last_name = new_last_name;
}

bool academia::Student::operator==(const Student other) const {
    return (m_last_name == other.m_last_name &&
            m_year == other.m_year &&
            m_program == other.m_program &&
            m_first_name == other.m_first_name &&
            m_id == other.m_id);
}

academia::Student::Student(const string &id, const string &first_name, const string &last_name, const string &program,
                           int year) {
    Validate(id, first_name, last_name, program, year);
    m_id = id;
    m_first_name = first_name;
    m_last_name = last_name;
    m_program = program;
    m_year = StudyYear(year);
}

academia::Student::Student() {}

void
academia::Student::Validate(const string &id, const string &first_name, const string &last_name, const string &program,
                            int year) {

    std::set<std::string> program_set = {"informatyka", "ekonomia", "matematyka", "fizyka", "filozofia"};
    std::regex correct_name ("[A-Z][a-z]+");

    if (year > 100 || year < 10) {
        throw InvalidAge(year);
    }
    if (program_set.find(program) == program_set.end()) {
        throw InvalidProgram(program);
    }
    if (!(std::regex_match(first_name, correct_name))) {
        throw InvalidFirstName(first_name);
    }
    if (!(std::regex_match(last_name, correct_name))) {
        throw InvalidLastName(last_name);
    }

}
