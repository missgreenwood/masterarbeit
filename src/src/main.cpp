//  main.cpp, Judith Greif
//  Description: Main executable for Bloom-Filter-Tree


#include "BloomFilterTree.hpp"

using namespace std;

int main(int argc, const char *argv[]) {
    
    // Class BloomFilter
    
    cout << "CLASS BloomFilter" << endl;
    cout << "-----------------" << endl << endl;
    cout << "Create 23 instances of BloomFilter with ids 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 25, 26, 96, 100, array length 10 and random values 0/1\n";
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
    BloomFilter f100(10, 100);
    
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
    f100.initRandom();
    f100.printData();
    
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

    cout << "\n\n\nCheck Jaccard distance computation";
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
    
    cout << "\n\njacc(f3, f16): " << l4.jacc(l4.filters[0], l4.filters[3]);
    cout << "\njacc(f3, f18): " << l4.jacc(l4.filters[0], l4.filters[4]);
    cout << "\njacc(f3, f19): " << l4.jacc(l4.filters[0], l4.filters[5]);
    
    cout << "\n\njacc(f5, f16): " << l4.jacc(l4.filters[1], l4.filters[3]);
    cout << "\njacc(f5, f18): " << l4.jacc(l4.filters[1], l4.filters[4]);
    cout << "\njacc(f5, f19): " << l4.jacc(l4.filters[1], l4.filters[5]);
    
    cout << "\n\njacc(f6, f16): " << l4.jacc(l4.filters[2], l4.filters[3]);
    cout << "\njacc(f6, f18): " << l4.jacc(l4.filters[2], l4.filters[4]);
    cout << "\njacc(f6, f19): " << l4.jacc(l4.filters[2], l4.filters[5]);
    
    cout << "\n\nCompute Jaccard distance of filters f4, f7, f10, f17, f25, f2, f8, f9, f26, f96, f16 and  tree root:\n\n";
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
    cout << " (key " << b2.computeMinJaccardKey(&f16) << ")\n";
    cout << "Min jacc(b2, f18): " << b2.computeMinJaccard(&f18);
    cout << " (key " << b2.computeMinJaccardKey(&f18) << ")\n";
    cout << "Min jacc(b2, f19): " << b2.computeMinJaccard(&f19);
    cout << " (key " << b2.computeMinJaccardKey(&f19) << ")\n\n";
    b2.insert(&f5);
    cout << "Min jacc(b2, f16): " << b2.computeMinJaccard(&f16);
    cout << " (key " << b2.computeMinJaccardKey(&f16) << ")\n";
    cout << "Min jacc(b2, f18): " << b2.computeMinJaccard(&f18);
    cout << " (key " << b2.computeMinJaccardKey(&f18) << ")\n";
    cout << "Min jacc(b2, f19): " << b2.computeMinJaccard(&f19);
    cout << " (key " << b2.computeMinJaccardKey(&f19) << ")\n";
    b2.insert(&f6);
    cout << "\nMin jacc(b2, f16): " << b2.computeMinJaccard(&f16);
    cout << " (key " << b2.computeMinJaccardKey(&f16) << ")\n";
    cout << "Min jacc(b2, f18): " << b2.computeMinJaccard(&f18);
    cout << " (key " << b2.computeMinJaccardKey(&f18) << ")\n";
    cout << "Min jacc(b2, f19): " << b2.computeMinJaccard(&f19);
    cout << " (key " << b2.computeMinJaccardKey(&f19) << ")\n";
    b2.insert(&f11);
    cout << "\nMin jacc(b2, f16): " << b2.computeMinJaccard(&f16);
    cout << " (key " << b2.computeMinJaccardKey(&f16) << ")\n";
    cout << "Min jacc(b2, f18): " << b2.computeMinJaccard(&f18);
    cout << " (key " << b2.computeMinJaccardKey(&f18) << ")\n";
    cout << "Min jacc(b2, f19): " << b2.computeMinJaccard(&f19);
    cout << " (key " << b2.computeMinJaccardKey(&f19) << ")\n";
    b2.insert(&f12);
    cout << "\nMin jacc(b2, f16): " << b2.computeMinJaccard(&f16);
    cout << " (key " << b2.computeMinJaccardKey(&f16) << ")\n";
    cout << "Min jacc(b2, f18): " << b2.computeMinJaccard(&f18);
    cout << " (key " << b2.computeMinJaccardKey(&f18) << ")\n";
    cout << "Min jacc(b2, f19): " << b2.computeMinJaccard(&f19);
    cout << " (key " << b2.computeMinJaccardKey(&f19) << ")\n";
    b2.insert(&f13);
    cout << "\nMin jacc(b2, f16): " << b2.computeMinJaccard(&f16);
    cout << " (key " << b2.computeMinJaccardKey(&f16) << ")\n";
    cout << "Min jacc(b2, f18): " << b2.computeMinJaccard(&f18);
    cout << " (key " << b2.computeMinJaccardKey(&f18) << ")\n";
    cout << "Min jacc(b2, f19): " << b2.computeMinJaccard(&f19);
    cout << " (key " << b2.computeMinJaccardKey(&f19) << ")\n";
    b2.insert(&f14);
    cout << "\nMin jacc(b2, f16): " << b2.computeMinJaccard(&f16);
    cout << " (key " << b2.computeMinJaccardKey(&f16) << ")\n";
    cout << "Min jacc(b2, f18): " << b2.computeMinJaccard(&f18);
    cout << " (key " << b2.computeMinJaccardKey(&f18) << ")\n";
    cout << "Min jacc(b2, f19): " << b2.computeMinJaccard(&f19);
    cout << " (key " << b2.computeMinJaccardKey(&f19) << ")\n";
    b2.insert(&f15);
    cout << "\nMin jacc(b2, f16): " << b2.computeMinJaccard(&f16);
    cout << " (key " << b2.computeMinJaccardKey(&f16) << ")\n";
    cout << "Min jacc(b2, f18): " << b2.computeMinJaccard(&f18);
    cout << " (key " << b2.computeMinJaccardKey(&f18) << ")\n";
    cout << "Min jacc(b2, f19): " << b2.computeMinJaccard(&f19);
    cout << " (key " << b2.computeMinJaccardKey(&f19) << ")\n\n";
    
    b2.traverse();
    cout << endl;
    b2.traverseFilters();
    
    cout << "\n\n\nCLASS BloomFilterLeaf";
    cout << "\n---------------------\n\n";
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

    
    // TODO
    /* cout << "\n\nCompute optimal ids for filters f16, f18, f19 regarding b2\n";
    cout << "\nSmallest key in b2: " << b2.getMinKey() << "\nBiggest key in b2: " << b2.getMaxKey();
    cout << "\nOptimal id for f16 should be: 4" << "\nComputed optimal id is: " << b2.computeSimilarityId(&f16);
    cout << "\nOptimal id for f18 should be: 4" << "\nComputed optimal id is: " << b2.computeSimilarityId(&f18);
    cout << "\nOptimal id for f19 should be: 10" << "\nComputed optimal id is: " << b2.computeSimilarityId(&f19);
    cout << "\n\nInsert f16 into b2, changing its id to optimal value:\n\n";
    b2.insertSimilarFilter(&f16);
    b2.traverse();
    cout << endl;
    b2.traverseFilters();
    cout << "\n\nInsert f18 into b2, changing its id to optimal value:\n\n";
    cout << "Max jacc(b2, f18): " << b2.computeMaxJaccard(&f18);
    cout << " (key " << b2.computeMaxJaccardKey(&f18) << ")\n";
    cout << "Optimal id for f18 should be: 7" << "\nComputed optimal id is: " << b2.computeSimilarityId(&f18) << endl << endl;
    b2.insertSimilarFilter(&f18);
    b2.traverse();
    cout << endl;
    b2.traverseFilters();
    cout << "\n\nInsert f19 into b2, changing its id to optimal value:\n\n";
    cout << "Max jacc(b2, f19): " << b2.computeMaxJaccard(&f19);
    cout << " (key " << b2.computeMaxJaccardKey(&f19) << ")\n";
    cout << "Optimal id for f19 should be: 10" << "\nComputed optimal id is: " << b2.computeSimilarityId(&f19) << endl;
    b2.insertSimilarFilter(&f19);
    cout << endl;
    b2.traverse();
    cout << endl;
    b2.traverseFilters();
    
    cout << "\n\nCheck correct insertion of f16 (";
    f16.printArr();
    cout << "): ";
    BloomFilterNode *L1 = b2.search(4);
    L1->filters[1]->printArr();
    cout << "\nCheck correct insertion of f18 (";
    f18.printArr();
    cout << "): ";
    L1 = b2.search(7);
    L1->filters[0]->printArr();
    cout << "\nCheck correct insertion of f19 (";
    f19.printArr();
    cout << "): ";
    L1 = b2.search(10);
    L1->filters[1]->printArr();
    cout << "\n\nCreate instance of 4-level BloomFilterTree with minimum degree 1/max. elements 2, filter size 10 (b3)\n\n";
    BloomFilterTree b3(1, 10);
    cout << "Insert all filters in v1 into b3, changing their ids to optimal values:\n\n"; */
    
    // TO CHECK
    /* for (int i=0; i<10; i++) {
        b3.insertSimilarFilter(&v1[i]);
    }
    cout << endl << endl;
    b3.traverse();
    cout << endl;
    b3.traverseFilters(); */
    
    // Class BloomFilterLeaf
    
    
    // TODO
    /* cout << "\n\n\nQuery functions for BloomFilterTree and BloomFilterLeaf";
    cout << "\n-------------------------------------------------------";
    cout << "\nTREE QUERY for f100 (";
    f100.printArr();
    cout << ")";
    
    cout << "\nNN should be: " << b3.computeMaxJaccardKey(&f100);
    cout << " (";
    b3.search(b3.computeMaxJaccardKey(&f100))->filters[0]->printArr();
    cout << ")";
    cout << "\n3 nearest neighbors should be: -1 (";
    L1->filters[0]->printArr();
    cout << "), ";
    BloomFilterNode *L2 = b3.search(8);
    cout << "8 (";
    L2->filters[1]->printArr();
    cout << "), ";
    BloomFilterNode *L3 = b3.search(4);
    cout << "4 (";
    // L3->filters[1]->printArr();
    cout << ")\n";
    
    cout << "\na) simpleSimQuery -- return nearest neighbor, no pruning: " << b3.simpleSimQuery(&f100)->getId() << " (";
    b3.simpleSimQuery(&f100)->printArr();
    cout << ")";
    
    cout << "\n\nb) simpleSimQueryVec -- return 3 nearest neighbors, no pruning: ";
    b3.simpleSimQueryVec(&f100, 3);
    
    cout << "\n\nc) simQuery -- return nearest neighbor, follow only best path: " << b3.simQuery(&f100)->getId() << " (";
    b3.simQuery(&f100)->printArr();
    cout << ")";
    
    cout << "\n\nd) simQueryVec -- return 3 nearest neighbors, follow only best path: ";
    b3.simQueryVec(&f100, 3);
    
    cout << "\n\n\nLEAF QUERY for f100 (";
    f100.printArr();
    cout << ")";
    cout << "\nNearest neighbor should be: " << l2.computeMaxJaccardKey(&f100);
    cout << " (";
    l2.filters[1]->printArr();
    cout << ")";
    cout << "\n3 nearest neighbors should be (because leaf is not sorted): " << l2.computeMaxJaccardKey(&f100) << " (";
    l2.filters[1]->printArr();
    cout << "), 11 (";
    l2.filters[3]->printArr();
    cout << "), 3 (";
    l2.filters[0]->printArr();
    cout << ")\n";
    
    cout << "\ne) simpleSimQueryVec -- return k nearest neighbors, no pruning";
    l2.simpleSimQueryVec(&f100, 3);
    
    cout << "\n\n\nLEAF QUERY for f13 (";
    f13.printArr();
    cout << ")";
    cout << "\nNearest neighbor should be: " << l2.computeMaxJaccardKey(&f13);
    cout << " (";
    l2.filters[5]->printArr();
    cout << ")";
    cout << "\n3 nearest neighbors should be (because leaves are not sorted): 13 (";
    l2.filters[5]->printArr();
    cout << "), 14 (";
    l2.filters[4]->printArr();
    cout << "), 11 (";
    l3.filters[0]->printArr();
    cout << ")\n";
    cout << "\nf) simpleSimQueryVec -- return k nearest neighbors, no pruning";
    l2.simpleSimQueryVec(&f13, 3);
    
    cout << "\n\n\nLEAF QUERY for f14 (";
    f14.printArr();
    cout << ")";
    cout << "\nNearest neighbor should be: " << l3.computeMaxJaccardKey(&f14) << " (";
    l3.filters[0]->printArr();
    cout << ")";
    cout << "\n3 nearest neighbors should be (because leaves are not sorted): 14 (";
    l3.filters[0]->printArr();
    cout << "), 13 (";
    l2.filters[5]->printArr();
    cout << "), 15 (";
    l3.filters[1]->printArr();
    cout << ")\n";
    cout << "\ng) simpleSimQueryVec -- return k nearest neighbors, no pruning";
    l3.simpleSimQueryVec(&f14, 3); */
    
    cout << endl;
    return 0;
}