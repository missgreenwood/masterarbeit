//  bloom_filter_tree.hpp, Judith Greif
//  Description: Header for class BloomFilterTree

//  Properties (same as B+Tree):
//  * All leaves at same level
//  * Defined by minimum degree t
//  * Every node has at least 2t keys
//  * Every node has keys+1 children
//  * Keys are sorted in increasing order
//  * Grows from root
//  * Child between keys k1 and k2 contains all keys >= k1 and < k2
//  * All keys are also stored in leaves

//  Properties (different from B+Tree):
//  * Bloom filters are data sets
//  * Each has pointers to n data sets
//  * No remove function


#ifndef BloomFilterTree_hpp
#define BloomFilterTree_hpp

#include "BloomFilterNode.hpp"
#include "BloomFilterIndexNode.hpp"
#include "BloomFilterLeaf.hpp"
#include "BloomFilterVec.hpp"


using namespace std;


class BloomFilterTree {
    
private:
    BloomFilterNode *root;      // Pointer to root node
    int t;                      // Order = minimum degree
    BloomFilterVec *filtersvec; // Associated Bloom filter vector
    
public:
    // Constructor with parameter t
    // Initializes tree as empty
    BloomFilterTree(int _t);
    
    // TODO
    // Constructor with parameters t and *filtersvec
    // Insert all filters from Bloom filter vector as BloomFilterNode instances in BloomFilterTree
    BloomFilterTree(int _t, BloomFilterVec *_f);
    
    ~BloomFilterTree();
    
    // TODO 
    void traverse();
    
    // TODO
    // Return leaf node to place k in
    BloomFilterNode *search(int k);
    
    // TODO
    // Insert new Bloom filter
    void insert(BloomFilter *filter);
    
    // TODO
    // Search key in tree
    // Return false if key is not present
    
    friend class BloomFilterNode;
    friend class BloomFilterIndexNode;
    friend class BloomFilterLeaf;
};

#endif
