//  BloomFilterIndexNode.hpp, Judith Greif
//  Description: Header for class BloomFilterIndexNode

#ifndef BloomFilterIndexNode_hpp
#define BloomFilterIndexNode_hpp

#include <iostream>
#include "BloomFilterNode.hpp"


class BloomFilterIndexNode : public BloomFilterNode {
private:
    BloomFilterNode **C;
    
public:
    BloomFilterIndexNode(int _t, int _s);
    ~BloomFilterIndexNode();
    
    // Tree management
    void traverse();
    void traverseFilters();
    double computeMinJaccard(BloomFilter *filter);
    int getMinJaccardKey(BloomFilter *filter);
    void updateUnionFilter();
    BloomFilter *getMinJaccardFilter(BloomFilter *filter);
    int getMinKey();
    int getMaxKey();
    vector<BloomFilter> collectAllFilters();
    int countFilters();
    int computeSubsetId(BloomFilter *filter);
    int computeSupersetId(BloomFilter *filter);
    bool contains(int k);
    BloomFilterNode *search(int k);
    
    BloomFilterIndexNode *split(BloomFilter *filter, BloomFilterNode *left, BloomFilterNode *right, int &middle);
    
    // Insertion
    void shiftAndInsert(BloomFilter *filter);
    void insert(BloomFilter *filter);
    void insert(BloomFilter *filter, BloomFilterNode *leftNode, BloomFilterNode *rightNode);
    
    // Similarity queries
    BloomFilter *simQuery(BloomFilter *filter);
    BloomFilter *simSubtreeQuery(BloomFilter *filter, int l);
    vector<BloomFilter*> simQueryVec(BloomFilter *filter, int k);
    vector<BloomFilter*> simSubtreeQueryVec(BloomFilter *filter, int k, int l);
};

#endif
