//  BloomFilterLeaf.cpp, Judith Greif
//  Description: Implementation of class BloomFilterLeaf

#include "BloomFilterLeaf.hpp"

using namespace std;


BloomFilterLeaf::BloomFilterLeaf(int _t, int _s): BloomFilterNode(_t, _s) {
    next = NULL;
    prev = NULL;
}

BloomFilterLeaf::BloomFilterLeaf(int _t, int _s, BloomFilterLeaf *_prev, BloomFilterLeaf *_next) : BloomFilterNode(_t, _s) {
    next = _next;
    prev = _prev;
}

BloomFilterLeaf::~BloomFilterLeaf() {
    if (next != NULL) {
        next->setPrev(this->prev);
    }
    if (prev != NULL) {
        prev->setNext(next);
    }
    setNext(NULL);
    setPrev(NULL);
}

BloomFilterLeaf * BloomFilterLeaf::split(BloomFilter *f) {
    assert(getCount() == getMax());
    
    int *keys = getKeys();
    int max = getMax();
    int *merged = new int[max+1];
    
    BloomFilter **mergedFilters = new BloomFilter *[max+1];
    
    int id = f->getId();
    int index = indexOfKey(id);
    
    // Merge keys and filters together
    for (int i=0; i<index; i++) {
        merged[i] = keys[i];
        mergedFilters[i] = filters[i];
    }
    
    merged[index] = id;
    mergedFilters[index] = f;
    
    for (int i=index+1; i<max+1; i++) {
        merged[i] = keys[i-1];
        mergedFilters[i] = filters[i-1];
    }
    
    BloomFilterLeaf *l = new BloomFilterLeaf(getOrder(), getFilterSize());
    
    int half = (max+1)/2;
    setCount(half);
    
    for (int i=0; i<half; i++) {
        keys[i] = merged[i];
        filters[i] = mergedFilters[i];
    }
    
    int *newNodeKeys = l->getKeys();
    
    // Hand over keys and filters to new sibling
    for (int i=half; i<max+1; i++) {
        newNodeKeys[i-half] = merged[i];
        l->filters[i-half] = mergedFilters[i];
        l->increment();
    }
    
    // Delete filters that have been handed over
    for (int i=half; i<max; i++) {
        filters[i] = NULL;
    }
    
    // Update sibling pointers
    if (next) {
        l->setNext(next);
        next->setPrev(l);
    }
    
    delete[] merged;
    delete[] mergedFilters;
    return l;
}

void BloomFilterLeaf::traverse() {
    assert(getCount() <= getMax());
    int *keys = getKeys();
    cout << "| ";
    for (int i=0; i<getCount(); i++) {
        cout << keys[i] << " ";
    }
    cout << "|";
}

void BloomFilterLeaf::traverseFilters() {
    assert (getCount() <= getMax());
    cout << "|";
    for (int i=0; i<getCount(); i++) {
        filters[i]->printArr();
        cout << "|";
    }
}

bool BloomFilterLeaf::contains(int k) {
    bool result = false;
    int *keys = getKeys();
    for (int i=0; i<getCount(); i++) {
        if (keys[i] == k) {
            result = true;
            break;
        }
    }
    return result;
}

BloomFilterNode *BloomFilterLeaf::search(int k) {
    return this;
}

BloomFilterLeaf * BloomFilterLeaf::getPrev() {
    return prev;
}

void BloomFilterLeaf::setPrev(BloomFilterLeaf *leaf) {
    prev = leaf;
}

BloomFilterLeaf * BloomFilterLeaf::getNext() {
    return next;
}

void BloomFilterLeaf::setNext(BloomFilterLeaf *leaf) {
    next = leaf;
}

void BloomFilterLeaf::insert(BloomFilter *filter) {
    
    // Get Bloom filter values
    if (getCount() < getMax()) {
        shiftAndInsert(filter);
    }
    else {
        BloomFilterLeaf *l = split(filter);
        l->setPrev(this);
        setNext(l);
        BloomFilterNode *p = getParent();
        if (p == NULL) {
            p = new BloomFilterIndexNode(getOrder(), getFilterSize());
            setParent(p);
        }
        l->setParent(p);
        
        // Get middle filter
        BloomFilter *middle = l->filters[0];
        cout << "\nKey to be inserted into parent: " << middle->getId();
        cout << "\nFilter to be inserted into parent: ";
        middle->printArr();
        cout << endl; 
        p->insert(middle, this, l);
    }
}

float BloomFilterLeaf::computeMaxJaccard(BloomFilter *filter) {
    float max = 0;
    float jacc;
    for (int i=0; i<getCount(); i++) {
        jacc = computeJaccard(filters[i], filter);
        if (jacc > max) {
            max = jacc;
        }
    }
    return max;
}

int BloomFilterLeaf::computeMaxJaccardKey(BloomFilter *filter) {
    int index = 0;
    float max = 0;
    float jacc;
    for (int i=0; i<getCount(); i++) {
        jacc = computeJaccard(filters[i], filter);
        if (jacc > max) {
            max = jacc;
            index = i;
        }
    }
    return getKeys()[index];
}

int BloomFilterLeaf::getMinKey() {
    return getKeys()[0];
}

int BloomFilterLeaf::getMaxKey() {
    return getKeys()[getCount()-1];
}

BloomFilter * BloomFilterLeaf::simpleSimQuery(BloomFilter *filter) {
    int index = 0;
    float max = 0;
    float jacc;
    for (int i=0; i<getCount(); i++) {
        jacc = computeJaccard(filters[i], filter);
        if (jacc > max) {
            max = jacc;
            index = i;
        }
    }
    return filters[index]; 
}