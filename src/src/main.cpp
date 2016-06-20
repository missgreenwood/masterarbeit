//  main.cpp, Judith Greif
//  Description: Main executable for Bloom filter data structures

#include <iostream>
#include <fstream>
#include <random>

#include "HelperFunctions.hpp"
#include "BloomFilterTree.hpp"


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
    vector<int> rand_index(NUM_ELEMENTS);
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
        f14.add(words[rand_index[i]]);
    }
    for (auto i=0; i<rand_index.size(); i++) {
        rand_index[i] = randomNumber();
        f15.add(words[rand_index[i]]);
    }
    for (auto i=0; i<rand_index.size(); i++) {
        rand_index[i] = randomNumber();
        f16.add(words[rand_index[i]]);
    }
    for (auto i=0; i<rand_index.size(); i++) {
        rand_index[i] = randomNumber();
        f17.add(words[rand_index[i]]);
    }
    for (auto i=0; i<rand_index.size(); i++) {
        rand_index[i] = randomNumber();
        f18.add(words[rand_index[i]]);
    }
    for (auto i=0; i<rand_index.size(); i++) {
        rand_index[i] = randomNumber();
        f19.add(words[rand_index[i]]);
    }
    for (auto i=0; i<rand_index.size(); i++) {
        rand_index[i] = randomNumber();
        f20.add(words[rand_index[i]]);
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
    
    // Compute optimal results and reference values
    vector<pair<int, double>> res1 = b1.computekDistances(&f1, NUM_FILTERS);
    vector<pair<int, double>> res2 = b1.computekDistances(&f2, NUM_FILTERS);
    vector<pair<int, double>> res3 = b1.computekDistances(&f3, NUM_FILTERS);
    vector<pair<int, double>> res4 = b1.computekDistances(&f4, NUM_FILTERS);
    vector<pair<int, double>> res5 = b1.computekDistances(&f5, NUM_FILTERS);
    vector<pair<int, double>> res6 = b1.computekDistances(&f6, NUM_FILTERS);
    vector<pair<int, double>> res7 = b1.computekDistances(&f7, NUM_FILTERS);
    vector<pair<int, double>> res8 = b1.computekDistances(&f8, NUM_FILTERS);
    vector<pair<int, double>> res9 = b1.computekDistances(&f9, NUM_FILTERS);
    vector<pair<int, double>> res10 = b1.computekDistances(&f10, NUM_FILTERS);
    vector<pair<int, double>> res11 = b2.computekDistances(&f11, NUM_FILTERS);
    vector<pair<int, double>> res12 = b2.computekDistances(&f12, NUM_FILTERS);
    vector<pair<int, double>> res13 = b2.computekDistances(&f13, NUM_FILTERS);
    vector<pair<int, double>> res14 = b2.computekDistances(&f14, NUM_FILTERS);
    vector<pair<int, double>> res15 = b2.computekDistances(&f15, NUM_FILTERS);
    vector<pair<int, double>> res16 = b2.computekDistances(&f16, NUM_FILTERS);
    vector<pair<int, double>> res17 = b2.computekDistances(&f17, NUM_FILTERS);
    vector<pair<int, double>> res18 = b2.computekDistances(&f18, NUM_FILTERS);
    vector<pair<int, double>> res19 = b2.computekDistances(&f19, NUM_FILTERS);
    vector<pair<int, double>> res20 = b2.computekDistances(&f20, NUM_FILTERS);
    
    // Create output csv files
    ofstream nn_256;
    ofstream nn3_256;
    ofstream nn_512;
    ofstream nn3_512;
    
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
    BloomFilter *r11 = b1.simQuery(&f11);
    BloomFilter *r12 = b1.simQuery(&f12);
    BloomFilter *r13 = b1.simQuery(&f13);
    BloomFilter *r14 = b1.simQuery(&f14);
    BloomFilter *r15 = b1.simQuery(&f15);
    BloomFilter *r16 = b1.simQuery(&f16);
    BloomFilter *r17 = b1.simQuery(&f17);
    BloomFilter *r18 = b1.simQuery(&f18);
    BloomFilter *r19 = b1.simQuery(&f19);
    BloomFilter *r20 = b1.simQuery(&f20);
    vector<BloomFilter*> rA = b1.simQueryVec(&f1, 3);
    vector<BloomFilter*> rB = b1.simQueryVec(&f2, 3);
    vector<BloomFilter*> rC = b1.simQueryVec(&f3, 3);
    vector<BloomFilter*> rD = b1.simQueryVec(&f4, 3);
    vector<BloomFilter*> rE = b1.simQueryVec(&f5, 3);
    vector<BloomFilter*> rF = b1.simQueryVec(&f6, 3);
    vector<BloomFilter*> rG = b1.simQueryVec(&f7, 3);
    vector<BloomFilter*> rH = b1.simQueryVec(&f8, 3);
    vector<BloomFilter*> rI = b1.simQueryVec(&f9, 3);
    vector<BloomFilter*> rJ = b1.simQueryVec(&f10, 3);
    vector<BloomFilter*> rK = b1.simQueryVec(&f11, 3);
    vector<BloomFilter*> rL = b1.simQueryVec(&f12, 3);
    vector<BloomFilter*> rM = b1.simQueryVec(&f13, 3);
    vector<BloomFilter*> rN = b1.simQueryVec(&f14, 3);
    vector<BloomFilter*> rO = b1.simQueryVec(&f15, 3);
    vector<BloomFilter*> rP = b1.simQueryVec(&f16, 3);
    vector<BloomFilter*> rQ = b1.simQueryVec(&f17, 3);
    vector<BloomFilter*> rR = b1.simQueryVec(&f18, 3);
    vector<BloomFilter*> rS = b1.simQueryVec(&f19, 3);
    vector<BloomFilter*> rT = b1.simQueryVec(&f20, 3);
    
    // Write results
    cout << "EXPERIMENT SETTINGS\n";
    cout << "-------------------\n";
    cout << "\nFilters: " << NUM_FILTERS;
    cout << "\nElements: " << NUM_ELEMENTS;
    cout << "\nFilter size: " << v1[0].getSize();
    cout << "\nHash functions: " << v1[0].getNumHashes();
    cout << "\nQuery filters: " << NUM_QUERYFILTERS;
    cout << "\nRun 1: NN query\nRun 2: 3NN query\n";
    
    // Quality of result (NN, 256)
    nn_256.open("nn_256.csv");
    nn_256 << "QFNN256,OptimalNN256,ComputedNN256,MaxNN256\n";
    nn_256 << "1," << res1[0].second << "," << f1.computeJaccard(r1) << "," << res1[NUM_FILTERS-1].second << "\n";
    nn_256 << "2," << res2[0].second << "," << f2.computeJaccard(r2) << "," << res2[NUM_FILTERS-1].second << "\n";
    nn_256 << "3," << res3[0].second << "," << f3.computeJaccard(r3) << "," << res3[NUM_FILTERS-1].second << "\n";
    nn_256 << "4," << res4[0].second << "," << f4.computeJaccard(r4) << "," << res4[NUM_FILTERS-1].second << "\n";
    nn_256 << "5," << res5[0].second << "," << f5.computeJaccard(r5) << "," << res5[NUM_FILTERS-1].second << "\n";
    nn_256 << "6," << res6[0].second << "," << f6.computeJaccard(r6) << "," << res6[NUM_FILTERS-1].second << "\n";
    nn_256 << "7," << res7[0].second << "," << f7.computeJaccard(r7) << "," << res7[NUM_FILTERS-1].second << "\n";
    nn_256 << "8," << res8[0].second << "," << f8.computeJaccard(r8) << "," << res8[NUM_FILTERS-1].second << "\n";
    nn_256 << "9," << res9[0].second << "," << f9.computeJaccard(r9) << "," << res9[NUM_FILTERS-1].second << "\n";
    nn_256 << "10," << res10[0].second << "," << f10.computeJaccard(r10) << "," << res10[NUM_FILTERS-1].second << "\n";
    nn_256.close();
    
    // Quality of result (3NN, 256)
    nn3_256.open("nn3_256.csv");
    nn3_256 << "QF3NN256,Optimal3NN256,Computed3NN256,Max3NN256\n";
    nn3_256 << "1," << res1[0].second << "," << f1.computeJaccard(rA[0]) << "," << res1[NUM_FILTERS-1].second << "\n";
    nn3_256 << "1," << res1[1].second << "," << f1.computeJaccard(rA[1]) << "," << res1[NUM_FILTERS-2].second << "\n";
    nn3_256 << "1," << res1[2].second << "," << f1.computeJaccard(rA[2]) << "," << res1[NUM_FILTERS-3].second << "\n";
    nn3_256 << "2," << res2[0].second << "," << f2.computeJaccard(rB[0]) << "," << res2[NUM_FILTERS-1].second << "\n";
    nn3_256 << "2," << res2[1].second << "," << f2.computeJaccard(rB[1]) << "," << res2[NUM_FILTERS-2].second << "\n";
    nn3_256 << "2," << res2[2].second << "," << f2.computeJaccard(rB[2]) << "," << res2[NUM_FILTERS-3].second << "\n";
    nn3_256 << "3," << res3[0].second << "," << f3.computeJaccard(rC[0]) << "," << res3[NUM_FILTERS-1].second << "\n";
    nn3_256 << "3," << res3[1].second << "," << f3.computeJaccard(rC[1]) << "," << res3[NUM_FILTERS-2].second << "\n";
    nn3_256 << "3," << res3[2].second << "," << f3.computeJaccard(rC[2]) << "," << res3[NUM_FILTERS-3].second << "\n";
    nn3_256 << "4," << res4[0].second << "," << f4.computeJaccard(rD[0]) << "," << res4[NUM_FILTERS-1].second << "\n";
    nn3_256 << "4," << res4[1].second << "," << f4.computeJaccard(rD[1]) << "," << res4[NUM_FILTERS-2].second << "\n";
    nn3_256 << "4," << res4[2].second << "," << f4.computeJaccard(rD[2]) << "," << res4[NUM_FILTERS-3].second << "\n";
    nn3_256 << "5," << res5[0].second << "," << f5.computeJaccard(rE[0]) << "," << res5[NUM_FILTERS-1].second << "\n";
    nn3_256 << "5," << res5[1].second << "," << f5.computeJaccard(rE[1]) << "," << res5[NUM_FILTERS-2].second << "\n";
    nn3_256 << "5," << res5[2].second << "," << f5.computeJaccard(rE[2]) << "," << res5[NUM_FILTERS-3].second << "\n";
    nn3_256 << "6," << res6[0].second << "," << f6.computeJaccard(rF[0]) << "," << res6[NUM_FILTERS-1].second << "\n";
    nn3_256 << "6," << res6[1].second << "," << f6.computeJaccard(rF[1]) << "," << res6[NUM_FILTERS-2].second << "\n";
    nn3_256 << "6," << res6[2].second << "," << f6.computeJaccard(rF[2]) << "," << res6[NUM_FILTERS-3].second << "\n";
    nn3_256 << "7," << res7[0].second << "," << f7.computeJaccard(rG[0]) << "," << res7[NUM_FILTERS-1].second << "\n";
    nn3_256 << "7," << res7[1].second << "," << f7.computeJaccard(rG[1]) << "," << res7[NUM_FILTERS-2].second << "\n";
    nn3_256 << "7," << res7[2].second << "," << f7.computeJaccard(rG[2]) << "," << res7[NUM_FILTERS-3].second << "\n";
    nn3_256 << "8," << res8[0].second << "," << f8.computeJaccard(rH[0]) << "," << res8[NUM_FILTERS-1].second << "\n";
    nn3_256 << "8," << res8[1].second << "," << f8.computeJaccard(rH[1]) << "," << res8[NUM_FILTERS-2].second << "\n";
    nn3_256 << "8," << res8[2].second << "," << f8.computeJaccard(rH[2]) << "," << res8[NUM_FILTERS-3].second << "\n";
    nn3_256 << "9," << res9[0].second << "," << f9.computeJaccard(rI[0]) << "," << res9[NUM_FILTERS-1].second << "\n";
    nn3_256 << "9," << res9[1].second << "," << f9.computeJaccard(rI[1]) << "," << res9[NUM_FILTERS-2].second << "\n";
    nn3_256 << "9," << res9[2].second << "," << f9.computeJaccard(rI[2]) << "," << res9[NUM_FILTERS-3].second << "\n";
    nn3_256 << "10," << res10[0].second << "," << f10.computeJaccard(rJ[0]) << "," << res10[NUM_FILTERS-1].second << "\n";
    nn3_256 << "10," << res10[1].second << "," << f10.computeJaccard(rJ[1]) << "," << res10[NUM_FILTERS-2].second << "\n";
    nn3_256 << "10," << res10[2].second << "," << f10.computeJaccard(rJ[2]) << "," << res10[NUM_FILTERS-3].second << "\n";
    nn3_256.close();
    
    cout << "\nFilters: " << NUM_FILTERS;
    cout << "\nElements: " << NUM_ELEMENTS;
    cout << "\nFilter size: " << v2[0].getSize();
    cout << "\nHash functions: " << v2[0].getNumHashes();
    cout << "\nQuery filters: " << NUM_QUERYFILTERS;
    cout << "\nRun 1: NN query\nRun 2: 3NN query\n";
    
    // Quality of result (NN, 512)
    nn_512.open("nn_512.csv");
    nn_512 << "QFNN512,OptimalNN512,ComputedNN512,MaxNN512\n";
    nn_512 << "11," << res11[0].second << "," << f11.computeJaccard(r11) << "," << res11[NUM_FILTERS-1].second << "\n";
    nn_512 << "12," << res12[0].second << "," << f12.computeJaccard(r12) << "," << res12[NUM_FILTERS-1].second << "\n";
    nn_512 << "13," << res13[0].second << "," << f13.computeJaccard(r13) << "," << res13[NUM_FILTERS-1].second << "\n";
    nn_512 << "14," << res14[0].second << "," << f14.computeJaccard(r14) << "," << res14[NUM_FILTERS-1].second << "\n";
    nn_512 << "15," << res15[0].second << "," << f15.computeJaccard(r15) << "," << res15[NUM_FILTERS-1].second << "\n";
    nn_512 << "16," << res16[0].second << "," << f16.computeJaccard(r16) << "," << res16[NUM_FILTERS-1].second << "\n";
    nn_512 << "17," << res17[0].second << "," << f17.computeJaccard(r17) << "," << res17[NUM_FILTERS-1].second << "\n";
    nn_512 << "18," << res18[0].second << "," << f18.computeJaccard(r18) << "," << res18[NUM_FILTERS-1].second << "\n";
    nn_512 << "19," << res19[0].second << "," << f19.computeJaccard(r19) << "," << res19[NUM_FILTERS-1].second << "\n";
    nn_512 << "20," << res20[0].second << "," << f20.computeJaccard(r20) << "," << res20[NUM_FILTERS-1].second << "\n";
    nn_512.close();
    
    // Quality of result (3NN, 512)
    nn3_512.open("nn3_512.csv");
    nn3_512 << "QF3NN512,Optimal3NN512,Computed3NN512,Max3NN512\n";
    nn3_512 << "11," << res11[0].second << "," << f11.computeJaccard(rK[0]) << "," << res11[NUM_FILTERS-1].second << "\n";
    nn3_512 << "11," << res11[1].second << "," << f11.computeJaccard(rK[1]) << "," << res11[NUM_FILTERS-2].second << "\n";
    nn3_512 << "11," << res11[2].second << "," << f11.computeJaccard(rK[2]) << "," << res11[NUM_FILTERS-3].second << "\n";
    nn3_512 << "12," << res12[0].second << "," << f12.computeJaccard(rL[0]) << "," << res12[NUM_FILTERS-1].second << "\n";
    nn3_512 << "12," << res12[1].second << "," << f12.computeJaccard(rL[1]) << "," << res12[NUM_FILTERS-2].second << "\n";
    nn3_512 << "12," << res12[2].second << "," << f12.computeJaccard(rL[2]) << "," << res12[NUM_FILTERS-3].second << "\n";
    nn3_512 << "13," << res13[0].second << "," << f13.computeJaccard(rM[0]) << "," << res13[NUM_FILTERS-1].second << "\n";
    nn3_512 << "13," << res13[1].second << "," << f13.computeJaccard(rM[1]) << "," << res13[NUM_FILTERS-2].second << "\n";
    nn3_512 << "13," << res13[2].second << "," << f13.computeJaccard(rM[2]) << "," << res13[NUM_FILTERS-3].second << "\n";
    nn3_512 << "14," << res14[0].second << "," << f14.computeJaccard(rN[0]) << "," << res14[NUM_FILTERS-1].second << "\n";
    nn3_512 << "14," << res14[1].second << "," << f14.computeJaccard(rN[1]) << "," << res14[NUM_FILTERS-2].second << "\n";
    nn3_512 << "14," << res14[2].second << "," << f14.computeJaccard(rN[2]) << "," << res14[NUM_FILTERS-3].second << "\n";
    nn3_512 << "15," << res15[0].second << "," << f15.computeJaccard(rO[0]) << "," << res15[NUM_FILTERS-1].second << "\n";
    nn3_512 << "15," << res15[1].second << "," << f15.computeJaccard(rO[1]) << "," << res15[NUM_FILTERS-2].second << "\n";
    nn3_512 << "15," << res15[2].second << "," << f15.computeJaccard(rO[2]) << "," << res15[NUM_FILTERS-3].second << "\n";
    nn3_512 << "16," << res16[0].second << "," << f16.computeJaccard(rP[0]) << "," << res16[NUM_FILTERS-1].second << "\n";
    nn3_512 << "16," << res16[1].second << "," << f16.computeJaccard(rP[1]) << "," << res16[NUM_FILTERS-2].second << "\n";
    nn3_512 << "16," << res16[2].second << "," << f16.computeJaccard(rP[2]) << "," << res16[NUM_FILTERS-3].second << "\n";
    nn3_512 << "17," << res17[0].second << "," << f17.computeJaccard(rQ[0]) << "," << res17[NUM_FILTERS-1].second << "\n";
    nn3_512 << "17," << res17[1].second << "," << f17.computeJaccard(rQ[1]) << "," << res17[NUM_FILTERS-2].second << "\n";
    nn3_512 << "17," << res17[2].second << "," << f17.computeJaccard(rQ[2]) << "," << res17[NUM_FILTERS-3].second << "\n";
    nn3_512 << "18," << res18[0].second << "," << f18.computeJaccard(rR[0]) << "," << res18[NUM_FILTERS-1].second << "\n";
    nn3_512 << "18," << res18[1].second << "," << f18.computeJaccard(rR[1]) << "," << res18[NUM_FILTERS-2].second << "\n";
    nn3_512 << "18," << res18[2].second << "," << f18.computeJaccard(rR[2]) << "," << res18[NUM_FILTERS-3].second << "\n";
    nn3_512 << "19," << res19[0].second << "," << f19.computeJaccard(rS[0]) << "," << res19[NUM_FILTERS-1].second << "\n";
    nn3_512 << "19," << res19[1].second << "," << f19.computeJaccard(rS[1]) << "," << res19[NUM_FILTERS-2].second << "\n";
    nn3_512 << "19," << res19[2].second << "," << f19.computeJaccard(rS[2]) << "," << res19[NUM_FILTERS-3].second << "\n";
    nn3_512 << "20," << res20[0].second << "," << f20.computeJaccard(rT[0]) << "," << res20[NUM_FILTERS-1].second << "\n";
    nn3_512 << "20," << res20[1].second << "," << f20.computeJaccard(rT[1]) << "," << res20[NUM_FILTERS-2].second << "\n";
    nn3_512 << "20," << res20[2].second << "," << f20.computeJaccard(rT[2]) << "," << res20[NUM_FILTERS-3].second << "\n";
    nn3_512.close();
    cout << endl;
    return 0;
}