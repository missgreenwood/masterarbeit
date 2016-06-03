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
    
public:
    BloomFilterLeaf(int _t, int _s); 
    BloomFilterLeaf(int _t, int _s, BloomFilterLeaf *_prev, BloomFilterLeaf *_next);
    ~BloomFilterLeaf();
    
    BloomFilterLeaf *split(BloomFilter *filter);
    void traverse();
    void traverseFilters();
    bool contains(int k);
    BloomFilterNode *search(int k);
    BloomFilterLeaf *getPrev();
    void setPrev(BloomFilterLeaf *leaf);
    BloomFilterLeaf *getNext();
    void setNext(BloomFilterLeaf *leaf);
    void updateUnionFilter(); 
    
    // Insertion methods
    void insert(BloomFilter *filter);
    
    // Tree management helper methods
    float computeMinJaccard(BloomFilter *filter);
    int computeMinJaccardKey(BloomFilter *filter);
    int getMinKey();
    int getMaxKey();
    vector<BloomFilter> collectAllFilters();
    
    // Similarity queries
    BloomFilter *simpleSimQuery(BloomFilter *filter);
    BloomFilter *simQuery(BloomFilter *filter);
    vector<BloomFilter> simpleSimQueryVec(BloomFilter *filter, int k);
    vector<BloomFilter> simQueryVec(BloomFilter *filter, int k);
};

#endif
