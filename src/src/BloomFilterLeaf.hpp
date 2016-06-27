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
    
    BloomFilterLeaf *getPrev();
    void setPrev(BloomFilterLeaf *leaf);
    BloomFilterLeaf *getNext();
    void setNext(BloomFilterLeaf *leaf);
    
    // Tree management
    void traverse();
    void traverseFilters();
    double computeMinJaccard(BloomFilter *filter);
    double computeMaxJaccard(BloomFilter *filter);
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
    BloomFilterLeaf *split(BloomFilter *filter);
    int countUnionFilters();
    int countComparisons(BloomFilter *filter);
    int allComparisons(BloomFilter *filter, int l);
    int countVecComparisons(BloomFilter *filter, int k);
    int allVecComparisons(BloomFilter *filter, int k, int l);
    
    // Insertion
    void insert(BloomFilter *filter);
    
    // Similarity queries
    BloomFilter *simQuery(BloomFilter *filter);
    BloomFilter *simSubtreeQuery(BloomFilter *filter, int l);
    vector<BloomFilter*> simQueryVec(BloomFilter *filter, int k);
    vector<BloomFilter*> simSubtreeQueryVec(BloomFilter *filter, int k, int l);
};

#endif
