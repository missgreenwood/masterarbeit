//  BloomFilter.cpp, Judith Greif
//  Description: Implementation of class BloomFilter

#include "BloomFilter.hpp"


// Default constructor with no parameters
BloomFilter::BloomFilter(): size(filtersize), id(rand()) {
    data = new int[size];
    for (int i=0; i<size; i++) {
        data[i] = 0;
    }
};

// Copy constructor
// Usage: If a new object has to be created before the copying can occur
BloomFilter::BloomFilter(const BloomFilter& fSource) {
    size = fSource.size;
    id = fSource.id;
    
    // Allocate memory (deep copy)
    data = new int[fSource.size];
    for (int i=0; i<fSource.size; i++) {
        data[i] = fSource.data[i];
    }
};

// Constructor with parameter id
BloomFilter::BloomFilter(int i): size(filtersize), id(i) {
    data = new int[size];
    for (int i=0; i<size; i++) {
        data[i] = 0;
    }
}

// Constructor with parameters size and id
BloomFilter::BloomFilter(int s, int i): size(s), id(i) {
    data = new int[size];
    for (int i=0; i<size; i++) {
        data[i] = 0;
    }
};

BloomFilter::~BloomFilter() {}

// Overloaded assignment operator
// Usage: If a new object does not have to be created before the copying can occur
BloomFilter & BloomFilter::operator= (const BloomFilter &fSource) {
    
    // Check for self assignment
    if (this != &fSource) {
        size = fSource.size;
        id = fSource.id;
        
        // Allocate memory (deep copy)
        data = new int[fSource.size];
        for (int i=0; i<fSource.size; i++) {
            data[i] = fSource.data[i];
        }
    }
    return *this; 
}

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
}

int * BloomFilter::getData() {
    return data;
}
 
void BloomFilter::printArr() {
    for (int i=0; i<getSize(); i++) {
        cout << data[i]; 
    }
}

void BloomFilter::initRandom() {
    for (int i=0; i<getSize(); i++) {
        setValue(i, (rand()%2));
    }
}