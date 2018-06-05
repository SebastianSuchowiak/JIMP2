//
// Created by sebastian on 29.05.18.
//

#ifndef JIMP_EXERCISES_TREEITERATOR_H
#define JIMP_EXERCISES_TREEITERATOR_H

#include <bits/unique_ptr.h>

namespace tree {
    template <typename T>
    class Tree {
    public:
        Tree(T data);
        void Insert(T value);
        void InserWithLevel(T value, int *l);
        T Value();
        int Size();
        int Depth();
    private:
        T data_;
        std::unique_ptr<Tree> right_;
        std::unique_ptr<Tree> left_;
        int size_;
        int depth_;
    };

    template<typename T>
    Tree<T>::Tree(T data) {
        right_ = nullptr;
        left_ = nullptr;
        data_ = data;
        size_ = 1;
        depth_ = 1;
    }

    template<typename T>
    T Tree<T>::Value() {
        return data_;
    }

    template<typename T>
    void Tree<T>::Insert(T value) {
        size_++;
        int level = 1;
        InserWithLevel(value, &level);
        if(level > Depth()) depth_ = level;

    }

    template<typename T>
    int Tree<T>::Size() {
        return size_;
    }

    template<typename T>
    int Tree<T>::Depth() {
        return depth_;
    }

    template<typename T>
    void Tree<T>::InserWithLevel(T value, int *l) {
        *l = *l + 1;
        if(data_ > value) {
            if(left_ != nullptr) return left_->InserWithLevel(value, l);
            left_ = std::make_unique<Tree<T>>(Tree<T>(value));
        }
        if(data_ <= value) {
            if(right_ != nullptr) return right_->InserWithLevel(value, l);
            right_ = std::make_unique<Tree<T>>(Tree<T>(value));
        }
    }


}
