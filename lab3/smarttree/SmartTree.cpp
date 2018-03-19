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

void datastructures::PrintTreeInOrder(const std::unique_ptr<SmartTree> &unique_ptr,
                                      std::ostream *out) {

    if (unique_ptr->left != nullptr) {
        PrintTreeInOrder(unique_ptr->left, out);
    }
    *out << unique_ptr->value << ", ";
    if (unique_ptr->right != nullptr) {
        PrintTreeInOrder(unique_ptr->right, out);
    }

}

std::string datastructures::DumpTree(const std::unique_ptr<SmartTree> &tree) {

    if (tree == nullptr) {
        return "[none]";
    }

    return "[" + std::to_string(tree->value) + " " +
           DumpTree(tree->left) + " " +
           DumpTree(tree->right) + "]";
}

std::unique_ptr <SmartTree> datastructures::RestoreTree(const std::string &tree) {

    std::unique_ptr<SmartTree> newTree;
    std::string leftString;
    std::string rightString;
    std::string tmpString;
    std::string valueString;
    int numOfBrackets = 0;
    int lenOfRootValue = 0;
    bool onLeft = true;

    if (tree == "[none]") {
        return nullptr;
    }

    tmpString = tree.substr(1, tree.length()-2);
    for (; tmpString[lenOfRootValue] != ' '; lenOfRootValue++);
    valueString = tmpString.substr(0, lenOfRootValue);
    tmpString = tmpString.substr(lenOfRootValue+1, tmpString.length() - lenOfRootValue);

    for (int j = 0; j < tmpString.length(); j++) {

        if (onLeft) {
            leftString += tmpString[j];
        } else {
            rightString += tmpString[j];
        }

        if (tmpString[j] == '[') {
            numOfBrackets++;
        } else if (tmpString[j] == ']') {
            numOfBrackets--;
            if (numOfBrackets == 0 && !onLeft) {
                break;
            } else if (numOfBrackets == 0) {
                onLeft = false;
                j++;
            }
        }
    }

    newTree = CreateLeaf(std::stoi(valueString));
    newTree->right = RestoreTree(rightString);
    newTree->left = RestoreTree(leftString);
    return newTree;
}