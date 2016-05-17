//  BloomFilterLeaf.cpp, Judith Greif
//  Description: Implementation of class BloomFilterLeaf

#include "BloomFilterLeaf.hpp"

using namespace std;


BloomFilterLeaf::BloomFilterLeaf(int _t) : BloomFilterNode(_t, filtersize) {
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

BloomFilterLeaf::BloomFilterLeaf(int _t, int _s): BloomFilterNode(_t, _s) {
    next = NULL;
    prev = NULL;
    
    filters = new int *[_t*2];
    for (int i=0; i<(_t*2); i++) {
        filters[i] = new int[_s];
    }
    for (int i=0; i<_t*2; i++) {
        for (int j=0; j<_s; j++) {
            filters[i][j] = 0;
        }
    }
}

BloomFilterLeaf::BloomFilterLeaf(int _t, int _s, BloomFilterLeaf *_prev, BloomFilterLeaf *_next) : BloomFilterNode(_t, _s) {
    next = _next;
    prev = _prev;
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
    for (int i=0; i<t*2; i++) {
        delete[] filters[i];
    }
    delete[] filters;
}

void BloomFilterLeaf::insert(BloomFilter *filter) {
    
    // Get Bloom filter values
    int *data = filter->getArr();
    int id = filter->getId();
    int index = indexOfKey(id);
    if (getCount() < getMax()) {
        shiftAndInsert(filter);
        for (int i=0; i<getFilterSize(); i++) {
            getFilters()[index][i] = data[i];
        }
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
        int correctId = filter->getId();
        filter->setId(l->getKeys()[0]);
        p->insert(filter, this, l);
        filter->setId(correctId); 
    }
}

// TODO
void BloomFilterLeaf::insertSimilarFilter(BloomFilter *filter) {
    
}

BloomFilterNode *BloomFilterLeaf::search(int k) {
    return this;
}

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
            l->getFilters()[i-half][j] = filters[i][j];
        }
    }
    for (int j=0; j<l->getFilterSize(); j++) {
        l->getFilters()[l->getCount()-1][j] = data[j];
    }
    
    // Delete filters that have been handed over
    for (int i=half; i<max; i++) {
        for (int j=0; j<getFilterSize(); j++) {
            filters[i][j] = 0;
        }
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

void BloomFilterLeaf::traverseFilters() {
    assert (getCount() <= getMax());
    int **filters = getFilters();
    cout << "|";
    for (int i=0; i<getCount(); i++) {
        for (int j=0; j<getFilterSize(); j++) {
            cout << filters[i][j];
        }
        cout << "|";
    }
}
