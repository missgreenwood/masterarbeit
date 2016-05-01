//  BPlusNode.cpp, Judith Greif
//  Description: Implementation of class BPlusNode

#include "BPlusNode.hpp"


BPlusNode::BPlusNode(int _t): t(_t), parent(0), n(0) {
    // Allocate memory for maximum number of possible keys
    keys = new int[t*2];
}

BPlusNode::~BPlusNode() {
    delete parent;
    delete[] keys;
}

int BPlusNode::getOrder() {
    return t;
}

int BPlusNode::getCount() {
    return n;
}

void BPlusNode::setCount(int count) {
    n = count;
}

BPlusNode * BPlusNode::getParent() {
    return parent;
}

void BPlusNode::setParent(BPlusNode *node) {
    parent = node;
}

int BPlusNode::indexOfKey(int k) {
    if (n == 0) {
        return 0;
    }
    int i=0;
    while (i<n && keys[i] <= k) {
        i++;
    }
    return i;
}

int * BPlusNode::getKeys() {
    return keys;
}

void BPlusNode::shiftAndInsert(int k) {
    assert(n < getMax());
    int index = indexOfKey(k);
    for (int i=n-1; i>=index; i--) {
        keys[i+1] = keys[i];
    }
    keys[index] = k;
    n++;
    return;
}

void BPlusNode::insert(int k) {
    assert(false);
}

void BPlusNode::insert(int k, BPlusNode *oldNode, BPlusNode *newNode) {
    assert(false);
}

BPlusNode * BPlusNode::leftMost(int k) {
    return NULL; 
}