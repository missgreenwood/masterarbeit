//  bloom_filter_tree.hpp, Judith Greif
//  Description: Header for classes BloomFilterNode, BloomFilterTree

#ifndef bloom_filter_tree_h
#define bloom_filter_tree_h

#include <iostream>

using namespace std;


// BloomFilterNode - Bloom filter in a B-Tree
// Differences from normal B-Tree:
//  * Only logical nodes
//  * The leaves hold the IDs of all physical nodes -> each internal key is also stored in leaf
//  * Leaves have pointers to physical nodes

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
