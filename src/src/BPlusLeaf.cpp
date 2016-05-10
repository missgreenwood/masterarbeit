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
        cout << "Key " << k << " not present in leaf ";
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
            if ((prev) && (getPrev()->getCount() > order)) {
                cout << "Borrowing key from previous sibling";
                int *prevKeys = prev->getKeys();
                
                // Shift own keys and retrieve biggest key from previous
                for (int i=1; i<=getCount(); i++) {
                    keys[i] = keys[i-1];
                }
                int newKey = prevKeys[prev->getCount()-1];
                keys[0] = newKey;
                increment();
                
                // Decrement previous's keys
                prev->decrement();
                
                // Update parent
                BPlusNode *parent = getParent();
                int *parentKeys = parent->getKeys();
                int index=0;
                cout << "\nParent's old keys:";
                for (int i=0; i<parent->getCount(); i++) {
                    cout << " " << parentKeys[i];
                }
                cout << endl;
                for (int i=0; i<parent->getCount(); i++) {
                    if (parentKeys[i] == k) {
                        index=i;
                        break;
                    }
                }
                parentKeys[index] = newKey;
                cout << "Parent's new keys:";
                for (int i=0; i<parent->getCount(); i++) {
                    cout << " " << parentKeys[i];
                }
                cout << endl;
                return;
            }
            else if ((next) && (getNext()->getCount() > order)) {
                cout << "Previous sibling has only minimal keys - borrowing key from next sibling";
                int *nextKeys = next->getKeys();
                
                // Retrieve smallest key from next
                increment();
                int newKey = nextKeys[0];
                int newParentKey = nextKeys[1];
                keys[getCount()-1] = newKey;
                
                // Shift next's keys and decrement next's keys
                for (int i=0; i < next->getCount(); i++) {
                    nextKeys[i] = nextKeys[i+1];
                }
                
                next->decrement();
                
                // Update parent
                BPlusNode *parent = getParent();
                int *parentKeys = parent->getKeys();
                int index = 0;
                cout << "\nParent's old keys:";
                for (int i=0; i<parent->getCount(); i++) {
                    cout << " " << parentKeys[i]; 
                }
                cout << endl;
                for (int i=0; i<parent->getCount(); i++) {
                    if (parentKeys[i] == newKey) {
                        index=i;
                        break;
                    }
                }
                parentKeys[index] = newParentKey;
                cout << "Parent's new keys:";
                for (int i=0; i<parent->getCount(); i++) {
                    cout << " " << parentKeys[i];
                }
                cout << endl;
                return;
            }
            else {
                // 8. YES -> Merge with neighbor
                cout << "Both siblings are minimal - ";
                
                if (prev) {
                    
                    // Merge own keys into prev and update previous's counter
                    cout << "merge with previous" << endl;
                    BPlusNode *prev = getPrev();
                    int *prevKeys = prev->getKeys();
                    cout << "\nPrevious's old keys:";
                    int prevCount = prev->getCount();
                    for (int i=0; i<prevCount; i++) {
                        cout << " " << prevKeys[i];
                    }
                    for (int i=0; i<getCount(); i++) {
                        prevKeys[prevCount+i] = keys[i];
                        prev->increment();
                    }
                    cout << "\nPrevious's new keys:";
                    for (int i=0; i<prev->getCount(); i++) {
                        cout << " " << prevKeys[i];
                    }
                    
                    // Update sibling pointer
                    prev->setNext(getNext());
                    
                    // 9. Unwind to parent node
                    BPlusNode *parent = getParent();
                    parent->remove(k);
                }
                else if (next) {
                    
                    // Merge next's keys into own and update own counter
                    
                    cout << "merge with next" << endl;
                    BPlusNode *next = getNext();
                    int *nextKeys = next->getKeys();
                    cout << "My old keys:";
                    int nextCount = next->getCount();
                    for (int i=0; i<getCount(); i++) {
                        cout << " " << keys[i];
                    }
                    
                    // Merge next's keys into own
                    for (int i=getCount(); i<nextCount+1; i++) {
                        keys[i] = nextKeys[i-1];
                    }
                    cout << "\nMy new keys:";
                    
                    // Increment counter
                    for (int i=0; i<nextCount; i++) {
                        increment();
                    }
                    for (int i=0; i<getCount(); i++) {
                        cout << " " << keys[i];
                    }
                    cout << endl;
                    
                    // Update sibling pointer
                    setNext(next->getNext());
                    
                    // 9. Unwind to parent node
                    getParent()->remove(k);
                }
            }
        }
    }
    return; 
}

// Continue steps 1. - 9. as long as neccessary

BPlusNode * BPlusLeaf::search(int k) {
    return this;
}

BPlusNode * BPlusLeaf::searchRemoveIndex(int k) {
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
    
    // BPlusNode *next = getNext();
    // BPlusNode *prev = getPrev();
    
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
