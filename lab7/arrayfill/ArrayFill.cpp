//
// Created by sebastian on 17.04.18.
//

#include "ArrayFill.h"

arrays::IncrementalFill::IncrementalFill(int start, int step) {
    m_start = start;
    m_step = step;
}

int arrays::IncrementalFill::GetValueToFill(size_t index) const {
    return m_start + m_step * int(index);
}

void arrays::FillArray(size_t length, const Filler &filler, std::vector<int> *to_fill) {

    (*to_fill).clear();
    for (int i = 0; i < length; ++i) {
        (*to_fill).push_back(filler.GetValueToFill(i));
    }
}

arrays::SquaredFill::SquaredFill(int a, int b) {
    m_a = a;
    m_b = b;
}

int arrays::SquaredFill::GetValueToFill(size_t index) const {
    return m_a * int(index) * int(index) + m_b;
}

arrays::UniformFill::UniformFill(int value) {
    m_value = value;
}

int arrays::UniformFill::GetValueToFill(size_t index) const {
    return m_value;
}
