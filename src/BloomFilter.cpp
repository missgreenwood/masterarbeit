//  BloomFilter.cpp, Judith Greif
//  Description: Implementation of class BloomFilter

#include "BloomFilter.hpp"


void BloomFilter::printData() {
    cout << "Bloom filter " << getId() << ": ";
    for (int i=0; i<size; i++) {
        cout << data[i];
    }
    cout << endl;
}

int BloomFilter::getId() {
    return id;
}

int BloomFilter::getSize() {
    return size;
}

void BloomFilter::setValue(int index, int value) {
    data[index] = value;
    dataArr[index] = value;
}

void BloomFilter::printValue() {
    for (int i=0; i<size; i++) {
        cout << data[i];
    }
    cout << endl;
}

int * BloomFilter::getArr() {
    return dataArr;
}

void BloomFilter::printArr() {
    for (int i=0; i<getSize(); i++) {
        cout << dataArr[i];
    }
    cout << endl;
}

void BloomFilter::initRandom() {
    for (int i=0; i<getSize(); i++) {
        setValue(i, (rand()%2));
    }
}
