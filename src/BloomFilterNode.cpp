//  BloomFilterNode.cpp, Judith Greif
//  Description: Implementation of class BloomFilterNode

#include "BloomFilterNode.hpp"


// Constructor with parameters t and leaf
BloomFilterNode::BloomFilterNode(int _t, bool _leaf): t(_t), leaf(_leaf) {
    
    // Allocate memory for maximum # of possible keys, child pointers and data of physical nodes
    // Set maximum # of keys to # of Bloom filters, i.e. m (default)
    keys = new int[m];
    C = new BloomFilterNode *[2*t];
    filtersArr = new int[m];
    
    // Initialize # of keys as 0
    n=0;
}

// Constructor with parameters t, leaf, # of Bloom filters
BloomFilterNode::BloomFilterNode(int _t, bool _leaf, int _count) {
    
    // Allocate memory for maximum # of possible keys, child pointers and data of physical nodes
    // Set maximum # of keys to # of Bloom filters
    keys = new int[_count];
    C = new BloomFilterNode *[2*t];
    filtersArr = new int[m];
    
    // Initialize # of keys as 0
    n=0;
}

BloomFilterNode::~BloomFilterNode() {
    delete[] keys;
    for (int i=0; i<2*t; i++) {
        delete C[i];
    }
    delete[] C;
    delete[] filtersArr; 
}