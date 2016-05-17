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
    int size; 
    
protected:
    int t;                  // Order/minimum degree
    
public:
    BloomFilterNode(int _t, int _s);
    virtual ~BloomFilterNode();
    int getOrder();
    int getCount();
    void setCount(int count);
    BloomFilterNode *getParent();
    void setParent(BloomFilterNode *node);
    virtual BloomFilterNode *search(int k) = 0;
    
    // Insertion methods
    virtual void shiftAndInsert(BloomFilter *filter);
    virtual void insert(BloomFilter *filter) = 0;
    virtual void insert(BloomFilter *filter, BloomFilterNode *oldNode, BloomFilterNode *newNode);
    virtual void insertSimilarFilter(BloomFilter *filter);

    int indexOfKey(int k);
    int *getKeys();
    virtual void traverse() = 0;
    virtual void traverseFilters() = 0; 
    virtual bool contains(int k) = 0;
    virtual int **getFilters() = 0; 
    int getMax();
    void increment();
    void decrement();
    int getFilterSize();
    
    // Helper methods for tree management
    float computeJaccard(int *arr1, int *arr2);
    bool isSubset(int *arr1, int *arr2);
    int *logicalAnd(int *arr1, int *arr2);
    int *logicalOr(int *arr1, int *arr2);
};

#endif 
