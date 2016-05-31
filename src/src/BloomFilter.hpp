//  BloomFilter.hpp, Judith Greif
//  Description: Header for class BloomFilter

#ifndef BloomFilter_hpp
#define BloomFilter_hpp

#include <iostream>
#include <vector>
#include <cstdlib>
#include <random>
#include <math.h>

using namespace std;

// TODO
const int filtersize = 10;   // # of bits in Bloom filter
const int d = 3;             // # of hash functions


class BloomFilter {
    
private:
    int size;
    int id;
    int *data;
    
public:
    BloomFilter();
    BloomFilter(const BloomFilter& fSource); 
    BloomFilter(int i);
    BloomFilter(int s, int i);
    ~BloomFilter();
    
    // Overloaded assignment operator
    BloomFilter & operator = (const BloomFilter &fSource); 
    
    void printData();
    void setId(int value);
    int getId();
    int getSize();
    void setValue(int index, int value);
    void printArr();
    int *getData();
    void initRandom();
    double fractionOfZeros();
    double eSize();
        
    friend class BloomFilterNode;
    friend class BloomFilterTree;
};


#endif
