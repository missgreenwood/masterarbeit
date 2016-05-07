//  BPlusNode.cpp, Judith Greif
//  Description: Implementation of class BPlusNode

#include "BPlusNode.hpp"


BPlusNode::BPlusNode(int _t): t(_t), n(0) {
    parent = NULL;
    keys = new int[2*_t-1];
}

BPlusNode::~BPlusNode() {
    delete parent;
    delete[] keys;
}

void BPlusNode::shiftAndInsert(int k){
    assert(n < getMax());
    int index = indexOfKey(k);
    for (int i=n-1; i>=index; i--) {
        keys[i+1] = keys[i];
    }
    keys[index] = k;
    increment();
    return;
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

void BPlusNode::insert(int k, BPlusNode *oldNode, BPlusNode *newNode) {
    assert(false);
}

// TODO

int BPlusNode::getMax() {
    return 2*t-1;
}

// TODO
