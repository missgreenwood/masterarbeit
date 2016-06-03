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
    
    BloomFilterIndexNode *split(BloomFilter *filter, BloomFilterNode *left, BloomFilterNode *right, int &middle);
    bool contains(int k);
    void traverse();
    void traverseFilters();
    BloomFilterNode *search(int k);
    void updateUnionFilter();
    
    // Insertion methods
    void shiftAndInsert(BloomFilter *filter);
    void insert(BloomFilter *filter);
    void insert(BloomFilter *filter, BloomFilterNode *leftNode, BloomFilterNode *rightNode);
    
    // Tree management helper methods
    float computeMinJaccard(BloomFilter *filter);
    int computeMinJaccardKey(BloomFilter *filter);
    int getMinKey();
    int getMaxKey();
    vector<BloomFilter> collectAllFilters(); 
    
    // Similarity queries
    // TODO 
    BloomFilter *simpleSimQuery(BloomFilter *filter);
    BloomFilter *simQuery(BloomFilter *filter);
    vector<BloomFilter> simpleSimQueryVec(BloomFilter *filter, int k);
    vector<BloomFilter> simQueryVec(BloomFilter *filter, int k);
};

#endif
