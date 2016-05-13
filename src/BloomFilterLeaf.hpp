//  BloomFilterLeaf.hpp, Judith Greif
//  Description: Header for class BloomFilterLeaf

#ifndef BloomFilterLeaf_hpp
#define BloomFilterLeaf_hpp

#include <iostream>
#include "BloomFilterNode.hpp"
#include "BloomFilterIndexNode.hpp"


class BloomFilterLeaf : public BloomFilterNode {
private:
    int **filters;
    BloomFilterLeaf *prev;
    BloomFilterLeaf *next; 

public:
    BloomFilterLeaf(int _t);
    BloomFilterLeaf(int _t, BloomFilterLeaf *_prev, BloomFilterLeaf *_next);
    ~BloomFilterLeaf();
    void insert(int k);
    BloomFilterNode *search(int k);
    BloomFilterLeaf *split(int k);
    void traverse();
    bool contains(int k);
    int **getFilters();
    void setPrev(BloomFilterLeaf *leaf);
    BloomFilterLeaf *getPrev();
    void setNext(BloomFilterLeaf *leaf);
    BloomFilterLeaf *getNext();
};

#endif
