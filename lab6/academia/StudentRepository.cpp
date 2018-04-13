//
// Created by sebastian on 10.04.18.
//

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
    m_id = id;
    m_first_name = first_name;
    m_last_name = last_name;
    m_program = program;
    m_year = StudyYear(year);
}

academia::Student::Student() {}
