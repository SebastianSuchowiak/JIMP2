//
// Created by sebastian on 18.05.18.
//

#include <map>
#include "Scheduler.h"

academia::SchedulingItem::SchedulingItem(int course_id, int teacher_id, int room_id, int time_slot,
                                         int year) :
        m_course_id{course_id},
        m_teacher_id{teacher_id},
        m_room_id{room_id},
        m_time_slot{time_slot},
        m_year{year} {}

int academia::SchedulingItem::CourseId() const {
    return m_course_id;
}

int academia::SchedulingItem::TeacherId() const {
    return m_teacher_id;
}

int academia::SchedulingItem::RoomId() const {
    return m_room_id;
}

int academia::SchedulingItem::TimeSlot() const {
    return m_time_slot;
}

int academia::SchedulingItem::Year() const {
    return m_year;
}

academia::Schedule::Schedule(const std::vector<SchedulingItem> &items) {
    m_schedule_items = items;
}

academia::SchedulingItem academia::Schedule::operator[](int index) const {
    return m_schedule_items[index];
}

void academia::Schedule::InsertScheduleItem(const academia::SchedulingItem &item) {
    m_schedule_items.push_back(item);
}

academia::Schedule academia::Schedule::OfTeacher(int teacher_id) const {

    std::vector<SchedulingItem> teacher_items;

    for (const SchedulingItem &item: m_schedule_items) {
        if (item.TeacherId() == teacher_id) {
            teacher_items.push_back(item);
        }
    }

    return Schedule(teacher_items);
}

academia::Schedule academia::Schedule::OfRoom(int room_id) const {

    std::vector<SchedulingItem> room_items;

    for (const SchedulingItem &item: m_schedule_items) {
        if (item.RoomId() == room_id) {
            room_items.push_back(item);
        }
    }

    return Schedule(room_items);
}

academia::Schedule academia::Schedule::OfYear(int year) const {

    std::vector<SchedulingItem> year_items;

    for (const SchedulingItem &item: m_schedule_items) {
        if (item.Year() == year) {
            year_items.push_back(item);
        }
    }

    return Schedule(year_items);
}

std::vector<int> academia::Schedule::AvailableTimeSlots(int n_time_slots) const {

    std::vector<int> available_time_slots;

    for (int i = 1; i <= n_time_slots; ++i) {
        available_time_slots.push_back(i);
    }

    for (const SchedulingItem &current_item: m_schedule_items) {
        if (current_item.TimeSlot() <= n_time_slots) {
            for (int i = 0; i < available_time_slots.size(); ++i) {
                if (available_time_slots[i] == current_item.TimeSlot()) {
                    available_time_slots.erase(available_time_slots.begin() + i);
                }
            }
        }
    }

    return available_time_slots;
}

size_t academia::Schedule::Size() const {
    return m_schedule_items.size();
}

academia::NoViableSolutionFound::NoViableSolutionFound() :
        std::invalid_argument("Unable to find solution") {
}

std::vector<int> keys(const std::map<int, std::set<int>> &m) {

    std::vector<int> result;

    std::transform(m.begin(), m.end(), std::back_inserter(result),
                   [](const auto &current) {
                       return current.first;
                   });

    return result;
}

std::vector<int> keys(const std::map<int, std::vector<int>> &m) {

    std::vector<int> result;

    std::transform(m.begin(), m.end(), std::back_inserter(result),
                   [](const auto &current) {
                       return current.first;
                   });

    std::sort(result.begin(), result.end(),
              [m](int left, int right) {
                  return m.at(left).size() > m.at(right).size();
              });

    return result;
}


std::vector<std::string> get_required_courses(const std::map<int, std::vector<int>> &teacher_courses_assignment) {

    std::vector<std::string> result;

    for (const auto &teacher: teacher_courses_assignment) {
        for (int course: teacher.second) {
            result.push_back(std::to_string(teacher.first) + ":" + std::to_string(course));
        }
    }

    return result;
}

std::vector<std::string> get_required_courses(const std::map<int, std::set<int>> &teacher_courses_assignment) {

    std::vector<std::string> result;

    for (const auto &teacher: teacher_courses_assignment) {
        for (int course: teacher.second) {
            result.push_back(std::to_string(teacher.first) + ":" + std::to_string(course));
        }
    }

    return result;
}

bool Contains(const std::vector<int> &v, int element) {
    return std::find(v.begin(), v.end(), element) != v.end();
}

bool Contains(const std::vector<std::string> &v,const std::string &element) {
    return std::find(v.begin(), v.end(), element) != v.end();
}

int find_year(const std::vector<int> &years_only, const std::vector<std::string> &year_courses,
              int course, int time, const academia::Schedule &schedule) {
    for (const auto &year: years_only) {
        if (Contains(year_courses, std::to_string(year) + ":" + std::to_string(course)) &&
            Contains(schedule.OfYear(year).AvailableTimeSlots(time), time)) {
            return year;
        }
    }
    return -1;
}


int find_room(const std::vector<int> &rooms, int time, const academia::Schedule &schedule) {
    for (auto room: rooms) {
        if (Contains(schedule.OfRoom(room).AvailableTimeSlots(time), time)) {
            return room;
        }
    }
    return -1;
}

void delete_element(std::vector<std::string> *vector, const std::string &element) {
    for (int i = 0; i<vector->size(); ++i) {
        if ((*vector)[i] == element) {
            vector->erase(vector->begin() + i);
            return;
        }
    }
}

bool is_free(int teacher, const academia::Schedule &schedule, int time) {
    return Contains(schedule.OfTeacher(teacher).AvailableTimeSlots(time), time);
}


academia::Schedule academia::GreedyScheduler::PrepareNewSchedule(const std::vector<int> &rooms,
                                                                 const std::map<int, std::vector<int>> &teacher_courses_assignment,
                                                                 const std::map<int, std::set<int>> &courses_of_year,
                                                                 int n_time_slots) {
    
    std::vector<int> years_only;
    std::vector<int> teachers_only;
    std::vector<std::string> left_teacher_courses;
    std::vector<std::string> year_courses;
    std::vector<int> m_free_years;
    std::vector<int> m_free_teachers;
    std::string course_string;
    Schedule m_schedule;
    int year;
    int room;
    size_t valid_size;


    left_teacher_courses = get_required_courses(teacher_courses_assignment);
    year_courses = get_required_courses(courses_of_year);
    valid_size = left_teacher_courses.size();
    years_only = keys(courses_of_year);
    teachers_only = keys(teacher_courses_assignment);
    int test = teachers_only[0];


    for (const auto &teacher: teachers_only) {
        for (const auto &course: teacher_courses_assignment.at(teacher)) {
            course_string = std::to_string(teacher) + ":" + std::to_string(course);
            if (!Contains(left_teacher_courses, course_string)) {
                continue;
            }
            for(int time = 1; time <= n_time_slots && Contains(left_teacher_courses, course_string); ++time) {
                if (!is_free(teacher, m_schedule, time)) {
                    continue;
                }
                year = find_year(years_only, year_courses, course, time, m_schedule);
                room = find_room(rooms, time, m_schedule);
                if (year != -1 && room != -1) {
                    m_schedule.InsertScheduleItem(SchedulingItem(course, teacher, room, time, year));
                    delete_element(&left_teacher_courses, course_string);
                }
            }

        }
    }

    if (m_schedule.Size() != valid_size) {
        throw academia::NoViableSolutionFound();
    }

    return m_schedule;

}
