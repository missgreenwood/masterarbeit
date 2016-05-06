//  BPlusLeaf.cpp, Judith Greif
//  Description: Implementation of class BPlusLeaf

#include "BPlusLeaf.hpp"

using namespace std;

BPlusLeaf::BPlusLeaf(int _t): BPlusNode(_t) {
    prev = NULL;
    next = NULL;
}

BPlusLeaf::BPlusLeaf(int _t, BPlusLeaf *_prev, BPlusLeaf *_next) : BPlusNode(_t) {
    prev = _prev;
    next = _next;
}

BPlusLeaf::~BPlusLeaf() {
    delete prev;
    delete next;
}

BPlusLeaf * BPlusLeaf::getPrev() {
    return prev;
}

BPlusLeaf * BPlusLeaf::getNext() {
    return next;
}

void BPlusLeaf::setPrev(BPlusLeaf *_prev) {
    prev = _prev;
}

void BPlusLeaf::setNext(BPlusLeaf *_next) {
    next = _next; 
}

void BPlusLeaf::insert(int k) {
    if (getCount() < getMax()) {
        shiftAndInsert(k);
    }
    else {
        BPlusLeaf *newNext = split(k);
        newNext->setPrev(this);
        setNext(newNext);
        BPlusNode *parent = getParent();
        if (parent == NULL) {
            parent = new BPlusIndexNode(getOrder());
            setParent(parent);
        }
        newNext->setParent(parent);
        parent->insert(newNext->getKeys()[0], this, newNext);
    }
}

// Attention: No lookup function, but search for correct place in tree to insert key
BPlusNode * BPlusLeaf::search(int k) {
    return this;
}

BPlusLeaf * BPlusLeaf::split(int k) {
    assert(getCount() == getMax());
    int *keys = getKeys();
    int max = getMax();
    int *merged = new int[2*max + 1];
    int index = indexOfKey(k);
    for (int i=0; i<index; i++) {
        merged[i] = keys[i];
    }
    merged[index] = k;
    for (int i=index+1; i<max+1; i++) {
        merged[i] = keys[i-1];
    }
    BPlusLeaf *leaf = new BPlusLeaf(getOrder());
    int half = (max+1)/2;
    setCount(half);
    for (int i=0; i<half; i++) {
        keys[i] = merged[i];
    }
    int *newNodeKeys = leaf->getKeys();
    for (int i=half; i<max+1; i++) {
        newNodeKeys[i - half] = merged[i];
        leaf->increment();
    }
    delete[] merged;
    return leaf;
}

void BPlusLeaf::traverse() {
    assert(getCount() <= getMax());
    int *keys = getKeys();
    cout << "|";
    for (int i=0; i<getCount(); i++) {
        cout << " " << keys[i] << " ";
    }
    cout << "|";
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

// 8.                 YES -> Merge with neighbor
// 9. Unwind to parent node
// Continue steps 1. - 9. as long as neccessary

// DO RECURSIVELY
void BPlusLeaf::remove(int k) {
    if (!contains(k)) {
        cout << " Key " << k << " is not present in leaf";
        return;
    }
    // 1. Remove key from target
    int *keys = getKeys();
    int index = indexOfKey(k);
    for (int i=index; i<getCount(); i++) {
        keys[i] = keys[i+1];
    }
    this->decrement();
    // 2. UNDERFLOW?
    int order = getOrder();
    if (getCount() >= order) {
        // 3. NO -> DONE
        return;
    }
    else {
        // 4. YES -> ROOT?
        // 5. YES -> Collapse root -> DONE
        if (getParent() == NULL) {
            return;
        }
        else {
            // 6. NO -> Check neighbors -> MINIMAL?
            // 7. NO -> Borrow from neighbor -> DONE
            if (prev) {
                if (getPrev()->getCount() > order) {
                
                    // Shift own keys and retrieve biggest key from previous
                    for (int i=1; i<=getCount(); i++) {
                        keys[i] = keys[i-1];
                    }
                    int *prevKeys = prev->getKeys();
                    int newKey = prevKeys[prev->getCount()-1];
                    keys[0] = newKey;
                    increment();
                    
                    // Decrement previous's keys
                    prev->decrement();
                    
                    // Update parent
                    int *parentKeys = getParent()->getKeys();
                    int parentIndex = getParent()->indexOfKey(k);
                    parentKeys[parentIndex] = newKey;
                }
        }
            else if (next) {
                if (getNext()->getCount() > order) {
                    
                    // Retrieve smallest key from next
                    increment();
                    int *nextKeys = next->getKeys();
                    int newKey = nextKeys[0];
                    keys[getCount()-1] = newKey;
                    
                    // Shift next's keys and decrement next's keys
                    for (int i=0; i < next->getCount()-2; i++) {
                        nextKeys[i] = nextKeys[i+1];
                    }
                    next->decrement();
                    
                    // Update parent
                    int *parentKeys = getParent()->getKeys();
                    int parentIndex = getParent()->indexOfKey(k);
                    parentKeys[parentIndex] = newKey; 
                }
            }
        }
    }
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