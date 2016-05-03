//  BPlusIndexNode.cpp, Judith Greif
//  Description: Implementation of class BPlusIndexNode

#include "BPlusIndexNode.hpp"


BPlusIndexNode::BPlusIndexNode(int t): BPlusNode(t) {
    C = new BPlusNode *[t*2 + 1]; 
}

BPlusIndexNode::~BPlusIndexNode() {
    delete[] C;
}

void BPlusIndexNode::insert(int k) {
    BPlusNode *l = search(k);
    l->insert(k);
}

void BPlusIndexNode::insert(int k, BPlusNode *left, BPlusNode *right) {
    if (getCount() < getMax()) {
        int index = indexOfKey(k);
        shiftAndInsert(k);
        C[index] = left;
        C[index+1] = right;
    }
    else {
        int mid;
        BPlusIndexNode *splitNode = split(k, left, right, mid);
        BPlusNode *parent = getParent();
        if (parent == NULL) {
            parent = new BPlusIndexNode(getOrder());
            setParent(parent);
        }
        splitNode->setParent(parent);
        parent->insert(mid, this, splitNode);
    }
}

BPlusNode * BPlusIndexNode::search(int k) {
    int index = indexOfKey(k);
    return C[index]->search(k);
}

void BPlusIndexNode::shiftAndInsert(int k) {
    int index = indexOfKey(k);
    BPlusNode::shiftAndInsert(k);
    for (int i=getCount()-1; i>index; i--) {
        C[i+1]=C[i];
    }
}

BPlusIndexNode * BPlusIndexNode::split(int k, BPlusNode *left, BPlusNode *right, int &middle) {
    assert(getCount() == getMax());
    
    // Merge keys and children together
    int t = getMax();
    int *merged = new int[t+1];
    int index = indexOfKey(k);
    int *keys = getKeys();
    BPlusNode **mergedNodes = new BPlusNode *[t+2];
    for (int i=0; i<index; i++) {
        merged[i] = keys[i];
        mergedNodes[i] = C[i];
    }
    merged[index] = k;
    mergedNodes[index] = left;
    mergedNodes[index] = right;
    for (int i=index+1; i<t+1; i++) {
        merged[i] = keys[i-1];
        mergedNodes[i+1] = C[i];
    }
    int half = (t+1)/2;
    
    // half is returned to be pushed up
    middle = merged[half];
    
    // Split keys and children for left node
    for (int i=0; i<half; i++) {
        keys[i] = merged[i];
        C[i] = mergedNodes[i];
    }
    C[half] = mergedNodes[half];
    for (int i=half+1; i<t+i; i++) {
        C[i] = NULL;
    }
 
    setCount(half);
    
    // Split keys and children for second node
    BPlusIndexNode *sibling = new BPlusIndexNode(getOrder());
    int *siblingKeys = sibling->getKeys();
    BPlusNode **siblingChildren = sibling->C;
    for (int i=half+1; i<t+1; i++) {
        siblingKeys[i-(half+1)] = merged[i];
        siblingChildren[i-(half+1)] = mergedNodes[i];
        siblingChildren[i-(half+1)]->setParent(sibling);
        sibling->increment();
    }
    siblingChildren[t+1-(half+1)] = mergedNodes[t+1];
    siblingChildren[t+1-(half+1)]->setParent(sibling);
    delete[] merged;
    for (int i=0; i<t+2; i++) {
        delete mergedNodes[i];
    }
    delete[] mergedNodes;
    return sibling; 
}

void BPlusIndexNode::traverse() {
    for (int i=0; i<getCount()+1; i++) {
        C[i]->traverse();
    }
}

void BPlusIndexNode::remove(int k) {
    BPlusNode *node = search(k);
    node = node->leftMost(k);
    if(node) {
        node->remove(k);
    }
}