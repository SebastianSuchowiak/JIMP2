//
// Created by sebastian on 18.03.18.
//

#include "SmartTree.h"

using namespace datastructures;

std::unique_ptr <SmartTree> datastructures::CreateLeaf(int value) {

    std::unique_ptr <SmartTree> newLeaf = std::make_unique<SmartTree>();

    newLeaf->value = value;
    return newLeaf;
}

std::unique_ptr <SmartTree> datastructures::InsertLeftChild(std::unique_ptr<SmartTree> tree,
                                            std::unique_ptr<SmartTree> left_subtree) {
    tree->left = std::move(left_subtree);
    return tree;
}

std::unique_ptr <SmartTree> datastructures::InsertRightChild(std::unique_ptr<SmartTree> tree,
                                             std::unique_ptr<SmartTree> right_subtree) {
    tree->right = std::move(right_subtree);
    return tree;
}

void datastructures::PrintTreeInOrder(const std::unique_ptr<SmartTree> &unique_ptr, std::ostream *out) {

    if (unique_ptr->left != nullptr) {
        PrintTreeInOrder(unique_ptr->left, out);
    }
    *out << unique_ptr->value << ", ";
    if (unique_ptr->right != nullptr) {
        PrintTreeInOrder(unique_ptr->right, out);
    }

}