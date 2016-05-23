//  main.cpp, Judith Greif
//  Description: Main executable for Bloom-Filter-Tree


// Includes for bloom_filter.hpp
#include <string>
#include <cstddef>
#include <cstdio>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <deque>
#include <set>

#include <iostream>
#include "bloom_filter.hpp"
#include "BloomFilterVec.hpp"
#include "BTree.hpp"
#include "BPlusTree.hpp"
#include "BloomFilterTree.hpp"

using namespace std;

int main(int argc, const char *argv[]) {
    
    // Class BloomFilterVec
    // Instantiate Bloom filter vectors and and call their methods
    
    cout << "CLASS BloomFilterVec" << endl;
    cout << "--------------------" << endl << endl;
    cout << "Create instance of BloomFilterVec of size 11 (v1)" << endl << endl;
    BloomFilterVec v1(11);
    cout << endl << "Fill all filters in vector with random values 0 or 1" << endl << endl;
    v1.initRandom();
    cout << "\nSet ids of BloomFilter objects in v1: 1, 4, 7, 10, 17, 25, 2, 8, 9, 26, 96\n\n";
    v1.filters[0].setId(1);
    v1.filters[1].setId(4);
    v1.filters[2].setId(7);
    v1.filters[3].setId(10);
    v1.filters[4].setId(17);
    v1.filters[5].setId(25);
    v1.filters[6].setId(2);
    v1.filters[7].setId(8);
    v1.filters[8].setId(9);
    v1.filters[9].setId(26);
    v1.filters[10].setId(96);
    for (int i=0; i<v1.getSize(); i++) {
        v1.filters[i].printData();
    }
    
    // Class BloomFilter
    
    cout << "\n\nCLASS BloomFilter" << endl;
    cout << "-----------------" << endl << endl;
    cout << "Create 11 instances of BloomFilter with ids 3, 5, 6, 11, 12, 13, 14, 15, 16, 18, 19, array length 10 and random values\n\n";
    BloomFilter f3(10, 3);
    BloomFilter f5(10, 5);
    BloomFilter f6(10, 6);
    BloomFilter f11(10, 11);
    BloomFilter f12(10, 12);
    BloomFilter f13(10, 13);
    BloomFilter f14(10, 14);
    BloomFilter f15(10, 15);
    BloomFilter f16(10, 16);
    BloomFilter f18(10, 18);
    BloomFilter f19(10, 19);
    cout << endl;
    f3.initRandom();
    f3.printData();
    f5.initRandom();
    f5.printData();
    f6.initRandom();
    f6.printData();
    f11.initRandom();
    f11.printData();
    f12.initRandom();
    f12.printData();
    f13.initRandom();
    f13.printData();
    f14.initRandom();
    f14.printData();
    f15.initRandom();
    f15.printData();
    f16.initRandom();
    f16.printData();
    f18.initRandom();
    f18.printData();
    f19.initRandom();
    f19.printData();
    
    // Class BloomFilterLeaf
    
    /* cout << "\n\nCLASS BloomFilterLeaf";
    cout << "\n---------------------\n\n";
    cout << "Create leaf with minimum degree 3/max. elements 6 (l2)\n\n";
    BloomFilterLeaf l2(3, f1.getSize());
    cout << "Insert filters into l2: f1, f4, f7, f10, f17, f25\n";
    l2.insert(&f1);
    l2.insert(&f4);
    l2.insert(&f7);
    l2.insert(&f10);
    l2.insert(&f17);
    l2.insert(&f25);
    cout << "\nTraverse l2: ";
    l2.traverse();
    cout << "\nTraverse l2 filters: ";
    l2.traverseFilters();
    cout << "\n\nCheck index function:\n";
    keys = l2.getKeys();
    for (int i=0; i<l2.getCount(); i++) {
        cout << "Key: " << keys[i] << ", index: " << l2.indexOfKey(keys[i]) << endl;
    }
    
    cout << "\nSplit l2 and traverse new sibling l3:\n";
    BloomFilterLeaf *l3 = l2.split(&f101);
    l3->traverse();
    cout << endl;
    l3->traverseFilters(); 
    
    cout << "\n\nInsert filters into l2: f2, f8, f9:\n";
    l2.insert(&f2);
    l2.insert(&f8);
    l2.insert(&f9);
    l2.traverse();
    cout << endl;
    l2.traverseFilters();
    l2.insert(&f101);
    cout << endl << "Insert filter into l2: f101\n";
    cout << "\nTraverse old leaf: ";
    l2.traverse();
    cout << "\nTraverse new parent:\n";
    BloomFilterNode *parent = l2.getParent();
    parent->traverse();
    cout << endl;
    parent->traverseFilters(); */
    
    // Class BloomFilterTree
    
    cout << "\n\nCLASS BloomFilterTree";
    cout << "\n---------------------\n\n";
    
    cout << "Create instance of 4-level BloomFilterTree with minimum degree 1/max. elements 2, filter size 32 (b1)\n\n";
    BloomFilterTree b1(1, 32);
    cout << "Insert filter into into b1: f1\n";
    b1.insert(&v1.filters[0]);
    b1.traverse();
    cout << endl;
    cout << "\nCompute Jaccard coefficient of filters f4, f7, f10, f17, f25, f2, f8, f9, f26, f96 and  tree root:\n\n";
    for (int i=0; i<v1.getSize(); i++) {
        cout << "jacc(root, filter " << i << "): " << b1.computeMaxJaccard(&v1.filters[i]) << endl;
    }
    
    cout << "\nInsert filters into b1: f4, f7, f10, f17, f25, f2, f8\n";
    for (int i=0; i<6; i++) {
        b1.insert(&v1.filters[i]);
    }
    cout << endl << "Traverse b1: ";
    b1.traverse();
    
    cout << "\n\nCreate instance of 4-level BloomFilterTree with minimum degree 1/max. elements 2, filter size 10 (b2)\n\n";
    BloomFilterTree b2(1, 10);
    cout << "Insert filters into b2: f3, f5, f6, f11, f12, f13, f14, f15";
    cout << "\nCompute highest Jaccard coefficient of f16, f18, f19 and each intermediate tree state\n\n";
    b2.insert(&f3);
    cout << "Max jacc(b2, f16): " << b2.computeMaxJaccard(&f16);
    cout << " (key " << b2.computeMaxJaccardKey(&f16) << ")\n";
    cout << "Max jacc(b2, f18): " << b2.computeMaxJaccard(&f18);
    cout << " (key " << b2.computeMaxJaccardKey(&f18) << ")\n";
    cout << "Max jacc(b2, f19): " << b2.computeMaxJaccard(&f19);
    cout << " (key " << b2.computeMaxJaccardKey(&f19) << ")\n\n";
    b2.insert(&f5);
    cout << "Max jacc(b2, f16): " << b2.computeMaxJaccard(&f16);
    cout << " (key " << b2.computeMaxJaccardKey(&f16) << ")\n";
    cout << "Max jacc(b2, f18): " << b2.computeMaxJaccard(&f18);
    cout << " (key " << b2.computeMaxJaccardKey(&f18) << ")\n";
    cout << "Max jacc(b2, f19): " << b2.computeMaxJaccard(&f19);
    cout << " (key " << b2.computeMaxJaccardKey(&f19) << ")\n";
    b2.insert(&f6);
    cout << "\nMax jacc(b2, f16): " << b2.computeMaxJaccard(&f16);
    cout << " (key " << b2.computeMaxJaccardKey(&f16) << ")\n";
    cout << "Max jacc(b2, f18): " << b2.computeMaxJaccard(&f18);
    cout << " (key " << b2.computeMaxJaccardKey(&f18) << ")\n";
    cout << "Max jacc(b2, f19): " << b2.computeMaxJaccard(&f19);
    cout << " (key " << b2.computeMaxJaccardKey(&f19) << ")\n";
    b2.insert(&f11);
    cout << "\nMax jacc(b2, f16): " << b2.computeMaxJaccard(&f16);
    cout << " (key " << b2.computeMaxJaccardKey(&f16) << ")\n";
    cout << "Max jacc(b2, f18): " << b2.computeMaxJaccard(&f18);
    cout << " (key " << b2.computeMaxJaccardKey(&f18) << ")\n";
    cout << "Max jacc(b2, f19): " << b2.computeMaxJaccard(&f19);
    cout << " (key " << b2.computeMaxJaccardKey(&f19) << ")\n";
    b2.insert(&f12);
    cout << "\nMax jacc(b2, f16): " << b2.computeMaxJaccard(&f16);
    cout << " (key " << b2.computeMaxJaccardKey(&f16) << ")\n";
    cout << "Max jacc(b2, f18): " << b2.computeMaxJaccard(&f18);
    cout << " (key " << b2.computeMaxJaccardKey(&f18) << ")\n";
    cout << "Max jacc(b2, f19): " << b2.computeMaxJaccard(&f19);
    cout << " (key " << b2.computeMaxJaccardKey(&f19) << ")\n";
    b2.insert(&f13);
    cout << "\nMax jacc(b2, f16): " << b2.computeMaxJaccard(&f16);
    cout << " (key " << b2.computeMaxJaccardKey(&f16) << ")\n";
    cout << "Max jacc(b2, f18): " << b2.computeMaxJaccard(&f18);
    cout << " (key " << b2.computeMaxJaccardKey(&f18) << ")\n";
    cout << "Max jacc(b2, f19): " << b2.computeMaxJaccard(&f19);
    cout << " (key " << b2.computeMaxJaccardKey(&f19) << ")\n";
    b2.insert(&f14);
    cout << "\n\nMax jacc(b2, f16): " << b2.computeMaxJaccard(&f16);
    cout << " (key " << b2.computeMaxJaccardKey(&f16) << ")\n";
    cout << "Max jacc(b2, f18): " << b2.computeMaxJaccard(&f18);
    cout << " (key " << b2.computeMaxJaccardKey(&f18) << ")\n";
    cout << "Max jacc(b2, f19): " << b2.computeMaxJaccard(&f19);
    cout << " (key " << b2.computeMaxJaccardKey(&f19) << ")\n";
    b2.insert(&f15);
    cout << "\nMax jacc(b2, f16): " << b2.computeMaxJaccard(&f16);
    cout << " (key " << b2.computeMaxJaccardKey(&f16) << ")\n";
    cout << "Max jacc(b2, f18): " << b2.computeMaxJaccard(&f18);
    cout << " (key " << b2.computeMaxJaccardKey(&f18) << ")\n";
    cout << "Max jacc(b2, f19): " << b2.computeMaxJaccard(&f19);
    cout << " (key " << b2.computeMaxJaccardKey(&f19) << ")\n";
    
    cout << "\nCompute optimal ids for filters f16, f18, f19 regarding b2";
    cout << "\nSmallest key in b2: " << b2.getMinKey() << "\nBiggest key in b2: " << b2.getMaxKey();
    cout << "\nOptimal id for f16 should be: 4" << "\nComputed optimal id is: " << b2.computeSimilarityId(&f16);
    cout << "\nOptimal id for f18 should be: 16" << "\nComputed optimal id is: " << b2.computeSimilarityId(&f18);
    cout << "\nOptimal id for f19 should be: 7" << "\nComputed optimal id is: " << b2.computeSimilarityId(&f19);
    
    cout << endl;
    return 0;
}