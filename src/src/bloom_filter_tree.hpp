//  bloom_filter_tree.hpp, Judith Greif
//  Description: Header for tree classes BTreeNode, BTree and BloomFilterTree
//  References: http://touc.org/btree.html
//              http://www.geeksforgeeks.org/b-tree-set-1-introduction-2/
//  B-Tree properties:
//  * Only logical nodes
//  * All leaves at same level
//  * IDs of physical nodes are stored in the leaves
//  * Defined by minimum degree t
//  * Every node except root must contain at least t-1 keys
//  * All nodes contain at most 2t-1 keys
//  * Every node has keys + 1 children
//  * Keys are sorted in increasing order
//  * Child between keys k1 and k2 contains all keys in range k1 - k2
//  * Grows and shrinks from root

#ifndef bloom_filter_tree_h
#define bloom_filter_tree_h

#include <iostream>
#include <stdio.h>
using namespace std;


class BTreeNode {
private:
    int *keys;          // Array of keys
    int t;              // Minimum degree
    BTreeNode **C;      // Array of child pointers
    int n;              // Current # of keys
    bool leaf;          // true if node is leaf, false otherwise
public:
    // Constructor
    BTreeNode(int _t, bool _leaf);
    
    // Traverse all nodes in a subtree rooted with this node
    void traverse();
    
    // Search a key in a subtree rooted with this node
    // Returns NULL if key is not present
    BTreeNode *search(int k);
    
    friend class BTree;
};


class BTree {
private:
    BTreeNode *root;    // Pointer to root node
    int t;              // Minimum degree
public:
    // Constructor
    // Initializes tree as empty
    BTree(int _t): t(_t), root(NULL) {};
    
    // Traverse tree
    void traverse() {
        if (root != NULL) {
            root->traverse();
        }
    };
    
    // Search key in tree
    // Return NULL if key is not present
    BTreeNode *search(int k) {
        if (root == NULL) {
            return NULL;
        }
        else {
            return root->search(k);
        }
        // return (root == NULL)? NULL : root->search(k);
    }
};


class BloomFilterTree {
    
};


// Constructor for class BTreeNode
BTreeNode::BTreeNode(int _t, bool _leaf): t(_t), leaf(_leaf), n(0) {

    // Allocate memory for maximum number of possible keys and child pointers
    keys = new int[2*t-1];
    C = new BTreeNode *[2*t];
}

// Traverse all nodes in subtree rooted with this node
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
    if (leaf == false) {
        C[i]->traverse();
    }
}

// Search key k in subtree rooted with this node
BTreeNode *BTreeNode::search(int k) {

    // Find first key greater than or equal to k
    int i=0;
    while (i<n && k>keys[i]) {
        i++;
    }
        
    // If the found key is equal to k, return this node
    if (keys[i] == k) {
        return this;
    }
        
    // If key is not found here and this is a leaf node
    if (leaf == true) {
        return NULL;
    }
    
    // Go to the appropriate child
    return C[i]->search(k);
}

#endif
