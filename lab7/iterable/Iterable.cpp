//
// Created by sebastian on 28.04.18.
//

#include <bits/unique_ptr.h>
#include "Iterable.h"

utility::ZipperIterator::ZipperIterator(std::vector<int>::const_iterator left_begin,
                                        std::vector<std::string>::const_iterator right_begin,
                                        std::vector<int>::const_iterator left_end,
                                        std::vector<std::string>::const_iterator right_end) {
    m_left_end = left_end;
    m_right_end = right_end;
    m_current_left = left_begin;
    m_current_right = right_begin;
}

std::pair<int, std::string> utility::ZipperIterator::Dereference() const {

    std::vector<int>::const_iterator first = m_current_left;
    std::vector<std::string>::const_iterator second = m_current_right;

    if (m_current_left == m_left_end) {
        first = m_current_left - 1;
    }
    if (m_current_right == m_right_end) {
        second = m_current_right - 1;
    }

    return std::pair<int , std::string>(*first, *second);
}

utility::IterableIterator &utility::ZipperIterator::Next() {
    if (m_current_left != m_left_end) {
        m_current_left++;
    }
    if (m_current_right != m_right_end) {
        m_current_right++;
    }
    return *this;
}

bool utility::ZipperIterator::NotEquals(const std::unique_ptr<utility::IterableIterator> &other) const {
    return m_current_right != other->m_current_right || m_current_left != other->m_current_left;
}

utility::IterableIteratorWrapper::IterableIteratorWrapper(std::unique_ptr<utility::IterableIterator> iterator) {
    m_iterator = std::move(iterator);
}

bool utility::IterableIteratorWrapper::operator!=(const IterableIteratorWrapper &other) const{
    return (*m_iterator).NotEquals(other.m_iterator);
}

std::pair<int, std::string> utility::IterableIteratorWrapper::operator*() const {
    return (*m_iterator).Dereference();
}

utility::IterableIteratorWrapper &utility::IterableIteratorWrapper::operator++() {
    (*m_iterator).Next();
    return *this;
}

std::unique_ptr<utility::IterableIterator> utility::Zipper::ConstBegin() const {
    return std::make_unique<ZipperIterator>(ZipperIterator(m_int_vector.begin(), m_string_vector.begin(),
                                                           m_int_vector.end(), m_string_vector.end()));
}

std::unique_ptr<utility::IterableIterator> utility::Zipper::ConstEnd() const {
    return std::make_unique<ZipperIterator>(ZipperIterator(m_int_vector.end(), m_string_vector.end(),
                                                           m_int_vector.end(), m_string_vector.end()));;
}

utility::Zipper::Zipper(const std::vector<int> &int_vector, const std::vector<std::string> &string_vector) {
    m_int_vector = int_vector;
    m_string_vector = string_vector;
}


utility::IterableIteratorWrapper utility::Iterator::cbegin() const {
    return IterableIteratorWrapper(ConstBegin());
}

utility::IterableIteratorWrapper utility::Iterator::cend() const {
    return IterableIteratorWrapper(ConstEnd());
}

utility::IterableIteratorWrapper utility::Iterator::begin() {
    return this->cbegin();
}

utility::IterableIteratorWrapper utility::Iterator::end() {
    return this->cend();
}

utility::EnumerateIterator::EnumerateIterator(std::vector<std::string>::const_iterator right_begin,
                                              std::vector<std::string>::const_iterator right_end) {
    m_current_index = 1;
    m_right_end = right_end;
    m_current_right = right_begin;
}

bool utility::EnumerateIterator::NotEquals(const std::unique_ptr<utility::IterableIterator> &other) const {
    return m_current_right != other->m_current_right;
}

utility::IterableIterator &utility::EnumerateIterator::Next() {
    if (m_current_right != m_right_end) {
        m_current_right++;
        m_current_index++;
    }
    return *this;
}

std::pair<int, std::string> utility::EnumerateIterator::Dereference() const {

    std::vector<std::string>::const_iterator second = m_current_right;

    if (m_current_right == m_right_end) {
        second = m_current_right - 1;
    }

    return std::pair<int, std::string>(m_current_index, *second);
}

utility::Enumerate::Enumerate(const std::vector<std::string> &string_vector) {
    m_string_vector = string_vector;
}

std::unique_ptr<utility::IterableIterator> utility::Enumerate::ConstBegin() const {
    return std::make_unique<EnumerateIterator>(EnumerateIterator(m_string_vector.begin(), m_string_vector.end()));
}

std::unique_ptr<utility::IterableIterator> utility::Enumerate::ConstEnd() const {
    return std::make_unique<EnumerateIterator>(EnumerateIterator(m_string_vector.end(), m_string_vector.end()));
}

utility::ProductIterator::ProductIterator(std::vector<int>::const_iterator left_begin,
                                          std::vector<std::string>::const_iterator right_begin,
                                          std::vector<int>::const_iterator left_end,
                                          std::vector<std::string>::const_iterator right_end) {
    m_right_begin = right_begin;
    m_right_end = right_end;
    m_left_end = left_end;
    m_current_right = right_begin;
    m_current_left = left_begin;
}

std::pair<int, std::string> utility::ProductIterator::Dereference() const {

    std::vector<int>::const_iterator first = m_current_left;
    std::vector<std::string>::const_iterator second = m_current_right;

    if (m_current_left == m_left_end) {
        first = m_current_left - 1;
    }
    if (m_current_right == m_right_end) {
        second = m_current_right - 1;
    }

    return std::pair<int , std::string>(*first, *second);
}

utility::IterableIterator &utility::ProductIterator::Next() {
    if (m_current_left != m_left_end && m_current_right != m_right_end) {
        if (m_current_right == m_right_end - 1) {
            m_current_right = m_right_begin;
            m_current_left++;
        } else if (m_current_right != m_right_end - 1 && m_current_left != m_left_end) {
            m_current_right++;
        }
        if (m_current_left == m_left_end) {
            m_current_right = m_right_end;
        }
    }

    return *this;
}

bool utility::ProductIterator::NotEquals(const std::unique_ptr<utility::IterableIterator> &other) const {
    return m_current_right != other->m_current_right || m_current_left != other->m_current_left;
}

utility::Product::Product(const std::vector<int> &int_vector, const std::vector<std::string> &string_vector) {
    m_string_vector = string_vector;
    m_int_vector = int_vector;
}

std::unique_ptr<utility::IterableIterator> utility::Product::ConstBegin() const {
    if (m_int_vector.empty() || m_string_vector.empty()) {
        return std::make_unique<ProductIterator>(ProductIterator(m_int_vector.end(), m_string_vector.end(),
                                                               m_int_vector.end(), m_string_vector.end()));
    }
    return std::make_unique<ProductIterator>(ProductIterator(m_int_vector.begin(), m_string_vector.begin(),
                                                           m_int_vector.end(), m_string_vector.end()));
}

std::unique_ptr<utility::IterableIterator> utility::Product::ConstEnd() const {
    return std::make_unique<ProductIterator>(ProductIterator(m_int_vector.end(), m_string_vector.end(),
                                                           m_int_vector.end(), m_string_vector.end()));
}
