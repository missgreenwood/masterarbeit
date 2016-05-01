//  BTree.cpp, Judith Greif
//  Description: Implementation of class BTree

#include "BTree.hpp"

using namespace std; 

BTreeNode * BTree::search(int k) {
    // return (root == NULL)? NULL : root->search(k);
    if (root == NULL) {
        return NULL;
    }
    else {
        return root->search(k);
    }
}

void BTree::insert(int k) {
    
    // Check if tree is empty
    if (root == NULL) {
        
        // Allocate memory for root
        root = new BTreeNode(t, true);
        
        // Insert key
        root->keys[0] = k;
        
        // Update # of keys in root
        root->n = 1;
    }
    
    // If tree is not empty
    else {
        
        // If root is full, tree grows in height
        if (root->n == 2*t-1) {
            
            // Allocate new memory for root
            BTreeNode *s = new BTreeNode(t, false);
            
            // Turn old root into child of new root
            s->C[0] = root;
            
            // Split old root and move one key into new root
            s->splitChild(0, root);
            
            // New root has 2 children now
            // Decide which one is to hold new key
            int i=0;
            if (s->keys[0]<k) {
                i++;
            }
            s->C[i]->insertNonFull(k);
            
            // Change root
            root = s;
        }
        
        // If root is not full, call InsertNonFull for root
        else {
            root->insertNonFull(k);
        }
    }
}

void BTree::remove(int k) {
    if(!root) {
        cout << "The tree is empty" << endl;
        return;
    }
    
    // Call remove() for BTreeNode root
    root->remove(k);
    
    // Check if root has 0 keys
    if (root->n == 0) {
        BTreeNode *tmp = root;
        // If root has a child, make it the new root
        if (!root->leaf) {
            root = root->C[0];
        }
        // Otherwise set root to NULL
        else {
            root = NULL;
        }
        // Delete old root
        delete tmp;
    }
    return;
}

void BTree::traverse() {
    if (root != NULL) {
        root->traverse();
    }
}