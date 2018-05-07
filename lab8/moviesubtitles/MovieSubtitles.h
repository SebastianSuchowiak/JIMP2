//
// Created by sebastian on 06.05.18.
//

#ifndef JIMP_EXERCISES_MOVIESUBTITLES_H
#define JIMP_EXERCISES_MOVIESUBTITLES_H

#include <iosfwd>
#include <regex>
#include <stdexcept>

namespace moviesubs {


    class MovieSubtitles {
    public:
        ~MovieSubtitles() = default;

        virtual void ShiftAllSubtitlesBy(int offset_in_micro_seconds, int frame_per_second,
                                         std::istream *in, std::ostream *out) = 0;
    };


    class MicroDvdSubtitles : public MovieSubtitles {
    public:
        void ShiftAllSubtitlesBy(int offset_in_micro_seconds, int frame_per_second,
                                 std::istream *in, std::ostream *out) override;
    };


    class SubRipSubtitles : public MovieSubtitles {
    public:
        void ShiftAllSubtitlesBy(int offset_in_micro_seconds, int frame_per_second,
                                 std::istream *in, std::ostream *out) override;

        std::string change_time(int frames_to_change, const std::cmatch &matches);
    };


    class SubtitlesException : public std::invalid_argument {
    public:
        SubtitlesException(size_t lineNumber, const std::string &line);

        size_t LineAt() const;

    private:
        size_t m_line_number;
        std::string msg;
    };

    class NegativeFrameAfterShift : public SubtitlesException {
    public:
        NegativeFrameAfterShift(size_t lineNumber, const std::string &line);
    };

    class SubtitleEndBeforeStart : public SubtitlesException {
    public:
        SubtitleEndBeforeStart(size_t lineNumber, const std::string &line);
    };

    class InvalidSubtitleLineFormat : public SubtitlesException {
    public:
        InvalidSubtitleLineFormat(size_t lineNumber, const std::string &line);
    };

    class OutOfOrderFrames : public SubtitlesException {
    public:
        OutOfOrderFrames(size_t lineNumber, const std::string &line);
    };

    class MissingTimeSpecification : public SubtitlesException {
    public:
        MissingTimeSpecification(size_t lineNumber, const std::string &line);

    };
}



#endif //JIMP_EXERCISES_MOVIESUBTITLES_H
