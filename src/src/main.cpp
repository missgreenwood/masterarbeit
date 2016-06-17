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
    
    // Store all lines from large dictionary in vector
    vector<string> words;
    ifstream file(filename);
    string word;
    while (file >> word) {
        words.push_back(word);
    }
    
    // Create 100 instances of BloomFilter with random ids, size 256 and insert 50 random elements from dictionary
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
    
    // Create 100 instances of BloomFilter with random ids, size 512 and insert 50 random elements from dictionary
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
    
    // Create 10 query filters f1..f10 with random ids, size 256 and insert 50 random elements from dictionary
    BloomFilter f1(rand(), 256);
    BloomFilter f2(rand(), 256);
    BloomFilter f3(rand(), 256);
    BloomFilter f4(rand(), 256);
    BloomFilter f5(rand(), 256);
    BloomFilter f6(rand(), 256);
    BloomFilter f7(rand(), 256);
    BloomFilter f8(rand(), 256);
    BloomFilter f9(rand(), 256);
    BloomFilter f10(rand(), 256);
    
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
    for (auto i=0; i<rand_index.size(); i++) {
        rand_index[i] = randomNumber();
        f7.add(words[rand_index[i]]);
    }
    for (auto i=0; i<rand_index.size(); i++) {
        rand_index[i] = randomNumber();
        f8.add(words[rand_index[i]]);
    }
    for (auto i=0; i<rand_index.size(); i++) {
        rand_index[i] = randomNumber();
        f9.add(words[rand_index[i]]);
    }
    for (auto i=0; i<rand_index.size(); i++) {
        rand_index[i] = randomNumber();
        f10.add(words[rand_index[i]]);
    }

    // Create 10 query filters f11..f20 with random ids, size 512 and insert 50 random elements from dictionary
    BloomFilter f11(rand(), 512);
    BloomFilter f12(rand(), 512);
    BloomFilter f13(rand(), 512);
    BloomFilter f14(rand(), 512);
    BloomFilter f15(rand(), 512);
    BloomFilter f16(rand(), 512);
    BloomFilter f17(rand(), 512);
    BloomFilter f18(rand(), 512);
    BloomFilter f19(rand(), 512);
    BloomFilter f20(rand(), 512);
    
    for (auto i=0; i<rand_index.size(); i++) {
        rand_index[i] = randomNumber();
        f11.add(words[rand_index[i]]);
    }
    for (auto i=0; i<rand_index.size(); i++) {
        rand_index[i] = randomNumber();
        f12.add(words[rand_index[i]]);
    }
    for (auto i=0; i<rand_index.size(); i++) {
        rand_index[i] = randomNumber();
        f13.add(words[rand_index[i]]);
    }
    for (auto i=0; i<rand_index.size(); i++) {
        rand_index[i] = randomNumber();
        f11.add(words[rand_index[i]]);
    }
    for (auto i=0; i<rand_index.size(); i++) {
        rand_index[i] = randomNumber();
        f12.add(words[rand_index[i]]);
    }
    for (auto i=0; i<rand_index.size(); i++) {
        rand_index[i] = randomNumber();
        f13.add(words[rand_index[i]]);
    }
    for (auto i=0; i<rand_index.size(); i++) {
        rand_index[i] = randomNumber();
        f11.add(words[rand_index[i]]);
    }
    for (auto i=0; i<rand_index.size(); i++) {
        rand_index[i] = randomNumber();
        f12.add(words[rand_index[i]]);
    }
    for (auto i=0; i<rand_index.size(); i++) {
        rand_index[i] = randomNumber();
        f13.add(words[rand_index[i]]);
    }
    for (auto i=0; i<rand_index.size(); i++) {
        rand_index[i] = randomNumber();
        f11.add(words[rand_index[i]]);
    }
    
    // Create instance of BloomFilterTree (b1) with minimum degree 3/max elements 6, filter size 256 and insert all filters in v1 as sets
    BloomFilterTree b1(3, 256);
    for (int i=0; i<v1.size(); i++) {
        b1.insertAsSets(&v1[i]);
    }
    
    // Create instance of BloomFilterTree (b2) with minimum degree 3/max elements 6, filter size 512 and insert all filters in v2 as sets
    BloomFilterTree b2(3, 512);
    for (int i=0; i<v2.size(); i++) {
        b2.insertAsSets(&v2[i]);
    }
    
    cout << "EXPERIMENT SETTINGS\n";
    cout << "-------------------\n";
    
    vector<pair<int, double>> res1 = b1.computekDistances(&f1, 10);
    vector<pair<int, double>> res2 = b1.computekDistances(&f2, 10);
    vector<pair<int, double>> res3 = b1.computekDistances(&f3, 10);
    vector<pair<int, double>> res4 = b1.computekDistances(&f4, 10);
    vector<pair<int, double>> res5 = b1.computekDistances(&f5, 10);
    vector<pair<int, double>> res6 = b1.computekDistances(&f6, 10);
    vector<pair<int, double>> res7 = b1.computekDistances(&f7, 10);
    vector<pair<int, double>> res8 = b1.computekDistances(&f8, 10);
    vector<pair<int, double>> res9 = b1.computekDistances(&f9, 10);
    vector<pair<int, double>> res10 = b1.computekDistances(&f10, 10);
    
    // Create output csv files
    ofstream nn1_256;
    /* ofstream nn3_256;
     nn3_256.open("nn3_256.txt");
     ofstream nn1_512;
     nn1_512.open("nn1_512.txt");
     ofstream nn3_512;
     nn3_512.open("nn3_512.txt"); */

    // Set search queries
    BloomFilter *r1 = b1.simQuery(&f1);
    BloomFilter *r2 = b1.simQuery(&f2);
    BloomFilter *r3 = b1.simQuery(&f3);
    BloomFilter *r4 = b1.simQuery(&f4);
    BloomFilter *r5 = b1.simQuery(&f5);
    BloomFilter *r6 = b1.simQuery(&f6);
    BloomFilter *r7 = b1.simQuery(&f7);
    BloomFilter *r8 = b1.simQuery(&f8);
    BloomFilter *r9 = b1.simQuery(&f9);
    BloomFilter *r10 = b1.simQuery(&f10);
    
    cout << "\nFilters: " << NUM_FILTERS;
    cout << "\nElements: " << NUM_ELEMENTS;
    cout << "\nFilter size: " << v1[0].getSize();
    cout << "\nHash functions: " << v1[0].getNumHashes();
    cout << "\nQuery filters: " << NUM_QUERYFILTERS << endl;
    
    nn1_256.open("nn1_256.txt");
    nn1_256 << "Filters: " << NUM_FILTERS << ", elements: " << NUM_ELEMENTS << ", filter size: " << v1[0].getSize() << ", hash functions: " << v1[0].getNumHashes() << ", query filters: " << NUM_QUERYFILTERS << endl;
    
    // Optimal
    cout << "\nNN query, optimal results:\n";
    cout << res1[0].first << " (" << res1[0].second << ")\n";
    cout << res2[0].first << " (" << res2[0].second << ")\n";
    cout << res3[0].first << " (" << res3[0].second << ")\n";
    cout << res4[0].first << " (" << res4[0].second << ")\n";
    cout << res5[0].first << " (" << res5[0].second << ")\n";
    cout << res6[0].first << " (" << res6[0].second << ")\n";
    cout << res7[0].first << " (" << res7[0].second << ")\n";
    cout << res8[0].first << " (" << res8[0].second << ")\n";
    cout << res9[0].first << " (" << res9[0].second << ")\n";
    cout << res10[0].first << " (" << res10[0].second << ")\n";
    
    nn1_256 << res1[0].second << "," << res2[0].second << "," << "," << res3[0].second << "," << res4[0].second << "," << res5[0].second << "," << res6[0].second << "," << res7[0].second << "," << res8[0].second << "," << res9[0].second << "," << res10[0].second << endl;
    
    // Computed
    cout << "\nNN query, computed results:\n";
    cout << r1->getId() << " (" << f1.computeJaccard(r1) << ")\n";
    cout << r2->getId() << " (" << f2.computeJaccard(r2) << ")\n";
    cout << r3->getId() << " (" << f3.computeJaccard(r3) << ")\n";
    cout << r4->getId() << " (" << f4.computeJaccard(r4) << ")\n";
    cout << r5->getId() << " (" << f5.computeJaccard(r5) << ")\n";
    cout << r6->getId() << " (" << f6.computeJaccard(r6) << ")\n";
    cout << r7->getId() << " (" << f7.computeJaccard(r7) << ")\n";
    cout << r8->getId() << " (" << f8.computeJaccard(r8) << ")\n";
    cout << r9->getId() << " (" << f9.computeJaccard(r9) << ")\n";
    cout << r10->getId() << " (" << f10.computeJaccard(r10) << ")\n";
    
    nn1_256 << f1.computeJaccard(r1) << "," << f2.computeJaccard(r2) << "," << f3.computeJaccard(r3) << f4.computeJaccard(r4) << "," << f5.computeJaccard(r5) << "," << f6.computeJaccard(r6) <<f7.computeJaccard(r7) << "," << f8.computeJaccard(r8) << "," << f9.computeJaccard(r9) << "," << f10.computeJaccard(r10) << endl;
    nn1_256.close();
    
    /* cout << "\n\nTREE QUERY for 3 nearest neighbors of filter " << f1.getId();
    cout << "\n\nResults should be: " << res1[0].first << ", " << res1[1].first << ", " << res1[2].first;
    vector<BloomFilter*> rA = b1.simQueryVec(&f1, 3);
    cout << "\nComputed results:\n";
    cout << rA[0]->getId() << " (" << f1.computeJaccard(rA[0]) << ")\n";
    cout << rA[1]->getId() << " (" << f1.computeJaccard(rA[1]) << ")\n";
    cout << rA[2]->getId() << " (" << f1.computeJaccard(rA[2]) << ")";
    
    cout << "\n\nTREE QUERY for 3 nearest neighbors of filter " << f2.getId();
    cout << "\nResults should be: " << res3[0].first << ", " << res3[1].first << ", " << res3[2].first;
    vector<BloomFilter*> rC = b1.simQueryVec(&f2, 3);
    cout << "\nComputed results:\n";
    cout << rC[0]->getId() << " (" << f2.computeJaccard(rC[0]) << ")\n";
    cout << rC[1]->getId() << " (" << f2.computeJaccard(rC[1]) << ")\n";
    cout << rC[2]->getId() << " (" << f2.computeJaccard(rC[2]) << ")";
    
    cout << "\n\nTREE QUERY for 3 nearest neighbors of filter " << f3.getId();
    cout << "\nResults should be: " << res5[0].first << ", " << res5[1].first << ", " << res5[2].first;
    vector<BloomFilter*> rE = b1.simQueryVec(&f3, 3);
    cout << "\nComputed results:\n";
    cout << rE[0]->getId() << " (" << f3.computeJaccard(rE[0]) << ")\n";
    cout << rE[1]->getId() << " (" << f3.computeJaccard(rE[1]) << ")\n";
    cout << rE[2]->getId() << " (" << f3.computeJaccard(rE[2]) << ")";
    
    cout << "\nFilter size: " << v2[0].getSize();
    cout << "\nQuery filters: " << f4.getId() << ", " << f5.getId() << ", " << f6.getId() << endl << endl;
    
    cout <<"\n\nTREE QUERY for nearest neighbor of filter " << f4.getId();
    cout << "\nResult should be: " << res7[0].first;
    BloomFilter* r7 = b2.simQuery(&f4);
    cout << "\nComputed result: " << r7->getId() << " (" << f4.computeJaccard(r7) << ")";

    cout << "\n\nTREE QUERY for nearest neighbor of filter " << f5.getId();
    cout << "\nResult should be: " << res9[0].first;
    BloomFilter* r9 = b2.simQuery(&f5);
    cout << "\nComputed result: " << r9->getId() << " (" << f5.computeJaccard(r9) << ")";

    cout << "\n\nTREE QUERY for nearest neighbor of filter " << f6.getId();
    cout << "\nResult should be: " << res11[0].first;
    BloomFilter* r11 = b2.simQuery(&f6);
    cout << "\nComputed result: " << r11->getId() << " (" << f6.computeJaccard(r11) << ")";
    
    cout << "\n\nTREE QUERY for 3 nearest neighbors of filter " << f4.getId();
    cout << "\nResults should be: " << res7[0].first << ", " << res7[1].first << ", " << res7[2].first;
    vector<BloomFilter*> rG= b2.simQueryVec(&f4, 3);
    cout << "\nComputed results:\n";
    cout << rG[0]->getId() << " (" << f4.computeJaccard(rG[0]) << ")\n";
    cout << rG[1]->getId() << " (" << f4.computeJaccard(rG[1]) << ")\n";
    cout << rG[2]->getId() << " (" << f4.computeJaccard(rG[2]) << ")";
    
    cout << "\n\nTREE QUERY for 3 nearest neighbors of filter " << f5.getId();
    cout << "\nResults should be: " << res9[0].first << ", " << res9[1].first << ", " << res9[2].first;
    vector<BloomFilter*> rI= b2.simQueryVec(&f5, 3);
    cout << "\nComputed results:\n";
    cout << rI[0]->getId() << " (" << f5.computeJaccard(rI[0]) << ")\n";
    cout << rI[1]->getId() << " (" << f5.computeJaccard(rI[1]) << ")\n";
    cout << rI[2]->getId() << " (" << f5.computeJaccard(rI[2]) << ")";

    cout << "\n\nTREE QUERY for 3 nearest neighbors of filter " << f6.getId();
    cout << "\nResults should be: " << res11[0].first << ", " << res11[1].first << ", " << res11[2].first;
    vector<BloomFilter*> rK= b2.simQueryVec(&f6, 3);
    cout << "\nComputed results:\n";
    cout << rK[0]->getId() << " (" << f6.computeJaccard(rK[0]) << ")\n";
    cout << rK[1]->getId() << " (" << f6.computeJaccard(rK[1]) << ")\n";
    cout << rK[2]->getId() << " (" << f6.computeJaccard(rK[2]) << ")"; */
    
    cout << endl;
    return 0;
}