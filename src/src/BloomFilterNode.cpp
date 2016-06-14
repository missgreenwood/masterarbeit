//  BloomFilterNode.cpp, Judith Greif
//  Description: Implementation of class BloomFilterNode

#include "BloomFilterNode.hpp"


// Constructor with parameters t and filtersize
BloomFilterNode::BloomFilterNode(int _t, int _s): t(_t), filtersize(_s), n(0), parent(NULL) {
    
    // Allocate memory
    keys = new int[2*_t];
    filters = new BloomFilter *[2*_t];
    for (int i=0; i<(2*_t); i++) {
        filters[i] = NULL;
    }
    unionfilter = new BloomFilter(rand(), _s);
}

BloomFilterNode::~BloomFilterNode() {
    delete parent;
    delete[] keys;
    delete[] filters;
}

int BloomFilterNode::getOrder() {
    return t;
}

int BloomFilterNode::getCount() {
    return n;
}

void BloomFilterNode::setCount(int count) {
    n = count;
}

BloomFilterNode * BloomFilterNode::getParent() {
    return parent;
}

void BloomFilterNode::setParent(BloomFilterNode *node) {
    parent = node;
}

int * BloomFilterNode::getKeys() {
    return keys;
}

int BloomFilterNode::getMax() {
    return 2*t;
}

int BloomFilterNode::getFilterSize() {
    return filtersize;
}

int BloomFilterNode::indexOfKey(int k) {
    if (n == 0) {
        return 0;
    }
    int i=0;
    while (i<n && keys[i]<=k) {
        i++;
    }
    return i;
}

void BloomFilterNode::increment() {
    n++;
}

void BloomFilterNode::decrement() {
    n--;
}

double BloomFilterNode::computeAmbienceJaccard(BloomFilter *f1, BloomFilter *f2) {
    double intersect_size = eIntersect(f1, f2);
    double union_size = eUnion(f1, f2);
    return 1 - (intersect_size/union_size);
}

double BloomFilterNode::computeJaccard(BloomFilter *f1, BloomFilter *f2) {
    return (double) 1-(f1->setIntersection(f2)/f1->setUnion(f2));
}

double BloomFilterNode::eUnion(BloomFilter *f1, BloomFilter *f2) {
    double dot = 0;
    int *arr1 = f1->getData();
    int *arr2 = f2->getData();
    for (int i=0; i<f1->getSize(); i++) {
        if (arr1[i] == 1 || arr2[i] == 1) {
            dot++;
        }
    }
    return -log(1-dot / (double) f1->getSize()) * f1->getSize()/NUM_HASHES;
}

double BloomFilterNode::eIntersect(BloomFilter *f1, BloomFilter *f2) {
    double union_size = eUnion(f1, f2);
    double e = f1->eSize() + f2->eSize() - union_size;
    return e;
}

void BloomFilterNode::shiftAndInsert(BloomFilter *filter) {
    assert(getCount() < getMax());
    int id = filter->getId();
    int index = indexOfKey(id);
    for (int i=getCount()-1; i>=index; i--) {
        keys[i+1] = keys[i];
        filters[i+1] = filters[i];
    }
    keys[index] = id;
    filters[index] = filter;
    increment();
    return;
}

void BloomFilterNode::insertAsSets(BloomFilter *filter) {
    
    // Compute optimal subset and superset ids for filter
    int subsetId = computeSubsetId(filter);
    int supersetId = computeSupersetId(filter);
    
    // If they are identical: Change id of filter and insert it
    filter->setId(subsetId);
    BloomFilterNode *l = search(subsetId);
    l->insert(filter);
    
    // Else create new BloomFilter with superset id and insert it
    if (subsetId != supersetId) {
        BloomFilter *f = new BloomFilter(*filter);
        f->setId(supersetId);
        BloomFilterNode *l2 = search(supersetId);
        l2->insert(f);
    }
    return;
}

void BloomFilterNode::insert(BloomFilter *filter, BloomFilterNode *oldNode, BloomFilterNode *newNode) {
    assert(false);
}