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
      
            // TODO
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
                
                // Insert my rightmost child's biggest key
                int newKey = C[getCount()]->getKeys()[0];
                keys[0] = newKey;
                
                // Decrement previous's keys
                prev->decrement();
                
                cout << "\nParent's new keys:";
                for (int i=0; i<parent->getCount(); i++) {
                    cout << " " << keys[i];
                }
                cout << endl;
                
                
                // AUSKOMMENTIEREN!
                return;
            }
            
            else if ((next) && next->getCount() > order) {
                cout << "Underflow in parent - borrowing key from next index node";
                int *nextKeys = next->getKeys();
                increment();
                
                // Retrieve smallest key from next
                int newKey = nextKeys[0];
                
            }
            // 8. YES -> Merge with neighbor
            // 9. Unwind to parent node
            // Continue steps 1. - 9. as long as neccessary
        
      
            return;
            
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