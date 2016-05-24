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

// Identical to simpleSimQuery() because pruning only takes place in index nodes
BloomFilter * BloomFilterLeaf::simQuery(BloomFilter *filter) {
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

// TODO
BloomFilterVec * BloomFilterLeaf::simpleSimQueryVec(BloomFilter *filter, int k) {
    BloomFilterVec *results = new BloomFilterVec(getFilterSize());
    int index = 0;
    float max = 0;
    float jacc;
    
    // Determine nearest neighbor
    for (int i=0; i<getCount(); i++) {
        jacc = computeJaccard(filters[i], filter);
        if (jacc > max) {
            max = jacc;
            index = i;
        }
    }
    results->filters.push_back(*filters[index]);
    cout << "Best result: ";
    results->filters[0].printData();
    
    // Determine k-1 nearest neighbors
    // Collect candidates with greater keys
    /* int *ids = new int[(k-1)*2];
    float *coefficients = new float[(k-1)*2];
    BloomFilter **candidates = new BloomFilter *[(k-1)*2];
    int count = 1;
    int first=0;
    for (int i=0; i<(k-1)/2; i++) {
        if (getKeys()[index+1+i]) {
            candidates[i] = filters[index+1+i];
            count++;
        }
        else if (next) {
            candidates[i] = next->filters[first];
            first++;
            count++;
        }
    }
    
    // Collect candidates with smaller keys
    first = 0;
    for (int i=0; i<(k-1)/2; i++) {
        if (getKeys()[index-1+i]) {
            candidates[((k-1)/2)-1+i] = filters[index-1-i];
            count++;
        }
        else if (prev) {
            candidates[((k-1)/2)-1+i] = filters[first];
            first++;
            count++;
        }
    }
    
    // Check if enough candidates have been found
    if (count != k*2) {
        cout << "Error - too little candidates for query!";
        for (int i=0; i<count; i++) {
            results->filters.push_back(*candidates[i]);
        }
        return results;
    }
    
    // Determine k-1 best candidates
    max = 0;
    for (int i=0; i<k-1; i++) {
        coefficients[i] = computeJaccard(candidates[i], filter);
        ids[i] = candidates[i]->getId();
    }
    
    index = 0;
    for (int i=0; i<k-1; i++) {
        for (int j=0; j<(k-1)*2; j++) {
            float max = 0;
            if (coefficients[j] > max) {
                max = coefficients[j];
                index = ids[j];
            }
        }
        results->filters.push_back(*candidates[index]);
    } */
    return results;
}

// TODO
BloomFilterVec * BloomFilterLeaf::simQueryVec(BloomFilter *filter, int k) {
    return NULL; 
}
