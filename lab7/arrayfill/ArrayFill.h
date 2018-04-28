//
// Created by sebastian on 17.04.18.
//

#ifndef JIMP_EXERCISES_ARRAYFILL_H
#define JIMP_EXERCISES_ARRAYFILL_H

#include <cstddef>
#include <vector>

namespace arrays {

    class Filler {

    public:
        virtual int GetValueToFill(size_t index) const = 0;
    };


    class IncrementalFill: public Filler {

    private:
        int m_start;
        int m_step;

    public:

        explicit IncrementalFill(int start, int step = 0);
        int GetValueToFill(size_t index) const override;
    };


    class SquaredFill: public Filler {

    private:
        int m_a;
        int m_b;

    public:

        explicit SquaredFill(int a = 0, int b = 0);
        int GetValueToFill(size_t index) const override;
    };


    class UniformFill: public Filler {

    private:
        int m_value;

    public:

        explicit UniformFill(int value = 0);
        int GetValueToFill(size_t index) const override;
    };

    void FillArray(size_t length, const Filler &filler, std::vector<int> *to_fill);
}



#endif //JIMP_EXERCISES_ARRAYFILL_H
