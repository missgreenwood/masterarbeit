//  BTreeNode.cpp, Judith Greif
//  Description: Implementation of class BTreeNode

#include "BTreeNode.hpp"

using namespace std;

void BTreeNode::traverse() {
    
    // Node has n keys, n+1 children
    // Traverse through n keys und first n children
    int i;
    for (i=0; i<n; i++) {
        // If no leaf, before printing key[i] traverse subtree rooted with child C[i]
        if (leaf == false) {
            C[i]->traverse();
        }
        cout << " " << keys[i];
    }
    
    // Print subtree rooted with last child
    // i == n after for loop
    if (leaf == false) {
        C[i]->traverse();
    }
}

BTreeNode * BTreeNode::search(int k) {
    
    // Find first key >= k
    int i=0;
    // i < #keys in node && value < key
    while (i<n && k>keys[i]) {
        i++;
    }
    
    // i == child which is just before the first greater key
    
    // If the found key is equal to k, return this node
    if (keys[i] == k) {
        return this;
    }
    
    // If key is not found here and this is a leaf node
    if (leaf == true) {
        return NULL;
    }
    
    // Search child which is just before the first greater key
    return C[i]->search(k);
}

void BTreeNode::insertNonFull(int k) {
    
    // Initialize index as index of rightmost element
    int i=n-1;
    
    // If this is a leaf node
    if (leaf == true) {
        
        // Find location to insert new key
        // Shift all greater keys one place to the right
        while (i>=0 && keys[i]>k) {
            keys[i+1] = keys[i];
            i--;
        }
        
        // Insert new key at found location
        keys[i+1] = k;
        n++;
    }
    
    // If this is no leaf node
    else {
        
        // Find child which is to hold new key
        while (i>=0 && keys[i]>k) {
            i--;
        }
        
        // Check if found child is full
        if (C[i+1]->n == 2*t-1) {
            // If child is full, split it
            splitChild(i+1, C[i+1]);
            
            // After split, the middle key of C[i] goes up and C[i] is splitted
            // Decide which part of C[i] is to hold new key
            if (keys[i+1]<k) {
                i++;
            }
        }
        C[i+1]->insertNonFull(k);
        
    }
}

void BTreeNode::splitChild(int i, BTreeNode *y) {
    
    // y is full, i.e. holds 2t-1
    // Create new node to store (t-1) keys of y
    BTreeNode *z = new BTreeNode(y->t, y->leaf);
    z->n = t-1;
    
    // Copy the last t-1 keys of y to z
    for (int j=0; j<t-1; j++) {
        z->keys[j] = y->keys[j+t];
    }
    
    // Check if y is leaf
    // If not, copy the last t-1 children of y to z
    if (y->leaf == false) {
        for (int j=0; j<t; j++) {
            z->C[j] = y->C[j+t];
        }
    }
    
    // Update # of keys in y
    y->n = t-1;
    
    // Create space for new child z
    // i is index of y in child array C[]
    for (int j=n; j>=i+1; j--) {
        C[j+1] = C[j];
    }
    
    // Link new child to this node
    C[i+1] = z;
    
    // Find location to insert middle key of y
    // Shift all greater keys one place to the right
    // n is current # of keys
    // i is index of y in child array C[]
    for (int j=n-1; j>=i; j--) {
        keys[j+1] = keys[j];
    }
    
    // Copy middle key of y to found location
    keys[i] = y->keys[t-1];
    
    // Increment # of keys
    n++;
}

int BTreeNode::findKey(int k) {
    int idx = 0;
    while (idx<n && keys[idx] < k) {
        idx++;
    }
    return idx;
}

void BTreeNode::remove(int k) {
    int idx = findKey(k);
    
    // The key to remove is present in this node
    if (idx<n && keys[idx] == k) {
        
        // If leafnode, call removeFromLeaf()
        if (leaf) {
            removeFromLeaf(idx);
        }
        // Otherwise call removeFromNonLeaf()
        else {
            removeFromNonLeaf(idx);
        }
    }
    else {
        
        // If leafnode, key k is not present in tree
        if (leaf) {
            cout << "The key " << k << " is not present in the tree" << endl;
            return;
        }
        
        // Key k is present in subtree rooted with this node
        // flag indicates whether k is present in subtree rooted with last child
        bool flag = ((idx==n)? true : false);
        
        // If the child that is supposed to hold k has less than t keys, fill it
        if (C[idx]->n < t) {
            fill(idx);
        }
        
        // If last child has been merged, it must have been merged with previous child -> recurse on (idx-1)-th child
        // Else recurse on idx-th child which now has at least t keys
        if (flag && idx > n) {
            C[idx-1]->remove(k);
        }
        else {
            C[idx]->remove(k);
        }
    }
    return;
}

void BTreeNode::removeFromLeaf(int idx) {
    
    // Shift all keys after idx-th position one place backward
    for (int i=idx+1; i<n; ++i) {
        keys[i-1] = keys[i];
    }
    // Update # of keys
    n--;
    return;
}

