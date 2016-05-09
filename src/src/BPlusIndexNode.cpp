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
    int index = indexOfKey(k);
    if (C[index]->contains(k)) {
        return true;
    }
    else if (C[index+1] && keys[index+1]<=k) {
        return C[index+1]->contains(k);
    }
    return false;
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
    
    // Update count
    decrement();
    
    cout << "\nParent's new keys:";
    for (int i=0; i<getCount(); i++) {
        cout << " " << keys[i];
    }
    cout << endl;
    
    // 2. UNDERFLOW?
    int order = getOrder();
    int count = getCount();
    if (count >= order) {
        // 3. NO -> DONE
        cout << "Delete operation finished!" << endl;
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
            if((prev) && (getPrev()->getCount() > order)) {
                cout << "Borrowing key from previous index node";
                int *prevKeys = prev->getKeys();
                for (int i=1; i<=getCount(); i++) {
                    keys[i] = keys[i-1];
                }
                int newKey = prevKeys[prev->getCount()-1];
                keys[0] = newKey;
                int newParentKey = prevKeys[prev->getCount()-2];
                increment();
                prev->decrement();
                BPlusNode *parent = getParent();
                int *parentKeys = parent->getKeys();
                int index = 0;
                cout << "\nOld parent keys (index node):";
                for (int i=0; i<parent->getCount(); i++) {
                    cout << " " << parentKeys[i];
                }
                cout << endl;
                
                // get index in parent keys
                for (int i=0; i<-parent->getCount(); i++) {
                    if (parentKeys[i] > newKey) {
                        index=i;
                        break;
                    }
                }
                parentKeys[index] = newParentKey;
                cout << "\nNew parent keys (index node):";
                for (int i=0; i<parent->getCount(); i++) {
                    cout << " " << parentKeys[i];
                }
                cout << endl;
                return;
            }
        }
    }
}
    
    
    //
    // 8.                 YES -> Merge with neighbor
    // 9. Unwind to parent node
    // Continue steps 1. - 9. as long as neccessary


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