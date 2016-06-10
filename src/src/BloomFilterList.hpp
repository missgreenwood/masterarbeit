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
    
    int getSize();
    
    // List management methods
    void clear();
    void printPosition(int index);
    void printAll(); 
    void updateNode(BloomFilter *filter, int index);
    void tailAppend(int position);
    BloomFilter *getMinJaccardFilter(BloomFilter *filter);
    vector<BloomFilter> collectAllFilters();
    int countFilters(); 
    vector<pair<int, float>> computeAllDistances(BloomFilter *filter);
    
    // Comparison
    vector<pair<BloomFilter, float>> compare(BloomFilter *filter, int k); 
    
    // Insertion
    void insert(BloomFilter *filter);
    
    // Similarity queries
    BloomFilter *simQuery(BloomFilter *filter);
    vector<BloomFilter*> simQueryVec(BloomFilter *filter, int k);
};

#endif
