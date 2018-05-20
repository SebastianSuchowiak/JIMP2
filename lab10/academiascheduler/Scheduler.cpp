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

    return result;
}

bool academia::GreedyScheduler::teacher_right(std::pair<int, std::vector<int>> teacher, int course, std::vector<int> *m_free_teachers) {
    return std::find(teacher.second.begin(), teacher.second.end(), course) != teacher.second.end() &&
            std::find(m_free_teachers->begin(), m_free_teachers->end(), teacher.first) != m_free_teachers->end();
}

std::vector<std::string> get_required_courses(const std::map<int, std::vector<int>> &teacher_courses_assignment) {

    std::vector<std::string> result;

    for (const std::pair<int, std::vector<int>> teacher: teacher_courses_assignment) {
        for (int course: teacher.second) {
            result.push_back(std::to_string(teacher.first) + ":" + std::to_string(course));
        }
    }

    return result;
}

academia::Schedule academia::GreedyScheduler::PrepareNewSchedule(const std::vector<int> &rooms,
                                                                 const std::map<int, std::vector<int>> &teacher_courses_assignment,
                                                                 const std::map<int, std::set<int>> &courses_of_year,
                                                                 int n_time_slots) {
    
    std::vector<int> years_only;
    std::vector<int> teachers_only;
    std::vector<std::string> m_required_courses;
    std::vector<int> m_free_years;
    std::vector<int> m_free_teachers;
    Schedule m_schedule;
    size_t valid_size;


    m_required_courses = get_required_courses(teacher_courses_assignment);
    valid_size = m_required_courses.size();
    years_only = keys(courses_of_year);
    teachers_only = keys(teacher_courses_assignment);

    for (int time_slot = 1; time_slot <= n_time_slots && !m_required_courses.empty(); ++time_slot) {
        m_free_teachers = teachers_only;
        m_free_years = years_only;
        for (int room: rooms) {
            scheduleRoom(teacher_courses_assignment, time_slot, room, courses_of_year, &m_free_teachers,
                         &m_free_years, &m_required_courses, &m_schedule);
        }
    }

    if (m_schedule.Size() != valid_size) {
        throw academia::NoViableSolutionFound();
    }

    return m_schedule;

}

void academia::GreedyScheduler::scheduleRoom(const std::map<int, std::vector<int>> &teachers_courses, int time_slot,
                                             int room,
                                             const std::map<int, std::set<int>> &years_courses,
                                             std::vector<int> *m_free_teachers,
                                             std::vector<int> *m_free_years, std::vector<std::string> *m_required_courses,
                                             Schedule *schedule) {


    for (std::pair<int, std::vector<int>> teacher: teachers_courses) {
        for (std::pair<int, std::set<int>> year: years_courses) {
            if (std::find(m_free_years->begin(), m_free_years->end(), year.first) == m_free_years->end()) {
                continue;
            }
            for (int course: year.second) {
                if (std::find(m_required_courses->begin(), m_required_courses->end(),
                    std::to_string(teacher.first) + ":" + std::to_string(course)) == m_required_courses->end()) {
                    continue;
                }
                if (teacher_right(teacher, course, m_free_teachers)) {
                    schedule->InsertScheduleItem(SchedulingItem(course, teacher.first, room, time_slot, year.first));

                    m_free_teachers->erase(remove(m_free_teachers->begin(), m_free_teachers->end(), teacher.first),
                                           m_free_teachers->end());
                    m_free_years->erase(remove(m_free_years->begin(), m_free_years->end(), year.first),
                                       m_free_years->end());
                    for (int i = 0; i < m_required_courses->size(); ++i) {
                        if (std::to_string(teacher.first) + ":" + std::to_string(course) == (*m_required_courses)[i]) {
                            m_required_courses->erase(m_required_courses->begin() + i);
                            break;
                        }
                    }
                    return;
                }
            }
        }
    }
}
