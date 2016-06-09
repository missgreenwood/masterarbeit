//  BloomFilterListNode.cpp, Judith Greif
//  Description: 


#include "BloomFilterListNode.hpp"


BloomFilterListNode::BloomFilterListNode(): next(NULL) {
    zeroLinks = *new vector<BloomFilter*>;
    oneLinks = *new vector<BloomFilter*>;
}

BloomFilterListNode::BloomFilterListNode(int _p): pos(_p), next(NULL) {
    zeroLinks = *new vector<BloomFilter*>;
    oneLinks = *new vector<BloomFilter*>;
}

BloomFilterListNode::BloomFilterListNode(int _p, BloomFilterListNode *_n): pos(_p), next(_n) {
    zeroLinks = *new vector<BloomFilter*>;
    oneLinks = *new vector<BloomFilter*>;
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

void BloomFilterListNode::printZeroLinks() {
    cout << "Zero links:\n";
    for (int i=0; i<zeroLinks.size(); i++) {
        cout << zeroLinks[i]->getId() << " (";
        zeroLinks[i]->printArr();
        cout << ")\n";
    }
}

void BloomFilterListNode::printOneLinks() {
    cout << "One links:\n";
    for (int i=0; i<oneLinks.size(); i++) {
        cout << oneLinks[i]->getId() << " (";
        oneLinks[i]->printArr();
        cout << ")\n"; 
    }
}