//  BloomFilterList.cpp, Judith Greif
//  Description: Implementation of class BloomFilterList


#include <map>
#include <algorithm>
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

BloomFilter * BloomFilterList::getMinJaccardFilter(BloomFilter *filter) {
    if (head == NULL) {
        cout << "List is empty!\n";
        return filter;
    }
    
    // All positions hold the same filters
    // Therefore it suffices to compare head's one and zero link lists
    vector<pair<BloomFilter*, float>> candidates;
    float jacc;
    
    // Retrieve all candidates
    for (int i=0; i<head->zeroLinks.size(); i++) {
        jacc = head->zeroLinks[i]->computeJaccard(filter);
        candidates.push_back(make_pair(head->zeroLinks[i], jacc));
    }
    for (int i=0; i<head->oneLinks.size(); i++) {
        jacc = head->oneLinks[i]->computeJaccard(filter);
        candidates.push_back(make_pair(head->oneLinks[i], jacc));
    }
    sort(candidates.begin(), candidates.end(), [](const pair<BloomFilter*, float> &left, const pair<BloomFilter*, float> &right) {
        return left.second < right.second;
    });
    return candidates[0].first;
}

vector<BloomFilter> BloomFilterList::collectAllFilters() {
    if (head == NULL) {
        cout << "List is empty!\n";
        return {};
    }
    
    // It suffices to collect only head's filters
    vector<BloomFilter> result;
    for (int i=0; i<head->zeroLinks.size(); i++) {
        result.push_back(*head->zeroLinks[i]);
    }
    for (int i=0; i<head->oneLinks.size(); i++) {
        result.push_back(*head->oneLinks[i]);
    }
    return result;
}

int BloomFilterList::countFilters() {
    if (head == NULL) {
        cout << "List is empty!\n";
        return 0;
    }
    int count = 0;
    for (int i=0; i<head->zeroLinks.size(); i++) {
        count++;
    }
    for (int i=0; i<head->oneLinks.size(); i++) {
        count++;
    }
    return count; 
}

vector<pair<int, float>> BloomFilterList::computeAllDistances(BloomFilter *filter) {
    vector<BloomFilter> filters = collectAllFilters();
    vector<pair<int, float>> result;
    float jacc;
    for (int i=0; i<head->zeroLinks.size(); i++) {
        jacc = head->zeroLinks[i]->computeJaccard(filter);
        result.push_back(make_pair(head->zeroLinks[i]->getId(), jacc));
    }
    for (int i=0; i<head->oneLinks.size(); i++) {
        jacc = head->oneLinks[i]->computeJaccard(filter);
        result.push_back(make_pair(head->oneLinks[i]->getId(), jacc));
    }
    return result;
}

vector<pair<BloomFilter, float>> BloomFilterList::compare(BloomFilter *filter, int k) {
    vector<pair<BloomFilter, float>> distances;
    if (head == NULL) {
        cout << "List is empty!\n";
        distances.push_back(make_pair(*filter, 0));
    }
    else {
        vector<BloomFilter> allFilters = collectAllFilters();
        float jacc;
        for (int i=0; i<allFilters.size(); i++) {
            jacc = filter->computeJaccard(&allFilters[i]);
            distances.push_back(make_pair(allFilters[i], jacc));
        }
        
        // Sort all filters in list by jaccard distance in ascending order
        sort(distances.begin(), distances.end(), [](const pair<BloomFilter, float> &left, const pair<BloomFilter, float> &right) {
            return left.second < right.second;
        });
        
        // Return Bloom filters with k smallest distances
        int size = distances.size();
        int diff = size-k;
        for (int i=0; i<diff; i++) {
            distances.pop_back();
        }
    }
    
    cout << k << " nearest neighbors of f" << filter->getId() << " (";
    filter->printArr();
    cout << ") in list:\n\n";
    for (int i=0; i<distances.size(); i++) {
        cout << "jacc(" << filter->getId() << ", " << distances[i].first.getId() << "): " << distances[i].second << "\n";
    }
    return distances;
}

void BloomFilterList::insert(BloomFilter *filter) {
    if (head == NULL) {
        cout << "List is empty!\n";
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

BloomFilter * BloomFilterList::simQuery(BloomFilter *filter) {
    if (head == NULL) {
        cout << "List is empty!\n";
        return {};
    }
    if (size != filter->getSize()) {
        cout << "List and filter have different sizes!\n";
        return {};
    }
    vector<BloomFilter*> candidates;
    BloomFilterListNode *tmp = head;
    
    // Collect all candidates
    int index = 0;
    while (tmp != NULL) {
        if (filter->getData()[index] == 0) {
            for (int i=0; i<tmp->zeroLinks.size(); i++) {
                candidates.push_back(tmp->zeroLinks[i]);
            }
        }
        else {
            for (int i=0; i<tmp->oneLinks.size(); i++) {
                candidates.push_back(tmp->oneLinks[i]);
            }
        }
        index++;
        tmp = tmp->getNext();
    }
    
    cout << "Found candidates:\n";
    for (int i=0; i<candidates.size(); i++) {
        cout << candidates[i]->getId() << endl;
    }
    
    // TODO
    // Sort candidates by frequency
    
    // Return first element
    return candidates[0];
}