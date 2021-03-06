//  BPlusNode.cpp, Judith Greif
//  Description: Implementation of class BPlusNode

#include "BPlusNode.hpp"

using namespace std;


BPlusNode::BPlusNode(int _t): t(_t), n(0) {
    parent = NULL;
    next = NULL;
    prev = NULL;
    keys = new int[2*_t-1];
}

BPlusNode::~BPlusNode() {
    delete parent;
    delete prev;
    delete next; 
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

int BPlusNode::indexOfKey(int k) {
    if (n == 0) {
        return 0;
    }
    int i=0;
    while (i<n && keys[i]<k) {
        i++;
    }
    return i;
}

int BPlusNode::removeIndex(int k) {
    if (n == 0) {
        return 0;
    }
    int i = 0;
    while (i<n && keys[i]<=k) {
        i++;
    }
    return i;
}

int * BPlusNode::getKeys() {
    return keys;
}

int BPlusNode::getMax() {
    return 2*t-1;
}

void BPlusNode::increment() {
    n++;
}

void BPlusNode::decrement() {
    n--;
}

BPlusNode * BPlusNode::getPrev() {
    return prev;
}

BPlusNode * BPlusNode::getNext() {
    return next;
}

void BPlusNode::setPrev(BPlusNode *_prev) {
    prev = _prev;
}

void BPlusNode::setNext(BPlusNode *_next) {
    next = _next;
}

