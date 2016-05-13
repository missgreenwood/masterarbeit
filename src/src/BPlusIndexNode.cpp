//  BPlusIndexNode.cpp, Judith Greif
//  Description: Implementation of class BPlusIndexNode

#include "BPlusIndexNode.hpp"

using namespace std;


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

BPlusNode * BPlusIndexNode::searchRemoveIndex(int k) {
    int ridx = removeIndex(k);
    return C[ridx]->searchRemoveIndex(k);
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
        
        // Set new sibling pointers
        if (keys[0] < s->getKeys()[0]) {
            s->setPrev(this);
            if (next) {
                s->setNext(next);
                next->setPrev(this);
            }
            setNext(s);
        }
        else {
            s->setNext(this);
            if (prev) {
                s->setPrev(prev);
                prev->setNext(s);
            }
            setPrev(s);            
        }
    }
}

bool BPlusIndexNode::contains(int k) {
    int i=0;
    while (keys[i]<k && i<getCount()-1) {
        i++;
    }
    
    if (k<keys[i]) {
        return C[i]->contains(k);
    }
    else if (k>=keys[i] && (C[i+1])) {
        return C[i+1]->contains(k);
    }
    else return false; 
}

void BPlusIndexNode::remove(int k) {
    
    // 1. Remove key from target
    // Shift keys in parent and delete k
    int index=0;
    for (int i=0; i<getCount(); i++) {
        if (keys[i] == k) {
            index=i;
            break;
        }
    }
    cout << "\nParent's old keys:";
    for (int i=0; i<getCount(); i++) {
        cout << " " << keys[i];
    }
    for (int i=index; i<getCount(); i++) {
        keys[i] = keys[i+1];
    }
    
    // Shift child pointers and delete dangeling child pointer
    int childPointer=index+1;
    for (int i=childPointer; i<getCount()+1; i++) {
        C[i] = C[i+1];
    }
    
    BPlusNode *parent = getParent();
    int order = getOrder();
    int count;
    int min;
    if (!parent) {
        min = 1;
    }
    else {
        min = order;
    }
    
    // NON ROOT
    if (min>1) {
        decrement();
        count = getCount();
        order = 1;
        
        // NO UNDERFLOW
        if (count >= order) {
            cout << "\nParent's new keys:";
            for (int i=0; i<getCount(); i++) {
                cout << " " << keys[i];
            }
            return;
        }
        
        // UNDERFLOW
        else {
            
            // 6. Check neighbors -> MINIMAL?
            // 7. NO -> Borrow from neighbor -> DONE
            if ((prev) && (prev->getCount() > order)) {
                cout << "\nUnderflow in parent - borrowing child from previous index node";
                increment();
                
                // Shift own children and get previous's rightmost child
                for (int i=getCount(); i>0; i--) {
                    C[i] = C[i-1];
                }
                C[0] = prev->C[prev->getCount()];
                
                // Insert my rightmost child's smallest key
                int newKey = C[getCount()]->getKeys()[0];
                keys[0] = newKey;
                
                // Update previous
                prev->decrement();
                
                cout << "\nParent's new keys:";
                for (int i=0; i<getCount(); i++) {
                    cout << " " << keys[i];
                }
                return;
            }
            else if ((next) && next->getCount() > order) {
                cout << "\nUnderflow in parent - borrowing key from next index node";
                int *nextKeys = next->getKeys();
                increment();
                
                // Get next's leftmost child
                C[getCount()] = next->C[0];
                
                // Backshift next's children
                for (int i=0; i<next->getCount(); i++) {
                    next->C[i] = next->C[i+1];
                }
                
                // Insert next's rightmost child's smallest key
                int newKey = next->C[getCount()]->getKeys()[0];
                nextKeys[0] = newKey;
                
                // Update next
                next->decrement();
                
                cout << "\nParent's new keys:";
                for (int i=0; i<getCount(); i++) {
                    cout << " " << keys[i];
                }
                return;
                
            }
            else {
                
                // TODO (traverse() not working)
                // 8. YES -> Merge with neighbor
                cout << "\nBoth siblings are minimal - ";
                if (prev) {
                    
                    // Merge own keys into prev and update previous's counter
                    cout << "merge with previous" << endl;
                    int *prevKeys = prev->getKeys();
                    int prevCount = prev->getCount();
                    cout << "Parent's previous's old keys:";
                    for (int i=0; i<prevCount; i++) {
                        cout << " " << prevKeys[i];
                    }
                    
                    // Increment self to retain children (THIS IS A HACK)
                    increment();
                    
                    // Retrieve my child's smallest key and insert into previous
                    int newKey = C[0]->getKeys()[0];
                    prev->increment();
                    prevKeys[prev->getCount()-1] = newKey;
                    
                    // Hand child over to previous
                    prev->C[prev->getCount()] = C[0];
                    prev->C[prev->getCount()]->setParent(this);
                    
                    cout << "\nParent's previous's new keys:";
                    for (int i=0; i<prev->getCount(); i++) {
                        cout << " " << prevKeys[i];
                    }
                    
                    // Update sibling pointers
                    if (next) {
                        next->setPrev(prev);
                        prev->setNext(next);
                    }
                    else {
                        prev->setNext(NULL);
                    }
                    
                    // 9. Unwind to parent node
                    parent->remove(k);
                }
                else if (next) {
                    
                    // TODO (traverse() not working)
                    // Merge next's keys into into own and update own counter
                    cout << "merge with next" << endl;
                    cout << "Parent's old keys: ";
                    for (int i=0; i<getCount(); i++) {
                        cout << " " << keys[i];
                    }
                    
                    // Retrieve next's children's smallest keys and insert into self
                    int newKey = next->C[0]->getKeys()[0];
                    int nextKey = next->C[next->getCount()]->getKeys()[0];
                    // cout << "\nNew key: " << newKey;
                    // cout << "\nNext key: " << nextKey;
                    keys[0] = newKey;
                    keys[1] = nextKey;
                    
                    // Increment self and next to retain children (THIS IS A HACK)
                    increment();
                    next->increment();
                    
                    // Retrieve next's children
                    for (int i=0; i<next->getCount(); i++) {
                        increment();
                        C[i+1] = next->C[i];
                        C[i+1]->setParent(this);
                    }
                    
                    // Update sibling pointers
                    if (next->next) {
                        next->next->setPrev(this);
                        setNext(next->next);
                    }
                    else {
                        setNext(NULL);
                    }
                    
                    cout << "\nParent's new keys: ";
                    for (int i=0; i<getCount()-1; i++) {
                        cout << " " << keys[i];
                    }
                    
                    // 9. Unwind to parent node
                    parent->remove(k);
                }
            }
            // return;
        }
    }
    
    // ROOT
    else if (min==1) {
        count = getCount()-1;
        
        // NO UNDERFLOW -> DONE
        if (count >= min) {
            decrement();
            cout << "\nParent's new keys:";
            for (int i=0; i<getCount(); i++) {
                cout << " " << keys[i];
            }
            return;
        }
        
        // UNDERFLOW
        else {
            
            // TODO (tree traversal not working)
            // COLLAPSE ROOT -> DONE
            decrement();
            cout << "\nParent's new keys:";
            for (int i=0; i<getCount(); i++) {
                cout << " " << keys[i];
            }
            return;
        }
    }
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