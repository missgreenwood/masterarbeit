//  BloomFilterVec.cpp, Judith Greif
//  Description: Implementation of class BloomFilterVec

#include "BloomFilterVec.hpp"


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
