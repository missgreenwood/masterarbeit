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
const int filtersize = 256;     // # of bits in Bloom filter
const int d = 3;                // # of hash functions

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
    
    BloomFilter & operator = (const BloomFilter &fSource);
    
    void setId(int value);
    int getId();
    int getSize();
    void setValue(int index, int value);
    int *getData();
    
    void printData();
    void printArr();
    void initRandom();
    double fractionOfZeros();
    double eSize();
    BloomFilter *logicalOr(BloomFilter *filter);
    BloomFilter *logicalAnd(BloomFilter *filter);
    bool isSubset(BloomFilter *filter);
    bool isSuperset(BloomFilter *filter);
    int mySupersetCount();
    int mySubsetCount();
    int binomialCoefficient(int n, int k);
    int setOnes();
    int setZeros();
    int validOnes();
    int possibleFreeZeros();
    int possibleAddedOnes();
    double setUnion(BloomFilter *filter) const;
    double setIntersection(BloomFilter *filter) const;
    double computeAmbienceJaccard(BloomFilter *filter);
    double computeJaccard(BloomFilter *filter) const;
    double eUnion(BloomFilter *filter);
    double eIntersect(BloomFilter *filter); 
};

#endif
