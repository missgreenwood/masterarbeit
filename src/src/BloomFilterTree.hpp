//  bloom_filter_tree.hpp, Judith Greif
//  Description: Header for classes BloomFilterNode, BloomFilterTree

#ifndef BloomFilterTree_hpp
#define BloomFilterTree_hpp

#include <iostream>
#include "BloomFilterNode.hpp"

using namespace std;


// BloomFilterNode - Bloom filter in a B-Tree
// Differences from normal B-Tree:
//  * Only logical nodes
//  * The leaves hold the IDs of all physical nodes -> each internal key is also stored in leaf
//  * Leaves have pointers to physical nodes


// BloomFilterTree
class BloomFilterTree {
    
private:
    BloomFilterNode *root;      // Pointer to root node
    int t;                      // Minimum degree
    BloomFilterVec *filtersvec; // Associated Bloom filter vector
    
public:
    // Constructor with parameter t
    // Initializes tree as empty
    BloomFilterTree(int _t): t(_t), root(NULL) {};
    
    // TODO: Constructor with parameters t and *filtersvec
    // Insert all filters from Bloom filter vector as BloomFilterNode instances in BloomFilterTree
    
    // Traverse tree
    void traverse();
    
    // Search key in tree
    // Return NULL if key is not present
    BloomFilterNode *search(int k);
    
    // Insert new Bloom filter
    void insert(BloomFilter *filter); // TODO: Create physical node for inserted key and link to logical node
    
    // Remove key
    void remove(int k);
 
    friend class BloomFilterNode;
};

#endif
