//
// Created by sebastian on 12.04.18.
//

#include <algorithm>
#include <set>
#include <fstream>
#include <sstream>
#include "WordCounter.h"

size_t datastructures::WordCounter::DistinctWords() {
    return m_distinct_words;
}

size_t datastructures::WordCounter::TotalWords() {
    return m_total_words;
}

void datastructures::WordCounter::FromInputStream(std::istream &text_stream) {

    std::string not_clean_word;
    std::stringstream new_word;

    while (text_stream >> not_clean_word) {

        for (char letter: not_clean_word) {
            if (isalpha(letter)) {
                new_word << letter;
            }
        }

        if (new_word.str().length() > 0) {
            this->append(Word(new_word.str()));
        }
        new_word.clear();
    }
}

datastructures::WordCounter::WordCounter() {
    m_distinct_words = 0;
    m_total_words = 0;
}

datastructures::WordCounter::WordCounter(const std::initializer_list<datastructures::Word> &words) {

    m_distinct_words = 0;
    m_total_words = 0;

    for (const Word &new_word: words) {
        this->append(new_word);
    }

}

size_t datastructures::WordCounter::operator[](std::string word) {
    if (m_words_map.find(word) == m_words_map.end()) {
        return 0;
    }
    return m_words_map[word].m_word_count;
}

std::set<datastructures::Word> datastructures::WordCounter::Words() {
    std::set<Word> words;
    for (auto const& element : m_words_map) {
        words.insert(element.first);
    }

    return words;
}

void datastructures::WordCounter::append(const datastructures::Word &new_word) {

    if(m_words_map.find(new_word) == m_words_map.end()) {
        m_words_map[new_word] = Counts();
        m_distinct_words++;
        m_total_words++;
    } else  {
        ++m_words_map[new_word];
        m_total_words++;
    }
}


datastructures::Word::Word(const std::string &word) {
    m_word_stirng = word;
}

bool datastructures::Word::operator<(datastructures::Word other) const {
    return m_word_stirng < other.m_word_stirng;
}

bool datastructures::Word::operator==(const Word &other) const {
    return m_word_stirng == other.m_word_stirng;
}

datastructures::Counts::Counts() {
    m_word_count = 1;
}

datastructures::Counts datastructures::Counts::operator++() {
    m_word_count++;
    return *this;
}

bool datastructures::Counts::operator==(datastructures::Counts other) const {
    return m_word_count == other.m_word_count;
}

bool datastructures::Counts::operator<(datastructures::Counts other) const {
    return m_word_count < other.m_word_count;
}

bool datastructures::Counts::operator>(datastructures::Counts other) const {
    return m_word_count > other.m_word_count;
}

datastructures::Counts::Counts(size_t word_count) {
    m_word_count = word_count;
}
