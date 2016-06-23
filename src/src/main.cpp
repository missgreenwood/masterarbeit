//  main.cpp, Judith Greif
//  Description: Main executable for Bloom filter data structures

#include <iostream>
#include <fstream>
#include <random>
#include <chrono>
#include "HelperFunctions.hpp"
#include "BloomFilterTree.hpp"

using namespace std;
using namespace std::chrono;


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
    
    // Create test filter vector (random ids, size 256)
    // Insert 50 random elements from dictionary into each
    vector<BloomFilter> q256;
    for (int i=0; i<NUM_QUERYFILTERS; i++) {
        filter = new BloomFilter(rand(), 256);
        vector<int> rand_index(NUM_ELEMENTS);
        for (auto i=0; i<rand_index.size(); i++) {
            rand_index[i] = randomNumber();
            filter->add(words[rand_index[i]]);
        }
        q256.push_back(*filter);
    }
    
    // Create test filter vector (random ids, size 512)
    // Insert 50 random elements from dictionary into each
    vector<BloomFilter> q512;
    for (int i=0; i<NUM_QUERYFILTERS; i++) {
        filter = new BloomFilter(rand(), 512);
        vector<int> rand_index(NUM_ELEMENTS);
        for (auto i=0; i<rand_index.size(); i++) {
            rand_index[i] = randomNumber();
            filter->add(words[rand_index[i]]);
        }
        q512.push_back(*filter);
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
    
    // Compute reference values
    vector<vector<pair<int,double>>> ref256;
    for (int i=0; i<NUM_QUERYFILTERS; i++) {
        vector<pair<int, double>> tmp = b1.computekDistances(&q256[i], NUM_FILTERS);
        ref256.push_back(tmp);
    }
    
    vector<vector<pair<int, double>>> ref512;
    for (int i=0; i<NUM_QUERYFILTERS; i++) {
        vector<pair<int, double>> tmp = b2.computekDistances(&q512[i], NUM_FILTERS);
        ref512.push_back(tmp);
    }
    
    // Create output csv files
    ofstream nn_256;
    ofstream nn3_256;
    ofstream nn_512;
    ofstream nn3_512;
    ofstream cputime_nn_256;
    ofstream cputime_nn_512;
    ofstream cputime_nn3_256;
    ofstream cputime_nn3_512;
    ofstream mem;
    
    // Memory measurement of BloomFilterTree vs. unsorted list (std::vector)
    mem.open("mem.csv");
    mem << "Filtergröße 256,Filtergröße 512\n";
    mem << b1.compareMem()[0] << "," << b2.compareMem()[0] << "\n";
    mem << b1.compareMem()[1] << "," << b2.compareMem()[1] << "\n";
    mem.close();
    
    // Create result vectors
    vector<BloomFilter*> res_nn_256;
    vector<BloomFilter*> res_nn_512;
    vector<vector<BloomFilter*>> res_nn3_256;
    vector<vector<BloomFilter*>> res_nn3_512;
    
    // Set search queries
    // Incl. cpu time measurement, comparison with unsorted list and result writing
    cputime_nn_256.open("cputime_nn_256.csv");
    cputime_nn_256 << "QFNN256,CPUTimeBFTree,CPUTimeUList\n";
    for (int i=0; i<NUM_QUERYFILTERS; i++) {
        high_resolution_clock::time_point t1 = high_resolution_clock::now();
        filter = b1.simQuery(&q256[i]);
        high_resolution_clock::time_point t2 = high_resolution_clock::now();
        b1.getMinJaccardFilter(&q256[i]);
        high_resolution_clock::time_point t3 = high_resolution_clock::now();
        auto durationTree = duration_cast<microseconds>(t2-t1).count();
        auto durationList = duration_cast<microseconds>(t3-t2).count();
        cputime_nn_256 << i << "," << durationTree << "," << durationList << "\n";
        res_nn_256.push_back(filter);
    }
    cputime_nn_256.close();
    
    cputime_nn_512.open("cputime_nn_512.csv");
    cputime_nn_512 << "QFNN512,CPUTimeBFTree,CPUTimeUList\n";
    for (int i=0; i<NUM_QUERYFILTERS; i++) {
        high_resolution_clock::time_point t1 = high_resolution_clock::now();
        filter = b2.simQuery(&q512[i]);
        high_resolution_clock::time_point t2 = high_resolution_clock::now();
        b2.getMinJaccardFilter(&q512[i]);
        high_resolution_clock::time_point t3 = high_resolution_clock::now();
        auto durationTree = duration_cast<microseconds>(t2-t1).count();
        auto durationList = duration_cast<microseconds>(t3-t2).count();
        cputime_nn_512 << i << "," << durationTree << "," << durationList << "\n";
        res_nn_512.push_back(filter);
    }
    cputime_nn_512.close();
    
    cputime_nn3_256.open("cputime_nn3_256.csv");
    cputime_nn3_256 << "QF3NN256,CPUTimeBFTree,CPUTimeUList\n";
    vector<BloomFilter*> refvec;
    for (int i=0; i<NUM_QUERYFILTERS; i++) {
        high_resolution_clock::time_point t1 = high_resolution_clock::now();
        refvec = b1.simQueryVec(&q256[i], 3);
        high_resolution_clock::time_point t2 = high_resolution_clock::now();
        b1.compare(&q256[i], 3);
        high_resolution_clock::time_point t3 = high_resolution_clock::now();
        auto durationTree = duration_cast<microseconds>(t2-t1).count();
        auto durationList = duration_cast<microseconds>(t3-t2).count();
        cputime_nn3_256 << i << "," << durationTree << "," << durationList << "\n";
        res_nn3_256.push_back(refvec);
    }
    cputime_nn3_256.close();
    
    cputime_nn3_512.open("cputime_nn3_512.csv");
    cputime_nn3_512 << "QF3NN512,CPUTimeBFTree, CPUTimeUList\n";
    for (int i=0; i<NUM_QUERYFILTERS; i++) {
        high_resolution_clock::time_point t1 = high_resolution_clock::now();
        refvec = b2.simQueryVec(&q512[i], 3);
        high_resolution_clock::time_point t2 = high_resolution_clock::now();
        b2.compare(&q512[i], 3);
        high_resolution_clock::time_point t3 = high_resolution_clock::now();
        auto durationTree = duration_cast<microseconds>(t2-t1).count();
        auto durationList = duration_cast<microseconds>(t3-t2).count();
        cputime_nn3_512 << i << "," << durationTree << "," << durationList << "\n";
        res_nn3_512.push_back(refvec);
    }
    cputime_nn3_512.close();
    
    // Display experiment settings
    cout << "EXPERIMENT SETTINGS\n";
    cout << "-------------------\n";
    cout << "\nFilters: " << NUM_FILTERS;
    cout << "\nElements: " << NUM_ELEMENTS;
    cout << "\nFilter size: " << v1[0].getSize();
    cout << "\nHash functions: " << v1[0].getNumHashes();
    cout << "\nQuery filters: " << NUM_QUERYFILTERS;
    cout << "\nTests:\n";
    cout << "1. Quality of result (NN query/3NN query)\n";
    cout << "2. CPU time for NN query/3NN query (BloomFilterTree vs. unsorted list)\n";
    cout << "3. Memory consumption of data structures (BloomFilterTree vs. unsorted list)\n";
    cout << "4. Complexity of NN query/NN3 query (BloomFilterTree vs. unsorted list)\n";
    
    cout << "\nFilters: " << NUM_FILTERS;
    cout << "\nElements: " << NUM_ELEMENTS;
    cout << "\nFilter size: " << v2[0].getSize();
    cout << "\nHash functions: " << v2[0].getNumHashes();
    cout << "\nQuery filters: " << NUM_QUERYFILTERS;
    cout << "\nTests:\n";
    cout << "1. Quality of result (NN query/3NN query)\n";
    cout << "2. CPU time for NN query/3NN query (BloomFilterTree vs. unsorted list)\n";
    cout << "3. Memory consumption of data structures (BloomFilterTree vs. unsorted list)\n";
    cout << "4. Complexity of NN query/NN3 query (BloomFilterTree vs. unsorted list)\n";
    
    // Write results
    // Quality of result (NN, 256)
    nn_256.open("nn_256.csv");
    nn_256 << "QFNN256,OptimalNN256,ComputedNN256,MaxNN256\n";
    for (int i=0; i<NUM_QUERYFILTERS; i++) {
        vector<pair<int, double>> refvec = ref256[i];
        nn_256 << i << "," << refvec[0].second << "," << q256[i].computeJaccard(res_nn_256[i]) << "," << refvec[NUM_FILTERS-1].second << "\n";
    }
    nn_256.close();
    
    // Quality of result (3NN, 256)
    nn3_256.open("nn3_256.csv");
    nn3_256 << "QF3NN256,Optimal1NN256,Optimal2NN256,Optimal3NN256,Computed1NN256,Computed2NN256,Computed3NN256,Max3NN256\n";
    for (int i=0; i<NUM_QUERYFILTERS; i++) {
        vector<pair<int, double>> refvec = ref256[i];
        nn3_256 << i << "," << refvec[0].second << "," << refvec[1].second << "," << refvec[2].second << "," << q256[i].computeJaccard(res_nn3_256[i][0]) << "," << q256[i].computeJaccard(res_nn3_256[i][1]) << "," << q256[i].computeJaccard(res_nn3_256[i][2]) << "," << refvec[NUM_FILTERS-1].second << "\n";
     }
    nn3_256.close();
    
    // Quality of result (NN, 512)
    nn_512.open("nn_512.csv");
    nn_512 << "QFNN512,OptimalNN512,ComputedNN512,MaxNN512\n";
    for (int i=0; i<NUM_QUERYFILTERS; i++) {
        vector<pair<int, double>> refvec = ref512[i];
        nn_512 << i << "," << refvec[0].second << "," << q512[i].computeJaccard(res_nn_512[i]) << ","<< refvec[NUM_FILTERS-1].second << "\n";
     }
    nn_512.close();
    
    // Quality of result (3NN, 512)
    nn3_512.open("nn3_512.csv");
    nn3_512 << "QF3NN512,Optimal1NN512,Optimal2NN512,Optimal3NN512,Computed1NN512,Computed2NN512,Computed3NN512,Max3NN512\n";
    for (int i=0; i<NUM_QUERYFILTERS; i++) {
        vector<pair<int, double>> refvec = ref512[i];
        nn3_512 << i << "," << refvec[0].second << "," << refvec[1].second << "," << refvec[2].second << "," << q512[i].computeJaccard(res_nn3_512[i][0]) << "," << q512[i].computeJaccard(res_nn3_512[i][1]) << "," << q512[i].computeJaccard(res_nn3_512[i][2]) << "," << refvec[NUM_FILTERS-1].second << "\n";
    }
    nn3_512.close();
    cout << endl;
    return 0;
}