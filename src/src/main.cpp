//  main.cpp, Judith Greif
//  Description: Main executable for Bloom-Filter-Tree


#include <algorithm>
#include "BloomFilterTree.hpp"

using namespace std;

int main(int argc, const char *argv[]) {
    
    // Class BloomFilter
    
    cout << "CLASS BloomFilter" << endl;
    cout << "-----------------" << endl << endl;
    cout << "Create 22 instances of BloomFilter with ids 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 25, 26, 96, array length 10\n";
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
    
    cout << "\n\nCLASS BloomFilterTree";
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
    cout << "\n----------------------------------\n";
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
    b2.insert(&f16);
    
    cout << "\nCheck union filter construction";
    cout << "\n-------------------------------\n\n";
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

    cout << "\n\n\nCheck subset relations";
    cout << "\n----------------------\n\n";
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
    cout << "Count should be: 4\n\n";
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
    cout << "Count should be: 1\n\n";
    for (int i=0; i<v2.size(); i++) {
        if (f105.isSuperset(&v2[i]) == true) {
            cout << v2[i].getId() << " (";
            v2[i].printArr();
            cout << ")" << endl;
        }
    }
    
    vector<pair<int, float>> v5;
    BloomFilterNode *L7 = b3.search(105);
    float jacc4;
    cout << "\nCompute all jacc distances of query filter f105 (";
    f105.printArr();
    cout << ")\n\n";
    for (int i=0; i<v2.size(); i++) {
        jacc4 = L7->computeJaccard(L7->filters[2], &v2[i]);
        v5.push_back(make_pair(v2[i].getId(), jacc4));
        cout << "jacc(f105, f" << v2[i].getId() << "): " <<  jacc4 << endl;
    }
    
    cout << "\n4 nearest neighbors of f105 in ascending order:\n\n";
    sort(v5.begin(), v5.end(), [](const pair<int, float> &left, const pair<int, float> &right) {
        return left.second < right.second;
    });
    for (int i=0; i<4; i++) {
        cout << "f" << v5[i].first << " (" << v5[i].second << ")\n";
    }
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
    b4.insert(&f601);
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
    cout << "Count should be: 4\n\n";
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
    cout << "Count should be: 5\n\n";
    for (int i=0; i<v3.size(); i++) {
        if (f609.isSuperset(&v3[i]) == true) {
            cout << v3[i].getId() << " (";
            v3[i].printArr();
            cout << ")" << endl;
        }
    }
    
    vector<pair<int, float>> v4;
    BloomFilterNode *L8 = b4.search(609);
    float jacc6;
    cout << "\nCompute all jacc distances of query filter f609 (";
    f609.printArr();
    cout << ")\n";
    for (int i=0; i<v3.size(); i++) {
        jacc6 = L8->computeJaccard(L8->filters[1], &v3[i]);
        v4.push_back(make_pair(v3[i].getId(), jacc6));
        // cout << "jacc(f609, f" << v3[i].getId() << "): " << jacc6 << endl;
    }
    
    cout << "8 nearest neighbors of f109 in ascending order:\n\n";
    sort(v4.begin(), v4.end(), [](const pair<int, float> &left, const pair<int, float> &right) {
        return left.second < right.second;
    });
    for (int i=0; i<8; i++) {
        cout << "f" << v4[i].first << " (" << v4[i].second << ")\n";
    }
    
    
    // TODO
    
    // Subset insertion
    // Section insertion
    // Search queries
    
    cout << endl;
    return 0;
}