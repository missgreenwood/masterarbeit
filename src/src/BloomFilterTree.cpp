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

// Compute best similarity id for filter regarding this tree
int BloomFilterTree::computeSimilarityId(BloomFilter *filter) {
    if (root == NULL) {
        cout << "Tree is empty!";
        return filter->getId();
    }
    else {
        int minId = getMinKey();
        int maxId = getMaxKey();
        int optimalId = computeMaxJaccardKey(filter);
        int smallId = minId;
        int bigId = maxId;
        
        // Get next available lesser key
        for (int i=optimalId-1; i>minId; i--) {
            if (!contains(i)) {
                smallId = i;
                break;
            }
        }
        if (smallId == minId) {
            smallId = minId-1;
        }
        
        // Get next available greater key
        for (int i=optimalId+1; i<maxId; i++) {
            if (!contains(i)) {
                bigId = i;
                break;
            }
        }
        if (bigId == maxId) {
            bigId = maxId+1;
        }
        
        // Decide which key is better
        // Returns smaller key if both are equally good
        if ((bigId-optimalId) > (optimalId-smallId)) {
            return smallId;
        }
        else {
            return bigId; 
        }
    }
}