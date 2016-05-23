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


using namespace std;


class BloomFilterTree {
    
private:
    int t;                      // Order = minimum degree
    int filtersize;             // Size of associated Bloom filters (# of bits)
    BloomFilterVec *filtersvec; // Associated Bloom filter vector
    
public:
    BloomFilterNode *root;      // Pointer to root node
    
    // Constructor with parameters t and size
    // Initializes tree as empty
    BloomFilterTree(int _t, int _s);

    ~BloomFilterTree();
    
    // TODO
    // Constructor with parameters t, size, *filtersvec
    // Insert all filters from Bloom filter vector as BloomFilterNode instances in BloomFilterTree
    BloomFilterTree(int _t, int _s, BloomFilterVec *_f);
    
    // Search key in tree
    // Return false if key is not present
    bool contains(int k);
    
    BloomFilterNode *search(int k);
    BloomFilterNode *getRoot();
    BloomFilterVec *getFiltersVec();
    void traverse();
    void traverseFilters();
    float computeMaxJaccard(BloomFilter *filter);
    int computeMaxJaccardKey(BloomFilter *filter);
    int getMinKey();
    int getMaxKey(); 
    int computeSimilarityId(BloomFilter *filter);
    
    // Insertion methods
    void insert(BloomFilter *filter);
};

#endif
