//  BloomFilterList.hpp, Judith Greif
//  Description: Header for class BloomFilterList


#ifndef BloomFilterList_hpp
#define BloomFilterList_hpp

#include "BloomFilterListNode.hpp"

class BloomFilterList {
private:
    BloomFilterListNode *head;
    BloomFilterListNode *tail;
    int size;                       // 2*filtersize, e.g. 0/1 for each position
    
public:
    BloomFilterList();
    BloomFilterList(int _f);
    ~BloomFilterList();
    
    // List management methods
    void clear();
    void traverse();
    void updateNode(BloomFilter *filter, int index);
    void tailAppend(int value);
    
    // Insertion
    void insert(BloomFilter *filter);
    
    // Similarity queries
};

#endif
