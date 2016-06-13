//  tests.cpp, Judith Greif
//  Description: Test drivers for all classes and methods


#include <iostream>
#include "BTree.hpp"
#include "BPlusTree.hpp"
#include "BloomFilterTree.hpp"
#include "BloomFilterList.hpp"

using namespace std;


int main(int argc, const char *argv[]) {
    
    // Class BTree
    cout << "CLASS BTree";
    cout << "\n-----------";
    cout << "\nCreate instance of BTree with minimum degree 3 (t1)";
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
    
    
    // Class BPlusTree
    cout << "CLASS BPlusTree";
    cout << "\n----------------\n";
    cout << "Create leaf with minimum degree 3/max. elements 5 (l7)";
    BPlusLeaf l7(3);
    cout << "\n\nInsert keys into l7: 1, 3, 7, 8, 9";
    l7.insert(1);
    l7.insert(3);
    l7.insert(7);
    l7.insert(8);
    l7.insert(9);
    cout << "\nTraverse l7:";
    l7.traverse();
    cout << "\n\nCheck index function:" << endl;
    int *keys = l7.getKeys();
    for (int i=0; i<l7.getCount(); i++) {
        cout << "Key: " << keys[i] << ", index: " << l7.indexOfKey(keys[i]) << endl;
    }
    cout << "\nCheck remove function for leaf:";
    cout << "\n\nTry to remove non existing key 23 from l7:\n";
    l7.remove(23);
    cout << "\n\nRemove key 1 from l7:\n";
    l7.remove(1);
    l7.traverse();
    cout << "\n\nRemove keys 3 and 7 from l7:\n";
    l7.remove(3);
    l7.remove(7);
    l7.traverse();
    cout << "\n\nRemove key 8 from l1, should not create underflow:\n";
    l7.remove(8);
    l7.traverse();
    cout << "\n\nRemove last remaining key 9 from l1, should not create underflow:\n";
    l7.remove(9);
    l7.traverse();
    cout << "\n\nCreate instance of BPlusTree with minimum degree 2/max. elements 3 (b7)";
    BPlusTree b7(2);
    cout << "\n\nInsert keys into b7: 1, 4, 7, 10, 17, 25, 2, 8\n";
    b7.insert(1);
    b7.insert(4);
    b7.insert(7);
    b7.insert(10);
    b7.insert(17);
    b7.insert(25);
    b7.insert(2);
    b7.insert(8);
    cout << "Traverse b7: ";
    b7.traverse();
    cout << "\nSearch for existing keys 1, 4, 7, 10 in b7: ";
    if (b7.contains(1)) {
        cout << "\nb7 contains key 1 ";
    }
    else {
        cout << "\nKey 1 not present in b7 ";
    }
    if (b7.contains(4)) {
        cout << "\nb7 contains key 4 ";
    }
    else {
        cout << "\nKey 4 not present in b7 ";
    }
    if (b7.contains(7)) {
        cout << "\nb7 contains key 7 ";
    }
    else {
        cout << "\nKey 7 not present in b7 ";
    }
    if (b7.contains(10)) {
        cout << "\nb7 contains key 10 ";
    }
    else {
        cout << "\nKey 10 not present in b7 ";
    }
    cout << "\nSearch for non existing key 5 in b7: ";
    if (b7.contains(5)) {
        cout << "\nError - b7 does not contain key 5, but it is said to be there ";
    }
    else {
        cout << "\nKey 5 not present in b7 ";
    }
    cout << "\nSearch for non existing key 0 in b7: ";
    if (b7.contains(0)) {
        cout << "\nError - b7 does not contain key 0, but it is said to be there ";
    }
    else {
        cout << "\nKey 0 not present in b7 ";
    }cout << "\nSearch for non existing key 23 in b7: ";
    if (b7.contains(23)) {
        cout << "\nError - b7 does not contain key 23, but it is said to be there ";
    }
    else {
        cout << "\nKey 23 not present in b7 ";
    }
    
    cout << "\n\nCheck correct tree construction:" << endl;
    cout << "Root's keys:";
    int *rootKeys = b7.root->getKeys();
    for (int i=0; i<b7.root->getCount(); i++) {
        cout << " " << rootKeys[i];
    }
    cout << "\nLeft child's keys:";
    BPlusNode *leaf1 = b7.search(1);
    int *leftChildKeys = leaf1->getKeys();
    for (int i=0; i<leaf1->getCount(); i++) {
        cout << " " << leftChildKeys[i];
    }
    cout << "\nMiddle child's keys:";
    BPlusNode *leaf2 = b7.search(10);
    int *MiddleChildKeys = leaf2->getKeys();
    for (int i=0; i<leaf2->getCount(); i++) {
        cout << " " << MiddleChildKeys[i];
    }
    cout << "\nRight child's keys:";
    BPlusNode *leaf3 = b7.search(25);
    int *RightChildKeys = leaf3->getKeys();
    for (int i=0; i<leaf3->getCount(); i++) {
        cout << " " << RightChildKeys[i];
    }
    
    cout << "\n\nCheck remove function:" << endl << endl;
    cout << "CASE 1 - Try to remove non existing key (3): ";
    b7.remove(3);
    
    cout << "\n\nCASE 2 - Remove from leaf, no underflow (1):";
    b7.remove(1);
    cout << "\nRoot's keys:";
    for (int i=0; i<b7.root->getCount(); i++) {
        cout << " " << rootKeys[i];
    }
    cout << "\nLeft child's keys:";
    leaf1 = b7.search(2);
    for (int i=0; i<leaf1->getCount(); i++) {
        cout << " " << leftChildKeys[i];
    }
    cout << "\nMiddle child's keys:";
    leaf2 = b7.search(8);
    for (int i=0; i<leaf2->getCount(); i++) {
        cout << " " << MiddleChildKeys[i];
    }
    cout << "\nRight child's keys:";
    for (int i=0; i<leaf3->getCount(); i++) {
        cout << " " << RightChildKeys[i];
    }
    cout << endl;
    b7.traverse();
    
    cout << "\n\nCASE 3a - Underflow, borrow from previous sibling (17):\n";
    b7.remove(17);
    cout << "Left child's keys:";
    leaf1 = b7.search(2);
    for (int i=0; i<leaf1->getCount(); i++) {
        cout << " " << leftChildKeys[i];
    }
    cout << "\nMiddle child's keys:";
    leaf2 = b7.search(8);
    for (int i=0; i<leaf2->getCount(); i++) {
        cout << " " << MiddleChildKeys[i];
    }
    cout << "\nRight child's keys:";
    for (int i=0; i<leaf3->getCount(); i++) {
        cout << " " << RightChildKeys[i];
    }
    cout << endl;
    b7.traverse();
    
    cout << "\n\nInsert key 11 into b7: ";
    b7.insert(11);
    b7.traverse();
    
    cout << "\n\nCASE 3b - Underflow, borrow from next sibling (8):\n";
    b7.remove(8);
    cout << "Left child's keys:";
    leaf1 = b7.search(2);
    for (int i=0; i<leaf1->getCount(); i++) {
        cout << " " << leftChildKeys[i];
    }
    cout << "\nMiddle child's keys:";
    leaf2 = b7.search(10);
    for (int i=0; i<leaf2->getCount(); i++) {
        cout << " " << MiddleChildKeys[i];
    }
    cout << "\nRight child's keys:";
    leaf3 = b7.search(25);
    for (int i=0; i<leaf3->getCount(); i++) {
        cout << " " << RightChildKeys[i];
    }
    cout << endl;
    b7.traverse();
    
    cout << "\n\nCASE 4a - Underflow, merge with previous sibling (10):\n";
    b7.remove(10);
    cout << "\nLeft child's keys:";
    leaf1 = b7.search(2);
    for (int i=0; i<leaf1->getCount(); i++) {
        cout << " " << leftChildKeys[i];
    }
    cout << "\nRight child's keys:";
    leaf2 = b7.search(25);
    int *rightChildKeys = leaf2->getKeys();
    for (int i=0; i<leaf2->getCount(); i++) {
        cout << " " << rightChildKeys[i];
    }
    cout << endl;
    b7.traverse();
    cout << "\n\nInsert key 12 into b3: ";
    b7.insert(12);
    b7.traverse();
    cout << "\n\nCASE 4b - Underflow, merge with next sibling (4, 7):\n";
    b7.remove(4);
    b7.remove(7);
    cout << "Left child's keys:";
    for (int i=0; i<leaf1->getCount(); i++) {
        cout << " " << leftChildKeys[i];
    }
    cout << "\nRight child's keys:";
    for (int i=0; i<leaf2->getCount(); i++) {
        cout << " " << rightChildKeys[i];
    }
    cout << endl;
    b7.traverse();
    
    cout << "\n\nCASE 5 - Underflow in parent, parent is root (12):\n";
    b7.remove(12);
    cout << endl;
    b7.traverse();
    
    cout << "\n\nCreate instance of BPlusTree with minimum degree 2/max. elements 3 (b6)";
    BPlusTree b6(2);
    cout << "\nInsert keys into b6: 1, 3, 4, 5, 6, 7, 8, 26, 2, 11, 25\n";
    b6.insert(1);
    b6.insert(3);
    b6.insert(4);
    b6.insert(5);
    b6.insert(6);
    b6.insert(7);
    b6.insert(8);
    b6.insert(26);
    b6.insert(2);
    b6.insert(11);
    b6.insert(25);
    b6.traverse();
    rootKeys = b6.root->getKeys();
    cout << "\nRoot's keys:";
    for (int i=0; i<b6.root->getCount(); i++) {
        cout << " " << rootKeys[i];
    }
    leaf1 = b6.search(3);
    leaf2 = b6.search(5);
    leaf3 = b6.search(7);
    BPlusNode *leaf5 = b6.search(26);
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
    b6.remove(25);
    cout << "\nRoot's keys:";
    for (int i=0; i<b6.root->getCount(); i++) {
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
    b6.traverse();
    cout << endl;
    
    cout << "\nInsert keys into into b6: 9, 27\n";
    b6.insert(9);
    b6.insert(27);
    b6.traverse();
    
    cout << "\n\nCASE 6b - Underflow in parent, borrow from next index node (4, 5):\n";
    b6.remove(4);
    b6.remove(5);
    cout << "\nRoot's keys:";
    for (int i=0; i<b6.root->getCount(); i++) {
        cout << " " << rootKeys[i];
    }
    cout << "\nLeft index node's keys:";
    for (int i=0; i<leftIndex->getCount(); i++) {
        cout << " " << leftIndexKeys[i];
    }
    leaf5 = b6.search(27);
    rightIndex = leaf5->getParent();
    cout << "\nRight index node's keys:";
    for (int i=0; i<rightIndex->getCount(); i++) {
        cout << " " << rightIndexKeys[i];
    }
    cout << endl;
    b6.traverse();
    
    // TODO
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
    
    // Class BloomFilter
    
    cout << "\n\n\nCLASS BloomFilter" << endl;
    cout << "-----------------" << endl << endl;
    cout << "Create 22 instances of BloomFilter with ids 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 25, 26, 96, array length 10, random values\n";
    BloomFilter f1(10, 1);
    BloomFilter f2(10, 2);
    BloomFilter f3(10, 3);
    BloomFilter f4(10, 4);
    BloomFilter f5(10, 5);
    BloomFilter f6(10, 6);
    BloomFilter f7(10, 7);
    BloomFilter f8(10, 8);
    BloomFilter f9(10, 9);
    BloomFilter f10(10, 10);
    BloomFilter f11(10, 11);
    BloomFilter f12(10, 12);
    BloomFilter f13(10, 13);
    BloomFilter f14(10, 14);
    BloomFilter f15(10, 15);
    BloomFilter f16(10, 16);
    BloomFilter f17(10, 17);
    BloomFilter f18(10, 18);
    BloomFilter f19(10, 19);
    BloomFilter f25(10, 25);
    BloomFilter f26(10, 26);
    BloomFilter f96(10, 96);
    cout << endl;
    f1.initRandom();
    f1.printData();
    f2.initRandom();
    f2.printData();
    f3.initRandom();
    f3.printData();
    f4.initRandom();
    f4.printData();
    f5.initRandom();
    f5.printData();
    f6.initRandom();
    f6.printData();
    f7.initRandom();
    f7.printData();
    f8.initRandom();
    f8.printData();
    f9.initRandom();
    f9.printData();
    f10.initRandom();
    f10.printData();
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
    f17.initRandom();
    f17.printData();
    f18.initRandom();
    f18.printData();
    f19.initRandom();
    f19.printData();
    f25.initRandom();
    f25.printData();
    f26.initRandom();
    f26.printData();
    f96.initRandom();
    f96.printData();
    
    // Class BloomFilterTree
    
    cout << "\n\n\nCLASS BloomFilterTree";
    cout << "\n---------------------\n\n";
    
    cout << "Create instance of 4-level BloomFilterTree with minimum degree 1/max. elements 2, filter size 10 (b1)\n\n";
    BloomFilterTree b1(1, 10);
    cout << "Insert filter into into b1: f1\n";
    b1.insert(&f1);
    b1.traverse();
    b1.traverseFilters();
    cout << endl;
    
    cout << "\nCreate BloomFilter vector (v1) and insert filters f4, f7, f10, f17, f25, f2, f8, f9, f26, f96\n\n";
    vector<BloomFilter> v1;
    v1.push_back(f4);
    v1.push_back(f7);
    v1.push_back(f10);
    v1.push_back(f17);
    v1.push_back(f25);
    v1.push_back(f2);
    v1.push_back(f8);
    v1.push_back(f9);
    v1.push_back(f26);
    v1.push_back(f96);
    for (int i=0; i<10; i++) {
        v1[i].printData();
    }
    
    cout << "\n\nCheck Jaccard distance computation";
    cout << "\n----------------------------------";
    cout << "\nf3: ";
    f3.printArr();
    cout << "\nf5: ";
    f5.printArr();
    cout << "\nf6: ";
    f6.printArr();
    cout << "\nf16: ";
    f16.printArr();
    cout << "\nf18: ";
    f18.printArr();
    cout << "\nf19: ";
    f19.printArr();
    BloomFilterLeaf l4(3, 10);
    l4.insert(&f3);
    l4.insert(&f5);
    l4.insert(&f6);
    l4.insert(&f16);
    l4.insert(&f18);
    l4.insert(&f19);
    cout << "\n\nFraction of zeros(f3): " << f3.fractionOfZeros();
    cout << "\nEstimated size(f3): " << f3.eSize();
    
    cout << "\n\nFraction of zeros(f5): " << f5.fractionOfZeros();
    cout << "\nEstimated size(f5): " << f5.eSize();
    
    cout << "\n\nFraction of zeros(f6): " << f6.fractionOfZeros();
    cout << "\nEstimated size(f6): " << f6.eSize();
    
    cout << "\n\nFraction of zeros(f16): " << f16.fractionOfZeros();
    cout << "\nEstimated size(f16): " << f16.eSize();
    
    cout << "\n\nFraction of zeros(f18): " << f18.fractionOfZeros();
    cout << "\nEstimated size(f18): " << f18.eSize();
    
    cout << "\n\nFraction of zeros(f19): " << f19.fractionOfZeros();
    cout << "\nEstimated size(f19): " << f19.eSize();
    
    cout << "\n\neUnion(f3, f16): " << l4.eUnion(l4.filters[0], l4.filters[3]);
    cout << "\neUnion(f3, f18): " << l4.eUnion(l4.filters[0], l4.filters[4]);
    cout << "\neUnion(f3, f19): " << l4.eUnion(l4.filters[0], l4.filters[5]);
    
    cout << "\n\neUnion(f5, f16): " << l4.eUnion(l4.filters[1], l4.filters[3]);
    cout << "\neUnion(f5, f18): " << l4.eUnion(l4.filters[1], l4.filters[4]);
    cout << "\neUnion(f5, f19): " << l4.eUnion(l4.filters[1], l4.filters[5]);
    
    cout << "\n\neUnion(f6, f16): " << l4.eUnion(l4.filters[2], l4.filters[3]);
    cout << "\neUnion(f6, f18): " << l4.eUnion(l4.filters[2], l4.filters[4]);
    cout << "\neUnion(f6, f19): " << l4.eUnion(l4.filters[2], l4.filters[5]);
    
    cout << "\n\neIntersect(f3, f16): " << l4.eIntersect(l4.filters[0], l4.filters[3]);
    cout << "\neIntersect(f3, f18): " << l4.eIntersect(l4.filters[0], l4.filters[4]);
    cout << "\neIntersect(f3, f19): " << l4.eIntersect(l4.filters[0], l4.filters[5]);
    
    cout << "\n\neIntersect(f5, f16): " << l4.eIntersect(l4.filters[1], l4.filters[3]);
    cout << "\neIntersect(f5, f18): " << l4.eIntersect(l4.filters[1], l4.filters[4]);
    cout << "\neIntersect(f5, f19): " << l4.eIntersect(l4.filters[1], l4.filters[5]);
    
    cout << "\n\neIntersect(f6, f16): " << l4.eIntersect(l4.filters[2], l4.filters[3]);
    cout << "\neIntersect(f6, f18): " << l4.eIntersect(l4.filters[2], l4.filters[4]);
    cout << "\neIntersect(f6, f19): " << l4.eIntersect(l4.filters[2], l4.filters[5]);
    
    cout << "\n\njacc(f3, f16): " << l4.computeJaccard(l4.filters[0], l4.filters[3]);
    cout << "\njacc(f3, f18): " << l4.computeJaccard(l4.filters[0], l4.filters[4]);
    cout << "\njacc(f3, f19): " << l4.computeJaccard(l4.filters[0], l4.filters[5]);
    
    cout << "\n\njacc(f5, f16): " << l4.computeJaccard(l4.filters[1], l4.filters[3]);
    cout << "\njacc(f5, f18): " << l4.computeJaccard(l4.filters[1], l4.filters[4]);
    cout << "\njacc(f5, f19): " << l4.computeJaccard(l4.filters[1], l4.filters[5]);
    
    cout << "\n\njacc(f6, f16): " << l4.computeJaccard(l4.filters[2], l4.filters[3]);
    cout << "\njacc(f6, f18): " << l4.computeJaccard(l4.filters[2], l4.filters[4]);
    cout << "\njacc(f6, f19): " << l4.computeJaccard(l4.filters[2], l4.filters[5]);
    
    cout << "\n\nCompute Jaccard distance of filters f4, f7, f10, f17, f25, f2, f8, f9, f26, f96, f16 and tree root:\n\n";
    BloomFilterNode *root = b1.root;
    for (int i=0; i<10; i++) {
        cout << "jacc(f1, f" << v1[i].getId() << "): " << root->computeJaccard(root->filters[0], &v1[i]) << endl;
    }
    
    cout << "\nCreate instance of 4-level BloomFilterTree with minimum degree 1/max. elements 2, filter size 10 (b2)\n\n";
    BloomFilterTree b2(1, 10);
    cout << "Insert filters into b2: f3, f5, f6, f11, f12, f13, f14, f15\n";
    cout << "\nCompute minimum Jaccard distance of f16, f18, f19 and each intermediate tree state\n\n";
    b2.insert(&f3);
    cout << "Min jacc(b2, f16): " << b2.computeMinJaccard(&f16);
    cout << " (key " << b2.getMinJaccardKey(&f16) << ")\n";
    cout << "Min jacc(b2, f18): " << b2.computeMinJaccard(&f18);
    cout << " (key " << b2.getMinJaccardKey(&f18) << ")\n";
    cout << "Min jacc(b2, f19): " << b2.computeMinJaccard(&f19);
    cout << " (key " << b2.getMinJaccardKey(&f19) << ")\n\n";
    b2.insert(&f5);
    cout << "Min jacc(b2, f16): " << b2.computeMinJaccard(&f16);
    cout << " (key " << b2.getMinJaccardKey(&f16) << ")\n";
    cout << "Min jacc(b2, f18): " << b2.computeMinJaccard(&f18);
    cout << " (key " << b2.getMinJaccardKey(&f18) << ")\n";
    cout << "Min jacc(b2, f19): " << b2.computeMinJaccard(&f19);
    cout << " (key " << b2.getMinJaccardKey(&f19) << ")\n";
    b2.insert(&f6);
    cout << "\nMin jacc(b2, f16): " << b2.computeMinJaccard(&f16);
    cout << " (key " << b2.getMinJaccardKey(&f16) << ")\n";
    cout << "Min jacc(b2, f18): " << b2.computeMinJaccard(&f18);
    cout << " (key " << b2.getMinJaccardKey(&f18) << ")\n";
    cout << "Min jacc(b2, f19): " << b2.computeMinJaccard(&f19);
    cout << " (key " << b2.getMinJaccardKey(&f19) << ")\n";
    b2.insert(&f11);
    cout << "\nMin jacc(b2, f16): " << b2.computeMinJaccard(&f16);
    cout << " (key " << b2.getMinJaccardKey(&f16) << ")\n";
    cout << "Min jacc(b2, f18): " << b2.computeMinJaccard(&f18);
    cout << " (key " << b2.getMinJaccardKey(&f18) << ")\n";
    cout << "Min jacc(b2, f19): " << b2.computeMinJaccard(&f19);
    cout << " (key " << b2.getMinJaccardKey(&f19) << ")\n";
    b2.insert(&f12);
    cout << "\nMin jacc(b2, f16): " << b2.computeMinJaccard(&f16);
    cout << " (key " << b2.getMinJaccardKey(&f16) << ")\n";
    cout << "Min jacc(b2, f18): " << b2.computeMinJaccard(&f18);
    cout << " (key " << b2.getMinJaccardKey(&f18) << ")\n";
    cout << "Min jacc(b2, f19): " << b2.computeMinJaccard(&f19);
    cout << " (key " << b2.getMinJaccardKey(&f19) << ")\n";
    b2.insert(&f13);
    cout << "\nMin jacc(b2, f16): " << b2.computeMinJaccard(&f16);
    cout << " (key " << b2.getMinJaccardKey(&f16) << ")\n";
    cout << "Min jacc(b2, f18): " << b2.computeMinJaccard(&f18);
    cout << " (key " << b2.getMinJaccardKey(&f18) << ")\n";
    cout << "Min jacc(b2, f19): " << b2.computeMinJaccard(&f19);
    cout << " (key " << b2.getMinJaccardKey(&f19) << ")\n";
    b2.insert(&f14);
    cout << "\nMin jacc(b2, f16): " << b2.computeMinJaccard(&f16);
    cout << " (key " << b2.getMinJaccardKey(&f16) << ")\n";
    cout << "Min jacc(b2, f18): " << b2.computeMinJaccard(&f18);
    cout << " (key " << b2.getMinJaccardKey(&f18) << ")\n";
    cout << "Min jacc(b2, f19): " << b2.computeMinJaccard(&f19);
    cout << " (key " << b2.getMinJaccardKey(&f19) << ")\n";
    b2.insert(&f15);
    cout << "\nMin jacc(b2, f16): " << b2.computeMinJaccard(&f16);
    cout << " (key " << b2.getMinJaccardKey(&f16) << ")\n";
    cout << "Min jacc(b2, f18): " << b2.computeMinJaccard(&f18);
    cout << " (key " << b2.getMinJaccardKey(&f18) << ")\n";
    cout << "Min jacc(b2, f19): " << b2.computeMinJaccard(&f19);
    cout << " (key " << b2.getMinJaccardKey(&f19) << ")\n\n";
    b2.insert(&f16);
    
    cout << "\nCheck union filter construction";
    cout << "\n-------------------------------\n";
    b2.traverse();
    cout << endl;
    b2.traverseFilters();
    cout << endl;
    
    BloomFilterNode *L0 = b2.search(3);
    BloomFilterNode *L4 = b2.search(12);
    BloomFilterNode *L6 = b2.search(14);
    BloomFilterNode *I0 = L0->getParent();
    BloomFilterNode *I2 = L4->getParent();
    BloomFilterNode *I3 = L6->getParent();
    BloomFilterNode *I4 = I0->getParent();
    BloomFilterNode *I5 = I2->getParent();
    root = b2.getRoot();
    cout << "\nI0 union filter: ";
    I0->unionfilter->printArr();
    cout << "\nI3 union filter: ";
    I3->unionfilter->printArr();
    cout << "\nI4 union filter: ";
    I4->unionfilter->printArr();
    cout << "\nI5 union filter: ";
    I5->unionfilter->printArr();
    cout << "\nRoot union filter: ";
    root->unionfilter->printArr();
    
    // Class BloomFilterLeaf
    
    cout << "\n\n\nCLASS BloomFilterLeaf";
    cout << "\n---------------------\n";
    cout << "Create leaves with minimum degree 3/max. elements 6 (l2, l3)\n\n";
    BloomFilterLeaf l2(3, f3.getSize());
    BloomFilterLeaf l3(3, f3.getSize());
    cout << "Insert filters into l2: f3, f5, f6, f11, f12, f13\n";
    cout << "Insert filters into l3: f14, f15, f17, f25, f26, f96\n";
    l2.insert(&f3);
    l2.insert(&f5);
    l2.insert(&f6);
    l2.insert(&f11);
    l2.insert(&f12);
    l2.insert(&f13);
    l3.insert(&f14);
    l3.insert(&f15);
    l3.insert(&f17);
    l3.insert(&f25);
    l3.insert(&f26);
    l3.insert(&f96);
    cout << "\nTraverse l2: ";
    l2.traverse();
    cout << "\nTraverse l2 filters: ";
    l2.traverseFilters();
    cout << "\n\nMake l2 and l3 siblings and traverse both: ";
    l2.setNext(&l3);
    l3.setPrev(&l2);
    l2.traverse();
    l2.getNext()->traverse();
    
    cout << "\n\n\nCheck subset relations";
    cout << "\n----------------------\n";
    cout << "Create 11 instances of BloomFilter with array size 4, all possible and valid permutations\n";
    BloomFilter f100(4, 100);
    BloomFilter f101(4, 101);
    BloomFilter f102(4, 102);
    BloomFilter f103(4, 103);
    BloomFilter f104(4, 104);
    BloomFilter f105(4, 105);
    BloomFilter f106(4, 106);
    BloomFilter f107(4, 107);
    BloomFilter f108(4, 108);
    BloomFilter f109(4, 109);
    BloomFilter f110(4, 110);
    
    f100.setValue(0, 0);
    f100.setValue(1, 0);
    f100.setValue(2, 0);
    f100.setValue(3, 0);
    
    f101.setValue(0, 0);
    f101.setValue(1, 0);
    f101.setValue(2, 0);
    f101.setValue(3, 1);
    
    f102.setValue(0, 0);
    f102.setValue(1, 0);
    f102.setValue(2, 1);
    f102.setValue(3, 0);
    
    f103.setValue(0, 0);
    f103.setValue(1, 0);
    f103.setValue(2, 1);
    f103.setValue(3, 1);
    
    f104.setValue(0, 0);
    f104.setValue(1, 1);
    f104.setValue(2, 0);
    f104.setValue(3, 0);
    
    f105.setValue(0, 0);
    f105.setValue(1, 1);
    f105.setValue(2, 0);
    f105.setValue(3, 1);
    
    f106.setValue(0, 0);
    f106.setValue(1, 1);
    f106.setValue(2, 1);
    f106.setValue(3, 0);
    
    f107.setValue(0, 1);
    f107.setValue(1, 0);
    f107.setValue(2, 0);
    f107.setValue(3, 0);
    
    f108.setValue(0, 1);
    f108.setValue(1, 0);
    f108.setValue(2, 0);
    f108.setValue(3, 1);
    
    f109.setValue(0, 1);
    f109.setValue(1, 0);
    f109.setValue(2, 1);
    f109.setValue(3, 0);
    
    f110.setValue(0, 1);
    f110.setValue(1, 1);
    f110.setValue(2, 0);
    f110.setValue(3, 0);
    
    cout << "\nCreate instance of BloomFilterTree with minimum degree 3/max elements 6, filter size 4 (b3) and insert all filters";
    BloomFilterTree b3(3, 4);
    b3.insert(&f100);
    b3.insert(&f101);
    b3.insert(&f102);
    b3.insert(&f103);
    b3.insert(&f104);
    b3.insert(&f105);
    b3.insert(&f106);
    b3.insert(&f107);
    b3.insert(&f108);
    b3.insert(&f109);
    b3.insert(&f110);
    
    
    vector<BloomFilter> v2;
    v2.push_back(f100);
    v2.push_back(f101);
    v2.push_back(f102);
    v2.push_back(f103);
    v2.push_back(f104);
    v2.push_back(f105);
    v2.push_back(f106);
    v2.push_back(f107);
    v2.push_back(f108);
    v2.push_back(f109);
    v2.push_back(f110);
    cout << "\n\nCompute possible and valid subsets of query filter f105 (";
    f105.printArr();
    cout << ")\n";
    cout << "Count should be: " << f105.mySubsetCount() << endl << endl;
    for (int i=0; i<v2.size(); i++) {
        if (f105.isSubset(&v2[i]) == true) {
            cout << v2[i].getId() << " (";
            v2[i].printArr();
            cout << ")" << endl;
        }
    }
    
    cout << "\nCompute possible and valid supersets of query filter f105 (";
    f105.printArr();
    cout << ")\n";
    cout << "Count should be: " << f105.mySupersetCount() << endl << endl;
    for (int i=0; i<v2.size(); i++) {
        if (f105.isSuperset(&v2[i]) == true) {
            cout << v2[i].getId() << " (";
            v2[i].printArr();
            cout << ")" << endl;
        }
    }
    
    cout << "\nCollect all filters in b3: ";
    vector<BloomFilter> v7 = b3.collectAllFilters();
    for (int i=0; i<v7.size(); i++) {
        cout << v7[i].getId() << " ";
    }
    
    cout << "\n\nCompute all jacc distances of query filter f105 (";
    f105.printArr();
    cout << ")\n\n";
    vector<pair<int, float>> v6 = b3.computeAllDistances(&f105);
    for (int i=0; i<v6.size(); i++) {
        cout << "jacc(" << f105.getId() << ", " <<  v6[i].first << "): " << v6[i].second << endl;
    }
    
    cout << "\n4 nearest neighbors of f105 in ascending order:\n\n";
    b3.computekDistances(&f105, 4);
    
    cout << "\nCreate 42 instances of BloomFilter with array size 6, all possible and valid permutations\n\n";
    BloomFilter f600(6, 600);
    BloomFilter f601(6, 601);
    BloomFilter f602(6, 602);
    BloomFilter f603(6, 603);
    BloomFilter f604(6, 604);
    BloomFilter f605(6, 605);
    BloomFilter f606(6, 606);
    BloomFilter f607(6, 607);
    BloomFilter f608(6, 608);
    BloomFilter f609(6, 609);
    BloomFilter f610(6, 610);
    BloomFilter f611(6, 611);
    BloomFilter f612(6, 612);
    BloomFilter f613(6, 613);
    BloomFilter f614(6, 614);
    BloomFilter f615(6, 615);
    BloomFilter f616(6, 616);
    BloomFilter f617(6, 617);
    BloomFilter f618(6, 618);
    BloomFilter f619(6, 619);
    BloomFilter f620(6, 620);
    BloomFilter f621(6, 621);
    BloomFilter f622(6, 622);
    BloomFilter f623(6, 623);
    BloomFilter f624(6, 624);
    BloomFilter f625(6, 625);
    BloomFilter f626(6, 626);
    BloomFilter f627(6, 627);
    BloomFilter f628(6, 628);
    BloomFilter f629(6, 629);
    BloomFilter f630(6, 630);
    BloomFilter f631(6, 631);
    BloomFilter f632(6, 632);
    BloomFilter f633(6, 633);
    BloomFilter f634(6, 634);
    BloomFilter f635(6, 635);
    BloomFilter f636(6, 636);
    BloomFilter f637(6, 637);
    BloomFilter f638(6, 638);
    BloomFilter f639(6, 639);
    BloomFilter f640(6, 640);
    BloomFilter f641(6, 641);
    
    f601.setValue(0, 0);
    f601.setValue(1, 0);
    f601.setValue(2, 0);
    f601.setValue(3, 0);
    f601.setValue(4, 0);
    f601.setValue(5, 1);
    
    f602.setValue(0, 0);
    f602.setValue(1, 0);
    f602.setValue(2, 0);
    f602.setValue(3, 0);
    f602.setValue(4, 1);
    f602.setValue(5, 0);
    
    f603.setValue(0, 0);
    f603.setValue(1, 0);
    f603.setValue(2, 0);
    f603.setValue(3, 0);
    f603.setValue(4, 1);
    f603.setValue(5, 1);
    
    f604.setValue(0, 0);
    f604.setValue(1, 0);
    f604.setValue(2, 0);
    f604.setValue(3, 1);
    f604.setValue(4, 0);
    f604.setValue(5, 0);
    
    f605.setValue(0, 0);
    f605.setValue(1, 0);
    f605.setValue(2, 0);
    f605.setValue(3, 1);
    f605.setValue(4, 0);
    f605.setValue(5, 1);
    
    f606.setValue(0, 0);
    f606.setValue(1, 0);
    f606.setValue(2, 0);
    f606.setValue(3, 1);
    f606.setValue(4, 1);
    f606.setValue(5, 0);
    
    f607.setValue(0, 0);
    f607.setValue(1, 0);
    f607.setValue(2, 0);
    f607.setValue(3, 1);
    f607.setValue(4, 1);
    f607.setValue(5, 1);
    
    f608.setValue(0, 0);
    f608.setValue(1, 0);
    f608.setValue(2, 1);
    f608.setValue(3, 0);
    f608.setValue(4, 0);
    f608.setValue(5, 0);
    
    f609.setValue(0, 0);
    f609.setValue(1, 0);
    f609.setValue(2, 1);
    f609.setValue(3, 0);
    f609.setValue(4, 0);
    f609.setValue(5, 1);
    
    f610.setValue(0, 0);
    f610.setValue(1, 0);
    f610.setValue(2, 1);
    f610.setValue(3, 0);
    f610.setValue(4, 1);
    f610.setValue(5, 0);
    
    f611.setValue(0, 0);
    f611.setValue(1, 0);
    f611.setValue(2, 1);
    f611.setValue(3, 0);
    f611.setValue(4, 1);
    f611.setValue(5, 1);
    
    f612.setValue(0, 0);
    f612.setValue(1, 0);
    f612.setValue(2, 1);
    f612.setValue(3, 1);
    f612.setValue(4, 0);
    f612.setValue(5, 0);
    
    f613.setValue(0, 0);
    f613.setValue(1, 0);
    f613.setValue(2, 1);
    f613.setValue(3, 1);
    f613.setValue(4, 0);
    f613.setValue(5, 1);
    
    f614.setValue(0, 0);
    f614.setValue(1, 0);
    f614.setValue(2, 1);
    f614.setValue(3, 1);
    f614.setValue(4, 1);
    f614.setValue(5, 0);
    
    f615.setValue(0, 0);
    f615.setValue(1, 1);
    f615.setValue(2, 0);
    f615.setValue(3, 0);
    f615.setValue(4, 0);
    f615.setValue(5, 0);
    
    f616.setValue(0, 0);
    f616.setValue(1, 1);
    f616.setValue(2, 0);
    f616.setValue(3, 0);
    f616.setValue(4, 0);
    f616.setValue(5, 1);
    
    f617.setValue(0, 0);
    f617.setValue(1, 1);
    f617.setValue(2, 0);
    f617.setValue(3, 0);
    f617.setValue(4, 1);
    f617.setValue(5, 0);
    
    f618.setValue(0, 0);
    f618.setValue(1, 1);
    f618.setValue(2, 0);
    f618.setValue(3, 0);
    f618.setValue(4, 1);
    f618.setValue(5, 1);
    
    f619.setValue(0, 0);
    f619.setValue(1, 1);
    f619.setValue(2, 0);
    f619.setValue(3, 1);
    f619.setValue(4, 0);
    f619.setValue(5, 0);
    
    f620.setValue(0, 0);
    f620.setValue(1, 1);
    f620.setValue(2, 0);
    f620.setValue(3, 1);
    f620.setValue(4, 0);
    f620.setValue(5, 1);
    
    f621.setValue(0, 0);
    f621.setValue(1, 1);
    f621.setValue(2, 0);
    f621.setValue(3, 1);
    f621.setValue(4, 1);
    f621.setValue(5, 0);
    
    f622.setValue(0, 0);
    f622.setValue(1, 1);
    f622.setValue(2, 1);
    f622.setValue(3, 0);
    f622.setValue(4, 0);
    f622.setValue(5, 0);
    
    f623.setValue(0, 0);
    f623.setValue(1, 1);
    f623.setValue(2, 1);
    f623.setValue(3, 0);
    f623.setValue(4, 0);
    f623.setValue(5, 1);
    
    f624.setValue(0, 0);
    f624.setValue(1, 1);
    f624.setValue(2, 1);
    f624.setValue(3, 0);
    f624.setValue(4, 1);
    f624.setValue(5, 0);
    
    f625.setValue(0, 0);
    f625.setValue(1, 1);
    f625.setValue(2, 1);
    f625.setValue(3, 1);
    f625.setValue(4, 0);
    f625.setValue(5, 0);
    
    f626.setValue(0, 1);
    f626.setValue(1, 0);
    f626.setValue(2, 0);
    f626.setValue(3, 0);
    f626.setValue(4, 0);
    f626.setValue(5, 0);
    
    f627.setValue(0, 1);
    f627.setValue(1, 0);
    f627.setValue(2, 0);
    f627.setValue(3, 0);
    f627.setValue(4, 0);
    f627.setValue(5, 1);
    
    f628.setValue(0, 1);
    f628.setValue(1, 0);
    f628.setValue(2, 0);
    f628.setValue(3, 0);
    f628.setValue(4, 1);
    f628.setValue(5, 0);
    
    f629.setValue(0, 1);
    f629.setValue(1, 0);
    f629.setValue(2, 0);
    f629.setValue(3, 0);
    f629.setValue(4, 1);
    f629.setValue(5, 1);
    
    f630.setValue(0, 1);
    f630.setValue(1, 0);
    f630.setValue(2, 0);
    f630.setValue(3, 1);
    f630.setValue(4, 0);
    f630.setValue(5, 0);
    
    f631.setValue(0, 1);
    f631.setValue(1, 0);
    f631.setValue(2, 0);
    f631.setValue(3, 1);
    f631.setValue(4, 0);
    f631.setValue(5, 1);
    
    f632.setValue(0, 1);
    f632.setValue(1, 0);
    f632.setValue(2, 0);
    f632.setValue(3, 1);
    f632.setValue(4, 1);
    f632.setValue(5, 0);
    
    f633.setValue(0, 1);
    f633.setValue(1, 0);
    f633.setValue(2, 1);
    f633.setValue(3, 0);
    f633.setValue(4, 0);
    f633.setValue(5, 0);
    
    f634.setValue(0, 1);
    f634.setValue(1, 0);
    f634.setValue(2, 1);
    f634.setValue(3, 0);
    f634.setValue(4, 0);
    f634.setValue(5, 1);
    
    f635.setValue(0, 1);
    f635.setValue(1, 0);
    f635.setValue(2, 1);
    f635.setValue(3, 0);
    f635.setValue(4, 1);
    f635.setValue(5, 0);
    
    f636.setValue(0, 1);
    f636.setValue(1, 0);
    f636.setValue(2, 1);
    f636.setValue(3, 1);
    f636.setValue(4, 0);
    f636.setValue(5, 0);
    
    f637.setValue(0, 1);
    f637.setValue(1, 1);
    f637.setValue(2, 0);
    f637.setValue(3, 0);
    f637.setValue(4, 0);
    f637.setValue(5, 0);
    
    f638.setValue(0, 1);
    f638.setValue(1, 1);
    f638.setValue(2, 0);
    f638.setValue(3, 0);
    f638.setValue(4, 0);
    f638.setValue(5, 1);
    
    f639.setValue(0, 1);
    f639.setValue(1, 1);
    f639.setValue(2, 0);
    f639.setValue(3, 0);
    f639.setValue(4, 1);
    f639.setValue(5, 0);
    
    f640.setValue(0, 1);
    f640.setValue(1, 1);
    f640.setValue(2, 0);
    f640.setValue(3, 1);
    f640.setValue(4, 0);
    f640.setValue(5, 0);
    
    f641.setValue(0, 1);
    f641.setValue(1, 1);
    f641.setValue(2, 1);
    f641.setValue(3, 0);
    f641.setValue(4, 0);
    f641.setValue(5, 0);
    
    cout << "Create instance of BloomFilterTree with minimum degree 3/max elements 6, filter size 6 (b4) and insert all filters";
    BloomFilterTree b4(3, 6);
    b4.insert(&f600);
    b4.insert(&f601);
    b4.insert(&f602);
    b4.insert(&f603);
    b4.insert(&f604);
    b4.insert(&f605);
    b4.insert(&f606);
    b4.insert(&f607);
    b4.insert(&f608);
    b4.insert(&f609);
    b4.insert(&f610);
    b4.insert(&f611);
    b4.insert(&f612);
    b4.insert(&f613);
    b4.insert(&f614);
    b4.insert(&f615);
    b4.insert(&f616);
    b4.insert(&f617);
    b4.insert(&f618);
    b4.insert(&f619);
    b4.insert(&f620);
    b4.insert(&f621);
    b4.insert(&f622);
    b4.insert(&f623);
    b4.insert(&f624);
    b4.insert(&f625);
    b4.insert(&f626);
    b4.insert(&f627);
    b4.insert(&f628);
    b4.insert(&f629);
    b4.insert(&f630);
    b4.insert(&f631);
    b4.insert(&f632);
    b4.insert(&f633);
    b4.insert(&f634);
    b4.insert(&f635);
    b4.insert(&f636);
    b4.insert(&f637);
    b4.insert(&f638);
    b4.insert(&f639);
    b4.insert(&f640);
    b4.insert(&f641);
    
    vector<BloomFilter> v3;
    v3.push_back(f600);
    v3.push_back(f601);
    v3.push_back(f602);
    v3.push_back(f603);
    v3.push_back(f604);
    v3.push_back(f605);
    v3.push_back(f606);
    v3.push_back(f607);
    v3.push_back(f608);
    v3.push_back(f609);
    v3.push_back(f610);
    v3.push_back(f611);
    v3.push_back(f612);
    v3.push_back(f613);
    v3.push_back(f614);
    v3.push_back(f615);
    v3.push_back(f616);
    v3.push_back(f617);
    v3.push_back(f618);
    v3.push_back(f619);
    v3.push_back(f620);
    v3.push_back(f621);
    v3.push_back(f622);
    v3.push_back(f623);
    v3.push_back(f624);
    v3.push_back(f625);
    v3.push_back(f626);
    v3.push_back(f627);
    v3.push_back(f628);
    v3.push_back(f629);
    v3.push_back(f630);
    v3.push_back(f631);
    v3.push_back(f632);
    v3.push_back(f633);
    v3.push_back(f634);
    v3.push_back(f635);
    v3.push_back(f636);
    v3.push_back(f637);
    v3.push_back(f638);
    v3.push_back(f639);
    v3.push_back(f640);
    v3.push_back(f641);
    
    cout << "\n\nCompute possible and valid subsets of query filter f609 (";
    f609.printArr();
    cout << ")\n";
    cout << "Count should be: " << f609.mySubsetCount() << endl << endl;
    for (int i=0; i<v3.size(); i++) {
        if (f609.isSubset(&v3[i]) == true) {
            cout << v3[i].getId() << " (";
            v3[i].printArr();
            cout << ")" << endl;
        }
    }
    
    cout << "\nCompute possible and valid supersets of query filter f609 (";
    f609.printArr();
    cout << ")\n";
    cout << "Count should be: " << f609.mySupersetCount() << endl << endl;
    for (int i=0; i<v3.size(); i++) {
        if (f609.isSuperset(&v3[i]) == true) {
            cout << v3[i].getId() << " (";
            v3[i].printArr();
            cout << ")" << endl;
        }
    }
    
    cout << "\nCollect all filters in b4: ";
    vector<BloomFilter> v5 = b4.collectAllFilters();
    for (int i=0; i<v5.size(); i++) {
        cout << v5[i].getId() << " ";
    }
    
    cout << "\n\n8 nearest neighbors of f609 in ascending order:\n\n";
    b4.computekDistances(&f609, 8);
    
    
    cout << "\n\nCheck subset insertion";
    cout << "\n----------------------\n";
    cout << "Remove f100 and f104 from b3 (subsets of query filter f105)";
    b3 = *new BloomFilterTree(3, 4);
    b3.insert(&f101);
    b3.insert(&f102);
    b3.insert(&f103);
    b3.insert(&f105);
    b3.insert(&f106);
    b3.insert(&f107);
    b3.insert(&f108);
    b3.insert(&f109);
    b3.insert(&f110);
    cout << endl << endl;
    b3.traverse();
    cout << "\n\nRemove f608 and f609 from b4 (subsets of query filter f609)";
    cout << "\nRemove f609, f623, f634 from b4 (supersets of query filter f609)";
    b4 = *new BloomFilterTree(3, 6);
    b4.insert(&f600);
    b4.insert(&f601);
    b4.insert(&f602);
    b4.insert(&f603);
    b4.insert(&f604);
    b4.insert(&f605);
    b4.insert(&f606);
    b4.insert(&f607);
    b4.insert(&f608);
    b4.insert(&f610);
    b4.insert(&f611);
    b4.insert(&f612);
    b4.insert(&f613);
    cout << endl << endl;
    b4.traverse();
    
    // Subset id for filter size 4
    cout << "\n\nComputed free subset ids for f105 should be: 100, 104, 111";
    cout << "\nBest subset id for f105 should be: 104";
    cout << "\nComputed optimal subset id for f105: " << b3.computeSubsetId(&f105);
    
    // Subset id for filter size 6
    cout << "\n\nComputed free subset ids for f609 should be: 599, 609, 614";
    cout << "\nBest subset id for f609 should be: 609";
    cout << "\nComputed optimal subset id for f609: " << b4.computeSubsetId(&f609);
    
    // Superset id for filter size 4
    cout << "\n\n\nCheck superset insertion";
    cout << "\n------------------------\n";
    cout << "Compute possible and valid supersets of query filter f101 (";
    f101.printArr();
    cout << ")\n\n";
    for (int i=0; i<v2.size(); i++) {
        if (f101.isSuperset(&v2[i]) == true) {
            cout << v2[i].getId() << " (";
            v2[i].printArr();
            cout << ")" << endl;
        }
    }
    cout << "\nComputed free superset ids for f101 should be: 100, 104, 111";
    cout << "\nBest superset id for f101 should be: 100";
    cout << "\nComputed optimal superset id for f101: " << b3.computeSupersetId(&f101);
    
    // Superset id for filter size 6
    cout << "\n\nComputed free superset ids for f609 should be: 599, 609, 614";
    cout << "\nBest supserset id for f609 should be: 614";
    cout << "\nComputed optimal superset id for f609: " << b4.computeSupersetId(&f609);
    
    // Set insertion
    cout << "\n\n\nCheck set insertion";
    cout << "\n-------------------";
    cout << "\nRemove all filters from b3 and insert filters f101..f103, f105..f110 as sets";
    b3 = *new BloomFilterTree(3, 4);
    cout << "\n\nInsert f101 (";
    f101.printArr();
    cout << ")\n\n";
    b3.insertAsSets(&f101);
    b3.traverse();
    cout << endl;
    b3.traverseFilters();
    cout << "\n\nInsert f102 (";
    f102.printArr();
    cout << ")\nComputed subset id: " << b3.computeSubsetId(&f102);
    cout << "\nComputed superset id: " << b3.computeSupersetId(&f102) << endl << endl;
    b3.insertAsSets(&f102);
    b3.traverse();
    cout << endl;
    b3.traverseFilters();
    cout << "\n\nInsert f103 (";
    f103.printArr();
    cout << ")\nComputed subset id: " << b3.computeSubsetId(&f103);
    cout << "\nComputed superset id: " << b3.computeSupersetId(&f103) << endl << endl;
    b3.insertAsSets(&f103);
    b3.traverse();
    cout << endl;
    b3.traverseFilters();
    cout << "\n\nInsert f105 (";
    f105.printArr();
    cout << ")\nComputed subset id: " << b3.computeSubsetId(&f105);
    cout << "\nComputed superset id: " << b3.computeSupersetId(&f105) << endl << endl;
    b3.insertAsSets(&f105);
    b3.traverse();
    cout << endl;
    b3.traverseFilters();
    cout << "\n\nInsert f106 (";
    f106.printArr();
    cout << ")\nComputed subset id: " << b3.computeSubsetId(&f106);
    cout << "\nComputed superset id: " << b3.computeSupersetId(&f106) << endl << endl;
    b3.insertAsSets(&f106);
    b3.traverse();
    cout << endl;
    b3.traverseFilters();
    cout << "\n\nInsert f107 (";
    f107.printArr();
    cout << ")\nComputed subset id: " << b3.computeSubsetId(&f107);
    cout << "\nComputed superset id: " << b3.computeSupersetId(&f107) << endl << endl;
    b3.insertAsSets(&f107);
    b3.traverse();
    cout << endl;
    b3.traverseFilters();
    cout << "\n\nInsert f108 (";
    f108.printArr();
    cout << ")\nComputed subset id: " << b3.computeSubsetId(&f108);
    cout << "\nComputed superset id: " << b3.computeSupersetId(&f108) << endl << endl;
    b3.insertAsSets(&f108);
    b3.traverse();
    cout << endl;
    b3.traverseFilters();
    cout << "\n\nInsert f109 (";
    f109.printArr();
    cout << ")\nComputed subset id: " << b3.computeSubsetId(&f109);
    cout << "\nComputed superset id: " << b3.computeSupersetId(&f109) << endl << endl;
    b3.insertAsSets(&f109);
    b3.traverse();
    cout << endl;
    b3.traverseFilters();cout << "\n\nInsert f110 (";
    f110.printArr();
    cout << ")\nComputed subset id: " << b3.computeSubsetId(&f110);
    cout << "\nComputed superset id: " << b3.computeSupersetId(&f110) << endl << endl;
    b3.insertAsSets(&f110);
    b3.traverse();
    cout << endl;
    b3.traverseFilters();
    cout << "\n\nRemove all filters from b4 and insert filters 600..604, 609..614, 619..624 as sets\n\n";
    b4 = *new BloomFilterTree(3, 6);
    b4.insertAsSets(&f600);
    b4.insertAsSets(&f601);
    b4.insertAsSets(&f602);
    b4.insertAsSets(&f603);
    b4.insertAsSets(&f604);
    b4.insertAsSets(&f609);
    b4.insertAsSets(&f610);
    b4.insertAsSets(&f611);
    b4.insertAsSets(&f612);
    b4.insertAsSets(&f613);
    b4.insertAsSets(&f614);
    b4.insertAsSets(&f619);
    b4.insertAsSets(&f620);
    b4.insertAsSets(&f621);
    b4.insertAsSets(&f622);
    b4.insertAsSets(&f623);
    b4.insertAsSets(&f624);
    b4.traverse();
    cout << endl;
    b4.traverseFilters();
    
    // Set search queries
    cout << "\n\n\nCheck set queries";
    cout << "\n-----------------\n";
    b3.compare(&f104, b3.countFilters());
    cout << endl;
    BloomFilter f595(f609);
    b4.compare(&f595, b4.countFilters());
    cout << endl;
    
    cout << "\nLEAF QUERY for nearest neighbor of f104 (";
    f104.printArr();
    cout << ")\n";
    cout << "Result should be: 93 (1100)";
    BloomFilterNode *L1 = b3.search(93);
    BloomFilter *result = L1->simQuery(&f104);
    cout << "\nComputed result: " << result->getId() << " (";
    result->printArr();
    
    cout << ")\n\nLEAF QUERY for nearest neighbor of f595 (";
    f595.printArr();
    cout << ")\n";
    cout << "Result should be: 595 (001001)";
    L1 = b4.search(595);
    result = L1->simQuery(&f595);
    cout << "\nComputed result: " << result->getId() << " (";
    result->printArr();
    
    cout << "\n\nLEAF QUERY for nearest neighbor of f605 (";
    f605.printArr();
    cout << ")\n";
    cout << "Result should be: 593 (";
    L1 = b4.search(593);
    L1->filters[0]->printArr();
    cout << ")\n";
    result = L1->simQuery(&f605);
    cout << "Computed result: " << result->getId() << " (";
    result->printArr();
    cout << ")\n";
    
    cout << "\nLEAF QUERY for 3 nearest neighbors of f104 (";
    f104.printArr();
    cout << ")\n";
    cout << "Result should be: 93, 98, 97";
    L1 = b3.search(93);
    vector<BloomFilter*> results = L1->simQueryVec(&f104, 3);
    cout << "\nComputed result: ";
    for (int i=0; i<results.size()-1; i++) {
        cout << results[i]->getId() << ", ";
    }
    cout << results[results.size()-1]->getId();
    
    cout << "\n\nLEAF QUERY for 3 nearest neighbors of f595 (";
    f595.printArr();
    cout << ")\n";
    cout << "Result should be: 595, 593, 591";
    L1 = b4.search(595);
    results = L1->simQueryVec(&f595, 3);
    cout << "\nComputed result: ";
    for (int i=0; i<results.size()-1; i++) {
        cout << results[i]->getId() << ", ";
    }
    cout << results[results.size()-1]->getId();
    
    cout << "\n\nTREE QUERY for nearest neighbor of f104 (";
    f104.printArr();
    cout << ")\n";
    cout << "Result should be: 93, 98 or 97";
    result = b3.simQuery(&f104);
    cout << "\nComputed result: " << result->getId() << " (";
    result->printArr();
    cout << ")\n";
    
    cout << "\nTREE QUERY for nearest neighbor of f595 (";
    f595.printArr();
    cout << ")\n";
    cout << "Result should be: 595 (001001)";
    result = b4.simQuery(&f595);
    cout << "\nComputed result: " << result->getId() << " (";
    result->printArr();
    cout << ")\n";
    
    cout << "\nTREE QUERY for 3 nearest neighbors of f104 (";
    f104.printArr();
    cout << ")\n";
    cout << "Result should be: 93, 98, 97 in any order";
    results = b3.simQueryVec(&f104, 3);
    cout << "\nComputed result: ";
    for (int i=0; i<results.size()-1; i++) {
        cout << results[i]->getId() << ", ";
    }
    cout << results[results.size()-1]->getId();
    
    cout << "\n\nTREE QUERY for 3 nearest neighbors of f595 (";
    f595.printArr();
    cout << ")\n";
    cout << "Result should be: 595 and two filters out of 593/585/591 in any order";
    results = b4.simQueryVec(&f595, 3);
    cout << "\nComputed result: ";
    for (int i=0; i<results.size()-1; i++) {
        cout << results[i]->getId() << ", ";
    }
    cout << results[results.size()-1]->getId();
    
    // Class BloomFilterListNode
    
    cout << "\n\n\nCLASS BloomFilterListNode";
    cout << "\n-------------------------\n";
    
    cout << "Create instance of BloomFilterListNode (n1) and test all methods\n\n";
    BloomFilterListNode n1;
    n1.setPosition(2);
    cout << "Position: " << n1.getPosition() << endl;
    for (int i=0; i<v1.size(); i++) {
        if (v1[i].getData()[2] == 0) {
            n1.zeroLinks.push_back(&v1[i]);
        }
        else {
            n1.oneLinks.push_back(&v1[i]);
        }
    }
    n1.printZeroLinks();
    n1.printOneLinks();
    
    // Class BloomFilterList
    
    cout << "\n\nCLASS BloomFilterList";
    cout << "\n---------------------\n";
    cout << "Create 3 instances of BloomFilterList (l1, l5, l6) and test all methods\n\n";
    BloomFilterList l1(10);
    for (int i=0; i<l1.getSize(); i++) {
        l1.updateNode(&f1, i);
    }
    l1.printAll();
    l1.clear();
    l1.printAll();
    BloomFilterList l5(4);
    BloomFilterList l6(6);
    l5.insert(&f600);
    
    // Section insertion
    cout << "\n\nCheck section insertion";
    cout << "\n-----------------------";
    cout << "\nInsert filters f101..f103, f105..f110 into l5";
    l5.insert(&f101);
    l5.insert(&f102);
    l5.insert(&f103);
    l5.insert(&f105);
    l5.insert(&f106);
    l5.insert(&f107);
    l5.insert(&f108);
    l5.insert(&f109);
    l5.insert(&f110);
    cout << "\nBloomFilterList l5:\n\n";
    // l5.printAll();
    cout << "Insert filters 601..604, 609..614, 619..624 into l6\n";
    l6.insert(&f601);
    l6.insert(&f602);
    l6.insert(&f603);
    l6.insert(&f604);
    l6.insert(&f609);
    l6.insert(&f610);
    l6.insert(&f611);
    l6.insert(&f612);
    l6.insert(&f613);
    l6.insert(&f614);
    l6.insert(&f619);
    l6.insert(&f620);
    l6.insert(&f621);
    l6.insert(&f622);
    l6.insert(&f623);
    l6.insert(&f624);
    l6.printAll();
    
    // Section search queries
    cout << "\nCheck section queries";
    cout << "\n---------------------\n";
    l5.compare(&f104, l5.countFilters());
    cout << endl;
    l6.compare(&f595, l6.countFilters());
    
    cout << "\nSection query for nearest neighbor of f104 (";
    f104.printArr();
    cout <<")\n";
    cout << "Result should be: 97, 93 or 98\n";
    result = l5.simQuery(&f104);
    cout << "Computed result: " << result->getId() << " (";
    result->printArr();
    cout << ")";
    
    cout << "\n\nSection query for nearest neighbor of f595 (";
    f595.printArr();
    cout << ")\n";
    cout << "Result should be: 595 (001001)";
    result = l6.simQuery(&f595);
    cout << "\nComputed result: " << result->getId() << " (";
    result->printArr();
    cout << ")";
    
    cout << "\n\nSection query for 3 nearest neighbors of f104 (";
    f104.printArr();
    cout << ")\n";
    cout << "Result should be: 93, 98, 97 in any order";
    vector<BloomFilter*> pResults = l5.simQueryVec(&f104, 3);
    cout << "\nComputed result: ";
    for (int i=0; i<pResults.size()-1; i++) {
        cout << pResults[i]->getId() << ", ";
    }
    cout << pResults[pResults.size()-1]->getId();
    
    cout << "\n\nSection query for 3 nearest neighbors of f595 (";
    f595.printArr();
    cout << ")\n";
    cout << "Result should be: 595 and two filters out of 593/585/591 in any order";
    pResults = l6.simQueryVec(&f595, 3);
    cout << "\nComputed result: ";
    for (int i=0; i<pResults.size()-1; i++) {
        cout << pResults[i]->getId() << ", ";
    }
    cout << pResults[pResults.size()-1]->getId();
    
    // Class BloomFilter
    
    cout << "CLASS BloomFilter\n";
    cout << "-----------------\n";
    
    cout << "Create 100 instances of BloomFilter with random ids, array length 256 and random values";
    cout << "\nCreate new BloomFilter vector (v4) and insert all filters";
    BloomFilter *filter;
    int id;
    vector<BloomFilter> v4;
    for (int i=0; i<100; i++) {
        filter = new BloomFilter(256, rand());
        id = filter->getId();
        filter->initRandom();
        v4.push_back(*filter);
    }
    cout << "\nCreate 3 query filters f20, f21, f22 with ids 20, 21, 22, array length 256 and random values";
    BloomFilter f20(256, 1);
    f20.initRandom();
    BloomFilter f21(256, 2);
    f21.initRandom();
    BloomFilter f22(256, 3);
    f22.initRandom();
    
    cout << "\n\nCreate 100 instances of BloomFilter with random ids, array length 512 and random values";
    cout << "Create new BloomFilter vector (v8) and insert all filters";
    BloomFilter *filter512;
    int id512;
    vector<BloomFilter> v8;
    for (int i=0; i<100; i++) {
        filter512 = new BloomFilter(512, rand());
        id512 = filter512->getId();
        filter512->initRandom();
        v8.push_back(*filter512);
    }
    
    cout << "Create 3 query filters f512, f513, f514 with ids 400, 500, 600, array length 512 and random values";
    BloomFilter f512(512, 4);
    f512.initRandom();
    BloomFilter f513(512, 5);
    f513.initRandom();
    BloomFilter f514(512, 6);
    f514.initRandom();
    
    // Class BloomFilterTree
    
    cout << "\n\n\nCLASS BloomFilterTree";
    cout << "\n---------------------\n";
    
    cout << "Create instance of BloomFilterTree (b5) with minimum degree 3/max elements 6, filter size 256 and insert all filters in v4 as sets\n\n";
    BloomFilterTree b5(3, 256);
    for (int i=0; i<v4.size(); i++) {
        b5.insertAsSets(&v4[i]);
    }
    
    cout << "Create instance of BloomFilterTree (b8) with minimum degree 3/max elements 6, filter size 256 and insert every second filter in v4 as sets\n\n";
    BloomFilterTree b8(3, 256);
    for (int i=0; i<v4.size(); i+=2) {
        b8.insertAsSets(&v4[i]);
    }
    
    cout << "Create instance of BloomFilterTree (b9) with minimum degree 3/max elements 6, filter size 512 and insert all filters in v8 as sets\n\n";
    BloomFilterTree b9(3, 512);
    for (int i=0; i<v8.size(); i++) {
        b9.insertAsSets(&v8[i]);
    }
    
    cout << "Create instance of BloomFilterTree (b10) with minimum degree 3/max elements 6, filter size 512 and insert every second filter in v8 as sets\n\n";
    BloomFilterTree b10(3, 512);
    for (int i=0; i<v8.size(); i+=2) {
        b10.insertAsSets(&v8[i]);
    }
    
    cout << "10 nearest neighbors of f20 in b5:\n\n";
    vector<pair<int, float>> res1 = b5.computekDistances(&f20, 10);
    
    cout << "\n10 nearest neighbors of f20 in b8:\n\n";
    vector<pair<int, float>> res2 = b8.computekDistances(&f20, 10);
    
    cout << "\n10 nearest neighbors of f21 in b5:\n\n";
    vector<pair<int, float>> res3 = b5.computekDistances(&f21, 10);
    
    cout << "\n10 nearest neighbors of f21 in b8:\n\n";
    vector<pair<int, float>> res4 = b8.computekDistances(&f21, 10);
    
    cout << "\n10 nearest neighbors of f22 in b5:\n\n";
    vector<pair<int, float>> res5 = b5.computekDistances(&f22, 10);
    
    cout << "\n10 nearest neighbors of f22 in b8:\n\n";
    vector<pair<int, float>> res6 = b8.computekDistances(&f22, 10);
    
    cout << "\n10 nearest neighbors of f512 in b9:\n\n";
    vector<pair<int, float>> res7 = b9.computekDistances(&f512, 10);
    
    cout << "\n10 nearest neighbors of f512 in b10:\n\n";
    vector<pair<int, float>> res8 = b10.computekDistances(&f512, 10);
    
    cout << "\n10 nearest neighbors of f513 in b9:\n\n";
    vector<pair<int, float>> res9 = b9.computekDistances(&f513, 10);
    
    cout << "\n10 nearest neighbors of f513 in b10:\n\n";
    vector<pair<int, float>> res10 = b10.computekDistances(&f513, 10);
    
    cout << "\n10 nearest neighbors of f514 in b9:\n\n";
    vector<pair<int, float>> res11 = b9.computekDistances(&f514, 10);
    
    cout << "\n10 nearest neighbors of f514 in b10:\n\n";
    vector<pair<int, float>> res12 = b10.computekDistances(&f514, 10);
    
    /* cout << "\n\nCheck subset insertion";
     cout << "\n----------------------";
     
     // Subset id for filter size 256
     cout << "\nComputed optimal subset id for f1 in b1: " << b1.computeSubsetId(&f1);
     cout << "\nComputed optimal subset id for f2 in b1: " << b1.computeSubsetId(&f2);
     cout << "\nComputed optimal subset id for f3 in b1: " << b1.computeSubsetId(&f3);
     
     cout << "\n\nComputed optimal subset id for f1 in b2: " << b2.computeSubsetId(&f1);
     cout << "\nComputed optimal subset id for f2 in b2: " << b2.computeSubsetId(&f2);
     cout << "\nComputed optimal subset id for f3 in b2: " << b2.computeSubsetId(&f3);
     
     cout << "\n\n\nCheck superset insertion";
     cout << "\n------------------------";
     
     // Superset id for filter size 256
     cout << "\nComputed optimal superset id for f1 in b1: " << b1.computeSupersetId(&f1);
     cout << "\nComputed optimal superset id for f1 in b1: " << b1.computeSupersetId(&f1);
     cout << "\nComputed optimal superset id for f1 in b1: " << b1.computeSupersetId(&f1);
     
     cout << "\n\nComputed optimal superset id for f1 in b2: " << b2.computeSupersetId(&f1);
     cout << "\nComputed optimal superset id for f1 in b2: " << b2.computeSupersetId(&f1);
     cout << "\nComputed optimal superset id for f1 in b2: " << b2.computeSupersetId(&f1); */
    
    // Set search queries
    cout << "\n\nCheck set queries";
    cout << "\n-----------------";
    
    /* cout << "\nTREE QUERY for nearest neighbor of f1 in b1";
     cout << "\nResult should be: " << res1[0].first;
     BloomFilter *r1 = b1.simQuery(&f1);
     cout << "\nComputed result: " << r1->getId() << " (" << f1.computeJaccard(r1) << ")";
     
     cout << "\n\nTREE QUERY for nearest neighbor of f1 in b2";
     cout << "\nResult should be: " << res2[0].first;
     BloomFilter *r2 = b2.simQuery(&f1);
     cout << "\nComputed result: " << r2->getId() << " (" << f1.computeJaccard(r2) << ")";
     
     cout << "\n\nTREE QUERY for nearest neighbor of f2 in b1";
     cout << "\nResult should be: " << res3[0].first;
     BloomFilter *r3 = b1.simQuery(&f2);
     cout << "\nComputed result: " << r3->getId() << " (" << f2.computeJaccard(r3) << ")";
     
     cout << "\n\nTREE QUERY for nearest neighbor of f2 in b2";
     cout << "\nResult should be: " << res4[0].first;
     BloomFilter* r4 = b2.simQuery(&f2);
     cout << "\nComputed result: " << r4->getId() << " (" << f2.computeJaccard(r4) << ")";
     
     cout << "\n\nTREE QUERY for nearest neighbor of f3 in b1";
     cout << "\nResult should be: " << res5[0].first;
     BloomFilter* r5 = b1.simQuery(&f3);
     cout << "\nComputed result: " << r5->getId() << " (" << f3.computeJaccard(r5) << ")";
     
     cout << "\n\nTREE QUERY for nearest neighbor of f3 in b2";
     cout << "\nResult should be: " << res6[0].first;
     BloomFilter* r6 = b2.simQuery(&f3);
     cout << "\nComputed result: " << r6->getId() << " (" << f3.computeJaccard(r6) << ")"; */
    
    cout << "\n\nTREE QUERY for nearest neighbor of f512 in b9";
    cout << "\nResult should be: " << res7[0].first;
    BloomFilter* r7 = b9.simQuery(&f512);
    cout << "\nComputed result: " << r7->getId() << " (" << f512.computeJaccard(r7) << ")";
    
    cout << "\n\nTREE QUERY for nearest neighbor of f512 in b10";
    cout << "\nResult should be: " << res8[0].first;
    BloomFilter* r8 = b10.simQuery(&f512);
    cout << "\nComputed result: " << r8->getId() << " (" << f512.computeJaccard(r8) << ")";
    
    cout << "\n\nTREE QUERY for nearest neighbor of f513 in b9";
    cout << "\nResult should be: " << res9[0].first;
    BloomFilter* r9 = b9.simQuery(&f513);
    cout << "\nComputed result: " << r9->getId() << " (" << f513.computeJaccard(r9) << ")";
    
    cout << "\n\nTREE QUERY for nearest neighbor of f513 in b10";
    cout << "\nResult should be: " << res10[0].first;
    BloomFilter* r10 = b10.simQuery(&f513);
    cout << "\nComputed result: " << r10->getId() << " (" << f513.computeJaccard(r10) << ")";
    
    cout << "\n\nTREE QUERY for nearest neighbor of f514 in b9";
    cout << "\nResult should be: " << res11[0].first;
    BloomFilter* r11 = b9.simQuery(&f514);
    cout << "\nComputed result: " << r11->getId() << " (" << f514.computeJaccard(r11) << ")";
    
    cout << "\n\nTREE QUERY for nearest neighbor of f514 in b10";
    cout << "\nResult should be: " << res12[0].first;
    BloomFilter* r12 = b10.simQuery(&f6);
    cout << "\nComputed result: " << r12->getId() << " (" << f514.computeJaccard(r12) << ")";
    
    cout << "\n\nTREE QUERY for 3 nearest neighbors of f20 in b5";
    cout << "\nResults should be: " << res1[0].first << ", " << res1[1].first << ", " << res1[2].first;
    vector<BloomFilter*> rA = b5.simQueryVec(&f20, 3);
    cout << "\nComputed results:\n";
    cout << rA[0]->getId() << " (" << f20.computeJaccard(rA[0]) << ")\n";
    cout << rA[1]->getId() << " (" << f20.computeJaccard(rA[1]) << ")\n";
    cout << rA[2]->getId() << " (" << f20.computeJaccard(rA[2]) << ")";
    
    cout << "\n\nTREE QUERY for 3 nearest neighbors of f20 in b8";
    cout << "\nResults should be: " << res2[0].first << ", " << res2[1].first << ", " << res2[2].first;
    vector<BloomFilter*> rB = b8.simQueryVec(&f20, 3);
    cout << "\nComputed results:\n";
    cout << rB[0]->getId() << " (" << f20.computeJaccard(rB[0]) << ")\n";
    cout << rB[1]->getId() << " (" << f20.computeJaccard(rB[1]) << ")\n";
    cout << rB[2]->getId() << " (" << f20.computeJaccard(rB[2]) << ")";
    
    cout << "\n\nTREE QUERY for 3 nearest neighbors of f21 in b5";
    cout << "\nResults should be: " << res3[0].first << ", " << res3[1].first << ", " << res3[2].first;
    vector<BloomFilter*> rC = b5.simQueryVec(&f2, 3);
    cout << "\nComputed results:\n";
    cout << rC[0]->getId() << " (" << f21.computeJaccard(rC[0]) << ")\n";
    cout << rC[1]->getId() << " (" << f21.computeJaccard(rC[1]) << ")\n";
    cout << rC[2]->getId() << " (" << f21.computeJaccard(rC[2]) << ")";
    
    cout << "\n\nTREE QUERY for 3 nearest neighbors of f21 in b8";
    cout << "\nResults should be: " << res4[0].first << ", " << res4[1].first << ", " << res4[2].first;
    vector<BloomFilter*> rD = b8.simQueryVec(&f2, 3);
    cout << "\nComputed results:\n";
    cout << rD[0]->getId() << " (" << f21.computeJaccard(rD[0]) << ")\n";
    cout << rD[1]->getId() << " (" << f21.computeJaccard(rD[1]) << ")\n";
    cout << rD[2]->getId() << " (" << f21.computeJaccard(rD[2]) << ")";
    
    cout << "\n\nTREE QUERY for 3 nearest neighbors of f22 in b5";
    cout << "\nResults should be: " << res5[0].first << ", " << res5[1].first << ", " << res5[2].first;
    vector<BloomFilter*> rE = b5.simQueryVec(&f3, 3);
    cout << "\nComputed results:\n";
    cout << rE[0]->getId() << " (" << f22.computeJaccard(rE[0]) << ")\n";
    cout << rE[1]->getId() << " (" << f22.computeJaccard(rE[1]) << ")\n";
    cout << rE[2]->getId() << " (" << f22.computeJaccard(rE[2]) << ")";
    
    cout << "\n\nTREE QUERY for 3 nearest neighbors of f22 in b8";
    cout << "\nResults should be: " << res6[0].first << ", " << res6[1].first << ", " << res6[2].first;
    vector<BloomFilter*> rF= b8.simQueryVec(&f22, 3);
    cout << "\nComputed results:\n";
    cout << rF[0]->getId() << " (" << f22.computeJaccard(rF[0]) << ")\n";
    cout << rF[1]->getId() << " (" << f22.computeJaccard(rF[1]) << ")\n";
    cout << rF[2]->getId() << " (" << f22.computeJaccard(rF[2]) << ")";
    
    cout << "\n\nTREE QUERY for 3 nearest neighbors of f512 in b9";
    cout << "\nResults should be: " << res7[0].first << ", " << res7[1].first << ", " << res7[2].first;
    vector<BloomFilter*> rG= b9.simQueryVec(&f512, 3);
    cout << "\nComputed results:\n";
    cout << rG[0]->getId() << " (" << f512.computeJaccard(rG[0]) << ")\n";
    cout << rG[1]->getId() << " (" << f512.computeJaccard(rG[1]) << ")\n";
    cout << rG[2]->getId() << " (" << f512.computeJaccard(rG[2]) << ")";
    
    cout << "\n\nTREE QUERY for 3 nearest neighbors of f512 in b10";
    cout << "\nResults should be: " << res8[0].first << ", " << res8[1].first << ", " << res8[2].first;
    vector<BloomFilter*> rH= b10.simQueryVec(&f512, 3);
    cout << "\nComputed results:\n";
    cout << rH[0]->getId() << " (" << f512.computeJaccard(rH[0]) << ")\n";
    cout << rH[1]->getId() << " (" << f512.computeJaccard(rH[1]) << ")\n";
    cout << rH[2]->getId() << " (" << f512.computeJaccard(rH[2]) << ")";
    
    cout << "\n\nTREE QUERY for 3 nearest neighbors of f513 in b9";
    cout << "\nResults should be: " << res9[0].first << ", " << res9[1].first << ", " << res9[2].first;
    vector<BloomFilter*> rI= b9.simQueryVec(&f513, 3);
    cout << "\nComputed results:\n";
    cout << rI[0]->getId() << " (" << f513.computeJaccard(rI[0]) << ")\n";
    cout << rI[1]->getId() << " (" << f513.computeJaccard(rI[1]) << ")\n";
    cout << rI[2]->getId() << " (" << f513.computeJaccard(rI[2]) << ")";
    
    cout << "\n\nTREE QUERY for 3 nearest neighbors of f513 in b10";
    cout << "\nResults should be: " << res10[0].first << ", " << res10[1].first << ", " << res10[2].first;
    vector<BloomFilter*> rJ= b10.simQueryVec(&f513, 3);
    cout << "\nComputed results:\n";
    cout << rJ[0]->getId() << " (" << f513.computeJaccard(rJ[0]) << ")\n";
    cout << rJ[1]->getId() << " (" << f513.computeJaccard(rJ[1]) << ")\n";
    cout << rJ[2]->getId() << " (" << f513.computeJaccard(rJ[2]) << ")";
    
    cout << "\n\nTREE QUERY for 3 nearest neighbors of f514 in b9";
    cout << "\nResults should be: " << res11[0].first << ", " << res11[1].first << ", " << res11[2].first;
    vector<BloomFilter*> rK= b9.simQueryVec(&f514, 3);
    cout << "\nComputed results:\n";
    cout << rK[0]->getId() << " (" << f514.computeJaccard(rK[0]) << ")\n";
    cout << rK[1]->getId() << " (" << f514.computeJaccard(rK[1]) << ")\n";
    cout << rK[2]->getId() << " (" << f514.computeJaccard(rK[2]) << ")";
    
    cout << "\n\nTREE QUERY for 3 nearest neighbors of f514 in b10";
    cout << "\nResults should be: " << res12[0].first << ", " << res12[1].first << ", " << res12[2].first;
    vector<BloomFilter*> rL= b10.simQueryVec(&f514, 3);
    cout << "\nComputed results:\n";
    cout << rL[0]->getId() << " (" << f514.computeJaccard(rL[0]) << ")\n";
    cout << rL[1]->getId() << " (" << f514.computeJaccard(rL[1]) << ")\n";
    cout << rL[2]->getId() << " (" << f514.computeJaccard(rL[2]) << ")";
    
    // Class BloomFilterList
    
    /* cout << "\n\n\nCLASS BloomFilterList";
     cout << "\n---------------------\n";
     cout << "Create instance of BloomFilterList (l1) with filtersize 256 and insert all filters in v1\n\n";
     BloomFilterList l1(256);
     for (int i=0; i<v1.size(); i++) {
     l1.insert(&v1[i]);
     }
     
     cout << "10 nearest neighbors of f1 in l1:\n\n";
     vector<pair<int, double>> res7 = l1.computekDistances(&f1, 10);
     
     cout << "\n10 nearest neighbors of f2 in l1:\n\n";
     vector<pair<int, double>> res8 = l1.computekDistances(&f2, 10);
     
     cout << "\n10 nearest neighbors of f3 in l1:\n\n";
     vector<pair<int, double>> res9 = l1.computekDistances(&f3, 10);
     
     // Section search queries
     cout << "\n\nCheck section queries";
     cout << "\n---------------------\n";
     
     cout << "\nLIST QUERY for nearest neighbor of f1 in l1";
     cout << "\nResult should be: " << res7[0].first;
     BloomFilter *ra = l1.simQuery(&f1);
     cout << "\nComputed result: " << ra->getId() << " (" << ra->computeJaccard(&f1) << ")";
     
     cout << "\n\nLIST QUERY for nearest neighbor of f2 in l1";
     cout << "\nResult should be: " << res8[0].first;
     BloomFilter *rb = l1.simQuery(&f2);
     cout << "\nComputed result: " << rb->getId() << " (" << rb->computeJaccard(&f2) << ")";
     
     cout << "\n\nLIST QUERY for nearest neighbor of f3 in l1";
     cout << "\nResult should be: " << res9[0].first;
     BloomFilter *rc = l1.simQuery(&f3);
     cout << "\nComputed result: " << rc->getId() << " (" << rc->computeJaccard(&f3) << ")";
     
     cout << "\n\nLIST QUERY for 3 nearest neighbors of f1 in l1";
     vector<BloomFilter*> rd = l1.simQueryVec(&f1, 3);
     cout << "\nResults should be: " << res7[0].first << ", " << res7[1].first << ", " << res7[2].first;
     cout << "\nComputed results:\n";
     cout << rd[0]->getId() << " (" << f1.computeJaccard(rd[0]) << ")\n";
     cout << rd[1]->getId() << " (" << f1.computeJaccard(rd[1]) << ")\n";
     cout << rd[2]->getId() << " (" << f1.computeJaccard(rd[2]) << ")";
     
     cout << "\n\nSection query for 3 nearest neighbors of f2 in l1";
     vector<BloomFilter*> re = l1.simQueryVec(&f2, 3);
     cout << "\nResults should be: " << res8[0].first << ", " << res8[1].first << ", " << res8[2].first;
     cout << "\nComputed results:\n";
     cout << re[0]->getId() << " (" << f1.computeJaccard(re[0]) << ")\n";
     cout << re[1]->getId() << " (" << f1.computeJaccard(re[1]) << ")\n";
     cout << re[2]->getId() << " (" << f1.computeJaccard(re[2]) << ")";
     
     cout << "\n\nSection query for 3 nearest neighbors of f3 in l1";
     vector<BloomFilter*> rf = l1.simQueryVec(&f3, 3);
     cout << "\nResults should be: " << res9[0].first << ", " << res9[1].first << ", " << res9[2].first;
     cout << "\nComputed results:\n";
     cout << rf[0]->getId() << " (" << f1.computeJaccard(rf[0]) << ")\n";
     cout << rf[1]->getId() << " (" << f1.computeJaccard(rf[1]) << ")\n";
     cout << rf[2]->getId() << " (" << f1.computeJaccard(rf[2]) << ")"; */
    
    cout << endl;
    return 0;
}
