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
    
    /* cout << "\n\nCLASS BloomFilter" << endl;
    cout << "-----------------" << endl << endl;
    cout << "Create 11 instances of BloomFilter with ids 1, 4, 7, 10, 17, 25, 2, 8, 9, 26, 96, array length 10 and random values\n\n";
    BloomFilter f1(10, 1);
    BloomFilter f4(10, 4);
    BloomFilter f7(10, 7);
    BloomFilter f10(10, 10);
    BloomFilter f17(10, 17);
    BloomFilter f25(10, 25);
    BloomFilter f2(10, 2);
    BloomFilter f8(10, 8);
    BloomFilter f9(10, 9);
    BloomFilter f26(10, 26);
    BloomFilter f96(10, 96);
    cout << endl;
    f1.initRandom();
    f1.printData();
    f4.initRandom();
    f4.printData();
    f7.initRandom();
    f7.printData();
    f10.initRandom();
    f10.printData();
    f17.initRandom();
    f17.printData();
    f25.initRandom();
    f25.printData();
    f2.initRandom();
    f2.printData();
    f8.initRandom();
    f8.printData();
    f9.initRandom();
    f9.printData();
    f26.initRandom();
    f26.printData();
    f96.initRandom();
    f96.printData(); */
    
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
    /* cout << "Create instance of 2-level BloomFilterTree with minimum degree 2/max. elements 4, filter size 10 (b1)\n\n";
    BloomFilterTree b1(2, 10);
    cout << "Insert filters into b1: f1, f4, f7, f10, f17\n";
    b1.insert(&f1);
    b1.insert(&f4);
    b1.insert(&f7);
    b1.insert(&f10);
    b1.insert(&f17);
    
    cout << "\nCheck tree management helper methods:\n\n";
    BloomFilter f20(10, 20);
    f20.setValue(1, 1);
    f20.setValue(9, 1);
    BloomFilter *fA = l2.logicalAnd(&f1, &f2);
    BloomFilter *fO = l2.logicalOr(&f1, &f2);
    cout << "f1: ";
    f1.printArr();
    cout << "\nf2: ";
    f2.printArr();
    cout << endl;
    cout << "f20: ";
    f20.printArr();
    cout << "\n\nJaccard distance of f1 and f2: ";
    float jaccard = l2.computeJaccard(&f1, &f2);
    cout << jaccard;
    cout << "\nf2 subset of f1: ";
    bool subset = l2.isSubset(&f1, &f2);
    cout << subset;
    cout << "\nf1 subset of f1: ";
    subset = l2.isSubset(&f1, &f1);
    cout << subset << endl;
    cout << "f20 subset of f1: ";
    subset = l2.isSubset(&f1, &f20);
    cout << subset;
    cout << "\nf1 AND f2: ";
    fA->printArr();
    cout << "\nf1 OR f2: ";
    fO->printArr();
    
    cout << "\n\nCheck 2-level tree construction:\n";
    BloomFilterNode *L1 = b1.search(1);
    BloomFilterNode *L2 = b1.search(17);
    BloomFilterNode *root = b1.getRoot();
    cout << "\nLeft leaf: ";
    L1->traverse();
    cout << "\nLeft leaf filters: ";
    L1->traverseFilters();
    cout << "\nRight leaf: ";
    L2->traverse();
    cout << "\nRight leaf filters: ";
    L2->traverseFilters();
    rootKeys = root->getKeys();
    cout << "\nRoot keys:";
    for (int i=0; i<root->getCount(); i++) {
        cout << " " << rootKeys[i];
    }
    cout << "\nRoot filters:";
    for (int i=0; i<root->getCount(); i++) {
        cout << "|";
        root->filters[i]->printArr();
    }
    cout << "|";
    cout << "\nTraverse b1: ";
    b1.traverse();
    cout << "\nTraverse b1 filters: ";
    b1.traverseFilters();
    
    cout << "\n\nCheck search functions: ";
    cout << "\n\nSearch in leaf l2: key 1\n";
    BloomFilterNode *L3 = l2.search(1);
    L3->traverse();
    L3->traverseFilters();
    cout << "\nSearch in leaf l2: key 4\n";
    L3 = l2.search(4);
    L3->traverse();
    L3->traverseFilters();
    
    cout << "\n\nSearch in leaf l3: key 10\n";
    L3 = l3->search(10);
    L3->traverse();
    L3->traverseFilters();
    cout << "\nSearch in leaf l3: key 101\n";
    L3 = l3->search(101);
    L3->traverse();
    L3->traverseFilters();
    
    cout << "\n\nSearch in 2-level tree b2: key 1\n";
    L3 = b1.search(1);
    L3->traverse();
    L3->traverseFilters();
    cout << "\nSearch in 2-level tree b2: key 4\n";
    L3 = b1.search(4);
    L3->traverse();
    L3->traverseFilters();
    cout << "\nSearch in 2-level tree b2: key 17\n";
    L3 = b1.search(17);
    L3->traverse();
    L3->traverseFilters();
    cout << "\nSearch in 2-level tree b2: key 7\n";
    BloomFilterNode *L4 = b1.search(7);
    L4->traverse();
    L4->traverseFilters();
    
    cout << "\n\nCheck contains functions: ";
    cout << "\n\nLeaf l2 contains key 1: " << l2.contains(1);
    cout << "\nLeaf l2 contains key 127: " << l2.contains(127);
    cout << "\n\nBloomFilterIndexNode root contains key 1: " << root->contains(1);
    cout << "\nBloomFilterIndexNode root contains key 127: " << root->contains(127);
    cout << "\n\nBloomFilterTree b1 contains key 1: " << b1.contains(1);
    cout << "\nBloomFilterTree b1 contains key 7: " << b1.contains(7);
    cout << "\nBloomFilterTree b1 contains key 127: " << b1.contains(127);
    
    cout << "\n\nCheck 3-level tree construction:\n";
    cout << "\nInsert filters into b1: f25, f2, f8, f9, f26, f96, f97, f98, f99\n";
    b1.insert(&f25);
    b1.insert(&f2);
    b1.insert(&f8);
    b1.insert(&f9);
    b1.insert(&f26);
    b1.insert(&f96);
    b1.insert(&f97);
    b1.insert(&f98);
    b1.insert(&f99);
    cout << endl;
    b1.traverse();
    cout << "\n\nInsert filter into b1: f101\n";
    b1.insert(&f101);
    
    BloomFilterNode *I1 = b1.search(1)->getParent();
    cout << "\nLeft index node count: " << I1->getCount();
    cout << "\nLeft index node's keys:";
    leftIndexKeys = I1->getKeys();
    for (int i=0; i<I1->getCount(); i++) {
        cout << " " << leftIndexKeys[i];
    }
    
    BloomFilterNode *I2 = b1.search(96)->getParent();
    cout << "\n\nRight index node count: " << I2->getCount();
    cout << "\nRight index node keys: ";
    rightIndexKeys = I2->getKeys();
    for (int i=0; i<I2->getCount(); i++) {
        cout << " " << rightIndexKeys[i];
    }
    
    root = I1->getParent();
    cout << "\n\nRoot count: " << root->getCount();
    rootKeys = root->getKeys();
    cout << "\nRoot's keys: ";
    for (int i=0; i<root->getCount(); i++) {
        cout << " " << rootKeys[i];
    }
    cout << endl;
    b1.traverse();
    cout << endl;
    b1.traverseFilters();
    
    cout << "\n\nCheck level 4 tree construction:\n"; */
    cout << "Create instance of 4-level BloomFilterTree with minimum degree 1/max. elements 2, filter size 10 (b1)\n\n";
    BloomFilterTree b1(1, 10);
    cout << "Insert filter into into b1: 1\n";
    b1.insert(&v1.filters[0]);
    b1.traverse();
    cout << endl;
    cout << "\nCompute similarity of filters f4, f7, f10, f17, f25, f2, f8, f9, f26, f96 with tree root:\n\n";
    for (int i=0; i<v1.getSize(); i++) {
        cout << "jacc(root, filter " << i << "): " << b1.computeMaxJaccard(&v1.filters[i]) << endl;
    }
    cout << endl;
    return 0;
}