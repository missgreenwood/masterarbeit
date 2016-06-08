//  BloomFilterList.cpp, Judith Greif
//  Description: Implementation of class BloomFilterList


#include "BloomFilterList.hpp"


BloomFilterList::BloomFilterList(): size(filtersize) {
    head = tail = NULL;
}

// Create new list with node for each Bloom filter position
BloomFilterList::BloomFilterList(int _f): size(_f) {
    head = tail = NULL;
    for (int i=0; i<size; i++) {
        tailAppend(i);
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

void BloomFilterList::printPosition(int index) {
    int idx = head->getPosition();
    BloomFilterListNode *tmp = head;
    while (idx < index) {
        tmp = head->getNext();
        idx = tmp->getPosition();
    }
    cout << "Position: " << tmp->getPosition() << endl;
    tmp->printZeroLinks();
    tmp->printOneLinks();
}

void BloomFilterList::printAll() {
    if (head == NULL) {
        cout << "List is empty!\n";
        return; 
    }
    BloomFilterListNode *tmp = head;
    while (tmp != NULL) {
        cout << "Position: " << tmp->getPosition() << endl;
        tmp->printZeroLinks();
        tmp->printOneLinks();
        cout << endl;
        tmp = tmp->getNext();
    }
}

void BloomFilterList::updateNode(BloomFilter *filter, int index) {
    int idx = head->getPosition();
    BloomFilterListNode *tmp = head;
    while (idx < index) {
        tmp = tmp->getNext();
        idx = tmp->getPosition();
    }
    if (filter->getData()[index] == 0) {
        tmp->zeroLinks.push_back(filter);
    }
    else {
        tmp->oneLinks.push_back(filter);
    }
}

void BloomFilterList::tailAppend(int value) {
    if (head == NULL) {
        head = tail = new BloomFilterListNode(0);
    }
    else {
        
        // Append new node to tail
        tail->setNext(new BloomFilterListNode(tail->getPosition()+1));
        
        // Update tail pointer
        tail = tail->getNext(); 
    }
}

int BloomFilterList::getSize() {
    return size;
}

void BloomFilterList::insert(BloomFilter *filter) {
    if (head == NULL) {
        cout << "List does not exist!\n";
        return;
    }
    if (size != filter->getSize()) {
        cout << "List and filter have different sizes!\n";
        return;
    }
    
    // Update corresponding node of each position in Bloom filter
    for (int i=0; i<size; i++) {
        updateNode(filter, i);
    }
}