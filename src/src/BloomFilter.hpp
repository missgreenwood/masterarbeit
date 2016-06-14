//  BloomFilter.hpp, Judith Greif
//  Description: Header for class BloomFilter

#ifndef BloomFilter_hpp
#define BloomFilter_hpp

#include <iostream>
#include <vector>
#include <cstdlib>
#include <random>
#include <math.h>
#include <string>
#include <functional>

using namespace std;

const int NUM_FILTERS = 100;
const int NUM_ELEMENTS = 50;
const int seed = rand();

class BloomFilter {
    
private:
    int id;
    int count;                  // # of elements inserted
    int size;                   // # of bits
    int d;                      // # of hash functions
    int *data;
    
public:
    BloomFilter();
    BloomFilter(const BloomFilter& fSource);
    BloomFilter(int _id, int _size);
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
    void add(string &elem);
    void increment();
    int getNumHashes(); 
};

#endif
