//  BloomFilterTree.cpp, Judith Greif
//  Description: Implementation of class BloomFilterTree

#include "BloomFilterTree.hpp"


// Constructor with parameter t
// Initializes tree as empty
BloomFilterTree::BloomFilterTree(int _t): t(_t), root(NULL) {};

// TODO
BloomFilterTree::BloomFilterTree(int _t, BloomFilterVec *_f) {

}

// TODO
// Constructor with parameters t and *filtersvec
// Insert all filters from Bloom filter vector as BloomFilterNode instances in BloomFilterTree
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

BloomFilterNode * BloomFilterTree::search(int k) {
    if (root == NULL) {
        cout << "Tree is empty!";
        return NULL;
    }
    else return root->search(k);
}

// TODO
void BloomFilterTree::insert(BloomFilter *filter) {

}

void BloomFilterTree::insert(int k) {
    if (root == NULL) {
        
        // Allocate memory for root
        root = new BloomFilterLeaf(t, NULL, NULL);
        root->insert(k);
    }
    else {
        root->insert(k);
        if (root->getParent() != NULL) {
            root = root->getParent();
        }
    }
}

bool BloomFilterTree::contains(int k) {

    // If tree is empty return false
    if (root == NULL) {
        cout << "Tree is empty!";
        return false;
    }
    else {
        return root->contains(k);
    }
}

BloomFilterNode * BloomFilterTree::getRoot() {
    return root; 
}