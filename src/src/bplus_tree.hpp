//  bplus_tree.hpp, Judith Greif
//  Description: Header for classes BPlusNode, BPlusIndexNode, BPlusLeaf, BPlusTree
//  Reference: https://github.com/JamesAn88/B-Tree/tree/master/B%2BTree

//  Difference to normal B-Tree:
//  * All keys are also stored in leaves

#ifndef bplus_tree_h
#define bplus_tree_h

#include <iostream>
// #include <assert.h>

using namespace std;

class BPlusNode {
private:
    int *keys;              // Array of keys
    int t;                  // Order
    BPlusNode *parent;
    int n;                  // Current # of keys
    
public:
    BPlusNode(int _t): t(_t), parent(0), n(0) {
        // Allocate memory for maximum number of possible keys
        keys = new int[t*2];
    }
    
    virtual ~BPlusNode() {
        delete parent;
        delete[] keys;
    };
    
    virtual void shiftAndInsert(int k);
    int getOrder();
    int getCount();
    void increment();
    void decrement();
    void setCount(int count);
    BPlusNode *getParent();
    void setParent(BPlusNode *child);
    virtual void insert(int k) = 0;
    virtual BPlusNode *search(int k) = 0;
    virtual void insert(int k, BPlusNode *oldNode, BPlusNode *newNode);
    int indexOfKey(int k);
    int *getKeys();
    virtual void traverse() = 0;
    int getMax();
    virtual void remove(int k) = 0;
    virtual BPlusNode *leftMost(int k);
};

class BPlusIndexNode {

};

class BPlusLeaf {

};

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

// Functions for class BPlusTree
void BPlusTree::traverse() {
    if (root != NULL) {
        root->traverse();
    }
}

BPlusNode * BPlusTree::search(int k) {
    if(root != NULL) {
        return root->search(k);
    }
    else {
        return NULL;
    }
}

void BPlusTree::insert(int k) {
    if (root == NULL) {
        // Allocate memory for root
        root = new BPlusLeaf(t, NULL, NULL);
        root->insert(k);
    }
    else {
        root->insert(k);
        if (root->getParent() != NULL) {
            root = root->getParent();
        }
    }
}

#endif
