//  BloomFilterNode.cpp, Judith Greif
//  Description: Implementation of class BloomFilterNode

#include "BloomFilterNode.hpp"


// Constructor with parameter t
BloomFilterNode::BloomFilterNode(int _t): t(_t), n(0) {
    parent = NULL;
    keys = new int[2*_t];
}

BloomFilterNode::~BloomFilterNode() {
    delete parent;
    delete[] keys;
}

void BloomFilterNode::shiftAndInsert(int k) {
    assert(n < getMax());
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

void BloomFilterNode::insert(int k, BloomFilterNode *oldNode, BloomFilterNode *newNode) {
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
