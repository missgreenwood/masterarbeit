//  BloomFilter.hpp, Judith Greif
//  Description: Header for class BloomFilter

#ifndef BloomFilter_hpp
#define BloomFilter_hpp

#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

const int n = 32;   // # of bits in Bloom filter


class BloomFilter {
    
private:
    int size;
    int id;
    vector<int> data;
    
public:
    int *dataArr;
    // Default constructor with no parameters
    BloomFilter(): size(n), id(rand()), data(vector<int>(size)) {
        for (int i=0; i<size; i++) {
            data[i] = 0;
        }
        cout << "Created Bloom filter with id = " << id << ", size = " << size << ", data: ";
        dataArr = new int[size];
        copy(data.begin(), data.end(), dataArr);
        printValue();
    };
    
    // Constructor with parameter id
    BloomFilter(int i): size(n), id(i), data(vector<int>(size)) {
        for (int i=0; i<size; i++) {
            data[i] = 0;
        }
        cout << "Created Bloom filter with id = " << id << ", size = " << size << ", data = ";
        cout << "Created Bloom filter with id = " << id << ", size = " << size << ", data: ";
        dataArr = new int[size];
        copy(data.begin(), data.end(), dataArr);
        printValue();
    }
    
    // Constructor with parameters size and id
    BloomFilter(int s, int i): size(s), id(i), data(vector<int>(s)) {
        for (int i=0; i<size; i++) {
            data[i] = 0;
        }
        cout << "Created Bloom filter with id = " << id << ", size = " << size << ", data = ";
        cout << "Created Bloom filter with id = " << id << ", size = " << size << ", data: ";
        dataArr = new int[size];
        copy(data.begin(), data.end(), dataArr);
        printValue();
    };
    
    void printData();
    void printValue();
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
