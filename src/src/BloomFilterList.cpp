//  BloomFilterList.cpp, Judith Greif
//  Description: Implementation of class BloomFilterList


#include <map>
#include <algorithm>
#include "BloomFilterList.hpp"


BloomFilterList::BloomFilterList(): size(0) {
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

int BloomFilterList::getSize() {
    return size;
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

BloomFilter * BloomFilterList::getMinJaccardFilter(BloomFilter *filter) {
    if (head == NULL) {
        cout << "List is empty!\n";
        return filter;
    }
    
    // All positions hold the same filters
    // Therefore it suffices to compare head's one and zero link lists
    vector<pair<BloomFilter*, double>> candidates;
    double jacc;
    
    // Retrieve all candidates
    for (int i=0; i<head->zeroLinks.size(); i++) {
        jacc = head->zeroLinks[i]->computeJaccard(filter);
        candidates.push_back(make_pair(head->zeroLinks[i], jacc));
    }
    for (int i=0; i<head->oneLinks.size(); i++) {
        jacc = head->oneLinks[i]->computeJaccard(filter);
        candidates.push_back(make_pair(head->oneLinks[i], jacc));
    }
    sort(candidates.begin(), candidates.end(), [](const pair<BloomFilter*, double> &left, const pair<BloomFilter*, double> &right) {
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

vector<pair<int, double>> BloomFilterList::computeAllDistances(BloomFilter *filter) {
    vector<BloomFilter> filters = collectAllFilters();
    vector<pair<int, double>> result;
    double jacc;
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

vector<pair<int, double>> BloomFilterList::computekDistances(BloomFilter *filter, int k) {
    vector<pair<int, double>> allDistances = computeAllDistances(filter);
    vector<pair<int, double>> result;
    sort(allDistances.begin(), allDistances.end(), [](const pair<int, double> &left, const pair<int, double> &right) {
        return left.second < right.second;
    });
    for (int i=0; i<k; i++) {
        cout << "jacc(" <<filter->getId() << ", " << allDistances[i].first << "): " << allDistances[i].second << "\n";
        result.push_back(allDistances[i]);
    }
    return result; 
}

vector<pair<BloomFilter, double>> BloomFilterList::compare(BloomFilter *filter, int k) {
    vector<pair<BloomFilter, double>> distances;
    if (head == NULL) {
        cout << "List is empty!\n";
        distances.push_back(make_pair(*filter, 0));
    }
    else {
        vector<BloomFilter> allFilters = collectAllFilters();
        double jacc;
        for (int i=0; i<allFilters.size(); i++) {
            jacc = filter->computeJaccard(&allFilters[i]);
            distances.push_back(make_pair(allFilters[i], jacc));
        }
        
        // Sort all filters in list by jaccard distance in ascending order
        sort(distances.begin(), distances.end(), [](const pair<BloomFilter, double> &left, const pair<BloomFilter, double> &right) {
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
    vector<pair<BloomFilter*, int>> candidates;
    BloomFilterListNode *tmp = head;
    
    // Collect all candidates
    int index = 0;
    while (tmp != NULL) {
        if (filter->getData()[index] == 0) {
            for (int i=0; i<tmp->zeroLinks.size(); i++) {
                candidates.push_back(make_pair(tmp->zeroLinks[i], tmp->zeroLinks[i]->getId()));
            }
        }
        else {
            for (int i=0; i<tmp->oneLinks.size(); i++) {
                candidates.push_back(make_pair(tmp->oneLinks[i], tmp->oneLinks[i]->getId()));
            }
        }
        index++;
        tmp = tmp->getNext();
    }
    
    // Sort candidates by id
    sort(candidates.begin(), candidates.end(), [] (const pair<BloomFilter*, int> &left, const pair<BloomFilter*, int> &right) {
        return left.second < right.second;
    });
    
    // Fill result vector with pairs <BloomFilter*, frequency>
    vector<pair<BloomFilter*, int>> result;
    int count = 0;
    for (int i=candidates.size()-1; i>0; i-=count) {
        count = 0;
        while (candidates[i].second == candidates[i-count].second) {
            count++;
        }
        result.push_back(make_pair(candidates[i].first, count));
    }
    
    // Sort result vector by frequency
    sort(result.begin(), result.end(), [] (const pair<BloomFilter*, int> &left, const pair<BloomFilter*, int> &right) {
        return left.second > right.second;
    });
    
    // Return first element
    return result[0].first;
}

vector <BloomFilter*> BloomFilterList::simQueryVec(BloomFilter *filter, int k) {
    if (head == NULL) {
        cout << "List is empty!\n";
        return {};
    }
    if (size != filter->getSize()) {
        cout << "List and filter have different sizes!\n";
        return {};
    }
    vector<pair<BloomFilter*, int>> candidates;
    BloomFilterListNode *tmp = head;
    
    // Collect all candidates
    int index = 0;
    while (tmp != NULL) {
        if (filter->getData()[index] == 0) {
            for (int i=0; i<tmp->zeroLinks.size(); i++) {
                candidates.push_back(make_pair(tmp->zeroLinks[i], tmp->zeroLinks[i]->getId()));
            }
        }
        else {
            for (int i=0; i<tmp->oneLinks.size(); i++) {
                candidates.push_back(make_pair(tmp->oneLinks[i], tmp->oneLinks[i]->getId()));
            }
        }
        index++;
        tmp = tmp->getNext();
    }
    
    // Sort candidates by id
    sort(candidates.begin(), candidates.end(), [] (const pair<BloomFilter*, int> &left, const pair<BloomFilter*, int> &right) {
        return left.second < right.second;
    });
    
    // Fill intermediate vector with pairs <BloomFilter*, frequency>
    vector<pair<BloomFilter*, int>> intermediate;
    int count = 0;
    for (int i=candidates.size()-1; i>0; i-=count) {
        count = 0;
        while (candidates[i].second == candidates[i-count].second) {
            count++;
        }
        intermediate.push_back(make_pair(candidates[i].first, count));
    }
    vector<BloomFilter*> result;
    
    // Sort intermediate vector by frequency
    sort(intermediate.begin(), intermediate.end(), [] (const pair<BloomFilter*, int> &left, const pair<BloomFilter*, int> &right) {
        return left.second > right.second;
    });
    
    // If list does not hold enough filters, return all results
    if (intermediate.size() < k) {
        cout << "Too little candidates in list!\n";
        for (int i=0; i<intermediate.size(); i++) {
            result.push_back(intermediate[i].first);
        }
    }
    else {
        
        // Return first k Bloom filters from intermediate vector
        for (int i=0; i<k; i++) {
            result.push_back(intermediate[i].first);
        }
    }
    return result;
}