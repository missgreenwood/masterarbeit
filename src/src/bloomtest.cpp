//  bloomtest.cpp, Judith Greif
//  Description: Bloom filter test implementation (classes BloomFilter and BloomFilterVec)

#include <iostream>
#include "bloomtest.hpp"

using namespace std;

int main(int argc, const char *argv[]) {
    
    // Create one Bloom filter and call its methods
    // BloomFilter f1(10, 0);
    // cout << "Id of Bloom filter f1: " << f1.getId() << endl;
    // cout << "Size of Bloom filter f1: " << f1.getSize() << endl;
    // f1.printData();
    // f1.printArr();
    // f1.initRandom();
    // f1.printData();
    // f1.printArr();
    
    // Create Bloom filter vectors and and call methods
    // BloomFilterVec v1;
    BloomFilterVec v2(2);
    // v1.initRandom();
    // v1.print();
    v2.initRandom();
    // v2.print();
    // cout << v1.getSize() << endl;
    // cout << v2.getSize() << endl;
    return 0;
}
