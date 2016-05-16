//  BloomFilter.hpp, Judith Greif
//  Description: Header for class BloomFilter

#ifndef BloomFilter_hpp
#define BloomFilter_hpp

#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

const int filtersize = 32;   // # of bits in Bloom filter


class BloomFilter {
    
private:
    int size;
    int id;
    vector<int> data;
    
public:
    int *dataArr;
    BloomFilter();
    BloomFilter(int i);
    BloomFilter(int s, int i);
    ~BloomFilter(); 
    
    void printData();
    void printValue();
    void setId(int value);
    int getId();
    int getSize();
    void setValue(int index, int value);
    int *getArr();
    void printArr();
    void initRandom();
    
    friend class BloomFilterVec;
    friend class BloomFilterNode;
    friend class BloomFilterTree;
    
};


#endif
