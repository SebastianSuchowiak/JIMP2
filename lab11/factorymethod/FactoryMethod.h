//
// Created by sebastian on 22.05.18.
//

#ifndef JIMP_EXERCISES_FACTORYMETHOD_H
#define JIMP_EXERCISES_FACTORYMETHOD_H


#include <vector>
#include <algorithm>

namespace factoryMethod {

    template <typename T>
    class Repository {

    public:

        Repository(std::initializer_list<T> values) : m_values{values}{};
        T operator[](int index) const;
        int NextId();
        template <typename Query>
        Repository FindBy(Query query);

    private:

        int m_id = 0;
        std::vector<T> m_values;
    };

    template<typename T>
    T Repository<T>::operator[](int index) const {
        return m_values[index];
    }

    template<typename T>
    int Repository<T>::NextId() {
        if (m_id < m_values.size()) {
            return m_id++;
        }
        return m_id;
    }

    template<typename T, typename Query>
    Repository Repository<T>::FindBy(Query query) {
        std::vector<T> result;

        for (const auto &value: m_values) {
            if (query.accept(value)) {
                result.push_back(value);
            }
        }

        return result;
    }

    template <typename T, typename O>
    T add_two(T left, O right) {
        return left + (T) right;
    }

    template <typename pointed>
    auto value(const pointed &pointer) {
        return *pointer;
    };

    template <typename T>
    T mean(std::vector<T> values) {
        T sum = 0;
        for (auto value: values) {
            sum += value;
        }
        return sum / (double) values.size();
    }
}


#endif //JIMP_EXERCISES_FACTORYMETHOD_H
