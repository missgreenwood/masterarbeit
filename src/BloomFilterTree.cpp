//  BloomFilterTree.cpp, Judith Greif
//  Description: Implementation of class BloomFilterTree

#include <iostream>
#include "BloomFilterTree.hpp"

using namespace std;


// Constructor with parameter t
// Initializes tree as empty
BloomFilterTree::BloomFilterTree(int _t): t(_t), root(NULL) {};
