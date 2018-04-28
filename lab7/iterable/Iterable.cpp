//
// Created by sebastian on 28.04.18.
//

#include <bits/unique_ptr.h>
#include <iostream>
#include "Iterable.h"

utility::ZipperIterator::ZipperIterator(std::vector<int>::const_iterator left_begin,
                                        std::vector<std::string>::const_iterator right_begin,
                                        std::vector<int>::const_iterator left_end,
                                        std::vector<std::string>::const_iterator right_end) {
    m_left_begin = left_begin;
    m_right_begin = right_begin;
    m_left_end = left_end;
    m_right_end = right_end;
    m_current_left = left_begin;
    m_current_right = right_begin;
}

std::pair<int, std::string> utility::ZipperIterator::Dereference() const {
    std::pair<int, std::string> p = std::make_pair(*m_current_left, *m_current_right);
    return p;
}

utility::IterableIterator &utility::ZipperIterator::Next() {
    if (m_current_left + 1 != m_left_end) {
        m_current_left++;
    }
    if (m_current_right + 1 != m_right_end) {
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

bool utility::IterableIteratorWrapper::operator!=(IterableIteratorWrapper &other) const{
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
    return nullptr;
}

std::unique_ptr<utility::IterableIterator> utility::Zipper::ConstEnd() const {
    return nullptr;
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
