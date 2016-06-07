//  BloomFilterListNode.cpp, Judith Greif
//  Description: 


#include "BloomFilterListNode.hpp"


BloomFilterListNode::BloomFilterListNode(): next(NULL) {
    links = *new vector<BloomFilter*>;
}

BloomFilterListNode::BloomFilterListNode(int _v, int _p): value(_v), pos(_p), next(NULL) {
    links = *new vector<BloomFilter*>;
}

BloomFilterListNode::BloomFilterListNode(int _v, int _p, BloomFilterListNode *_n): value(_v), pos(_p), next(_n) {
    links = *new vector<BloomFilter*>;
}

int BloomFilterListNode::getValue() {
    return value;
}

void BloomFilterListNode::setValue(int v) {
    value = v;
}

int BloomFilterListNode::getPosition() {
    return pos;
}

void BloomFilterListNode::setPosition(int p) {
    pos = p;
}

BloomFilterListNode * BloomFilterListNode::getNext() {
    return next; 
}

void BloomFilterListNode::setNext(BloomFilterListNode *n) {
    next = n;
}

void BloomFilterListNode::printLinkList() {
    for (int i=0; i<links.size(); i++) {
        cout << links[i]->getId() << " (";
        links[i]->printArr();
        cout << ")\n";
    }
}