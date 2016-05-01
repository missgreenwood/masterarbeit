//  BPlusTree.hpp, Judith Greif
//  Description: Header for class BPlusTree
//  Reference: https://github.com/JamesAn88/B-Tree/tree/master/B%2BTree

//  Difference to normal B-Tree:
//  * All keys are also stored in leaves

#ifndef BPlusTree_h
#define BPlusTree_h

#include "BPlusNode.hpp"
#include "BPlusNode.hpp"
#include "BPlusIndexNode.hpp"
#include "BPlusLeaf.hpp"

using namespace std;


class BPlusTree {
private:
    BPlusNode *root;
    int t;                  // Minimum degree
    
public:
    // Constructor with parameter t
    // Initializes tree as empty
    BPlusTree(int _t): t(_t), root(NULL) {};
    
    ~BPlusTree() {
        delete root;
    }
    
    void traverse();
    
    // Search key in tree
    // Return NULL if key is not present
    // Return leaf node if key is present
    BPlusNode *search(int k);
    void insert(int k);
    void remove(int k);
    
    friend class BPlusNode;
    friend class BPlusIndexNode;
    friend class BPlusLeaf;
};

#endif
