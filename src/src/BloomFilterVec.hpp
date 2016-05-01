//  BloomFilterVec.hpp, Judith Greif
//  Description: Header for class BloomFilterVec

#ifndef BloomFilterVec_h
#define BloomFilterVec_h

#include "BloomFilter.hpp"

const int m = 100;          // default # of Bloom filters in array


// Vector of Bloom filters with constructors
class BloomFilterVec {
    
private:
    int size;
    vector<BloomFilter> filters;
    int *filtersArr;
    int arrSize;
    
public:
    
    // Default constructor with no parameters
    BloomFilterVec(): size(m) {
        for (int i=0; i<m; i++) {
            filters.push_back(BloomFilter(32, i));
        }
        cout << endl << "Created Bloom filter vector with size = " << size << ", ids = " << filters[0].getId() << " - " << filters[size-1].getId() << endl;
        arrSize = size * 32;
        filtersArr = new int[arrSize];
        cout << endl;
        for (int i=0; i<size; i++) {
            cout << "Array filter at index " << i << ": ";
            for (int j=0; j<32; j++) {
                filtersArr[j] = filters[i].dataArr[j];
                cout << filtersArr[j];
            }
            cout << endl; 
        }
    };
    
    // Constructor with parameter size
    BloomFilterVec(int s): size(s) {
        for (int i=0; i<size; i++) {
            filters.push_back(BloomFilter(32, i));
        }
        cout << endl << "Created Bloom filter vector with size = " << size << ", ids = " << filters[0].getId() << " - " << filters[size-1].getId() << endl;
        arrSize = size * 32;
        filtersArr = new int[arrSize];
        cout << endl;
        for (int i=0; i<size; i++) {
            cout << "Array filter at index " << i << ": ";
            for (int j=0; j<32; j++) {
                filtersArr[j] = filters[i].dataArr[j];
                cout << filtersArr[j];
            }
            cout << endl;
        }
    };
    
    int getSize();
    void initRandom();
    void print();
    int *getFiltersArr();
    
    friend class BloomFilterNode; 
    friend class BloomFilterTree;
};

#endif
