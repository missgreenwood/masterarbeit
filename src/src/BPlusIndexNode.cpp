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
    int max = getMax();
    int *merged = new int[max+1];
    int index = indexOfKey(k);
    int *keys = getKeys();
    BPlusNode **mergedNodes = new BPlusNode *[max+2];
    for (int i=0; i<index; i++) {
        merged[i] = keys[i];
        mergedNodes[i] = C[i];
    }
    merged[index] = k;
    mergedNodes[index] = left;
    mergedNodes[index+1] = right;
    for (int i=index+1; i<max+1; i++) {
        merged[i] = keys[i-1];
        mergedNodes[i+1] = C[i];
    }
    mergedNodes[max+2] = C[max+1];
    int half = (max+1)/2;
    
    // half is returned to be pushed up
    middle = merged[half];
    
    // Split keys and children for left node
    for (int i=0; i<half; i++) {
        keys[i] = merged[i];
        C[i] = mergedNodes[i];
    }
    C[half] = mergedNodes[half];
    for (int i=half+1; i<max+1; i++) {
        C[i] = NULL;
    }
 
    setCount(half);
    
    // Split keys and children for second node
    BPlusIndexNode *sibling = new BPlusIndexNode(getOrder());
    int *siblingKeys = sibling->getKeys();
    BPlusNode **siblingChildren = sibling->C;
    // for (int i=half+1; i<max+1; i++) {
    for (int i=half; i<=max; i++) {
        int pos = i-half;
        siblingKeys[pos] = merged[i];
        siblingChildren[pos] = mergedNodes[i+1];
        siblingChildren[pos]->setParent(sibling);
        sibling->increment();
    }
    siblingChildren[max+1-half] = mergedNodes[max+1];
    siblingChildren[max+1-half]->setParent(sibling);
    delete[] merged;
    for (int i=0; i<max+2; i++) {
        delete mergedNodes[i];
    }
    delete[] mergedNodes;
    return sibling; 
}

void BPlusIndexNode::traverse() {
    for (int i=0; i<getCount(); i++) {
        C[i]->traverse();
    }
}

bool BPlusIndexNode::contains(int k) {
    bool result = false;
    for (int i=0; i<getCount(); i++) {
        if (C[i]->contains(k)) {
            result = true;
            break;
        }
    }
    return result;
}


// TODO RECURSIVELY

// 1. Remove key from target

// 2. UNDERFLOW?
// 3.     NO -> DONE
// 4.     YES -> ROOT?
// 5.           YES -> Collapse root -> DONE
// 6.           NO -> Check neighbors -> MINIMAL?
// 7.                 NO -> Borrow from neighbor -> DONE
// 8.                 YES -> Merge with neighbor
// 9. Unwind to parent node
// Continue steps 1. - 9. as long as neccessary


void BPlusIndexNode::remove(int k) {

}
