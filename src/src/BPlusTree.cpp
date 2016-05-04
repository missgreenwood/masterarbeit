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
            cout << "\nKey " << k << " is not present in tree\n";
            return;
        }
        else {
            // Find position of k
            BPlusNode *target = search(k);
            // DO RECURSIVELY
            
            // 1. Remove key from leaf
            // 2. UNDERFLOW?
            // 3.     NO -> DONE
            // 4.     YES -> ROOT?
            // 5.           YES -> Collapse root -> DONE
            // 6.           NO -> Check neighbors -> MINIMAL?
            // 7.                 NO -> Borrow from neighbor -> DONE
            // 8.                 YES -> Merge with neighbor
            // 9. Unwind to parent node
            // Continue steps 1. - 9. as long as neccessary
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
