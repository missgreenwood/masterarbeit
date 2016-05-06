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
    BPlusIndexNode(int t);
    ~BPlusIndexNode();
    BPlusNode *search(int k);
    virtual void shiftAndInsert(int k);
    virtual void insert(int k);
    virtual void insert(int k, BPlusNode *leftNode, BPlusNode *rightNode);
    virtual bool contains(int k);
    virtual void remove(int k);
    BPlusIndexNode *split(int k, BPlusNode *left, BPlusNode *right, int &middle);
    void traverse();
};

#endif
