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
public:
    vector<int> data;
    // Constructor with no arguments
    BloomFilter(): size(n), id(rand()), data(vector<int>(size)) {
        for (int i=0; i<size; i++) {
            data[i] = 0;
        }
        cout << "Created Bloom filter with id = " << id << ", size = " << size << ", data: ";
        printValue();
    };
    
    // Constructor with id
    BloomFilter(int i): size(n), id(i), data(vector<int>(size)) {
        for (int i=0; i<size; i++) {
            data[i] = 0;
        }
        cout << "Created Bloom filter with id = " << id << ", size = " << size << ", data = ";
        printValue();
    }
    
    // Constructor with size and id
    BloomFilter(int s, int i): size(s), id(i), data(vector<int>(s)) {
        for (int i=0; i<size; i++) {
            data[i] = 0; 
        }
        cout << "Created Bloom filter with id = " << id << ", size = " << size << ", data = ";
        printValue();
    };
    
    void printData();
    void printValue();
    int getId();
    int getSize();
    void setValue(int value, int index);
    int *getDataAsArr();
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

void BloomFilter::setValue(int value, int index) {
    data[index] = value;
}

void BloomFilter::printValue() {
    for (int i=0; i<size; i++) {
        cout << data[i];
    }
    cout << endl;
}

class BloomFilterVec {
private:
    int size;
    vector<BloomFilter> filters;
public:
    BloomFilterVec(): size(m) {
        for (int i=0; i<m; i++) {
            filters.push_back(BloomFilter(32, i));
        }
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
    int *makeList();
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

/* int * BloomFilterVec::makeList() {
    int *arr = new int[size][filters[0].getSize()];
    for (int i= 0; i<size; i++) {
        for (int j=0; j<filters[0].getSize(); j++) {
            arr[i][j] = filters[i].data[j];
        }
    }
    return *arr;
} */

#endif
