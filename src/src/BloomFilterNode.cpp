//  BloomFilterNode.cpp, Judith Greif
//  Description: Implementation of class BloomFilterNode

#include "BloomFilterNode.hpp"


// Constructor with parameters t and filtersize
BloomFilterNode::BloomFilterNode(int _t, int _s): t(_t), filtersize(_s), n(0), parent(NULL) {
    
    // Allocate memory
    keys = new int[2*_t];
    filters = new BloomFilter *[2*_t];
    for (int i=0; i<(2*_t); i++) {
        filters[i] = NULL;
    }
    unionfilter = new BloomFilter(filtersize, rand());
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
    float intersect_size = eIntersect(f1, f2);
    float union_size = eUnion(f1, f2);
    return 1 - (intersect_size/union_size); 
}



double BloomFilterNode::eUnion(BloomFilter *f1, BloomFilter *f2) {
    double dot = 0;
    int *arr1 = f1->getData();
    int *arr2 = f2->getData();
    for (int i=0; i<f1->getSize(); i++) {
        if (arr1[i] == 1 || arr2[i] == 1) {
            dot++;
        }
    }
    return -log(1-dot / (double) f1->getSize()) * f1->getSize()/d;
}

double BloomFilterNode::eIntersect(BloomFilter *f1, BloomFilter *f2) {
    double union_size = eUnion(f1, f2);
    double e = f1->eSize() + f2->eSize() - union_size;
    return e;
}

double BloomFilterNode::jacc(BloomFilter *f1, BloomFilter *f2) {
    return 1 - (eIntersect(f1, f2)/eUnion(f1, f2)); 
}