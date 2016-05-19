//  BloomFilterLeaf.hpp, Judith Greif
//  Description: Header for class BloomFilterLeaf

#ifndef BloomFilterLeaf_hpp
#define BloomFilterLeaf_hpp

#include <iostream>
#include "BloomFilterNode.hpp"
#include "BloomFilterIndexNode.hpp"


class BloomFilterLeaf : public BloomFilterNode {
private:
    
    BloomFilterLeaf *prev;
    BloomFilterLeaf *next;
    int **filters;
    
public:
    BloomFilterLeaf(int _t);
    BloomFilterLeaf(int _t, int _s); 
    BloomFilterLeaf(int _t, int _s, BloomFilterLeaf *_prev, BloomFilterLeaf *_next);
    ~BloomFilterLeaf();
    
    // Insertion methods
    void insertKey(int k);
    void insert(BloomFilter *filter);
    void insertSimilarFilter(BloomFilter *filter);
    
    BloomFilterNode *search(int k);
    BloomFilterLeaf *split(BloomFilter *filter);
    BloomFilterLeaf *splitKey(int k);
    void traverse();
    bool contains(int k);
    int **getFilters();
    void setPrev(BloomFilterLeaf *leaf);
    BloomFilterLeaf *getPrev();
    void setNext(BloomFilterLeaf *leaf);
    BloomFilterLeaf *getNext();
    void traverseFilters();
};

#endif
