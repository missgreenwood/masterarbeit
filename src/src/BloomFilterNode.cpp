//  BloomFilterNode.cpp, Judith Greif
//  Description: Implementation of class BloomFilterNode

#include "BloomFilterNode.hpp"


// Constructor with parameters t and size
BloomFilterNode::BloomFilterNode(int _t, int _s): t(_t), n(0), size(_s) {
    parent = NULL;
    keys = new int[2*_t];
}

BloomFilterNode::~BloomFilterNode() {
    delete parent;
    delete[] keys;
}

void BloomFilterNode::shiftAndInsert(BloomFilter *filter) {
    assert(n < getMax());
    int id = filter->getId();
    int index = indexOfKey(id);
    for (int i=n-1; i>=index; i--) {
        keys[i+1] = keys[i];
    }
    keys[index] = id;
    increment();
    return; 
}

void BloomFilterNode::shiftAndInsertKey(int k) {
    assert(getCount() < getMax());
    int index = indexOfKey(k);
    for (int i=n-1; i>=index; i--) {
        keys[i+1] = keys[i];
    }
    keys[index] = k;
    increment();
    return;
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

void BloomFilterNode::insert(BloomFilter *filter, BloomFilterNode *oldNode, BloomFilterNode *newNode) {
    assert(false);
}

void BloomFilterNode::insertKey(int k, BloomFilterNode *oldNode, BloomFilterNode *newNode) {
    assert(false); 
}

void BloomFilterNode::insertSimilarFilter(BloomFilter *filter) {
    assert(false);
}

int BloomFilterNode::indexOfKey(int k) {
    if (n == 0) {
        return 0;
    }
    int i=0;
    while (i<n && keys[i]<k) {
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
    return size; 
}

float BloomFilterNode::computeJaccard(int *arr1, int *arr2) {
    float count1 = 0;
    float count2 = 0;
    float same = 0;
    for (int i=0; i<getFilterSize(); i++) {
        if (arr1[i] == 1) {
            count1++;
        }
        if (arr2[i] == 1) {
            count2++;
        }
        if ((arr1[i] == 1) && (arr2[i] == 1)) {
            same++;
        }
    }
    float count = count1+count2;
    float res = (float)same/count;
    return res;
}

// Return true if arr2 is subset of arr1
bool BloomFilterNode::isSubset(int *arr1, int *arr2) {
    bool result = true;
    for (int i=0; i<getFilterSize(); i++) {
        if ((arr2[i] == 1) && (arr1[i] != arr2[i])) {
            result = false;
            break;
        }
    }
    return result;
}

int * BloomFilterNode::logicalAnd(int *arr1, int *arr2) {
    int *arr3 = new int[getFilterSize()];
    for (int i=0; i<getFilterSize(); i++) {
        if ((arr1[i] == 1) && (arr2[i] == 1)) {
            arr3[i] = 1;
        }
        else {
            arr3[i] = 0;
        }
        cout << arr3[i];
    }
    return arr3;
}

int * BloomFilterNode::logicalOr(int *arr1, int *arr2) {
    int *arr3 = new int[getFilterSize()];
    for (int i=0; i<getFilterSize(); i++) {
        if ((arr1[i] == 1) || (arr2[i] == 1)) {
            arr3[i] = 1;
        }
        else {
            arr3[i] = 0;
        }
        cout << arr3[i];
    }
    return arr3;
}
