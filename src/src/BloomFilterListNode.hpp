//  BloomFilterListNode.hpp, Judith Greif
//  Description: Header for class BloomFilterListNode


#ifndef BloomFilterListNode_hpp
#define BloomFilterListNode_hpp


#include <iostream>
#include "BloomFilter.hpp"


class BloomFilterListNode {
private:
    int pos;
    BloomFilterListNode *next;
    
public:
    vector<BloomFilter*> zeroLinks;
    vector<BloomFilter*> oneLinks;
    BloomFilterListNode();
    BloomFilterListNode(int _p);
    BloomFilterListNode(int _p, BloomFilterListNode *_n);
    
    int getPosition();
    void setPosition(int p);
    BloomFilterListNode *getNext();
    void setNext(BloomFilterListNode *n);
    void printZeroLinks();
    void printOneLinks(); 
    
    friend class BloomFilterList;
};

#endif 
