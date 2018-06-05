//
// Created by sebastian on 01.06.18.
//

#ifndef JIMP_EXERCISES_TREE_H
#define JIMP_EXERCISES_TREE_H

#include <memory>
#include <iostream>
#include "Tree.h"

namespace tree{
    template <typename T>
    class Tree {
    public:
        Tree(T data);
        void Insert(T value);
        void InserWithLevel(T value, int *l);
        T Value();
        int Size();
        int Depth();
        Tree<T> *Parent();
        std::unique_ptr<Tree<T>> &Left();
        std::unique_ptr<Tree<T>> &Right();
        Tree<T> *Root();
        void SetVisited(bool v);
        bool Visited();
    private:
        T data_;
        std::unique_ptr<Tree> right_;
        std::unique_ptr<Tree> left_;
        int size_;
        int depth_;
        Tree<T> *root_;
        Tree<T> *parent_;
        bool visited_;
    };

    template<typename T>
    Tree<T>::Tree(T data) {
        right_ = nullptr;
        left_ = nullptr;
        data_ = data;
        size_ = 1;
        depth_ = 1;
        root_ = this;
        parent_ = nullptr;
        visited_ = false;
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
            left_->parent_ = this;
        }
        if(data_ <= value) {
            if(right_ != nullptr) return right_->InserWithLevel(value, l);
            right_ = std::make_unique<Tree<T>>(Tree<T>(value));
            right_->parent_ = this;
        }
    }

    template<typename T>
    std::unique_ptr<Tree<T>> &Tree<T>::Left() {
        return left_;
    }

    template<typename T>
    std::unique_ptr<Tree<T>> &Tree<T>::Right() {
        return right_;
    }

    template<typename T>
    Tree<T> *Tree<T>::Root() {
        return root_;
    }

    template<typename T>
    Tree<T> *Tree<T>::Parent() {
        return parent_;
    }

    template<typename T>
    void Tree<T>::SetVisited(bool v) {
        visited_ = v;
    }

    template<typename T>
    bool Tree<T>::Visited() {
        return visited_;
    }


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <typename T>
    void Inor(Tree<T> *tree){
        if(tree->Left() != nullptr) Inor(&*tree->Left());
        std::cout<<tree->Value()<<std::endl;
        if(tree->Right() != nullptr)Inor(&*tree->Right());
    }


    template <typename T>
    class PreOrderTreeIterator{
    public:
        explicit PreOrderTreeIterator(Tree<T> *tree);
        virtual void operator++();
        T operator*();
        bool operator!=(const PreOrderTreeIterator &other) const;
        void SetLast(bool v);
        Tree<T> *GetTree();
        void SetTree(Tree<T> *tree);
        void Visit();

    private:
        Tree<T> *tree_;
        bool isLast_;
    };

    template<typename T>
    PreOrderTreeIterator<T>::PreOrderTreeIterator(Tree<T> *tree) : tree_(tree), isLast_(false){}

    template<typename T>
    bool PreOrderTreeIterator<T>::operator!=(const PreOrderTreeIterator &other) const {
        if(other.isLast_ == true) return true;
        if(isLast_ == true) return true;
        return !(tree_->Value() == other.tree_->Value());
    }

    template<typename T>
    T PreOrderTreeIterator<T>::operator*() {
        return tree_->Value();
    }

    template<typename T>
    void PreOrderTreeIterator<T>::operator++() {
        if(tree_->Left() != nullptr) tree_ = &(*tree_->Left());
        else if(tree_->Right() != nullptr) tree_ = &(*tree_->Right());
        else{
            Tree<T> *it = this->tree_;
            if(&*(it->Parent()->Left()) == it){
                while(it != nullptr && it->Parent()->Right() == nullptr) it = &*it->Parent();
                tree_ = &*it->Parent()->Right();
            } else if(&*(it->Parent()->Right()) == it){
                while(it != nullptr && it->Parent()->Right()->Visited())it = &*it->Parent();
                tree_ = &*it->Parent()->Right();
            }
            else{
                isLast_ = true;
            }
        }
        Visit();
    }

    template<typename T>
    void PreOrderTreeIterator<T>::SetLast(bool v) {
        isLast_ = v;
    }

    template<typename T>
    Tree<T> *PreOrderTreeIterator<T>::GetTree() {
        return tree_;
    }

    template<typename T>
    void PreOrderTreeIterator<T>::SetTree(Tree<T> *tree) {
        tree_ = tree;
    }

    template<typename T>
    void PreOrderTreeIterator<T>::Visit() {
        tree_->SetVisited(true);
    }

    template <typename T>
    class PreOrderTreeView{
    public:
        explicit PreOrderTreeView(Tree<T> *tree);
        PreOrderTreeIterator<T> begin();
        PreOrderTreeIterator<T> end();

    private:
        Tree<T> *tree_;
    };

    template<typename T>
    PreOrderTreeView<T>::PreOrderTreeView(Tree<T> *tree) : tree_(tree){}

    template<typename T>
    PreOrderTreeIterator<T> PreOrderTreeView<T>::begin() {
        Tree<T> *t = tree_->Root();
        return PreOrderTreeIterator<T>(t);
    }

    template<typename T>
    PreOrderTreeIterator<T> PreOrderTreeView<T>::end() {
        PreOrderTreeIterator<T> it = begin();
        ++it;
        return it;
    }

    template <typename T>
    PreOrderTreeView<T> PreOrder(Tree<T> *tree){
        return PreOrderTreeView<T>(tree);
    }

