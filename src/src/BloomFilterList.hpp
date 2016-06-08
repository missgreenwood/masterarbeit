//  BloomFilterList.hpp, Judith Greif
//  Description: Header for class BloomFilterList


#ifndef BloomFilterList_hpp
#define BloomFilterList_hpp

#include "BloomFilterListNode.hpp"

class BloomFilterList {
private:
    BloomFilterListNode *head;
    BloomFilterListNode *tail;
    int size;
    
public:
    BloomFilterList();
    BloomFilterList(int _f);
    ~BloomFilterList();
    
    // List management methods
    void clear();
    void printPosition(int index);
    void printAll(); 
    void updateNode(BloomFilter *filter, int index);
    void tailAppend(int position);
    int getSize(); 
    
    // Insertion
    // TODO
    void insert(BloomFilter *filter);
    
    // Similarity queries
    // TODO
    BloomFilter *simQuery(BloomFilter *filter);
    vector<BloomFilter> simQueryVec(BloomFilter *filter, int k);
};

#endif
