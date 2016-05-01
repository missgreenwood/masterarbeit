//  BPlusLeaf.cpp, Judith Greif
//  Description: Implementation of class BPlusLeaf

#include "BPlusLeaf.hpp"

using namespace std;

BPlusLeaf::BPlusLeaf(int _t): BPlusNode(_t) {}

BPlusLeaf::BPlusLeaf(int _t, BPlusLeaf *_prev, BPlusLeaf *_next) : BPlusNode(_t) {
    prev = _prev;
    next = _next;
}

BPlusLeaf::~BPlusLeaf() {
    delete prev;
    delete next;
}

void BPlusLeaf::insert(int k) {
    if (getCount() < getMax()) {
        shiftAndInsert(k);
    }
    else {
        BPlusLeaf *left = split(k);
        left->setPrev(this);
        setNext(left);
        BPlusNode *parent = getParent();
        if (parent == NULL) {
            parent = new BPlusIndexNode(getOrder());
            setParent(parent);
        }
        left->setParent(parent);
        parent->insert(left->getKeys()[0], this, left);
    }
}

BPlusNode * BPlusLeaf::search(int k) {
    return this;
}

BPlusLeaf * BPlusLeaf::split(int k) {
    assert(getCount() == getMax());
    int *keys = getKeys();
    int order = getMax();
    int *merged = new int[order + 1];
    int index = indexOfKey(k);
    for (int i=0; i<index; i++) {
        merged[i] = keys[i];
    }
    merged[index] = k;
    for (int i=index+1; i<order+1; i++) {
        merged[i] = keys[i-1];
    }
    BPlusLeaf *leaf = new BPlusLeaf(getOrder());
    int half = (order+1)/2;
    setCount(half);
    for (int i=0; i<half; i++) {
        keys[i] = merged[i];
    }
    int *newNodeKeys = leaf->getKeys();
    for (int i=half; i<order+1; i++) {
        newNodeKeys[i - half] = merged[i];
        leaf->increment();
    }
    delete[] merged;
    return leaf;
}

void BPlusLeaf::traverse() {
    assert(getCount() <= getMax());
    int *keys = getKeys();
    for (int i=0; i<getCount(); i++) {
        cout << keys[i] << " ";
    }
    cout << "\nEnd of node\n";
}

bool BPlusLeaf::contains(int k) {
    bool result = false;
    int *keys = getKeys();
    for (int i=0; i<getCount(); i++) {
        if (keys[i] == k) {
            result = true;
            break;
        }
    }
    return result;
}

void BPlusLeaf::remove(int key) {
    // BIG TODO
}

BPlusNode *BPlusLeaf::leftMost(int k) {
    if (prev->contains(k)) {
        return prev->leftMost(k);
    }
    else {
        if (contains(k)) {
            return this;
        }
    }
    return NULL;
}