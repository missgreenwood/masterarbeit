//  BPlusIndexNode.hpp, Judith Greif
//  Description: Header for class BPlusIndexNode

#ifndef BPlusIndexNode_hpp
#define BPlusIndexNode_hpp

#include <iostream>
#include "BPlusNode.hpp"


class BPlusIndexNode : public BPlusNode {
private:
    BPlusNode **C;

public:
    virtual void shiftAndInsert(int k);
    BPlusIndexNode(int t);
    ~BPlusIndexNode();
    BPlusNode *search(int k);
    virtual void insert(int k);
    virtual void insert(int k, BPlusNode *oldNode, BPlusNode *newNode);
    virtual void remove(int k);
    BPlusIndexNode *split(int k, BPlusNode *left, BPlusNode *right, int &middle);
    void traverse();
};

#endif
