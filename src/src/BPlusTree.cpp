//  BPlusTree.cpp, Judith Greif
//  Description: Implementation of class BPlusTree

#include "BPlusTree.hpp"

// Constructor with parameter t
// Initializes tree as empty
BPlusTree::BPlusTree(int _t): t(_t), root(NULL) {};

BPlusTree::~BPlusTree() {
    delete root;
}


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

void BPlusTree::remove(int k) {
    
    // Check if root is empty or k is not present in tree
    if (root != NULL) {
        if (!contains(k)) {
            cout << " Key " << k << " is not present in tree\n";
            return;
        }
        else {
            
            // Find position of k
            BPlusNode *target = search(k);
            
            // Recursively remove k from target
            target->remove(k);
        }
    }
}

bool BPlusTree::contains(int k) {
    // If tree is empty return false
    if (root == NULL) {
        return false;
    }
    else {
        return root->contains(k);
    }
}
