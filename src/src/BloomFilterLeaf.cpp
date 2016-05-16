//  BloomFilterLeaf.cpp, Judith Greif
//  Description: Implementation of class BloomFilterLeaf

#include "BloomFilterLeaf.hpp"

using namespace std;


BloomFilterLeaf::BloomFilterLeaf(int _t) : BloomFilterNode(_t) {
    next = NULL;
    prev = NULL;
    
    // Allocate memory
    filters = new int *[_t*2];
    for (int i=0; i<(_t*2); i++) {
        filters[i] = new int[filtersize];
    }
    
    // Initialize 2D filters array with zeros
    for (int i=0; i<2*_t; i++) {
        for (int j=0; j<filtersize; j++) {
            filters[i][j] = 0;
        }
    }
}

BloomFilterLeaf::BloomFilterLeaf(int _t, int _s): BloomFilterNode(_t) {
    next = NULL;
    prev = NULL;
    size = _s;
    
    filters = new int *[_t*2];
    for (int i=0; i<(_t*2); i++) {
        filters[i] = new int[_s];
    }
    cout << "Initialize filters array:\n";
    for (int i=0; i<_t*2; i++) {
        for (int j=0; j<_s; j++) {
            filters[i][j] = 0;
            cout << filters[i][j];
        }
        cout << endl;
    }
}

BloomFilterLeaf::BloomFilterLeaf(int _t, int _s, BloomFilterLeaf *_prev, BloomFilterLeaf *_next) : BloomFilterNode(_t) {
    next = _next;
    prev = _prev;
    size = _s; 
    // Allocate memory
    filters = new int *[_t*2];
    for (int i=0; i<_t*2; i++) {
        filters[i] = new int[_s];
    }
    
    // Initialize 2D filters array with zeros
    for (int i=0; i<_t*2; i++) {
        for (int j=0; j<_s; j++) {
            filters[i][j] = 0;
        }
    }
}

BloomFilterLeaf::~BloomFilterLeaf() {
    delete prev;
    delete next;
    for (int i=0; i<t; i++) {
        delete[] filters[i];
    }
    delete[] filters;
}

void BloomFilterLeaf::insert(int k) {
    if (getCount() < getMax()) {
        shiftAndInsert(k);
    }
    else {
        BloomFilterLeaf *l = split(k);
        l->setPrev(this);
        setNext(l);
        BloomFilterNode *p = getParent();
        if (p == NULL) {
            p = new BloomFilterIndexNode(getOrder());
            setParent(p);
        }
        l->setParent(p);
        p->insert(l->getKeys()[0], this, l);
    }
}

void BloomFilterLeaf::insertFilter(BloomFilter *f) {
    
    // Get Bloom filter values
    int *data = f->getArr();
    cout << "Data: ";
    for (int i=0; i<f->getSize(); i++) {
        cout << data[i];
    }
    int id = f->getId();
    cout << "\nId: " << id << endl;
    
    int index;
    int *filter;
    if (getCount() < getMax()) {
        index = indexOfKey(id);
        cout << "Index in leaf: " << index << endl;
        shiftAndInsert(id);
        filter = getFilters()[index];
        for (int i=0; i<getFilterSize(); i++) {
            filter[i] = data[i];
        }
    }
    else {
        BloomFilterLeaf *l = split(index);
        cout << "Index: " << index;
        l->setPrev(this);
        setNext(l);
        /* BloomFilterNode *p = getParent();
        if (p == NULL) {
            p = new BloomFilterIndexNode(getOrder());
            setParent(p);
        }
        l->setParent(p);
        p->insert(l->getKeys()[0], this, l);
        if (l->contains(id)) {
            index = l->indexOfKey(id);
            filter = l->getFilters()[index];
            for (int i=0; i<filtersize; i++) {
                filter[i] = data[i];
            }
        }
        else {
            index = indexOfKey(id);
            filter = getFilters()[index];
            for (int i=0; i<filtersize; i++) {
                filter[i] = data[i];
            }
        } */
    }
}

BloomFilterNode *BloomFilterLeaf::search(int k) {
    return this;
}

BloomFilterLeaf *BloomFilterLeaf::split(int k) {
    assert(getCount() == getMax());
    int *keys = getKeys();
    int max = getMax();
    int *merged = new int[max+1];
    int index = indexOfKey(k);
    for (int i=0; i<index; i++) {
        merged[i] = keys[i];
    }
    merged[index] = k;
    for (int i=index+1; i<max+1; i++) {
        merged[i] = keys[i-1];
    }
    BloomFilterLeaf *l = new BloomFilterLeaf(getOrder());
    int half = (max+1)/2;
    setCount(half);
    for (int i=0; i<half; i++) {
        keys[i] = merged[i];
    }
    int *newNodeKeys = l->getKeys();
    for (int i=half; i<max+1; i++) {
        newNodeKeys[i-half] = merged[i];
        l->increment();
    }
    
    // Update sibling pointers
    if (keys[0] < newNodeKeys[0]) {
        l->setPrev(this);
        if (next) {
            l->setNext(next);
            next->setPrev(l);
        }
        setNext(l);
    }
    else {
        l->setNext(this);
        if (prev) {
            l->setPrev(prev);
            prev->setNext(l);
        }
        setPrev(l);
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

void BloomFilterLeaf::setPrev(BloomFilterLeaf *leaf) {
    prev = leaf;
}

BloomFilterLeaf * BloomFilterLeaf::getPrev() {
    return prev;
}

void BloomFilterLeaf::setNext(BloomFilterLeaf *leaf) {
    next = leaf;
}

BloomFilterLeaf * BloomFilterLeaf::getNext() {
    return next;
}

int ** BloomFilterLeaf::getFilters() {
    return filters;
}

int BloomFilterLeaf::getFilterSize() {
    return size;
}

void BloomFilterLeaf::traverseFilters() {
    assert (getCount() <= getMax()); 
    int **filters = getFilters();
    cout << "|";
    for (int i=0; i<getCount(); i++) {
        cout << "|";
        for (int j=0; j<getFilterSize(); j++) {
            cout << filters[i][j];
        }
    }
    cout << "||";
}