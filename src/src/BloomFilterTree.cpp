//  BloomFilterTree.cpp, Judith Greif
//  Description: Implementation of class BloomFilterTree

#include "BloomFilterTree.hpp"

// Constructor with parameter t
// Initializes tree as empty
BloomFilterTree::BloomFilterTree(int _t): t(_t), root(NULL) {};

BloomFilterTree::~BloomFilterTree() {
    delete root;
}

void BloomFilterTree::traverse() {
    if (root == NULL) {
        cout << "Tree is empty!";
        return;
    }
    else {
        root->traverse();
    }
}