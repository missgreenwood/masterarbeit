//  main.cpp, Judith Greif
//  Description: Main executable for Bloom filter data structures

#include <iostream>
#include <fstream>
#include <random>

#include "RandomFunctions.hpp"
#include "BloomFilterTree.hpp"
#include "BloomFilterList.hpp"


using namespace std;

const char* filename = "/Users/judith/Documents/MA/src/src/words.txt";

int main(int argc, const char *argv[]) {

    // Class BloomFilter
    cout << "CLASS BloomFilter\n";
    cout << "-----------------\n";
    cout << "Create 100 instances of BloomFilter with random ids, array length 256 and insert 50 random elements from dictionary";
    
    // Store all lines from large dictionary in vector
    vector<string> words;
    ifstream file(filename);
    string word;
    while (file >> word) {
        words.push_back(word);
    }
    
    // Repeat 100 times:
    // Pick 50 lines from dictionary at random and insert into new BloomFilter object (size 256)
    BloomFilter *filter;
    vector<BloomFilter> v1;
    
    for (int i=0; i<NUM_FILTERS; i++) {
        filter = new BloomFilter(rand(), 256);
        vector<int> rand_index(NUM_ELEMENTS);
        for (auto i=0; i<rand_index.size(); i++) {
            rand_index[i] = randomNumber();
            filter->add(words[rand_index[i]]);
        }
        v1.push_back(*filter);
    }
    
    cout << "\n\nCreate 100 instances of BloomFilter with random ids, array length 512 and insert 50 random elements from dictionary";
    
    // Repeat 100 times:
    // Pick 50 lines from dictionary at random and insert into new BloomFilter object (size 512)
    vector<BloomFilter> v2;
    
    for (int i=0; i<NUM_FILTERS; i++) {
        filter = new BloomFilter(rand(), 512);
        vector<int> rand_index(NUM_ELEMENTS);
        for (auto i=0; i<rand_index.size(); i++) {
            rand_index[i] = randomNumber();
            filter->add(words[rand_index[i]]);
        }
        v2.push_back(*filter);
    }
    
    cout << "\n\nCreate 3 query filters f1, f2, f3 with ids 1, 2, 3, array length 256 and insert 50 random elements from dictionary";
    BloomFilter f1(1, 256);
    BloomFilter f2(2, 256);
    BloomFilter f3(3, 256);
    vector<int> rand_index(NUM_ELEMENTS);
    
    for (auto i=0; i<rand_index.size(); i++) {
        rand_index[i] = randomNumber();
        f1.add(words[rand_index[i]]);
    }
    
    for (auto i=0; i<rand_index.size(); i++) {
        rand_index[i] = randomNumber();
        f2.add(words[rand_index[i]]);
    }

    for (auto i=0; i<rand_index.size(); i++) {
        rand_index[i] = randomNumber();
        f3.add(words[rand_index[i]]);
    }

    cout << "\n\nCreate 3 query filters f4, f5, f6 with ids 4, 5, 6, array length 512 and insert 50 random elements from dictionary";
    BloomFilter f4(4, 512);
    BloomFilter f5(5, 512);
    BloomFilter f6(6, 512);
    
    for (auto i=0; i<rand_index.size(); i++) {
        rand_index[i] = randomNumber();
        f4.add(words[rand_index[i]]);
    }
    
    for (auto i=0; i<rand_index.size(); i++) {
        rand_index[i] = randomNumber();
        f5.add(words[rand_index[i]]);
    }
    
    for (auto i=0; i<rand_index.size(); i++) {
        rand_index[i] = randomNumber();
        f6.add(words[rand_index[i]]);
    }

    // Class BloomFilterTree
    
    cout << "\n\n\nCLASS BloomFilterTree";
    cout << "\n---------------------\n";
    
    cout << "Create instance of BloomFilterTree (b1) with minimum degree 3/max elements 6, filter size 256 and insert all filters in v1 as sets\n\n";
    BloomFilterTree b1(3, 256);
    for (int i=0; i<v1.size(); i++) {
        b1.insertAsSets(&v1[i]);
    }
    
    cout << "Create instance of BloomFilterTree (b2) with minimum degree 3/max elements 6, filter size 256 and insert every second filter in v1 as sets\n\n";
    BloomFilterTree b2(3, 256);
    for (int i=0; i<v1.size(); i+=2) {
        b2.insertAsSets(&v1[i]);
    }
    
    cout << "Create instance of BloomFilterTree (b3) with minimum degree 3/max elements 6, filter size 512 and insert all filters in v2 as sets\n\n";
    BloomFilterTree b3(3, 512);
    for (int i=0; i<v2.size(); i++) {
        b3.insertAsSets(&v2[i]);
    }
    
    cout << "Create instance of BloomFilterTree (b4) with minimum degree 3/max elements 6, filter size 512 and insert every second filter in v2 as sets\n\n";
    BloomFilterTree b4(3, 512);
    for (int i=0; i<v2.size(); i+=2) {
        b4.insertAsSets(&v2[i]);
    }
    
    cout << "10 nearest neighbors of f1 in b1:\n\n";
    vector<pair<int, double>> res1 = b1.computekDistances(&f1, 10);

    /* cout << "\n10 nearest neighbors of f1 in b2:\n\n";
    vector<pair<int, double>> res2 = b2.computekDistances(&f1, 10);
    
    cout << "\n10 nearest neighbors of f2 in b1:\n\n";
    vector<pair<int, double>> res3 = b1.computekDistances(&f2, 10);
    
    cout << "\n10 nearest neighbors of f2 in b2:\n\n";
    vector<pair<int, double>> res4 = b2.computekDistances(&f2, 10);
    
    cout << "\n10 nearest neighbors of f3 in b1:\n\n";
    vector<pair<int, double>> res5 = b1.computekDistances(&f3, 10);
    
    cout << "\n10 nearest neighbors of f3 in b2:\n\n";
    vector<pair<int, double>> res6 = b2.computekDistances(&f3, 10);
    
    cout << "\n10 nearest neighbors of f4 in b3:\n\n";
    vector<pair<int, double>> res7 = b3.computekDistances(&f4, 10);
    
    cout << "\n10 nearest neighbors of f4 in b4:\n\n";
    vector<pair<int, double>> res8 = b4.computekDistances(&f4, 10);
    
    cout << "\n10 nearest neighbors of f5 in b3:\n\n";
    vector<pair<int, double>> res9 = b3.computekDistances(&f5, 10);
    
    cout << "\n10 nearest neighbors of f5 in b4:\n\n";
    vector<pair<int, double>> res10 = b4.computekDistances(&f5, 10);
    
    cout << "\n10 nearest neighbors of f6 in b3:\n\n";
    vector<pair<int, double>> res11 = b3.computekDistances(&f6, 10);
    
    cout << "\n10 nearest neighbors of f6 in b4:\n\n";
    vector<pair<int, double>> res12 = b4.computekDistances(&f6, 10);
    
    cout << "\n\nCheck subset insertion";
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
    cout << "\nComputed optimal superset id for f1 in b2: " << b2.computeSupersetId(&f1);
    
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
    cout << "\nComputed result: " << r6->getId() << " (" << f3.computeJaccard(r6) << ")";
    
    cout << "\n\nTREE QUERY for nearest neighbor of f4 in b3";
    cout << "\nResult should be: " << res7[0].first;
    BloomFilter* r7 = b3.simQuery(&f4);
    cout << "\nComputed result: " << r7->getId() << " (" << f4.computeJaccard(r7) << ")";

    cout << "\n\nTREE QUERY for nearest neighbor of f4 in b4";
    cout << "\nResult should be: " << res8[0].first;
    BloomFilter* r8 = b4.simQuery(&f4);
    cout << "\nComputed result: " << r8->getId() << " (" << f4.computeJaccard(r8) << ")";

    cout << "\n\nTREE QUERY for nearest neighbor of f5 in b3";
    cout << "\nResult should be: " << res9[0].first;
    BloomFilter* r9 = b3.simQuery(&f5);
    cout << "\nComputed result: " << r9->getId() << " (" << f5.computeJaccard(r9) << ")";

    cout << "\n\nTREE QUERY for nearest neighbor of f5 in b4";
    cout << "\nResult should be: " << res10[0].first;
    BloomFilter* r10 = b4.simQuery(&f5);
    cout << "\nComputed result: " << r10->getId() << " (" << f5.computeJaccard(r10) << ")";

    cout << "\n\nTREE QUERY for nearest neighbor of f6 in b3";
    cout << "\nResult should be: " << res11[0].first;
    BloomFilter* r11 = b3.simQuery(&f6);
    cout << "\nComputed result: " << r11->getId() << " (" << f6.computeJaccard(r11) << ")";
    
    cout << "\n\nTREE QUERY for nearest neighbor of f6 in b4";
    cout << "\nResult should be: " << res12[0].first;
    BloomFilter* r12 = b4.simQuery(&f6);
    cout << "\nComputed result: " << r12->getId() << " (" << f6.computeJaccard(r12) << ")";

    cout << "\n\nTREE QUERY for 3 nearest neighbors of f1 in b1";
    cout << "\nResults should be: " << res1[0].first << ", " << res1[1].first << ", " << res1[2].first;
    vector<BloomFilter*> rA = b1.simQueryVec(&f1, 3);
    cout << "\nComputed results:\n";
    cout << rA[0]->getId() << " (" << f1.computeJaccard(rA[0]) << ")\n";
    cout << rA[1]->getId() << " (" << f1.computeJaccard(rA[1]) << ")\n";
    cout << rA[2]->getId() << " (" << f1.computeJaccard(rA[2]) << ")";
    
    cout << "\n\nTREE QUERY for 3 nearest neighbors of f1 in b2";
    cout << "\nResults should be: " << res2[0].first << ", " << res2[1].first << ", " << res2[2].first;
    vector<BloomFilter*> rB = b2.simQueryVec(&f1, 3);
    cout << "\nComputed results:\n";
    cout << rB[0]->getId() << " (" << f1.computeJaccard(rB[0]) << ")\n";
    cout << rB[1]->getId() << " (" << f1.computeJaccard(rB[1]) << ")\n";
    cout << rB[2]->getId() << " (" << f1.computeJaccard(rB[2]) << ")";
    
    cout << "\n\nTREE QUERY for 3 nearest neighbors of f2 in b1";
    cout << "\nResults should be: " << res3[0].first << ", " << res3[1].first << ", " << res3[2].first;
    vector<BloomFilter*> rC = b1.simQueryVec(&f2, 3);
    cout << "\nComputed results:\n";
    cout << rC[0]->getId() << " (" << f2.computeJaccard(rC[0]) << ")\n";
    cout << rC[1]->getId() << " (" << f2.computeJaccard(rC[1]) << ")\n";
    cout << rC[2]->getId() << " (" << f2.computeJaccard(rC[2]) << ")";

    cout << "\n\nTREE QUERY for 3 nearest neighbors of f2 in b2";
    cout << "\nResults should be: " << res4[0].first << ", " << res4[1].first << ", " << res4[2].first;
    vector<BloomFilter*> rD = b2.simQueryVec(&f2, 3);
    cout << "\nComputed results:\n";
    cout << rD[0]->getId() << " (" << f2.computeJaccard(rD[0]) << ")\n";
    cout << rD[1]->getId() << " (" << f2.computeJaccard(rD[1]) << ")\n";
    cout << rD[2]->getId() << " (" << f2.computeJaccard(rD[2]) << ")";
    
    cout << "\n\nTREE QUERY for 3 nearest neighbors of f3 in b1";
    cout << "\nResults should be: " << res5[0].first << ", " << res5[1].first << ", " << res5[2].first;
    vector<BloomFilter*> rE = b1.simQueryVec(&f3, 3);
    cout << "\nComputed results:\n";
    cout << rE[0]->getId() << " (" << f3.computeJaccard(rE[0]) << ")\n";
    cout << rE[1]->getId() << " (" << f3.computeJaccard(rE[1]) << ")\n";
    cout << rE[2]->getId() << " (" << f3.computeJaccard(rE[2]) << ")";
    
    cout << "\n\nTREE QUERY for 3 nearest neighbors of f3 in b2";
    cout << "\nResults should be: " << res6[0].first << ", " << res6[1].first << ", " << res6[2].first;
    vector<BloomFilter*> rF= b2.simQueryVec(&f3, 3);
    cout << "\nComputed results:\n";
    cout << rF[0]->getId() << " (" << f3.computeJaccard(rF[0]) << ")\n";
    cout << rF[1]->getId() << " (" << f3.computeJaccard(rF[1]) << ")\n";
    cout << rF[2]->getId() << " (" << f3.computeJaccard(rF[2]) << ")";

    cout << "\n\nTREE QUERY for 3 nearest neighbors of f4 in b3";
    cout << "\nResults should be: " << res7[0].first << ", " << res7[1].first << ", " << res7[2].first;
    vector<BloomFilter*> rG= b3.simQueryVec(&f4, 3);
    cout << "\nComputed results:\n";
    cout << rG[0]->getId() << " (" << f4.computeJaccard(rG[0]) << ")\n";
    cout << rG[1]->getId() << " (" << f4.computeJaccard(rG[1]) << ")\n";
    cout << rG[2]->getId() << " (" << f4.computeJaccard(rG[2]) << ")";
    
    cout << "\n\nTREE QUERY for 3 nearest neighbors of f4 in b4";
    cout << "\nResults should be: " << res8[0].first << ", " << res8[1].first << ", " << res8[2].first;
    vector<BloomFilter*> rH= b4.simQueryVec(&f4, 3);
    cout << "\nComputed results:\n";
    cout << rH[0]->getId() << " (" << f4.computeJaccard(rH[0]) << ")\n";
    cout << rH[1]->getId() << " (" << f4.computeJaccard(rH[1]) << ")\n";
    cout << rH[2]->getId() << " (" << f4.computeJaccard(rH[2]) << ")";

    cout << "\n\nTREE QUERY for 3 nearest neighbors of f5 in b3";
    cout << "\nResults should be: " << res9[0].first << ", " << res9[1].first << ", " << res9[2].first;
    vector<BloomFilter*> rI= b3.simQueryVec(&f5, 3);
    cout << "\nComputed results:\n";
    cout << rI[0]->getId() << " (" << f5.computeJaccard(rI[0]) << ")\n";
    cout << rI[1]->getId() << " (" << f5.computeJaccard(rI[1]) << ")\n";
    cout << rI[2]->getId() << " (" << f5.computeJaccard(rI[2]) << ")";

    cout << "\n\nTREE QUERY for 3 nearest neighbors of f5 in b4";
    cout << "\nResults should be: " << res10[0].first << ", " << res10[1].first << ", " << res10[2].first;
    vector<BloomFilter*> rJ= b4.simQueryVec(&f5, 3);
    cout << "\nComputed results:\n";
    cout << rJ[0]->getId() << " (" << f5.computeJaccard(rJ[0]) << ")\n";
    cout << rJ[1]->getId() << " (" << f5.computeJaccard(rJ[1]) << ")\n";
    cout << rJ[2]->getId() << " (" << f5.computeJaccard(rJ[2]) << ")";

    cout << "\n\nTREE QUERY for 3 nearest neighbors of f6 in b3";
    cout << "\nResults should be: " << res11[0].first << ", " << res11[1].first << ", " << res11[2].first;
    vector<BloomFilter*> rK= b3.simQueryVec(&f6, 3);
    cout << "\nComputed results:\n";
    cout << rK[0]->getId() << " (" << f6.computeJaccard(rK[0]) << ")\n";
    cout << rK[1]->getId() << " (" << f6.computeJaccard(rK[1]) << ")\n";
    cout << rK[2]->getId() << " (" << f6.computeJaccard(rK[2]) << ")";

    cout << "\n\nTREE QUERY for 3 nearest neighbors of f6 in b4";
    cout << "\nResults should be: " << res12[0].first << ", " << res12[1].first << ", " << res12[2].first;
    vector<BloomFilter*> rL= b4.simQueryVec(&f6, 3);
    cout << "\nComputed results:\n";
    cout << rL[0]->getId() << " (" << f6.computeJaccard(rL[0]) << ")\n";
    cout << rL[1]->getId() << " (" << f6.computeJaccard(rL[1]) << ")\n";
    cout << rL[2]->getId() << " (" << f6.computeJaccard(rL[2]) << ")"; */

    cout << endl;
    return 0;
}