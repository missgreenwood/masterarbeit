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
    delete prev;
    delete next;
}

// TODO
BloomFilterLeaf * BloomFilterLeaf::split(BloomFilter *f) {
    assert(getCount() == getMax());
    int *keys = getKeys();
    int max = getMax();
    int *merged = new int[max+1];
    int id = f->getId();
    int index = indexOfKey(id);
    int *data = f->getArr();
    for (int i=0; i<index; i++) {
        merged[i] = keys[i];
    }
    merged[index] = id;
    for (int i=index+1; i<max+1; i++) {
        merged[i] = keys[i-1];
    }
    BloomFilterLeaf *l = new BloomFilterLeaf(getOrder(), getFilterSize());
    int half = (max+1)/2;
    setCount(half);
    for (int i=0; i<half; i++) {
        keys[i] = merged[i];
    }
    
    // Hand over keys and filters to new sibling
    for (int i=half; i<max+1; i++) {
        l->getKeys()[i-half] = merged[i];
        l->increment();
    }
    for (int i=half; i<max; i++) {
        for (int j=0; j<l->getFilterSize(); j++) {
            l->getFilters()[i-half][j] = getFilters()[i][j];
        }
    }
    for (int j=0; j<l->getFilterSize(); j++) {
        l->getFilters()[l->getCount()-1][j] = data[j];
    }
    
    // Delete filters that have been handed over
    for (int i=half; i<max; i++) {
        for (int j=0; j<getFilterSize(); j++) {
            getFilters()[i][j] = 0;
        }
    }
    
    // Decrement self
    setCount(half); 
    
    // Update sibling pointers
    if (next) {
        l->setNext(next);
        next->setPrev(l);
    }
    
    delete[] merged;
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

// TODO 
void BloomFilterLeaf::traverseFilters() {
    assert (getCount() <= getMax());
    BloomFilter **filters = getFilters();
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
        BloomFilter *middle = l->getFilters()[0];
        p->insert(middle, this, l);
    }
}