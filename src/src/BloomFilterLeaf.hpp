//  BloomFilterLeaf.hpp, Judith Greif
//  Description: Header for class BloomFilterLeaf

#ifndef BloomFilterLeaf_hpp
#define BloomFilterLeaf_hpp

#include <iostream>
#include "BloomFilterNode.hpp"
#include "BloomFilterIndexNode.hpp"
#include "BloomFilter.hpp"


class BloomFilterLeaf : public BloomFilterNode {
private:
    
    BloomFilterLeaf *prev;
    BloomFilterLeaf *next;
    int **filters;
    int size;
    
public:
    BloomFilterLeaf(int _t);
    BloomFilterLeaf(int _t, int _s); 
    BloomFilterLeaf(int _t, BloomFilterLeaf *_prev, BloomFilterLeaf *_next);
    ~BloomFilterLeaf();
    void insert(int k);
    void insertFilter(BloomFilter *f);
    BloomFilterNode *search(int k);
    BloomFilterLeaf *split(int k);
    void traverse();
    bool contains(int k);
    int **getFilters();
    void setPrev(BloomFilterLeaf *leaf);
    BloomFilterLeaf *getPrev();
    void setNext(BloomFilterLeaf *leaf);
    BloomFilterLeaf *getNext();
    int getFilterSize();
    void traverseFilters(); 
};

#endif
