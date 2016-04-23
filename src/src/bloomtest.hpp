//  bloomtest.hpp, Judith Greif
//  Description: Header for Bloom filter test implementation, including method declarations for unit tests

#ifndef bloomtest_h
#define bloomtest_h

#include <iostream>
using namespace std;

const int filter_size = 32; // number of bits in the Bloom filter

class BloomFilter {
private:
    int size;
    int id;
public:
    void print();
    int getId();
    void setId(int id);    
};

void print(BloomFilter filter) {
    cout << "Printing bloom filter: " << endl;
}

#endif
