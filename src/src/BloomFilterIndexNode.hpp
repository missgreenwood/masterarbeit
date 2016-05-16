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
    BloomFilterIndexNode(int _t);
    ~BloomFilterIndexNode();
    BloomFilterNode *search(int k);
    void shiftAndInsert(int k);
    void insert(int k);
    void insertFilter(BloomFilter *filter);
    void insert(int k, BloomFilterNode *leftNode, BloomFilterNode *rightNode);
    bool contains(int k);
    BloomFilterIndexNode *split(int k, BloomFilterNode *left, BloomFilterNode *right, int &middle);
    void traverse();
    void traverseFilters(); 
};

#endif
