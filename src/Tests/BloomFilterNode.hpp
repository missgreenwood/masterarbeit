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
    int n;                  // Current # of keys
    int filtersize;
    int t;                  // Order/minimum degree
    int *keys;              // Array of keys
    BloomFilterNode *parent;
    
public:
    BloomFilter **filters;
    BloomFilterNode(int _t, int _s);
    virtual ~BloomFilterNode();
    
    int getOrder();
    int getCount();
    void setCount(int count);
    BloomFilterNode *getParent();
    void setParent(BloomFilterNode *node);
    int indexOfKey(int k);
    int *getKeys();
    int getMax();
    void increment();
    void decrement();
    int getFilterSize();
    
    virtual void traverse() = 0;
    virtual void traverseFilters() = 0;
    virtual bool contains(int k) = 0;
    virtual BloomFilterNode *search(int k) = 0;
    
    // Insertion methods
    virtual void shiftAndInsert(BloomFilter *filter);
    virtual void insert(BloomFilter *filter, BloomFilterNode *oldNode, BloomFilterNode *newNode);
    virtual void insert(BloomFilter *filter) = 0;

    // Helper methods for tree management
    float computeJaccard(BloomFilter *f1, BloomFilter *f2);
    bool isSubset(BloomFilter *f1, BloomFilter *f2);
    BloomFilter *logicalAnd(BloomFilter *f1, BloomFilter *f2);
    BloomFilter *logicalOr(BloomFilter *f1, BloomFilter *f2);
};

#endif 