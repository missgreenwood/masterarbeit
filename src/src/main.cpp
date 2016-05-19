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
    cout << "Create instance of bloom_filter with seleceted parameters (f27)" << endl << endl;
    bloom_filter f27(parameters);
    
    string str_list[] = {"AbC", "iJk", "XYZ"};
    
    // Insert strings into Bloom filter f2
    cout << "Insert strings into filter: \"AbC\", \"iJk\", \"XYZ\"" << endl << endl;
    for (int i=0; i<(sizeof(str_list)/sizeof(string)); i++) {
        f27.insert(str_list[i]);
    }
    
    // Query Bloom filter for existence of strings
    cout << "Query filter for existence of strings" << endl << endl;
    for (size_t i=0; i<(sizeof(str_list)/sizeof(string)); i++) {
        if (f27.contains(str_list[i])) {
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
    
    
    // Test driver for class BPlusTree
    cout << "CLASS BPlusTree";
    cout << "\n----------------\n\n";
    cout << "Create leaf with minimum degree 3/max. elements 5 (l1)";
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
    cout << "\n\nInsert keys into b3: 1, 4, 7, 10, 17, 25, 2, 8\n";
    b3.insert(1);
    b3.insert(4);
    b3.insert(7);
    b3.insert(10);
    b3.insert(17);
    b3.insert(25);
    b3.insert(2);
    b3.insert(8);
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
    for (int i=0; i<leaf3->getCount(); i++) {
        cout << " " << RightChildKeys[i];
    }
    
    cout << "\n\nCheck remove function:" << endl << endl;
    cout << "CASE 1 - Try to remove non existing key (3): ";
    b3.remove(3);
    
    cout << "\n\nCASE 2 - Remove from leaf, no underflow (1):";
    b3.remove(1);
    cout << "\nRoot's keys:";
    for (int i=0; i<b3.root->getCount(); i++) {
        cout << " " << rootKeys[i];
    }
    cout << "\nLeft child's keys:";
    leaf1 = b3.search(2);
    for (int i=0; i<leaf1->getCount(); i++) {
        cout << " " << leftChildKeys[i];
    }
    cout << "\nMiddle child's keys:";
    leaf2 = b3.search(8);
    for (int i=0; i<leaf2->getCount(); i++) {
        cout << " " << MiddleChildKeys[i];
    }
    cout << "\nRight child's keys:";
    for (int i=0; i<leaf3->getCount(); i++) {
        cout << " " << RightChildKeys[i];
    }
    cout << endl;
    b3.traverse();
    
    cout << "\n\nCASE 3a - Underflow, borrow from previous sibling (17):\n";
    b3.remove(17);
    cout << "Left child's keys:";
    leaf1 = b3.search(2);
    for (int i=0; i<leaf1->getCount(); i++) {
        cout << " " << leftChildKeys[i];
    }
    cout << "\nMiddle child's keys:";
    leaf2 = b3.search(8);
    for (int i=0; i<leaf2->getCount(); i++) {
        cout << " " << MiddleChildKeys[i];
    }
    cout << "\nRight child's keys:";
    for (int i=0; i<leaf3->getCount(); i++) {
        cout << " " << RightChildKeys[i];
    }
    cout << endl;
    b3.traverse();
    
    cout << "\n\nInsert key 11 into b3: ";
    b3.insert(11);
    b3.traverse();
    
    cout << "\n\nCASE 3b - Underflow, borrow from next sibling (8):\n";
    b3.remove(8);
    cout << "Left child's keys:";
    leaf1 = b3.search(2);
    for (int i=0; i<leaf1->getCount(); i++) {
        cout << " " << leftChildKeys[i];
    }
    cout << "\nMiddle child's keys:";
    leaf2 = b3.search(10);
    for (int i=0; i<leaf2->getCount(); i++) {
        cout << " " << MiddleChildKeys[i];
    }
    cout << "\nRight child's keys:";
    leaf3 = b3.search(25);
    for (int i=0; i<leaf3->getCount(); i++) {
        cout << " " << RightChildKeys[i];
    }
    cout << endl;
    b3.traverse();
    
    cout << "\n\nCASE 4a - Underflow, merge with previous sibling (10):\n";
    b3.remove(10);
    cout << "\nLeft child's keys:";
    leaf1 = b3.search(2);
    for (int i=0; i<leaf1->getCount(); i++) {
        cout << " " << leftChildKeys[i];
    }
    cout << "\nRight child's keys:";
    leaf2 = b3.search(25);
    int *rightChildKeys = leaf2->getKeys();
    for (int i=0; i<leaf2->getCount(); i++) {
        cout << " " << rightChildKeys[i];
    }
    cout << endl;
    b3.traverse();
    cout << "\n\nInsert key 12 into b3: ";
    b3.insert(12);
    b3.traverse();
    cout << "\n\nCASE 4b - Underflow, merge with next sibling (4, 7):\n";
    b3.remove(4);
    b3.remove(7);
    cout << "Left child's keys:";
    for (int i=0; i<leaf1->getCount(); i++) {
        cout << " " << leftChildKeys[i];
    }
    cout << "\nRight child's keys:";
    for (int i=0; i<leaf2->getCount(); i++) {
        cout << " " << rightChildKeys[i];
    }
    cout << endl;
    b3.traverse();
    
    cout << "\n\nCASE 5 - Underflow in parent, parent is root (12):\n";
    b3.remove(12);
    cout << endl;
    b3.traverse();
    
    cout << "\n\nCreate instance of BPlusTree with minimum degree 2/max. elements 3 (b2)";
    BPlusTree b2(2);
    cout << "\nInsert keys into b2: 1, 3, 4, 5, 6, 7, 8, 26, 2, 11, 25\n";
    b2.insert(1);
    b2.insert(3);
    b2.insert(4);
    b2.insert(5);
    b2.insert(6);
    b2.insert(7);
    b2.insert(8);
    b2.insert(26);
    b2.insert(2);
    b2.insert(11);
    b2.insert(25);
    b2.traverse();
    rootKeys = b3.root->getKeys();
    cout << "\nRoot's keys:";
    for (int i=0; i<b2.root->getCount(); i++) {
        cout << " " << rootKeys[i];
    }
    leaf1 = b2.search(3);
    leaf2 = b2.search(5);
    leaf3 = b2.search(7);
    BPlusNode *leaf5 = b2.search(26);
    BPlusNode *leftIndex = leaf1->getParent();
    int *leftIndexKeys = leftIndex->getKeys();
    BPlusNode *rightIndex = leaf5->getParent();
    int *rightIndexKeys = rightIndex->getKeys();
    cout << "\nLeft index node's keys:";
    for (int i=0; i<leftIndex->getCount(); i++) {
        cout << " " << leftIndexKeys[i];
    }
    cout << "\nRight index node's keys:";
    for (int i=0; i<rightIndex->getCount(); i++) {
        cout << " " << rightIndexKeys[i];
    }
    cout << "\n\nCASE 6a - Underflow in parent, borrow from previous index node (25):\n";
    b2.remove(25);
    cout << "\nRoot's keys:";
    for (int i=0; i<b2.root->getCount(); i++) {
        cout << " " << rootKeys[i];
    }
    cout << "\nLeft index node's keys:";
    for (int i=0; i<leftIndex->getCount(); i++) {
        cout << " " << leftIndexKeys[i];
    }
    rightIndex = leaf5->getParent();
    cout << "\nRight index node's keys:";
    for (int i=0; i<rightIndex->getCount(); i++) {
        cout << " " << rightIndexKeys[i];
    }
    cout << endl;
    b2.traverse();
    cout << endl;
    
    cout << "\nInsert keys into into b2: 9, 27\n";
    b2.insert(9);
    b2.insert(27);
    b2.traverse();
    
    cout << "\n\nCASE 6b - Underflow in parent, borrow from next index node (4, 5):\n";
    b2.remove(4);
    b2.remove(5);
    cout << "\nRoot's keys:";
    for (int i=0; i<b2.root->getCount(); i++) {
        cout << " " << rootKeys[i];
    }
    cout << "\nLeft index node's keys:";
    for (int i=0; i<leftIndex->getCount(); i++) {
        cout << " " << leftIndexKeys[i];
    }
    leaf5 = b2.search(27);
    rightIndex = leaf5->getParent();
    cout << "\nRight index node's keys:";
    for (int i=0; i<rightIndex->getCount(); i++) {
        cout << " " << rightIndexKeys[i];
    }
    cout << endl;
    b2.traverse();
    
    /* cout << "\n\nCASE 7a - Underflow in parent, merge parent with previous index node (11, 26):\n";
     b2.remove(11);
     b2.remove(26);
     cout << endl;
     b2.traverse();
     
     cout << "\n\nCASE 7b - Underflow in parent, merge parent with next index node (3, 6):\n";
     b2.remove(3);
     b2.remove(6);
     cout << endl;
     b2.traverse(); */
    
    // Test driver for class BloomFilter
    
    cout << "\n\n\nCLASS BloomFilter" << endl;
    cout << "-----------------" << endl << endl;
    cout << "Create 15 instances of BloomFilter with ids 1, 4, 7, 10, 17, 25, 2, 8, 9, 26, 96, 97, 98, 99, array length 10 and random values\n\n";
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
    BloomFilter f97(10, 97);
    BloomFilter f98(10, 98);
    BloomFilter f99(10, 99);
    BloomFilter f101(10, 101);
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
    f96.printData();
    f97.initRandom();
    f97.printData();
    f98.initRandom();
    f98.printData();
    f99.initRandom();
    f99.printData();
    f101.initRandom();
    f101.printData();
    
    // Test driver for class BloomFilterLeaf
    cout << "\n\nCLASS BloomFilterLeaf";
    cout << "\n---------------------\n\n";
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
    
    cout << "Split l2 and traverse new sibling l3: ";
    BloomFilterLeaf *l3 = l2.split(&f101);
    l3->traverse();
    cout << endl;
    l3->traverseFilters(); 
    
    cout << "\nInsert filters into l2: f2, f8, f9, f101: ";
    l2.insert(&f2);
    l2.insert(&f8);
    l2.insert(&f9);
    l2.traverse();
    cout << endl;
    l2.traverseFilters();
    l2.insert(&f101);
    l2.traverse();
    cout << "\nTraverse new parent: ";
    BloomFilterNode *parent = l2.getParent();
    parent->traverse();
    cout << endl;
    parent->traverseFilters();
    
    // Test driver for class BloomFilterTree
    cout << "\n\nCLASS BloomFilterTree";
    cout << "\n---------------------\n\n";
    cout << "Create leaf with minimum degree 3/max. elements 6 (l2)\n\n";
    cout << "Create instance of BloomFilterTree with minimum degree 2/max. elements 4, filter size 10 (b1)\n\n";
    BloomFilterTree b1(2, 10);
    cout << "Insert filters into b1: f1, f4, f7, f10, f17\n";
    b1.insert(&f1);
    b1.insert(&f4);
    b1.insert(&f7);
    b1.insert(&f10);
    b1.insert(&f17);
    
    cout << "\nCheck tree management helper methods:\n\n";
    cout << "Compute Jaccard distance of f1 and f2: ";
    int *arr1 = l2.getFilters()[0];
    int *arr2 = l2.getFilters()[1];
    cout << l2.computeJaccard(arr1, arr2);
    
    BloomFilterNode *L1 = b1.search(1);
    BloomFilterNode *L2 = b1.search(17);
    cout << "\nCompute subset property of f1 and f2: ";
    cout << L1->isSubset(arr1, arr2);
    cout << "\nCompute subset property of f1 and identical filter: ";
    int arr3[] = { 0, 1, 1, 0, 0, 1, 0, 1, 1, 1 };
    cout << L1->isSubset(arr1, arr3);
    cout << "\nCompute subset property of f1 and actual subset filter: ";
    int arr4[] = { 0, 1, 1, 0, 0, 0, 0, 0, 0, 0 };
    cout << L1->isSubset(arr1, arr4);
    cout << "\nCompute f1 AND f2: ";
    int *arr5 = L1->logicalAnd(arr1, arr2);
    cout << "\nCompute f1 OR f2: ";
    arr5 = L1->logicalOr(arr1, arr2);
    
    
    BloomFilterNode *root = L1->getParent();
    cout << "\nLeft leaf: ";
    L1->traverse();
    cout << "\nLeft leaf's filters: ";
    L1->traverseFilters();
    cout << "\n\nRight leaf: ";
    L2->traverse();
    cout << "\nRight leaf's filters: ";
    L2->traverseFilters();
    rootKeys = root->getKeys();
    cout << "\n\nRoot's keys:";
    for (int i=0; i<root->getCount(); i++) {
        cout << " " << rootKeys[i];
    }
    cout << "\n\nTraverse b1: ";
    b1.traverse();
    cout << "\nTraverse b1 filters: ";
    b1.traverseFilters();
    
    cout << "\n\nInsert into b1: f25, f2, f8, f9, f26, f96, f97, f98, f99\n";
    b1.insert(&f25);
    b1.insert(&f2);
    b1.insert(&f8);
    b1.insert(&f9);
    b1.insert(&f26);
    b1.insert(&f96);
    b1.insert(&f97);
    b1.insert(&f98);
    b1.insert(&f99);
    b1.traverse();
    L1 = b1.search(1);
    root = L1->getParent();
    rootKeys = root->getKeys();
    cout << "\nRoot's keys:";
    for (int i=0; i<root->getCount(); i++) {
        cout << " " << rootKeys[i];
    }
    // b1.insert(&f101);
    cout << endl;
    BloomFilterNode *I1 = b1.search(1);
    I1->traverse();
    // b1.traverse(); */
    
    cout << endl;
    return 0;
}
