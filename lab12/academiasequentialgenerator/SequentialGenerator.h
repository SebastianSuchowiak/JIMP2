//
// Created by sebastian on 02.06.18.
//

#ifndef JIMP_EXERCISES_SEQUENTIALGENERATOR_H
#define JIMP_EXERCISES_SEQUENTIALGENERATOR_H

template <typename Id, typename Value>
class SequentialIdGenerator {

public:
    SequentialIdGenerator(Value starting_value = 0) { m_current_value = starting_value; };

    Id NextValue();

private:

    Value m_current_value;
};

template<typename Id, typename Value>
Id SequentialIdGenerator<Id, Value>::NextValue() {
    m_current_value = m_current_value + 1;
    return Id(m_current_value - 1);
}


#endif //JIMP_EXERCISES_SEQUENTIALGENERATOR_H
