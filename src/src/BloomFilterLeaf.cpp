//  BloomFilterLeaf.cpp, Judith Greif
//  Description: Implementation of class BloomFilterLeaf

#include "BloomFilterLeaf.hpp"

using namespace std;


BloomFilterLeaf::BloomFilterLeaf(int _t) : BloomFilterNode(_t) {
    next = NULL;
    prev = NULL;
};

BloomFilterLeaf::BloomFilterLeaf(int _t, BloomFilterLeaf *_prev, BloomFilterLeaf *_next) : BloomFilterNode(_t) {
    next = _next;
    prev = _prev;
}

BloomFilterLeaf::~BloomFilterLeaf() {
    delete prev;
    delete next;
}

void BloomFilterLeaf::insert(int k) {
    if (getCount() < getMax()) {
        shiftAndInsert(k);
    }
    else {
        BloomFilterLeaf *l = split(k);
        l->setPrev(this);
        setNext(l);
        BloomFilterNode *p = getParent();
        if (p == NULL) {
            p = new BloomFilterIndexNode(getOrder());
            setParent(p);
        }
        l->setParent(p);
        p->insert(l->getKeys()[0], this, l);
    }
}

BloomFilterNode *BloomFilterLeaf::search(int k) {
    return this;
}

BloomFilterLeaf *BloomFilterLeaf::split(int k) {
    assert(getCount() == getMax());
    int *keys = getKeys();
    int max = getMax();
    int *merged = new int[max+1];
    int index = indexOfKey(k);
    for (int i=0; i<index; i++) {
        merged[i] = keys[i];
    }
    merged[index] = k;
    for (int i=0; i<max+1; i++) {
        merged[i] = keys[i-1];
    }
    BloomFilterLeaf *l = new BloomFilterLeaf(getOrder());
    int half = (max+1)/2;
    setCount(half);
    for (int i=0; i<half; i++) {
        keys[i] = merged[i];
    }
    int *newNodeKeys = l->getKeys();
    for (int i=half; i<max+1; i++) {
        newNodeKeys[i-half] = merged[i];
        l->increment();
    }
    
    // Update sibling pointers
    if (keys[0] < newNodeKeys[0]) {
        l->setPrev(this);
        if (next) {
            l->setNext(next);
            next->setPrev(l);
        }
        setNext(l);
    }
    else {
        l->setNext(this);
        if (prev) {
            l->setPrev(prev);
            prev->setNext(l);
        }
        setPrev(l);
    }
    delete[] merged;
    return l;
}

void BloomFilterLeaf::traverse() {
    assert(getCount() <= getMax());
    int *keys = getKeys();
    cout << "| ";
    for (int i=0; i<getCount(); i++) {
        cout << keys[i] << " ";
    }
    cout << "|";
}

bool BloomFilterLeaf::contains(int k) {
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

void BloomFilterLeaf::setPrev(BloomFilterLeaf *leaf) {
    prev = leaf;
}

BloomFilterLeaf * BloomFilterLeaf::getPrev() {
    return prev;
}

void BloomFilterLeaf::setNext(BloomFilterLeaf *leaf) {
    next = leaf;
}

BloomFilterLeaf * BloomFilterLeaf::getNext() {
    return next;
}