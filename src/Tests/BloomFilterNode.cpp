//  BloomFilterNode.cpp, Judith Greif
//  Description: Implementation of class BloomFilterNode

#include "BloomFilterNode.hpp"


// Constructor with parameters t and filtersize
BloomFilterNode::BloomFilterNode(int _t, int _s): n(0), filtersize(_s), t(_t), parent(NULL) {
    
    // Allocate memory
    keys = new int[2*_t];
    filters = new BloomFilter *[(2*_t)];
    
    for (int i=0; i<(2*_t); i++) {
        filters[i] = NULL;
    }
}

BloomFilterNode::~BloomFilterNode() {
    delete parent;
    delete[] keys;
    delete[] filters;
}

int BloomFilterNode::getOrder() {
    return t;
}

int BloomFilterNode::getCount() {
    return n;
}

void BloomFilterNode::setCount(int count) {
    n = count;
}

BloomFilterNode * BloomFilterNode::getParent() {
    return parent;
}

void BloomFilterNode::setParent(BloomFilterNode *node) {
    parent = node;
}

int BloomFilterNode::indexOfKey(int k) {
    if (n == 0) {
        return 0;
    }
    int i=0;
    // while (i<n && keys[i]<k) {
    while (i<n && keys[i]<=k) {
        i++;
    }
    return i;
}

int * BloomFilterNode::getKeys() {
    return keys;
}

int BloomFilterNode::getMax() {
    return 2*t;
}

void BloomFilterNode::increment() {
    n++;
}

void BloomFilterNode::decrement() {
    n--;
}

int BloomFilterNode::getFilterSize() {
    return filtersize;
}

void BloomFilterNode::shiftAndInsert(BloomFilter *filter) {
    assert(getCount() < getMax());
    int id = filter->getId();
    int index = indexOfKey(id);
    for (int i=getCount()-1; i>=index; i--) {
        keys[i+1] = keys[i];
        filters[i+1] = filters[i];
    }
    keys[index] = id;
    filters[index] = filter; 
    increment();
    return;
}

void BloomFilterNode::insert(BloomFilter *filter, BloomFilterNode *oldNode, BloomFilterNode *newNode) {
    assert(false);
}

float BloomFilterNode::computeJaccard(BloomFilter *f1, BloomFilter *f2) {
    // float count1 = 0;
    float elementCount = 0;
    float intersection = 0;
    int *arr1 = f1->getArr();
    int *arr2 = f2->getArr();
    for (int i=0; i<getFilterSize(); i++) {
        if ((arr1[i] == 1) && (arr2[i] == 1)) {
            intersection++;
            elementCount++;
        }
        else if ((arr1[i] == 1) && arr2[i] == 0) {
            elementCount++;
        }
        else if ((arr1[i] == 0) && (arr2[i] == 1)) {
            elementCount++;
        }
    }
    float result = (float) intersection/elementCount;
    return result;
}

// Return true if f2 is subset of f1
bool BloomFilterNode::isSubset(BloomFilter *f1, BloomFilter *f2) {
    bool result = true;
    int *arr1 = f1->getArr();
    int *arr2 = f2->getArr();
    for (int i=0; i<getFilterSize(); i++) {
        if ((arr2[i] == 1) && (arr1[i] != arr2[i])) {
            result = false;
            break;
        }
    }
    return result; 
}

BloomFilter * BloomFilterNode::logicalAnd(BloomFilter *f1, BloomFilter *f2) {
     int *arr1 = f1->getArr();
     int *arr2 = f2->getArr();
     BloomFilter *result = new BloomFilter(getFilterSize(), rand());
     for (int i=0; i<getFilterSize(); i++) {
         if ((arr1[i] == 1) && (arr2[i] == 1)) {
             result->setValue(i, 1);
         }
     }
     return result;
 }


BloomFilter * BloomFilterNode::logicalOr(BloomFilter *f1, BloomFilter *f2) {
    int *arr1 = f1->getArr();
    int *arr2 = f2->getArr();
    BloomFilter *result = new BloomFilter(getFilterSize(), rand());
    for (int i=0; i<getFilterSize(); i++) {
        if ((arr1[i] == 1) || (arr2[i] == 1 )) {
            result->setValue(i, 1);
        }
    }
    return result;
}
