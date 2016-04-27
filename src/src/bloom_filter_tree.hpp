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
    BTreeNode(int _t, bool _leaf): t(_t), leaf(_leaf), n(0) {
        
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


// B-Tree with constructor
class BTree {
    
private:
    BTreeNode *root;    // Pointer to root node
    int t;              // Minimum degree
    
public:
    // Constructor with parameter t
    // Initializes tree as empty
    BTree(int _t): t(_t), root(NULL) {};
    
    // Traverse tree
    void traverse();
    
    // Search key in tree
    // Return NULL if key is not present
    BTreeNode *search(int k);
    
    // Insert new key
    void insert(int k);
    
};


// BTree of Bloom filters
class BloomFilterTree {
    
};


// Functions of class BTreeNode
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


// Functions of class BTree
void BTree::traverse() {
    if (root != NULL) {
        root->traverse();
    }
}

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

#endif
