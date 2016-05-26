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
    
    // Insertion methods
    void shiftAndInsert(BloomFilter *filter);
    void insert(BloomFilter *filter);
    void insert(BloomFilter *filter, BloomFilterNode *leftNode, BloomFilterNode *rightNode);
};

#endif