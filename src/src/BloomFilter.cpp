//  BloomFilter.cpp, Judith Greif
//  Description: Implementation of class BloomFilter

#include "BloomFilter.hpp"


// Default constructor with no parameters
BloomFilter::BloomFilter(): size(filtersize), id(rand()), data(vector<int>(size)) {
    for (int i=0; i<size; i++) {
        data[i] = 0;
    }
    cout << "Created Bloom filter with id: " << id << ", size: " << size << ", data: ";
    dataArr = new int[size];
    copy(data.begin(), data.end(), dataArr);
    printValue();
};

// Constructor with parameter id
BloomFilter::BloomFilter(int i): size(filtersize), id(i), data(vector<int>(size)) {
    for (int i=0; i<size; i++) {
        data[i] = 0;
    }
    cout << "Created Bloom filter with id: " << id << ", size: " << size << ", data: ";
    dataArr = new int[size];
    copy(data.begin(), data.end(), dataArr);
    printValue();
}

// Constructor with parameters size and id
BloomFilter::BloomFilter(int s, int i): size(s), id(i), data(vector<int>(s)) {
    for (int i=0; i<size; i++) {
        data[i] = 0;
    }
    cout << "Created Bloom filter with id: " << id << ", size: " << size << ", data: ";
    dataArr = new int[size];
    copy(data.begin(), data.end(), dataArr);
    printValue();
};

BloomFilter::~BloomFilter() {}

void BloomFilter::printData() {
    cout << "Bloom filter " << getId() << ": ";
    for (int i=0; i<size; i++) {
        cout << data[i];
    }
    cout << endl;
}

void BloomFilter::setId(int value) {
    id = value;
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
