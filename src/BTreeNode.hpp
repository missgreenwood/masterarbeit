//  BTreeNode.hpp, Judith Greif
//  Description: Header for class BTreeNode

#ifndef BTreeNode_hpp
#define BTreeNode_hpp

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
    
    // Constructor with parameters minimum degree and leaf
    BTreeNode(int _t, bool _leaf);
    
    ~BTreeNode(); 
    
    // Function to traverse all nodes in a subtree rooted with this node
    void traverse();
    
    // Function to search key in a subtree rooted with this node
    // Returns NULL if key is not present
    BTreeNode *search(int k);
    
    // Function to insert new key in subtree rooted with this node
    // Node must be non-full when this function is called
    void insertNonFull(int k);
    
    // Function to split child y of this node
    // i is index of y in child array C[]
    // Child y must be full when this function is called
    void splitChild(int i, BTreeNode *y);
    
    // Functions for key deletion
    
    // Function to return index of first key >= k
    int findKey(int k);
    
    // Wrapper function to remove key k in subtree rooted with this node
    void remove(int k);
    
    // Function to remove the key present in idx-th position in leaf node
    void removeFromLeaf(int idx);
    
    // Function to remove key present in idx-th position from non-leaf node
    void removeFromNonLeaf(int idx);
    
    // Function to get predecessor of key present in idx-th position of node
    int getPred(int idx);
    
    // Function to get successor of key present in idx-th position of node
    int getSucc(int idx);
    
    // Function to fill up child node present in idx-th position of C[]-array of node if it has < t-1 keys
    void fill(int idx);
    
    // Function to borrow key from C[idx-1]-th node and place it in C[idx]-th node
    void borrowFromPrev(int idx);
    
    // Function to borrow key from C[idx+1]-th node and place it in C[idx]-th node
    void borrowFromNext(int idx);
    
    // Function to merge idx-th child of node with (idx+1)-th child
    void merge(int idx);
    
    friend class BTree;
    
};

#endif
