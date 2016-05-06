//  BPlusTree.hpp, Judith Greif
//  Description: Header for class BPlusTree
//  Reference: https://github.com/JamesAn88/B-Tree/tree/master/B%2BTree

//  B+-Tree properties (same as B-Tree):
//  * All leaves at same level
//  * Defined by minimum degree t
//  * All nodes contain at most 2t-1 keys (maximum degree)
//  * Every node has keys+1 children
//  * Keys are sorted in increasing order
//  * Grows and shrinks from root

//  B+-Tree properties (different from B-Tree):
//  * Every node except root must contain at least t keys
//  * Child between keys k1 and k2 contains all keys >= k1 and < k2
//  * All keys are also stored in leaves

#ifndef BPlusTree_h
#define BPlusTree_h

#include "BPlusNode.hpp"
#include "BPlusIndexNode.hpp"
#include "BPlusLeaf.hpp"

using namespace std;


class BPlusTree {
private:
    BPlusNode *root;        // Pointer to root node
    int t;                  // Order = minimum degree
    
public:
    BPlusTree(int _t);
    ~BPlusTree();
    
    void traverse();
    
    // Return leaf node to place k in
    BPlusNode *search(int k);
    
    void insert(int k);
    void remove(int k);
    
    // Search key in tree
    // Return false if key is not present
    bool contains(int k);
    
    friend class BPlusNode;
    friend class BPlusIndexNode;
    friend class BPlusLeaf;
};

#endif
