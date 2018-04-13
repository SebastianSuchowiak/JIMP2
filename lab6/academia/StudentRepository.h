//
// Created by sebastian on 10.04.18.
//

#ifndef JIMP_EXERCISES_STUDENTREPOSITORY_H
#define JIMP_EXERCISES_STUDENTREPOSITORY_H

#include <string>

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
    };



}



#endif //JIMP_EXERCISES_STUDENTREPOSITORY_H
