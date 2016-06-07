//  BloomFilterList.cpp, Judith Greif
//  Description: Implementation of class BloomFilterList


#include "BloomFilterList.hpp"


BloomFilterList::BloomFilterList(): size(2*filtersize) {
    head = tail = NULL;
}

// Create new list with 2*filtersize nodes, two for each Bloom filter position
// Initialize values with alternating 0 and 1 (both for each Bloom filter position)
BloomFilterList::BloomFilterList(int _f): size(2*_f) {
    head = tail = NULL;
    for (int i=0; i<size; i++) {
        if (i%2 == 0) {
            tailAppend(0);
        }
        else {
            tailAppend(1);
        }
    }
}

BloomFilterList::~BloomFilterList() {
    clear();
}

void BloomFilterList::clear() {
    BloomFilterListNode *del = head;
    while (del != NULL) {
        head = head->getNext();
        delete del;
        del = head;
    }
    head = tail = NULL;
}

void BloomFilterList::traverse() {
    BloomFilterListNode *tmp = head;
    if (tmp == NULL) {
        cout << "List is empty!\n";
        return;
    }
    else {
        cout << "|";
        do {
            cout << tmp->getValue();
            tmp = tmp->getNext();
        }
        while (tmp != NULL);
    }
    cout << "|";
}

void BloomFilterList::updateNode(BloomFilter *filter, int index) {
    int idx = head->getPosition();
    BloomFilterListNode *tmp = head;
    while (idx < index) {
        tmp = head->getNext();
        idx = tmp->getPosition();
    }
    tmp->links.push_back(filter);
}

void BloomFilterList::tailAppend(int value) {
    if (head == NULL) {
        head = tail = new BloomFilterListNode(value, 0);
    }
    else {
        
        // Append new node to tail
        tail->setNext(new BloomFilterListNode(value, tail->getPosition()+1));
        
        // Update tail pointer
        tail = tail->getNext(); 
    }
}