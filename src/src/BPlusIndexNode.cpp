//  BPlusIndexNode.cpp, Judith Greif
//  Description: Implementation of class BPlusIndexNode

#include "BPlusIndexNode.hpp"


BPlusIndexNode::BPlusIndexNode(int _t): BPlusNode(_t) {
    C = new BPlusNode *[2*_t];
    for (int i=0; i<2*_t; i++) {
        C[i] = NULL;
    }
}

BPlusIndexNode::~BPlusIndexNode() {
    delete[] C;
}

BPlusNode * BPlusIndexNode::search(int k) {
    int index = indexOfKey(k);
    return C[index]->search(k);
}

void BPlusIndexNode::shiftAndInsert(int k) {
    int index = indexOfKey(k);
    BPlusNode::shiftAndInsert(k);
    for (int i=getCount()-1; i>index; i--) {
        C[i+1] = C[i];
    }
}

void BPlusIndexNode::insert(int k) {
    BPlusNode *l = search(k);
    l->insert(k);
}

void BPlusIndexNode::insert(int k, BPlusNode *leftNode, BPlusNode *rightNode) {
    if (getCount() < getMax()) {
        int index = indexOfKey(k);
        shiftAndInsert(k);
        C[index] = leftNode;
        C[index+1] = rightNode;
    }
    else {
        int mid;
        BPlusIndexNode *s = split(k, leftNode, rightNode, mid);
        BPlusNode *p = getParent();
        if (p == NULL) {
            p = new BPlusIndexNode(getOrder());
            setParent(p);
        }
        s->setParent(p);
        p->insert(mid, this, s);
    }
}

bool BPlusIndexNode::contains(int k) {
    bool result = false;
    int *keys = getKeys();
    for (int i=0; i<getMax()+1; i++) {
        if (keys[i]<k && keys[i+1]>=k && i<getCount()) {
            return C[i]->contains(k);
        }
    }
    return result;
}


void BPlusIndexNode::remove(int k) {

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
    
}

BPlusIndexNode * BPlusIndexNode::split(int k, BPlusNode *left, BPlusNode *right, int &middle) {
    assert(getCount() == getMax());
    int max = getMax();
    int *merged = new int[max+1];
    int index = indexOfKey(k);
    int *keys = getKeys();
    BPlusNode **mergedNodes = new BPlusNode*[max+2];
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
    int half = (max+1)/2;
    middle = merged[half];
    for (int i=0; i<half; i++) {
        keys[i] = merged[i];
        C[i] = mergedNodes[i];
    }
    C[half] = mergedNodes[half];
    for (int i=half+1; i<max+1; i++) {
        C[i] = NULL;
    }
    setCount(half);
    BPlusIndexNode *s = new BPlusIndexNode(getOrder());
    int *sKeys = s->getKeys();
    BPlusNode **sChildren = s->C;
    for (int i=half+1; i<max+1; i++) {
        sKeys[i-(half+1)] = merged[i];
        sChildren[i-(half+1)] = mergedNodes[i];
        sChildren[i-(half+1)]->setParent(s);
        s->increment();
    }
    int pos;
    if (half % 2 == 1) {
        pos = half;
        sChildren[pos] = mergedNodes[max+1];
        sChildren[pos]->setParent(s);
    }
    else {
        pos = half-1;
        sChildren[pos] = mergedNodes[max+1];
        sChildren[pos]->setParent(s);
    }
    delete[] merged;
    delete[] mergedNodes;
    return s;
}


void BPlusIndexNode::traverse() {
    for (int i=0; i<getCount()+1; i++) {
        C[i]->traverse();
    }
}