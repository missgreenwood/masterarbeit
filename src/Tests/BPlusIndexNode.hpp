//  BPlusIndexNode.hpp, Judith Greif
//  Description: Header for class BPlusIndexNode

#ifndef BPlusIndexNode_hpp
#define BPlusIndexNode_hpp

#include <iostream>
#include "BPlusNode.hpp"


class BPlusIndexNode : public BPlusNode {
private:
    // BPlusNode **C;

public:
    // BPlusIndexNode *prev;
    // BPlusIndexNode *next;
    BPlusIndexNode(int t);
    ~BPlusIndexNode();
    BPlusNode *search(int k);
    virtual void shiftAndInsert(int k);
    void insert(int k);
    void insert(int k, BPlusNode *leftNode, BPlusNode *rightNode);
    bool contains(int k);
    void remove(int k);
    BPlusIndexNode *split(int k, BPlusNode *left, BPlusNode *right, int &middle);
    void traverse();
    BPlusNode *searchRemoveIndex(int k);
};

#endif
