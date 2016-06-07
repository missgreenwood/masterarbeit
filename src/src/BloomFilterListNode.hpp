//  BloomFilterListNode.hpp, Judith Greif
//  Description: Header for class BloomFilterListNode


#ifndef BloomFilterListNode_hpp
#define BloomFilterListNode_hpp


#include <iostream>
#include "BloomFilter.hpp"


class BloomFilterListNode {
private:
    int value;
    int pos;
    BloomFilterListNode *next;
    
public:
    vector<BloomFilter*> links;
    BloomFilterListNode();
    BloomFilterListNode(int _v, int _p);
    BloomFilterListNode(int _v, int _p, BloomFilterListNode *_n);
    
    int getValue();
    void setValue(int v);
    int getPosition();
    void setPosition(int p);
    BloomFilterListNode *getNext();
    void setNext(BloomFilterListNode *n);
    void printLinkList();
    
    friend class BloomFilterList;
};

#endif 
