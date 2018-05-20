//
// Created by sebastian on 18.05.18.
//

#ifndef JIMP_EXERCISES_SCHEDULER_H
#define JIMP_EXERCISES_SCHEDULER_H


#include <cstddef>
#include <vector>
#include <algorithm>
#include <experimental/optional>
#include <set>

namespace academia {

    class SchedulingItem {

    public:

        SchedulingItem(int course_id, int teacher_id, int room_id, int time_slot, int year);

        int CourseId() const;
        int TeacherId() const;
        int RoomId() const;
        int TimeSlot() const;
        int Year() const;

    private:

        int m_course_id;
        int m_teacher_id;
        int m_room_id;
        int m_time_slot;
        int m_year;
    };


    class Schedule {

    public:

        Schedule() = default;
        explicit Schedule(const std::vector<SchedulingItem> &items);

        SchedulingItem operator[](int index) const;

        Schedule OfTeacher(int teacher_id) const;
        Schedule OfRoom(int room_id) const;
        Schedule OfYear(int year) const;
        std::vector<int> AvailableTimeSlots(int n_time_slots) const;
        void InsertScheduleItem(const SchedulingItem &item);
        size_t Size() const;

    private:

        std::vector<SchedulingItem> m_schedule_items;
    };


    class Scheduler {

    public:

        Scheduler() = default;

        virtual Schedule PrepareNewSchedule(const std::vector<int> &rooms,
                                   const std::map<int, std::vector<int>> &teacher_courses_assignment,
                                   const std::map<int, std::set<int>> &courses_of_year,
                                   int n_time_slots) = 0;

    };


    class NoViableSolutionFound : public std::invalid_argument {

    public:

        NoViableSolutionFound();
    };


    class GreedyScheduler : public Scheduler {

    public:

        Schedule PrepareNewSchedule(const std::vector<int> &rooms,
                                    const std::map<int, std::vector<int>> &teacher_courses_assignment,
                                    const std::map<int, std::set<int>> &courses_of_year, int n_time_slots) override;

    private:

        void scheduleRoom(const std::map<int, std::vector<int>> &teachers_courses, int time_slot, int room,
                          const std::map<int, std::set<int>> &years_courses, std::vector<int> *m_free_teachers,
                          std::vector<int> *m_free_years, std::vector<std::string> *m_required_courses, Schedule *schedule);
        bool teacher_right(std::pair<int, std::vector<int>> teacher, int course, std::vector<int> *m_free_teachers);

    };

}


#endif //JIMP_EXERCISES_SCHEDULER_H
