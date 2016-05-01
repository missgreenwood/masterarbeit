//  BTree.hpp, Judith Greif
//  Description: Header for class BTree
//  Reference: http://www.geeksforgeeks.org/
//  B-Tree properties:
//  * All leaves at same level
//  * Defined by minimum degree t
//  * Every node except root must contain at least t-1 keys
//  * All nodes contain at most 2t-1 keys
//  * Every node has keys+1 children
//  * Keys are sorted in increasing order
//  * Child between keys k1 and k2 contains all keys in range k1 - k2
//  * Grows and shrinks from root


#ifndef BTree_h
#define BTree_h

#include "BTreeNode.hpp"


class BTree {
    
private:
    BTreeNode *root;    // Pointer to root node
    int t;              // Minimum degree
    
public:
    BTree(int _t);
    ~BTree();
    
    // Traverse tree
    void traverse();
    
    // Search key in tree
    // Return NULL if key is not present
    BTreeNode *search(int k);
    
    // Insert new key
    void insert(int k);
    
    // Remove key
    void remove(int k);
    
};

// Functions of class BTreeNode


#endif
