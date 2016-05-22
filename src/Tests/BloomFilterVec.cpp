//  BloomFilterVec.cpp, Judith Greif
//  Description: Implementation of class BloomFilterVec

#include "BloomFilterVec.hpp"


// Default constructor with no parameters
BloomFilterVec::BloomFilterVec(): size(m) {
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
BloomFilterVec::BloomFilterVec(int s): size(s) {
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
