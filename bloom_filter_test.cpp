// bloom_filter_test.cpp, Judith Greif
// Description: Test driver for Bloom filter library (bloom_filter.hpp)

#include <iostream>
#include <string>
#include <cstddef>
#include <cstdio>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <deque>
#include <set>
#include <cstdlib>

#include "bloom_filter.hpp"

using namespace std;

/* int main(int argc, const char *argv[]) {
    
    bloom_parameters parameters;
    
    // How many elements per Bloom filter do we expect to insert?
    parameters.projected_element_count = 50;
    
    // Maximum tolerable false positive probability? [0,1]
    parameters.false_positive_probability = 0.0001; // 1 in 10000
    
    // Simple randomizer (optional)
    // parameters.random_seed = 0xA5A5A5A5;
    
    if (!parameters) {
        cout << "Error - Invalid set of bloom filter parameters!" << endl;
        return 1;
    }
    
    // parameters.compute_optimal_parameters();
    
    // Instantiate test Bloom filter
    bloom_filter filter(parameters);
    
    string str_list[] = {"AbC", "iJk", "XYZ"};
    
    // Insert some strings into Bloom filter
    for (size_t i=0; i < (sizeof(str_list)/sizeof(string)); i++) {
        filter.insert(str_list[i]);
    }
    
    // Query Bloom filter for existence of strings
    for (size_t i=0; i < (sizeof(str_list)/sizeof(string)); i++) {
        if (filter.contains(str_list[i])) {
            cout << "BF contains: " << str_list[i] << endl;
        }
    }
    
    // Generate 100 unique instances of Bloom filter
    
    // The address of a message is defined to be a small set of strings represented as a Bloom filter of previuosly known configuration
    // Use subset and similarity queries to select messages
    
    return 0; 
} */