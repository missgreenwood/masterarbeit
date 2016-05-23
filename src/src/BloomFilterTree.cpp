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

float BloomFilterTree::computeMaxJaccard(BloomFilter *filter) {
    if (root == NULL) {
        cout << "Tree is empty!";
        return 1.0;
    }
    else {
        return root->computeMaxJaccard(filter);
    }
}

// Returns key with highest Jaccard coefficient
// Returns first key if there are several keys with equal Jaccard coefficient
int BloomFilterTree::computeMaxJaccardKey(BloomFilter *filter) {
    if (root == NULL) {
        cout << "Tree is empty - this is the first filter!";
        return filter->getId();
    }
    else {
        return root->computeMaxJaccardKey(filter);
    }
}

// int BloomFilterTree::computeSimilarityId(BloomFilter *filter) {}