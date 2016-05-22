//  BPlusLeaf.hpp, Judith Greif
//  Description: Header for class BPlusLeaf

#ifndef BPlusLeaf_hpp
#define BPlusLeaf_hpp

#include <iostream>
#include "BPlusNode.hpp"
#include "BPlusIndexNode.hpp"


class BPlusLeaf : public BPlusNode {

public:
    BPlusLeaf(int _t);
    BPlusLeaf(int _t, BPlusLeaf *prev, BPlusLeaf *next);
    ~BPlusLeaf();
    void insert(int k);
    void remove(int k);
    BPlusNode *search(int k);
    BPlusLeaf *split(int k);
    void traverse();
    bool contains(int k);
    BPlusNode *searchRemoveIndex(int k);
};

#endif