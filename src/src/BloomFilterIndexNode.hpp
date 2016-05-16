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
    void shiftAndInsert(BloomFilter *filter);
    void insertKey(int key, BloomFilterNode *leftNode, BloomFilterNode *rightNode);
    void insert(BloomFilter *filter);
    void insert(BloomFilter *filter, BloomFilterNode *leftnode, BloomFilterNode *rightNode);
    bool contains(int k);
    BloomFilterIndexNode *split(BloomFilter *filter, BloomFilterNode *left, BloomFilterNode *right, int &middle);
    void traverse();
    void traverseFilters(); 
};

#endif
