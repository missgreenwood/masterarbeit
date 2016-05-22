//  BPlusNode.hpp, Judith Greif
//  Description: Header for class BPlusNode

#ifndef BPlusNode_hpp
#define BPlusNode_hpp

#include <iostream>
#include <assert.h>


class BPlusNode {
private:
    int t;                  // Order/minimum degree
    BPlusNode *parent;
    int n;                  // Current # of keys
    
public:
    BPlusNode *next;
    BPlusNode *prev;
    BPlusNode **C;          // Array of children
    int *keys;              // Array of keys
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
    virtual BPlusNode *searchRemoveIndex(int k) = 0; 
    
    virtual void insert(int k, BPlusNode *oldNode, BPlusNode *newNode);
    
    int indexOfKey(int k);
    int *getKeys();
    virtual void traverse() = 0;
    virtual bool contains(int k) = 0;
    int getMax();
    virtual void remove(int k) = 0;
    void increment();
    void decrement();
    int removeIndex(int k);
    BPlusNode *getPrev();
    BPlusNode *getNext();
    void setPrev(BPlusNode *prev);
    void setNext(BPlusNode *next);
};

#endif