void BTreeNode::removeFromNonLeaf(int idx) {
    int k = keys[idx];
    
    // If the child C[idx] that precedes k has at least t keys
    if (C[idx]->n >= t) {
        // Find predecessor of k in the subtree rooted at C[idx]
        int pred = getPred(idx);
        // Replace k by pred
        keys[idx] = pred;
        // Recursively delete pred in C[idx]
        C[idx]->remove(pred);
    }
    
    // C[idx] has less than t keys -> examine C[idx+1]
    // If C[idx+1] has at least t keys
    else if (C[idx+1]->n >= t) {
        // Find successor of k in the subtree rooted at C[idx+1]
        int succ = getSucc(idx);
        // Replace k by succ
        keys[idx] = succ;
        // Recursicely delete succ in C[idx+1]
        C[idx+1]->remove(succ);
    }
    
    // Both C[idx] and C[idx+1] have less than t keys -> merge k and all of C[idx+1] into C[idx]
    else {
        merge(idx);
        // C[idx] has now 2t-1 keys
        // Free C[idx+1] and recursively delete k from C[idx]
        C[idx]->remove(k);
    }
    return;
}

int BTreeNode::getPred(int idx) {
    
    // Keep moving towards rightmost node until leaf is found
    BTreeNode *curr = C[idx];
    while(!curr->leaf) {
        curr = curr->C[curr->n];
    }
    
    // Return last key of the leaf
    return curr->keys[curr->n-1];
}

int BTreeNode::getSucc(int idx) {
    
    // Keep moving towards leftmost node starting from C[idx+1] until leaf is found
    BTreeNode *curr = C[idx+1];
    while (!curr->leaf) {
        curr = curr->C[0];
    }
    
    // Return first key of the leaf
    return curr->keys[0];
}

void BTreeNode::fill(int idx) {
    
    // If previous child C[idx-1] has more than t-1 keys -> borrow key
    if (idx!=0 && C[idx-1]->n >= t) {
        borrowFromPrev(idx);
    }
    
    // C[idx-1] has t-1 keys -> examine C[idx+1]
    else if (idx!=n && C[idx+1]->n >= t) {
        borrowFromNext(idx);
    }
    
    // Both siblings have only t keys
    else {
        // If this is the last node, merge it with previous sibling
        if (idx != n) {
            merge(idx);
        }
        // Otherwise merge this node with next sibling
        else {
            merge(idx-1);
        }
    }
    return;
}

void BTreeNode::borrowFromPrev(int idx) {
    BTreeNode *child = C[idx];  // child = C[idx]
    BTreeNode *sibling = C[idx-1];  // sibling = C[idx-1]
    
    // The last key from silbling goes up to the parent
    // keys[idx-1] from parent is inserted as first key in child
    
    // Shift all keys in child one position to the right
    for (int i=child->n-1; i>=0; --i) {
        child->keys[i+1] = child->keys[i];
    }
    
    // If child is no leaf, shift all of its child pointers one position to the right
    if(!child->leaf) {
        for(int i=child->n; i>=0; --i) {
            child->C[i+1] = child->C[i];
        }
    }
    
    // Set child's first key equal to keys[idx-1] from parent
    child->keys[0] = keys[idx-1];
    
    // Sibling's last child becomes child's first child
    if (!leaf) {
        child->C[0] = sibling->C[sibling->n];
    }
    
    // Move key from sibling to parent
    keys[idx-1] = sibling->keys[sibling->n-1];
    
    // Update # of keys in sibling and child
    sibling->n--;
    child->n++;
    return;
}

void BTreeNode::borrowFromNext(int idx) {
    BTreeNode *child = C[idx];  // child = C[idx]
    BTreeNode *sibling = C[idx+1];  // sibling = C[idx+1]
    
    // The first key from sibling goes up to the parent
    // keys[idx] from parent is inserted as last key in child
    
    // Set child's last key equal to keys[idx] from parent
    child->keys[(child->n)] = keys[idx];
    
    // Sibling's first child becomes child's last child
    if(!(child->leaf)) {
        child->C[(child->n)+1] = sibling->C[0];
    }
    
    // Move key from sibling to parent
    keys[idx] = sibling->keys[0];
    
    // Shift all keys in sibling one position to the left
    for (int i=1; i<sibling->n; ++i) {
        sibling->keys[i-1] = sibling->keys[i];
    }
    
    // If sibling is no leaf, shift all of its child pointers one position to the left
    if(!sibling->leaf) {
        for (int i=1; i<=sibling->n; ++i) {
            sibling->C[i-1] = sibling->C[i];
        }
    }
    
    // Update # of keys in sibling and child
    sibling->n--;
    child->n++;
    return;
}

void BTreeNode::merge(int idx) {
    BTreeNode *child = C[idx];  // child = C[idx]
    BTreeNode *sibling = C[idx+1];   // next sibling = C[idx+1]
    
    // Merge next sibling into child
    // Retrieve key from parent and insert it into (t-1)-th position of child
    child->keys[t-1] = keys[idx];
    
    // Move keys from sibling to child
    for (int i=0; i<sibling->n; ++i) {
        child->keys[t+i] = sibling->keys[i];
    }
    
    if(!child->leaf) {
        for (int i=0; i<=sibling->n; ++i) {
            child->C[i+t] = sibling->C[i];
        }
    }
    
    // Shift all keys in parent after idx one position to the left
    for (int i=idx+1; i<n; ++i) {
        keys[i-1] = keys[i];
    }
    
    // Shift all child pointers in parents after idx one position to the left
    for (int i=idx+2; i<=n; ++i) {
        C[i-1] = C[i];
    }
    
    // Update # of keys in parent and child
    n--;
    child->n += sibling->n+1;
    
    // Delete sibling after merge
    delete sibling;
    return;
}