/////////////////////////////////////////////////////////////////////////////////
    template <typename T>
    class InOrderTreeIterator : public PreOrderTreeIterator<T>{
    public:
        InOrderTreeIterator(Tree<T> *tree);
        void operator++() override;

    private:
        Tree<T> *PrepareRoot(Tree<T> *tree);
    };

    template<typename T>
    Tree<T> *InOrderTreeIterator<T>::PrepareRoot(Tree<T> *tree) {
        Tree<T> *t = tree;
        while (t->Left() != nullptr) t=&*t->Left();
        return t;
    }

    template<typename T>
    InOrderTreeIterator<T>::InOrderTreeIterator(Tree<T> *tree):PreOrderTreeIterator<T>(PrepareRoot(tree)) {}

    template<typename T>
    void InOrderTreeIterator<T>::operator++() {
        Tree<T> *tree_ = this->GetTree();
        if(tree_->Right() != nullptr){
            tree_ = &*tree_->Right();
            while (tree_->Left() != nullptr) tree_=&*tree_->Left();
        }
        else{
            if(&*tree_->Parent()->Left() == tree_) tree_=&*tree_->Parent();
            else {
                while (tree_->Parent() != nullptr && &*tree_->Parent()->Right() == tree_) tree_=tree_->Parent();
                tree_ = tree_->Parent();
            }

        }
        T val = tree_->Value();
        tree_->SetVisited(true);
        this->SetTree(tree_);
    }

    template <typename T>
    class InOrderTreeView{
    public:
        explicit InOrderTreeView(Tree<T> *tree);
        InOrderTreeIterator<T> begin();
        InOrderTreeIterator<T> end();

    private:
        Tree<T> *tree_;
    };

    template<typename T>
    InOrderTreeView<T>::InOrderTreeView(Tree<T> *tree) : tree_(tree) {}

    template<typename T>
    InOrderTreeIterator<T> InOrderTreeView<T>::begin() {
        Tree<T> *t = tree_;
        while (t->Left() != nullptr) t=&*t->Left();
        InOrderTreeIterator<T> it(t);
        return it;
    }

    template<typename T>
    InOrderTreeIterator<T> InOrderTreeView<T>::end() {
        InOrderTreeIterator<T> it = begin();
        ++it;
        return it;
    }


    template <typename T>
    InOrderTreeView<T> InOrder(Tree<T> *tree){
        return InOrderTreeView<T>(tree);
    }


    /////////////////////////////////////////////////////////////////////////////////
    template <typename T>
    class PostOrderTreeIterator : public PreOrderTreeIterator<T>{
    public:
        PostOrderTreeIterator(Tree<T> *tree);
        void operator++() override;

    private:
        Tree<T> *PrepareRoot(Tree<T> *tree);
    };

    template<typename T>
    PostOrderTreeIterator<T>::PostOrderTreeIterator(Tree<T> *tree):PreOrderTreeIterator<T>(PrepareRoot(tree)) {}

    template<typename T>
    void PostOrderTreeIterator<T>::operator++() {
        Tree<T> *tree_ = this->GetTree();
        if(tree_->Right() != nullptr && !tree_->Right()->Visited()) {
            while(tree_->Right() != nullptr && tree_->Right()->Left() == nullptr)tree_ = &*tree_->Right();
            if(tree_->Left() != nullptr) while(tree_!= nullptr) tree_ = &*tree_->Left();
        }
        else{
            if(&*tree_->Parent()->Left() == tree_) {
                tree_ = &*tree_->Parent();
                if(tree_->Right() != nullptr) {
                    while(tree_->Right() != nullptr && tree_->Right()->Left() == nullptr)tree_ = &*tree_->Right();
                    if(tree_->Left() != nullptr) while(tree_!= nullptr) tree_ = &*tree_->Left();
                }
            }
            else if(&*tree_->Parent()->Right() == tree_) tree_ = &*tree_->Parent();

        }
        tree_->SetVisited(true);
        this->SetTree(tree_);
    }

    template<typename T>
    Tree<T> *PostOrderTreeIterator<T>::PrepareRoot(Tree<T> *tree) {
        Tree<T> *t = tree;
        while (t->Left() != nullptr) t=&*t->Left();
        return t;
    }

    template<typename T>
    class PostOrderTreeView{
    public:
        PostOrderTreeView(Tree<T> *tree);
        PostOrderTreeIterator<T> begin();
        PostOrderTreeIterator<T> end();

    private:
        Tree<T> *tree_;
    };

    template<typename T>
    PostOrderTreeView<T>::PostOrderTreeView(Tree<T> *tree) : tree_(tree){}

    template<typename T>
    PostOrderTreeIterator<T> PostOrderTreeView<T>::begin() {
        Tree<T> *t = tree_;
        while (t->Left() != nullptr) t=&*t->Left();
        PostOrderTreeIterator<T> it(t);
        return it;
    }

    template<typename T>
    PostOrderTreeIterator<T> PostOrderTreeView<T>::end() {
        PostOrderTreeIterator<T> it = begin();
        ++it;
        ++it;
        return it;
    }

    template <typename T>
    PostOrderTreeView<T> PostOrder(Tree<T> *tree){
        return PostOrderTreeView<T>(tree);
    }
}


#endif //JIMP_EXERCISES_TREE_H