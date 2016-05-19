//  BloomFilterTree.cpp, Judith Greif
//  Description: Implementation of class BloomFilterTree

#include "BloomFilterTree.hpp"


// Constructor with parameters t and size
// Initializes tree as empty
BloomFilterTree::BloomFilterTree(int _t, int _s): t(_t), filtersize(_s), root(NULL) {};

// TODO
BloomFilterTree::BloomFilterTree(int _t, int _s, BloomFilterVec *_f): t(_t), filtersize(_s), root(NULL) {
    filtersvec = _f;
}

BloomFilterTree::~BloomFilterTree() {
    delete root;
}

// TODO
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

BloomFilterNode * BloomFilterTree::search(int k) {
    if (root == NULL) {
        cout << "Tree is empty!";
        return NULL;
    }
    else return root->search(k);
}

BloomFilterNode * BloomFilterTree::getRoot() {
    return root;
}

BloomFilterVec * BloomFilterTree::getFiltersVec() {
    return filtersvec;
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

void BloomFilterTree::traverseFilters() {
    if (root == NULL) {
        cout << "The tree is empty!";
        return;
    }
    else {
        root->traverseFilters(); 
    }
}

// TODO 
void BloomFilterTree::insert(BloomFilter *filter) {
    if (root == NULL) {
        root = new BloomFilterLeaf(t, filtersize, NULL, NULL);
        root->insert(filter);
    }
    else {
        root->insert(filter);
        if (root->getParent() != NULL) {
            root = root->getParent(); 
        }
    }
}