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
    BloomFilter *unionfilter;    // Set union of all filters in subtree of this node
    BloomFilterNode(int _t, int _s);
    virtual ~BloomFilterNode();
    
    int getOrder();
    int getCount();
    void setCount(int count);
    BloomFilterNode *getParent();
    void setParent(BloomFilterNode *node);
    int *getKeys();
    int getMax();
    int getFilterSize();
    
    int indexOfKey(int k);
    void increment();
    void decrement();
    
    // Tree management
    virtual void traverse() = 0;
    virtual void traverseFilters() = 0;
    virtual double computeMinJaccard(BloomFilter *filter) = 0;
    virtual double computeMaxJaccard(BloomFilter *filter) = 0;
    virtual int getMinJaccardKey(BloomFilter *filter) = 0;
    double computeJaccard(BloomFilter *f1, BloomFilter *f2);
    double computeAmbienceJaccard(BloomFilter *f1, BloomFilter *f2);
    double eUnion(BloomFilter *f1, BloomFilter *f2);
    double eIntersect(BloomFilter *f1, BloomFilter *f2);
    virtual void updateUnionFilter() = 0;
    virtual BloomFilter *getMinJaccardFilter(BloomFilter *filter) = 0;
    virtual int getMinKey() = 0;
    virtual int getMaxKey() = 0;
    virtual vector<BloomFilter> collectAllFilters() = 0;
    virtual int countFilters() = 0; 
    virtual int computeSubsetId(BloomFilter *filter) = 0;
    virtual int computeSupersetId(BloomFilter *filter) = 0;
    virtual bool contains(int k) = 0;
    virtual BloomFilterNode *search(int k) = 0;
    virtual int countUnionFilters() = 0;
    virtual int countComparisons(BloomFilter *filter) = 0;
    virtual int allComparisons(BloomFilter *filter, int l) = 0;
    virtual int countVecComparisons(BloomFilter *filter, int k) = 0;
    virtual int allVecComparisons(BloomFilter *filter, int k, int l) = 0;
    
    // Insertion
    virtual void shiftAndInsert(BloomFilter *filter);
    virtual void insert(BloomFilter *filter, BloomFilterNode *oldNode, BloomFilterNode *newNode);
    virtual void insert(BloomFilter *filter) = 0;
    virtual void insertAsSets(BloomFilter *filter);
    
    // Similarity queries
    virtual BloomFilter *simQuery(BloomFilter *filter) = 0;
    virtual BloomFilter *simSubtreeQuery(BloomFilter *filter, int l) = 0;
    virtual vector<BloomFilter*> simQueryVec(BloomFilter *filter, int k) = 0;
    virtual vector<BloomFilter*> simSubtreeQueryVec(BloomFilter *filter, int k, int l) = 0; 
};

#endif 
