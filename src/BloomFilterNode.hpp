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
    BloomFilterNode(int _t, bool _leaf);
    BloomFilterNode(int _t, bool _leaf, int _count);
    ~BloomFilterNode(); 
    
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
