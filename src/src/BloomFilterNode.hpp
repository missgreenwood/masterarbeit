//  BloomFilterNode.hpp, Judith Greif
//  Description: Header for class BloomFilterNode

#ifndef BloomFilterNode_hpp
#define BloomFilterNode_hpp

#include <iostream>
#include <assert.h>
#include "BloomFilter.hpp"
#include "BloomFilterVec.hpp"


class BloomFilterNode {
    
private:
    int *keys;              // Array of keys
    int n;                  // Current # of keys
    BloomFilterNode *parent; 
    
protected:
    int t;                  // Order/minimum degree
    
public:
    BloomFilterNode(int _t);
    virtual ~BloomFilterNode();
    virtual void shiftAndInsert(int k);
    int getOrder();
    int getCount();
    void setCount(int count);
    BloomFilterNode *getParent();
    void setParent(BloomFilterNode *node);
    virtual void insert(int k) = 0;
    virtual void insertFilter(BloomFilter *filter) = 0;
    virtual BloomFilterNode *search(int k) = 0;
    virtual void insert(int k, BloomFilterNode *oldNode, BloomFilterNode *newNode);
    int indexOfKey(int k);
    int *getKeys();
    virtual void traverse() = 0;
    virtual void traverseFilters() = 0; 
    virtual bool contains(int k) = 0;
    int getMax();
    void increment();
    void decrement();
};

#endif 
