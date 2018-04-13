//
// Created by sebastian on 12.04.18.
//

#ifndef JIMP_EXERCISES_WORDCOUNTER_H
#define JIMP_EXERCISES_WORDCOUNTER_H

#include <vector>
#include <cstddef>
#include <iosfwd>
#include <string>
#include <map>


namespace datastructures {

    class Word {
    public:
        std::string m_word_stirng;

    public:
        Word(const std::string &word);

        bool operator<(Word other) const;
        bool operator==(const Word &other) const;
    };


    class Counts {

    public:
        size_t m_word_count;

    public:
        Counts();
        Counts(size_t word_count);

        Counts operator++();
        bool operator==(Counts other) const ;
        bool operator<(Counts other) const;
        bool operator>(Counts other) const;
    };


    class WordCounter {

    private:
        std::map<Word, Counts> m_words_map;
        size_t m_total_words;
        size_t m_distinct_words;

    public:
        WordCounter();
        WordCounter(const std::initializer_list<Word> &words);

        size_t operator[](std::string word);

        void FromInputStream(const std::istream &text_stream);
        size_t DistinctWords();
        size_t TotalWords();
        std::set<Word> Words();
    };
};



#endif //JIMP_EXERCISES_WORDCOUNTER_H
