//  BloomFilterNode.hpp, Judith Greif
//  Description: Header for class BloomFilterNode

#ifndef BloomFilterNode_hpp
#define BloomFilterNode_hpp

#include <iostream>
#include <assert.h>
#include <math.h>
#include "BloomFilter.hpp"


class BloomFilterNode {
private:
    int n;                      // Current # of keys
    int filtersize;
    int t;                      // Order/minimum degree
    int *keys;                  // Array of keys
    BloomFilterNode *parent;
    
public:
    BloomFilter **filters;
    BloomFilter *unionfilter;    // Union of all filters in subtree of this node
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
    
    // Tree management
    virtual void traverse() = 0;
    virtual void traverseFilters() = 0;
    double computeAmbienceJaccard(BloomFilter *f1, BloomFilter *f2);
    float computeJaccard(BloomFilter *f1, BloomFilter *f2);
    double eUnion(BloomFilter *f1, BloomFilter *f2);
    double eIntersect(BloomFilter *f1, BloomFilter *f2);
    virtual void updateUnionFilter() = 0;
    virtual float computeMinJaccard(BloomFilter *filter) = 0;
    virtual int computeMinJaccardKey(BloomFilter *filter) = 0;
    virtual int getMinKey() = 0;
    virtual int getMaxKey() = 0;
    virtual vector<BloomFilter> collectAllFilters() = 0;
    virtual int computeSubsetId(BloomFilter *filter) = 0;
    virtual bool contains(int k) = 0;
    virtual BloomFilterNode *search(int k) = 0;
    virtual int computeSupersetId(BloomFilter *filter) = 0;
    
    // Insertion methods
    virtual void shiftAndInsert(BloomFilter *filter);
    virtual void insert(BloomFilter *filter, BloomFilterNode *oldNode, BloomFilterNode *newNode);
    virtual void insert(BloomFilter *filter) = 0;
    // virtual void insertAsSets(BloomFilter *filter) = 0;

    // Query methods
    // virtual BloomFilter *simpleSimQuery(BloomFilter *filter) = 0;
    // virtual BloomFilter *simQuery(BloomFilter *filter) = 0;
    // virtual vector<BloomFilter> simpleSimQueryVec(BloomFilter *filter, int k) = 0;
    // virtual vector<BloomFilter> simQueryVec(BloomFilter *filter, int k) = 0;
};

#endif 
