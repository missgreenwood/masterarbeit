//  bloomtest.hpp, Judith Greif
//  Description: Header for Bloom filter test implementation, including method declarations for unit tests

#ifndef bloomtest_h
#define bloomtest_h

#include <iostream>
#include <vector>
using namespace std;

const int n = 32;   // number of bits in the Bloom filter
const int m = 100;  // number of Bloom filters in array

// Basic Bloom filter
class BloomFilter {
private:
    const int size;
    const int id;
    vector<int> data;
    int *dataArr;
public:
    // Constructor with no arguments
    BloomFilter(): size(n), id(rand()), data(vector<int>(size)) {
        for (int i=0; i<size; i++) {
            data[i] = 0;
        }
        cout << "Created Bloom filter with id = " << id << ", size = " << size << ", data: ";
        dataArr = new int[size];
        copy(data.begin(), data.end(), dataArr);
        printValue();
    };
    
    // Constructor with id
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
    
    // Constructor with size and id
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
};

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

class BloomFilterVec {
private:
    int size;
    vector<BloomFilter> filters;
    int *filtersArr;
public:
    BloomFilterVec(): size(m) {
        for (int i=0; i<m; i++) {
            filters.push_back(BloomFilter(32, i));
        }
        filtersArr = NULL;
        cout << "Created Bloom filter vector with size = " << size << ", ids = " << filters[0].getId() << " - " << filters[size-1].getId() << endl;
    };
    BloomFilterVec(int s): size(s) {
        for (int i=0; i<size; i++) {
            filters.push_back(BloomFilter(32, i));
        }
        cout << "Created Bloom filter vector with size = " << size << ", ids = " << filters[0].getId() << " - " << filters[size-1].getId() << endl;
    };
    int getSize();
    void initRandom();
    void print();
    int *createFiltersArr();
};

void BloomFilterVec::initRandom() {
    for (int i=0; i<size; i++) {
        for (int j=0; j<filters[i].getSize(); j++) {
            filters[i].setValue((rand()%2), j);
        }
        filters[i].printData(); 
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

int * BloomFilterVec::createFiltersArr() {
    // filtersArr = new int[size][filters[0].getSize()];
    return filtersArr;
}
#endif
