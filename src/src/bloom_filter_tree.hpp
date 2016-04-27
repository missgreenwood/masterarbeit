//  bloom_filter_tree.hpp, Judith Greif
//  Description: Header for tree classes BTreeNode, BTree, BloomFilterTree
//  References: http://touc.org/btree.html
//              http://www.geeksforgeeks.org/
//  B-Tree properties:
//  * Only logical nodes
//  * All leaves at same level
//  * IDs of physical nodes are stored in the leaves
//  * Defined by minimum degree t
//  * Every node except root must contain at least t-1 keys
//  * All nodes contain at most 2t-1 keys
//  * Every node has keys+1 children
//  * Keys are sorted in increasing order
//  * Child between keys k1 and k2 contains all keys in range k1 - k2
//  * Grows and shrinks from root


#ifndef bloom_filter_tree_h
#define bloom_filter_tree_h

#include <iostream>

using namespace std;


// B-Tree-Node with constructors
class BTreeNode {
    
private:
    int *keys;          // Array of keys
    int t;              // Minimum degree
    BTreeNode **C;      // Array of child pointers
    int n;              // Current # of keys
    bool leaf;          // true if node is leaf, false otherwise

public:

    // Constructor with parameters t and leaf
    BTreeNode(int t, bool leaf): t(t), leaf(leaf), n(0) {
        
        // Allocate memory for maximum number of possible keys and child pointers
        keys = new int[2*t-1];
        C = new BTreeNode *[2*t];
    };
    
    // Traverse all nodes in a subtree rooted with this node
    void traverse();
    
    // Search a key in a subtree rooted with this node
    // Returns NULL if key is not present
    BTreeNode *search(int k);
    
    // Insert new key in subtree rooted with this node
    // Node must be non-full when this function is called
    void insertNonFull(int k);
    
    // Split child y of this node
    // i is index of y in child array C[]
    // Child y must be full when this function is called
    void splitChild(int i, BTreeNode *y);
    
    friend class BTree;
    
};


// B-Tree with constructors
class BTree {
    
private:
    BTreeNode *root;    // Pointer to root node
    int t;              // Minimum degree
    
public:
    // Default constructor with no parameters
    // Initializes tree as empty
    BTree(int _t): t(_t), root(NULL) {};
    
    // Traverse tree
    void traverse();
    
    // Search key in tree
    // Return NULL if key is not present
    BTreeNode *search(int k);
    
};


// BTree of Bloom filters
class BloomFilterTree {
    
};


// Functions of class BTreeNode
void BTreeNode::traverse() {
    
    // Node has n keys, n+1 children
    // Traverse through n keys und first n children
    int i;
    cout << "i before loop: " << i << endl;
    for (i=0; i<n; i++) {
        // If no leaf, before printing key[i] traverse subtree rooted with child C[i]
        if (leaf == false) {
            C[i]->traverse();
        }
        cout << " " << keys[i];
    }
    cout << "i after loop: " << i << endl;
    
    // Print subtree rooted with last child
    // i == n after for loop
    if (leaf == false) {
        C[i]->traverse();
    }
    cout << "i after loop: " << i << endl;
}

BTreeNode *BTreeNode::search(int k) {

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


// Functions of class BTree
void BTree::traverse() {
    if (root != NULL) {
        root->traverse();
    }
}

BTreeNode * BTree::search(int k) {
    if (root == NULL) {
        return NULL;
    }
    else {
        return root->search(k);
    }
}


#endif
