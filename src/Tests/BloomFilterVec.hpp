//  BloomFilterVec.hpp, Judith Greif
//  Description: Header for class BloomFilterVec

#ifndef BloomFilterVec_h
#define BloomFilterVec_h

#include "BloomFilter.hpp"

const int m = 100;          // default # of Bloom filters in array


class BloomFilterVec {
    
private:
    int size;
    int filtersize;
    int *filtersArr;
    int arrSize;
    
public:
    vector<BloomFilter> filters;
    BloomFilterVec();
    BloomFilterVec(int s);
    BloomFilterVec(int s, int f); 
    ~BloomFilterVec(); 
    int getSize();
    void initRandom();
    void print();
    int *getFiltersArr();
    
    friend class BloomFilterNode;
    friend class BloomFilterTree;
};

#endif
