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
#include "bloom_filter_basic.hpp"
#include "bloom_filter_tree.hpp"
#include "bloom_filter.hpp"
// #include "b-tree.hpp"

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
    cout << "\n\nTraverse the constructed tree (start with leftmost child, recursively print leftmost child, repeat process for remaining children and keys, print rightmost child last):" ;
    t1.traverse();
    cout << "\n\nSearch for existing key 10 in t1: ";
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
    cout << endl;
    return 0;
}
