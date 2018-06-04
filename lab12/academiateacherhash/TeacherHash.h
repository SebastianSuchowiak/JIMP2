//
// Created by sebastian on 02.06.18.
//

#ifndef JIMP_EXERCISES_TEACHERHASH_H
#define JIMP_EXERCISES_TEACHERHASH_H


#include <cstddef>
#include <string>

namespace academia {

    class TeacherId {

    public:

        explicit TeacherId(size_t id){ m_id = id; };

        bool operator==(const TeacherId &other) const { return m_id == other.m_id; };
        operator int() const { return (int) m_id; };

    private:

        size_t m_id;
    };

    class Teacher {

    public:

        Teacher(TeacherId id, const std::string &name, const std::string &department) : m_id{id},
                                                                                     m_name{name},
                                                                                     m_department{department}{};

        bool operator==(Teacher other) const { return m_id == other.m_id &&
                                                      m_name == other.m_name &&
                                                      m_department == other.m_department; };
        bool operator!=(Teacher other) const { return m_id != other.m_id ||
                                                      m_name != other.m_name ||
                                                      m_department != other.m_department; };
        
        TeacherId Id() const { return m_id; };
        std::string Name() const { return m_name; };
        std::string Department() const { return m_department; };

    private:

        TeacherId m_id;
        std::string m_name;
        std::string m_department;

    };

    class TeacherHash {

    public:
        size_t operator()(const Teacher& teacher) const
        {
            using std::hash;
            using std::string;

            return ((hash<string>()(teacher.Department())
                     ^ (hash<string>()(teacher.Name()) << 1)) >> 1)
                   ^ (hash<int>()(teacher.Id()) << 1);
        }
    };
}


#endif //JIMP_EXERCISES_TEACHERHASH_H
