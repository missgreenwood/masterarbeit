//  BloomFilterTree.cpp, Judith Greif
//  Description: Implementation of class BloomFilterTree

#include "BloomFilterTree.hpp"


// Constructor with parameters order and size
// Initializes tree as empty
BloomFilterTree::BloomFilterTree(int _t, int _s): t(_t), filtersize(_s), root(NULL) {}

BloomFilterTree::~BloomFilterTree() {
    delete root;
}

// Function to determine if key is present in tree
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
        // Returns greater key if both are equally good
        if ((bigId-optimalId) > (optimalId-smallId)) {
            return smallId;
        }
        else {
            return bigId; 
        }
    }
}

void BloomFilterTree::insertSimilarFilter(BloomFilter *filter) {
    if (root == NULL) {
        cout << "Tree is empty - this is the first filter!";
        insert(filter);
    }
    else {
        int newId = computeSimilarityId(filter);
        filter->setId(newId);
        insert(filter);
    }
}

// Function to find Bloom filter with highest Jaccard coefficient in tree
// Naive approach, no pruning
BloomFilter *BloomFilterTree::simpleSimQuery(BloomFilter *filter) {
    if (root == NULL) {
        cout << "Tree is empty!";
        return filter;
    }
    else {
        return root->simpleSimQuery(filter);
    }
}

// Function to find Bloom filter with highest Jaccard coefficient in tree
// Follow only best path in tree
BloomFilter * BloomFilterTree::simQuery(BloomFilter *filter) {
    if (root == NULL) {
        cout << "Tree is empty!";
        return filter;
    }
    else {
        return root->simQuery(filter); 
    }
}

// TODO
// Function to find k Bloom filters with highest Jaccard coeffients in tree and return them as Bloom filter vector
// Naive approach, no pruning
/* vector<BloomFilter> BloomFilterTree::simpleSimQueryVec(BloomFilter *filter, int k) {
    if (root == NULL) {
        vector<BloomFilter> results(1);
        cout << "Tree is empty!";
        results.push_back(*filter);
        return results;
    }
    else {
        return *root->simpleSimQueryVec(filter, k);
    }
} */

// TODO 
// Function to find k Bloom filters with highest Jaccard coeffients in tree and return them as Bloom filter vector
// Follow only best path in tree
/* vector<BloomFilter> BloomFilterTree::simQueryVec(BloomFilter *filter, int k) {
    if (root == NULL) {vector<BloomFilter> results(1);
        cout << "Tree is empty!";
        results.push_back(*filter);
        return results;
    }
    else {
        return *root->simpleSimQueryVec(filter, k);
    }
} */