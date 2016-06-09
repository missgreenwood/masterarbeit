//  BloomFilterVec.cpp, Judith Greif
//  Description: Implementation of class BloomFilterVec

#include "BloomFilterVec.hpp"


// Default constructor with no parameters
BloomFilterVec::BloomFilterVec(): size(m), filtersize(32) {
    for (int i=0; i<m; i++) {
        filters.push_back(BloomFilter(32, i));
    }
    arrSize = size * 32;
    filtersArr = new int[arrSize];
    for (int i=0; i<size; i++) {
        for (int j=0; j<32; j++) {
            filtersArr[j] = filters[i].dataArr[j];
        }
    }
};

// Constructor with parameter size
BloomFilterVec::BloomFilterVec(int s): size(s), filtersize(32) {
    for (int i=0; i<size; i++) {
        filters.push_back(BloomFilter(32, i));
    }
    arrSize = size * 32;
    filtersArr = new int[arrSize];
    for (int i=0; i<size; i++) {
        for (int j=0; j<32; j++) {
            filtersArr[j] = filters[i].dataArr[j];
        }
    }
};

// Constructor with parameters size and filtersize
BloomFilterVec::BloomFilterVec(int s, int f): size(s), filtersize(f) {
    for (int i=0; i<size; i++) {
        filters.push_back(BloomFilter(f, i));
    }
    arrSize = size * filtersize;
    filtersArr = new int[arrSize];
    for (int i=0; i<size; i++) {
        for (int j=0; j<filtersize; j++) {
            filtersArr[j] = filters[i].dataArr[j]; 
        }
    }
}

BloomFilterVec::~BloomFilterVec() {
    filters.clear(); 
}

void BloomFilterVec::initRandom() {
    for (int i=0; i<size; i++) {
        filters[i].initRandom();
        filters[i].printData();
    }
    cout << endl;
    for (int i=0; i<size; i++) {
        cout << "Array filter at index " << i << ": ";
        for (int j=0; j<32; j++) {
            filtersArr[j] = filters[i].dataArr[j];
            cout << filtersArr[j];
        }
        cout << endl;
    }
}

int BloomFilterVec::getSize() {
    return size;
}

void BloomFilterVec::print() {
    for (int i=0; i<size; i++) {
        cout << "Filter " << filters[i].getId() << ": Size = " << filters[i].getSize() << ", data = ";
        filters[i].printValue();
    }
}

int * BloomFilterVec::getFiltersArr() {
    return filtersArr;
}
