//
// Created by sebastian on 10.04.18.
//

#ifndef JIMP_EXERCISES_STUDENTREPOSITORY_H
#define JIMP_EXERCISES_STUDENTREPOSITORY_H

#include <string>
#include <stdexcept>


using std::string;

namespace academia {

    class StudyYear {
    public:
        StudyYear(int year);
        StudyYear();

        StudyYear operator++();
        StudyYear operator--();
        bool operator<(StudyYear other) const;
        bool operator==(const StudyYear &other) const;
        operator int ()const;
    public:
        int m_year;
    };


    class Student {
    public:
        Student(const string &id, const string &first_name, const string &last_name, const string &program, int year);

        Student();

        string Id();
        string FirstName();
        string LastName();
        string Program();
        StudyYear Year();

        void ChangeLastName(const string &new_last_name);

        bool operator==(const Student other) const;
    public:
        string m_id;
        string m_first_name;
        string m_last_name;
        string m_program;
        StudyYear m_year;

    private:
        void Validate(const string &id, const string &first_name, const string &last_name, const string &program, int year);
    };


    class InvalidAge : public std::invalid_argument {
    public:
        InvalidAge(const int &age) : std::invalid_argument{"Wrong age"}, m_age{age}{}
    public:
        int GetAge() const {
            return m_age;
        }
    private:
        int m_age;
    };


    class InvalidFirstName : public std::invalid_argument {
    public:
        InvalidFirstName(const std::string &name) : std::invalid_argument{"Wrong first name: " + name}, m_name{name}{}
    public:
        std::string GetFirstName() const {
            return m_name;
        }
    private:
        std::string m_name;
    };


    class InvalidLastName : public std::invalid_argument {
    public:
        InvalidLastName(const std::string &name) : std::invalid_argument{"Wrong last name"}, m_name{name}{}
    public:
        std::string GetLastName() const {
            return m_name;
        }
    private:
        std::string m_name;
    };


    class InvalidProgram : public std::invalid_argument {
    public:
        explicit InvalidProgram(const std::string &program) : std::invalid_argument{"Wrong program name"}, m_program{program}{}
    public:
        std::string GetProgram() const {
            return m_program;
        }
    private:
        std::string m_program;
    };

}

//InvalidNameSurname, InvalidNameCharacters, InvalidAge, InvalidProgram

#endif //JIMP_EXERCISES_STUDENTREPOSITORY_H
