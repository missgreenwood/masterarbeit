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

#include <algorithm>
#include "BloomFilterNode.hpp"
#include "BloomFilterIndexNode.hpp"
#include "BloomFilterLeaf.hpp"


using namespace std;


class BloomFilterTree {
    
private:
    int t;                          // Order = minimum degree
    int filtersize;                 // Size of associated Bloom filters (# of bits)
    
public:
    BloomFilterNode *root;      // Pointer to root node
    
    // Constructor with parameters order and filter size
    BloomFilterTree(int _t, int _s);
    ~BloomFilterTree();
    
    bool contains(int k);
    BloomFilterNode *search(int k);
    BloomFilterNode *getRoot();
    void traverse();
    void traverseFilters();
    float computeMinJaccard(BloomFilter *filter); 
    int computeMinJaccardKey(BloomFilter *filter);
    int getMinKey();
    int getMaxKey();
    int computeSubsetId(BloomFilter *filter);
    int computeSegmentId(BloomFilter *filter);
    vector<BloomFilter> collectAllFilters();
    vector<pair<int, double>>computeAllDistances(BloomFilter *filter);
    vector<pair<int, double>>computekDistances(BloomFilter *filter, int k);
    
    // Insertion methods
    void insert(BloomFilter *filter);
    void insertAsSubset(BloomFilter *filter);
    void insertAsSegments(BloomFilter *filter);
    
    // Similarity queries
    // TODO 
    BloomFilter *simpleSimQuery(BloomFilter *filter);
    BloomFilter *simQuery(BloomFilter *filter);
    vector<BloomFilter> simpleSimQueryVec(BloomFilter *filter, int k);
    vector<BloomFilter> simQueryVec(BloomFilter *filter, int k);
    
};

#endif
