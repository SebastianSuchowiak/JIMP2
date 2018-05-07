//
// Created by sebastian on 06.05.18.
//

#include <iostream>
#include "MovieSubtitles.h"

void
moviesubs::MicroDvdSubtitles::ShiftAllSubtitlesBy(int offset_in_micro_seconds, int frame_per_second, std::istream *in,
                                                  std::ostream *out) {

    std::regex pattern ("\\{(\\d+)\\}\\{(\\d+)\\}(.+)");
    std::string current_line;
    std::cmatch matches;
    int frames_to_change;
    size_t line_number = 1;
    size_t last_frame = 0;

    if(frame_per_second <= 0) {
        throw std::invalid_argument("fps <= 0");
    }

    frames_to_change = offset_in_micro_seconds * frame_per_second / 1000;

    while(std::getline(*in, current_line))
    {
        if (std::regex_match(current_line.c_str(), matches, pattern)) {

            if (std::stoi(matches[1]) + frames_to_change < 0) {
                throw moviesubs::NegativeFrameAfterShift(line_number, current_line);
            } else if (std::stoi(matches[1]) > std::stoi(matches[2])) {
                throw moviesubs::SubtitleEndBeforeStart(line_number, current_line);
            } else if (last_frame > std::stoi(matches[2])) {
                throw moviesubs::OutOfOrderFrames(line_number, current_line);
            }

            *out << "{" << std::stoi(matches[1]) + frames_to_change << "}"
                << "{" << std::stoi(matches[2]) + frames_to_change << "}"
                << matches[3] << "\n";

            last_frame = (size_t) std::stoi(matches[2]);
        } else {
            throw moviesubs::InvalidSubtitleLineFormat(line_number, current_line);
        };
        line_number++;
    }
}

std::string moviesubs::SubRipSubtitles::change_time(int frames_to_change, const std::cmatch &matches) {

    std::vector<int> time;
    std::vector<std::string> str_time;
    std::string new_str;
    int reminder = 0;
    std::string result;

    time.push_back(0);
    for (size_t i = 1; i < matches.size(); i++) {
        time.push_back(std::stoi(matches[i]));
    }


    reminder = (time[4] + frames_to_change) / 1000;
    time[4] = (time[4] + frames_to_change) % 1000;
    for (int i = 3; i >= 1 && reminder > 0; --i) {
        time[i] += reminder;
        reminder = time[i] / 60;
    }

    reminder = (time[8] + frames_to_change) / 1000;
    time[8] = (time[8] + frames_to_change) % 1000;
    for (int i = 7; i >= 5 && reminder > 0; --i) {
        time[i] += reminder;
        reminder = time[i] / 60;
    }

    for (int i = 1; i < time.size(); i++) {
        new_str = std::to_string(time[i]);
        if (i == 4 || i == 8) {
            if (new_str.length() > 2) {
                str_time.push_back(new_str);
            } else if (new_str.length() > 1) {
                str_time.push_back("0" + new_str);
            } else {
                str_time.push_back("00" + new_str);
            }
        } else {
            if (new_str.length() > 1) {
                str_time.push_back(new_str);
            } else {
                str_time.push_back("0" + new_str);
            }
        }
    }

    return str_time[0] + ":" + str_time[1] + ":" + str_time[2] + "," + str_time[3]
           + " --> " + str_time[4] + ":" + str_time[5] + ":" + str_time[6] + "," + str_time[7] + "\n";
}

void
moviesubs::SubRipSubtitles::ShiftAllSubtitlesBy(int offset_in_micro_seconds, int frame_per_second, std::istream *in,
                                                std::ostream *out) {

    std::regex pattern (R"regex((\d+):(\d+):(\d+),(\d+) --> (\d+):(\d+):(\d+),(\d+))regex");
    std::cmatch matches;
    std::string current_line;
    bool next_line_time = false;
    bool last_line_was_empty = true;
    int seconds_to_change;
    int proper_index = 1;
    size_t line_number = 1;

    if(frame_per_second <= 0) {
        throw std::invalid_argument("fps <= 0");
    }

    seconds_to_change = offset_in_micro_seconds;

    while(std::getline(*in, current_line))
    {
        if (std::regex_match(current_line.c_str(), matches, pattern)) {
            if (std::stoi(matches[1])*3600000 + std::stoi(matches[2]) * 60000
                + std::stoi(matches[3]) * 1000 + std::stoi(matches[4]) < -seconds_to_change) {
                throw moviesubs::NegativeFrameAfterShift(line_number, current_line);
            } else if (std::stoi(matches[1])*3600000 + std::stoi(matches[2]) * 60000
                       + std::stoi(matches[3]) * 1000 + std::stoi(matches[4]) >
                    std::stoi(matches[5])*3600000 + std::stoi(matches[6]) * 60000
                    + std::stoi(matches[7]) * 1000 + std::stoi(matches[8])) {
                throw moviesubs::SubtitleEndBeforeStart(line_number, current_line);
            }
            *out << change_time(seconds_to_change, matches);
            line_number++;
            next_line_time = false;
        } else if(next_line_time) {
            throw moviesubs::InvalidSubtitleLineFormat(line_number, current_line);
        } else {
            if (last_line_was_empty) {
                next_line_time = true;
                if (std::stoi(current_line) != proper_index) {
                    throw moviesubs::OutOfOrderFrames(line_number, current_line);
                }
                proper_index++;
            }
            last_line_was_empty = current_line.empty();
            *out << current_line << "\n";
        };
    }

}


moviesubs::SubtitlesException::SubtitlesException(size_t lineNumber, const std::string &line) :
        std::invalid_argument("At line "  + std::to_string(lineNumber) + ": " + line) {
    m_line_number = lineNumber;
}

size_t moviesubs::SubtitlesException::LineAt() const {
    return m_line_number;
}


moviesubs::NegativeFrameAfterShift::NegativeFrameAfterShift(size_t lineNumber, const std::string &line) :
        moviesubs::SubtitlesException(lineNumber, line) {}
moviesubs::InvalidSubtitleLineFormat::InvalidSubtitleLineFormat(size_t lineNumber, const std::string &line) :
        moviesubs::SubtitlesException(lineNumber, line) {}
moviesubs::OutOfOrderFrames::OutOfOrderFrames(size_t lineNumber, const std::string &line) :
        moviesubs::SubtitlesException(lineNumber, line) {}
moviesubs::SubtitleEndBeforeStart::SubtitleEndBeforeStart(size_t lineNumber, const std::string &line) :
        moviesubs::SubtitlesException(lineNumber, line) {}
moviesubs::MissingTimeSpecification::MissingTimeSpecification(size_t lineNumber, const std::string &line) :
        moviesubs::SubtitlesException(lineNumber, line) {}

