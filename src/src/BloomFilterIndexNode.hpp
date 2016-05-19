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
    BloomFilterNode *search(int k);
    
    // Insertion methods
    void shiftAndInsert(BloomFilter *filter);
    void shiftAndInsertKey(int k);
    void insert(BloomFilter *filter);
    void insertKey(int k);
    void insert(BloomFilter *filter, BloomFilterNode *leftNode, BloomFilterNode *rightNode);
    void insertKey(int k, BloomFilterNode *leftNode, BloomFilterNode *rightNode);
    void insertSimilarFilter(BloomFilter *filter); 
    
    bool contains(int k);
    int **getFilters();
    BloomFilterIndexNode *split(BloomFilter *filter, BloomFilterNode *left, BloomFilterNode *right, int &middle);
    BloomFilterIndexNode *splitKey(int k, BloomFilterNode *left, BloomFilterNode *right, int &middle); 
    void traverse();
    void traverseFilters(); 
};

#endif
