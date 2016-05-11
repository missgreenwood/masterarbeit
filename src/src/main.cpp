//  main.cpp, Judith Greif
//  Description: Test driver

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
    
    // Test driver for class BloomFilter
    // Instantiate one Bloom filter and call its methods
    
    cout << "CLASS BloomFilter" << endl;
    cout << "-----------------" << endl << endl;
    cout << "Create instance of BloomFilter (f1)" << endl << endl;
    BloomFilter f1(10, 0);
    cout << "Id: " << f1.getId() << endl;
    cout << "Size: " << f1.getSize() << endl;
    cout << "Data: ";
    f1.printData();
    cout << "Associated int array: ";
    f1.printArr();
    cout << endl << "Fill filter with random values 0 or 1" << endl << endl;
    f1.initRandom();
    f1.printData();
    cout << "Associated int array: ";
    f1.printArr();
    cout << endl << endl << endl;
    
    
    // Test driver for class BloomFilterVec
    // Instantiate Bloom filter vectors and and call their methods
    
    cout << "CLASS BloomFilterVec (VECTOR OF BloomFilter OBJECTS)" << endl;
    cout << "----------------------------------------------------" << endl << endl;
    cout << "Create instance of BloomFilterVec of custom size 2 (v2)" << endl << endl;
    BloomFilterVec v2(2);
    cout << endl << "Fill all filters in vector with random values 0 or 1" << endl << endl;
    v2.initRandom();
    cout << "Create instance of BloomFilterVec with default parameters (v1)" << endl << endl;
    BloomFilterVec v1;
    cout << endl << "Fill all filters in vector with random values 0 or 1" << endl << endl;
    v1.initRandom();
    cout << endl << endl << endl;
    
    
    // Test driver for Bloom filter library (bloom_filter.h)
    
    cout << "CLASS bloom_filter FROM LIBRARY bloom_filter.hpp" << endl;
    cout << "------------------------------------------------" << endl << endl;
    
    cout << "Choose parameters: ";
    bloom_parameters parameters;
    
    // How many elements per Bloom filter do we expect to insert?
    parameters.projected_element_count = 50;
    
    // Maximum tolerable false positive probability? [0,1]
    parameters.false_positive_probability = 0.0001;  // 1 in 10000

    cout << "Projected element count = " << parameters.projected_element_count << ", maximum false probability = " << parameters.false_positive_probability << endl << endl;
    
    if (!parameters) {
        cout << "Error - Invalid set of Bloom filter parameters!" << endl;
        return 1;
    }
    
    // Instantiate one Bloom filter
    cout << "Create instance of bloom_filter with seleceted parameters (f2)" << endl << endl;
    bloom_filter f2(parameters);
    
    string str_list[] = {"AbC", "iJk", "XYZ"};
    
    // Insert strings into Bloom filter f2
    cout << "Insert strings into filter: \"AbC\", \"iJk\", \"XYZ\"" << endl << endl;
    for (int i=0; i<(sizeof(str_list)/sizeof(string)); i++) {
        f2.insert(str_list[i]);
    }
    
    // Query Bloom filter for existence of strings
    cout << "Query filter for existence of strings" << endl << endl;
    for (size_t i=0; i<(sizeof(str_list)/sizeof(string)); i++) {
        if (f2.contains(str_list[i])) {
            cout << "f2 contains: " << str_list[i] << endl;
        }
    }
    cout << endl << endl << endl;
    
    
    // Test driver for class BTree
    cout << "CLASS BTree";
    cout << "\n-----------";
    cout << "\n\nCreate instance of BTree with minimum degree 3 (t1)";
    BTree t1(3);
    cout << "\n\nInsert keys into t1: 10, 20, 30, 40, 50, 60, 70, 80, 90";
    t1.insert(10);
    t1.insert(20);
    t1.insert(30);
    t1.insert(40);
    t1.insert(50);
    t1.insert(60);
    t1.insert(70);
    t1.insert(80);
    t1.insert(90);
    cout << "\nTraverse the constructed tree (start with leftmost child, recursively print leftmost child, repeat process for remaining children and keys, print rightmost child last):";
    t1.traverse();
    cout << "\nSearch for existing key 10 in t1: ";
    BTreeNode *tmp = t1.search(10);
    if (tmp == NULL) {
        cout << "Error! Key 10 should be in t1" << endl;
    }
    else {
        cout << "t1 contains key 10" << endl;
    }
    cout << "\nSearch for non existing key 11 in t1: ";
    tmp = t1.search(11);
    if (tmp == NULL) {
        cout << "t1 does not contain key 11" << endl;
    }
    else {
        cout << "Error! Key 11 should not be in t1" << endl;
    }
    cout << "\nCreate instance of BTree with minimum degree 3 (t2)";
    cout << "\n\nInsert keys into t2: 1, 3, 7, 10, 11, 13, 14, 15, 18, 16, 19, 24, 25, 26, 21, 4, 5, 20, 22, 2, 17, 12, 6";
    BTree t2(3);
    t2.insert(1);
    t2.insert(3);
    t2.insert(7);
    t2.insert(10);
    t2.insert(11);
    t2.insert(13);
    t2.insert(14);
    t2.insert(15);
    t2.insert(18);
    t2.insert(16);
    t2.insert(19);
    t2.insert(24);
    t2.insert(25);
    t2.insert(26);
    t2.insert(21);
    t2.insert(4);
    t2.insert(5);
    t2.insert(20);
    t2.insert(22);
    t2.insert(2);
    t2.insert(17);
    t2.insert(12);
    t2.insert(6);
    cout << "\n\nTraverse the constructed tree (start with leftmost child, recursively print leftmost child, repeat process for remaining children and keys, print rightmost child last):";
    t2.traverse();
    cout << "\nDelete key 6" << endl;
    t2.remove(6);
    cout << "Traverse t2:";
    t2.traverse();
    cout << "\nDelete key 13" << endl;
    t2.remove(13);
    cout << "Traverse t2:";
    t2.traverse();
    cout << "\nDelete key 7" << endl;
    t2.remove(7);
    cout << "Traverse t2:";
    t2.traverse();
    cout << "\nDelete key 4" << endl;
    t2.remove(4);
    cout << "Traverse t2:";
    t2.traverse();
    cout << "\nDelete key 2" << endl;
    t2.remove(2);
    cout << "Traverse t2:";
    t2.traverse();
    cout << "\nDelete key 16" << endl;
    t2.remove(16);
    cout << "Traverse t2:";
    t2.traverse();
    cout << endl << endl << endl;
    
    // Test driver for class BloomFilterTree
    cout << "CLASS BloomFilterTree";
    cout << "\n---------------------\n\n";
    cout << "Create instance of BloomFilterTree with minimum degree 3 (b1)\n\n";
    BloomFilterTree b1(3);
    
    // TODO
    
    // Test driver for class BPlusTree
    cout << "\nCLASS BPlusTree";
    cout << "\n----------------\n\n";
    cout << "\n\nCreate leaf with minimum degree 3/max. elements 5 (l1)";
    BPlusLeaf l1(3);
    cout << "\n\nInsert keys into l1: 1, 3, 7, 8, 9";
    l1.insert(1);
    l1.insert(3);
    l1.insert(7);
    l1.insert(8);
    l1.insert(9);
    cout << "\nTraverse l1:";
    l1.traverse();
    cout << "\n\nCheck index function:" << endl;
    int *keys = l1.getKeys();
    for (int i=0; i<l1.getCount(); i++) {
        cout << "Key: " << keys[i] << ", index: " << l1.indexOfKey(keys[i]) << endl; 
    }
    cout << "\nCheck remove function for leaf:";
    cout << "\n\nTry to remove non existing key 23 from l1:\n";
    l1.remove(23);
    cout << "\n\nRemove key 1 from l1:\n";
    l1.remove(1);
    l1.traverse();
    cout << "\n\nRemove keys 3 and 7 from l1:\n";
    l1.remove(3);
    l1.remove(7);
    l1.traverse();
    cout << "\n\nRemove key 8 from l1, should not create underflow:\n";
    l1.remove(8);
    l1.traverse();
    cout << "\n\nRemove last remaining key 9 from l1, should not create underflow:\n";
    l1.remove(9);
    l1.traverse(); 
    cout << "\n\nCreate instance of BPlusTree with minimum degree 2/max. elements 3 (b3)";
    BPlusTree b3(2);
    cout << "\n\nInsert keys into b2: 1, 4, 7, 10, 17, 25\n";
    b3.insert(1);
    b3.insert(4);
    b3.insert(7);
    b3.insert(10);
    b3.insert(17);
    b3.insert(25);
    cout << "Traverse b3: ";
    b3.traverse();
    cout << "\nSearch for existing keys 1, 4, 7, 10 in b3: ";
    if (b3.contains(1)) {
        cout << "\nb3 contains key 1 ";
    }
    else {
        cout << "\nKey 1 not present in b3 ";
    }
    if (b3.contains(4)) {
        cout << "\nb3 contains key 4 ";
    }
    else {
        cout << "\nKey 4 not present in b3 ";
    }
    if (b3.contains(7)) {
        cout << "\nb3 contains key 7 ";
    }
    else {
        cout << "\nKey 7 not present in b3 ";
    }
    if (b3.contains(10)) {
        cout << "\nb3 contains key 10 ";
    }
    else {
        cout << "\nKey 10 not present in b3 ";
    }
    cout << "\nSearch for non existing key 5 in b3: ";
    if (b3.contains(5)) {
        cout << "\nError - b3 does not contain key 5, but it is said to be there ";
    }
    else {
        cout << "\nKey 5 not present in b3 ";
    }
    cout << "\nSearch for non existing key 0 in b3: ";
    if (b3.contains(0)) {
        cout << "\nError - b3 does not contain key 0, but it is said to be there ";
    }
    else {
        cout << "\nKey 0 not present in b3 ";
    }cout << "\nSearch for non existing key 23 in b3: ";
    if (b3.contains(23)) {
        cout << "\nError - b3 does not contain key 23, but it is said to be there ";
    }
    else {
        cout << "\nKey 23 not present in b3 ";
    }
    
    cout << "\n\nCheck correct tree construction:" << endl;
    cout << "Root's keys:";
    int *rootKeys = b3.root->getKeys();
    for (int i=0; i<b3.root->getCount(); i++) {
        cout << " " << rootKeys[i];
    }
    cout << "\nLeft child's keys:";
    BPlusNode *leaf1 = b3.search(1);
    int *leftChildKeys = leaf1->getKeys();
    for (int i=0; i<leaf1->getCount(); i++) {
        cout << " " << leftChildKeys[i];
    }
    cout << "\nMiddle child's keys:";
    BPlusNode *leaf2 = b3.search(10);
    int *MiddleChildKeys = leaf2->getKeys();
    for (int i=0; i<leaf2->getCount(); i++) {
        cout << " " << MiddleChildKeys[i];
    }
    cout << "\nRight child's keys:";
    BPlusNode *leaf3 = b3.search(25);
    int *RightChildKeys = leaf3->getKeys();
    for (int i=0; i<leaf2->getCount(); i++) {
        cout << " " << RightChildKeys[i];
    }
    cout << endl;
    return 0;
}
