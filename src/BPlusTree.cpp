//  BPlusTree.cpp, Judith Greif
//  Description: Implementation of class BPlusTree

#include "BPlusTree.hpp"

void BPlusTree::traverse() {
    if (root != NULL) {
        root->traverse();
    }
}

BPlusNode * BPlusTree::search(int k) {
    if(root != NULL) {
        return root->search(k);
    }
    else {
        return NULL;
    }
}

void BPlusTree::insert(int k) {
    if (root == NULL) {
        // Allocate memory for root
        root = new BPlusLeaf(t, NULL, NULL);
        root->insert(k);
    }
    else {
        root->insert(k);
        if (root->getParent() != NULL) {
            root = root->getParent();
        }
    }
}


