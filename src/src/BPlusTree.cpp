//  BPlusTree.cpp, Judith Greif
//  Description: Implementation of class BPlusTree

#include "BPlusTree.hpp"

BPlusTree::BPlusTree(int _t): t(_t) {
    root = NULL;
}

BPlusTree::~BPlusTree() {
    delete root; 
}

void BPlusTree::traverse() {
    if (root == NULL) {
        cout << "Tree is empty!";
        return;
    }
    else root->traverse();
}

BPlusNode * BPlusTree::search(int k) {
    if (root == NULL) {
        cout << "Tree is empty!";
        return NULL;
    }
    else return root->search(k);
}

BPlusNode * BPlusTree::searchRemoveIndex(int k) {
    if (root == NULL) {
        cout << "Tree is empty!";
        return NULL;
    }
    else return root->searchRemoveIndex(k);
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
    if (root == NULL) {
        cout << "Tree is empty!";
        return;
    }
    else if (!contains(k)) {
        cout << "Key " << k << " is not present in tree";
        return;
    } 
    else {
        // Find leaf where k is placed in
        BPlusNode *target = search(k);
        if (!(target->contains(k))) {
            target = searchRemoveIndex(k);
        }
        // Recursively remove k from target
        target->remove(k);
    }
}

bool BPlusTree::contains(int k) {
    // If tree is empty return false
    if (root == NULL) {
        cout << "Tree is empty!";
        return false;
    }
    else {
        return root->contains(k);
    }
}