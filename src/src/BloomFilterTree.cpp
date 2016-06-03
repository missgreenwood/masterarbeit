//  BloomFilterTree.cpp, Judith Greif
//  Description: Implementation of class BloomFilterTree

#include "BloomFilterTree.hpp"


// Constructor with parameters order and size
// Initializes tree as empty
BloomFilterTree::BloomFilterTree(int _t, int _s): t(_t), filtersize(_s), root(NULL) {}

BloomFilterTree::~BloomFilterTree() {
    delete root;
}

// Determine if key is present in tree
// Return false otherwise
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

float BloomFilterTree::computeMinJaccard(BloomFilter *filter) {
    if (root == NULL) {
        cout << "Tree is empty!";
        return 0;
    }
    else {
        return root->computeMinJaccard(filter);
    }
}

// Determine key with minimal Jaccard distance
// Return first key if there are several with equal distance
int BloomFilterTree::computeMinJaccardKey(BloomFilter *filter) {
    if (root == NULL) {
        cout << "Tree is empty - this is the first filter!";
        return filter->getId();
    }
    else {
        return root->computeMinJaccardKey(filter);
    }
}

int BloomFilterTree::getMinKey() {
    if (root == NULL) {
        cout << "Tree is emtpy!";
        return 0;
    }
    else {
        return root->getMinKey();
    }
}

int BloomFilterTree::getMaxKey() {
    if (root == NULL) {
        cout << "Tree is empty!";
        return 0;
    }
    else {
        return root->getMaxKey(); 
    }
}

// Compute best id for filter
// Treating filters as subsets of each other
int BloomFilterTree::computeSubsetId(BloomFilter *filter) {
    if (root == NULL) {
        cout << "Tree is empty!";
        return filter->getId();
    }
    /* else if {
        // Check if filter is subset of any tree nodes
        
        
    } */
    else {
        // Check if any tree nodes are subset of filter
    }
    
        // Best id for filter: in best similarity circle (take any free id from there)
    return 0;
}

vector<BloomFilter> BloomFilterTree::collectAllFilters() {
    if (root == NULL) {
        cout << "Tree is empty!\n";
        return {};
    }
    else {
        return root->collectAllFilters();
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