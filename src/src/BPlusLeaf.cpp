//  BPlusLeaf.cpp, Judith Greif
//  Description: Implementation of class BPlusLeaf

#include "BPlusLeaf.hpp"

using namespace std;


BPlusLeaf::BPlusLeaf(int _t) : BPlusNode(_t) {};

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
        BPlusLeaf *l = split(k);
        l->setPrev(this);
        setNext(l);
        BPlusNode *p = getParent();
        if (p == NULL) {
            p = new BPlusIndexNode(getOrder());
            setParent(p);
        }
        l->setParent(p);
        p->insert(l->getKeys()[0], this, l);
    }
}

void BPlusLeaf::remove(int k) {
    if (!contains(k)) {
        cout << " Key " << k << " not present in leaf ";
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
    int count = getCount();
    if (count >= order) {
        // 3. NO -> DONE
        // cout << "No underflow!";
        return;
    }
    else {
        // 4. YES -> ROOT?
        // 5. YES -> Collapse root -> DONE
        if (getParent() == NULL) {
            // cout << "This is root!";
            return;
        }
        else {
            // 6. NO -> Check neighbors -> MINIMAL?
            // 7. NO -> Borrow from neighbor -> DONE
            if (prev) {
                /* if (getPrev()->getCount() > order) {
                    
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
                } */
            }
            else {
                cout << "No previous sibling!";
            }
            /* else if (next) {
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
            } */
        } 
    } 
    return; 
}

// 8. YES -> Merge with neighbor
// 9. Unwind to parent node
// Continue steps 1. - 9. as long as neccessary

BPlusNode * BPlusLeaf::search(int k) {
    return this;
}

BPlusLeaf * BPlusLeaf::split(int k) {
    assert(getCount() == getMax());
    int *keys = getKeys();
    int max = getMax();
    int *merged = new int[max+1];
    int index = indexOfKey(k);
    for (int i=0; i<index; i++) {
        merged[i] = keys[i];
    }
    merged[index] = k;
    for (int i=index+1; i<max+1; i++) {
        merged[i] = keys[i-1];
    }
    BPlusLeaf *l = new BPlusLeaf(getOrder());
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
    delete[] merged;
    return l;
}

void BPlusLeaf::traverse() {
    assert(getCount() <= getMax());
    int *keys = getKeys();
    cout << "| ";
    for (int i=0; i<getCount(); i++) {
        cout << keys[i] << " ";
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
