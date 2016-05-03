//  BPlusNode.hpp, Judith Greif
//  Description: Header for class BPlusNode

#ifndef BPlusNode_hpp
#define BPlusNode_hpp

#include <iostream>
#include <assert.h>


class BPlusNode {
private:
    int *keys;              // Array of keys
    int t;                  // Order
    BPlusNode *parent;
    int n;                  // Current # of keys
    
public:
    BPlusNode(int _t);
    virtual ~BPlusNode();
    virtual void shiftAndInsert(int k);
    int getOrder();
    int getCount();
    void setCount(int count);
    BPlusNode *getParent();
    void setParent(BPlusNode *node);
    virtual void insert(int k) = 0;
    virtual BPlusNode *search(int k) = 0;
    virtual void insert(int k, BPlusNode *oldNode, BPlusNode *newNode);
    int indexOfKey(int k);
    int *getKeys();
    virtual void traverse() = 0;
    int getMax();
    virtual void remove(int k) = 0;
    virtual BPlusNode *leftMost(int k);
    void increment();
    void decrement();
};

#endif
