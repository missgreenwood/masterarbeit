//  BloomFilterNode.hpp, Judith Greif
//  Description: Header for class BloomFilterNode

#ifndef BloomFilterNode_hpp
#define BloomFilterNode_hpp

#include <iostream>
#include "BloomFilterVec.hpp"

class BloomFilterNode {
    
private:
    int *keys;              // Array of keys
    int t;                  // Minimum degree
    BloomFilterNode **C;    // Array of child pointers
    int n;                  // Current # of keys
    bool leaf;
    int *filtersArr;        // The associated data of this logical node (physical nodes)
    
public:
    
    // Constructor with parameters t and leaf
    BloomFilterNode(int _t, bool _leaf): t(_t), leaf(_leaf) {
        
        // Allocate memory for maximum # of possible keys, child pointers and data of physical nodes
        // Set maximum # of keys to # of Bloom filters, i.e. m (default)
        keys = new int[m];
        C = new BloomFilterNode *[2*t];
        filtersArr = new int[m];
        
        // Initialize # of keys as 0
        n=0;
    }
    
    // Constructor with parameters t, leaf, # of Bloom filters
    BloomFilterNode(int _t, bool _leaf, int _count) {
        
        // Allocate memory for maximum # of possible keys, child pointers and data of physical nodes
        // Set maximum # of keys to # of Bloom filters
        keys = new int[_count];
        C = new BloomFilterNode *[2*t];
        filtersArr = new int[m];
        
        // Initialize # of keys as 0
        n=0;
    }
    
    // Function to traverse all nodes in a subtree rooted with this node
    // Print only keys present in leaf nodes
    void traverse();
    
    // Search key in a subtree rooted with this node
    // Return NULL if key is not present
    // Return first occurence if key is present
    BloomFilterNode *search(int k);
    
    friend class BloomFilterTree;
};

#endif 
