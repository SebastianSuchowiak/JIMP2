//
// Created by sebastian on 28.04.18.
//

#ifndef JIMP_EXERCISES_ITERABLE_H
#define JIMP_EXERCISES_ITERABLE_H

#include <string>
#include <vector>

namespace utility {

    class IterableIterator {
    public:

        ~IterableIterator() = default;

        virtual std::pair<int, std::string> Dereference() const = 0;
        virtual IterableIterator &Next() = 0;
        virtual bool NotEquals(const std::unique_ptr<IterableIterator> &other) const = 0;

    public:

        std::vector<int>::const_iterator m_left_begin;
        std::vector<std::string>::const_iterator m_right_begin;
        std::vector<int>::const_iterator m_left_end;
        std::vector<std::string>::const_iterator m_right_end;
        std::vector<int>::const_iterator m_current_left;
        std::vector<std::string>::const_iterator m_current_right;
    };


    class ZipperIterator : public IterableIterator {
    public:

        ZipperIterator(std::vector<int>::const_iterator left_begin,
        std::vector<std::string>::const_iterator right_begin,
                std::vector<int>::const_iterator left_end,
        std::vector<std::string>::const_iterator right_end);

        std::pair<int, std::string> Dereference() const override;

        IterableIterator &Next() override;

        bool NotEquals(const std::unique_ptr<IterableIterator> &other) const override;
    };


    class IterableIteratorWrapper {
    public:
        explicit IterableIteratorWrapper(std::unique_ptr<IterableIterator> iterator);
        bool operator!=(const IterableIteratorWrapper &other) const;
        std::pair<int, std::string> operator*() const;
        IterableIteratorWrapper &operator++();

    private:
        std::unique_ptr<IterableIterator> m_iterator;
    };


    class Iterator {
    public:
        virtual std::unique_ptr<IterableIterator> ConstBegin() const = 0;
        virtual std::unique_ptr<IterableIterator> ConstEnd() const = 0;
        IterableIteratorWrapper cbegin() const;
        IterableIteratorWrapper cend() const;
        IterableIteratorWrapper begin();
        IterableIteratorWrapper end();

    };


    class Zipper : public Iterator {
    public:
        Zipper(std::vector<int> int_vector, std::vector<std::string> string_vector);

        std::unique_ptr<IterableIterator> ConstBegin() const override;
        std::unique_ptr<IterableIterator> ConstEnd() const override;

    public:
        std::vector<int> m_int_vector;
        std::vector<std::string> m_string_vector;
    };
}



#endif //JIMP_EXERCISES_ITERABLE_H
