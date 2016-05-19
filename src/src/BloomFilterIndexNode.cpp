//  BloomFilterIndexNode.cpp, Judith Grei
//  Description: Implementation of class BloomFilterIndexNode

#include "BloomFilterIndexNode.hpp"

using namespace std;


BloomFilterIndexNode::BloomFilterIndexNode(int _t, int _s): BloomFilterNode(_t, _s) {
    C = new BloomFilterNode *[2*_t+1];
    for (int i=0; i<2*_t+1; i++) {
        C[i] = NULL; 
    }
}

BloomFilterIndexNode::~BloomFilterIndexNode() {
    delete[] C;
}

BloomFilterNode * BloomFilterIndexNode::search(int k) {
    int index = indexOfKey(k);
    return C[index]->search(k);
}

void BloomFilterIndexNode::shiftAndInsert(BloomFilter *filter) {
    int id = filter->getId();
    int index = indexOfKey(id);
    BloomFilterNode::shiftAndInsert(filter);
    for (int i=getCount()-1; i>index; i--) {
        C[i+1] = C[i];
    }
}

void BloomFilterIndexNode::shiftAndInsertKey(int k) {
    int index = indexOfKey(k);
    BloomFilterNode::shiftAndInsertKey(k);
    for (int i=getCount()-1; i>index; i--) {
        C[i+1] = C[i];
    }
}

void BloomFilterIndexNode::insert(BloomFilter *filter) {
    int id = filter->getId();
    BloomFilterNode *l = search(id);
    l->insert(filter);
}

void BloomFilterIndexNode::insertKey(int k) {
    BloomFilterNode *l = search(k);
    l->insertKey(k); 
}

// TODO
void BloomFilterIndexNode::insertSimilarFilter(BloomFilter *filter) {
    
}

// Evtl. TODO
void BloomFilterIndexNode::insert(BloomFilter *filter, BloomFilterNode *leftNode, BloomFilterNode *rightNode) {
    int id = filter->getId();
    if (getCount()<getMax()) {
        int index = indexOfKey(id);
        shiftAndInsert(filter);
        C[index] = leftNode;
        C[index+1] = rightNode;
    }
    else {
        int mid;
        BloomFilterIndexNode *s = split(filter, leftNode, rightNode, mid);
        BloomFilterNode *p = getParent();
        if (p == NULL) {
            p = new BloomFilterIndexNode(getOrder(), getFilterSize());
            setParent(p);
        }
        s->setParent(p);
        int correctId = filter->getId();
        filter->setId(mid);
        p->insert(filter, this, s);
        filter->setId(correctId); 
    }
}

void BloomFilterIndexNode::insertKey(int k, BloomFilterNode *leftNode, BloomFilterNode *rightNode) {
    if (getCount()<getMax()) {
        int index = indexOfKey(k);
        shiftAndInsertKey(k);
        C[index] = leftNode;
        C[index+1] = rightNode;
    }
    else {
        int mid;
        BloomFilterIndexNode *s = splitKey(k, leftNode, rightNode, mid);
        BloomFilterNode *p = getParent();
        if (p == NULL) {
            p = new BloomFilterIndexNode(getOrder(), getFilterSize());
            setParent(p);
            int *rootKeys = p->getKeys();
            rootKeys[0] = mid;
            p->increment(); 
            return;
        }
        s->setParent(p);
        p->insertKey(mid, this, s);        
    }
}


// Returns false if k is not in leaf of subtree
// Returns true if k is in leaf of subtree
bool BloomFilterIndexNode::contains(int k) {
    int i=0;
    while (getKeys()[i]<k && i<getCount()-1) {
        i++;
    }
    if (k<getKeys()[i]) {
        return C[i]->contains(k);
    }
    else if (k>=getKeys()[i] && C[i+1]) {
        return C[i+1]->contains(k);
    }
    else return false;
}

// TODO 
int ** BloomFilterIndexNode::getFilters() {
    assert(false);
}

BloomFilterIndexNode * BloomFilterIndexNode::split(BloomFilter *filter, BloomFilterNode *left, BloomFilterNode *right, int &middle) {
    assert(getCount() == getMax());
    int max = getMax();
    int id = filter->getId();
    int *merged = new int[max+1];
    int index = indexOfKey(id);
    int *keys = getKeys();
    BloomFilterNode **mergedNodes = new BloomFilterNode *[max+2];
    for (int i=0; i<index; i++) {
        merged[i] = keys[i];
        mergedNodes[i] = C[i];
    }
    
    merged[index] = id;
    mergedNodes[index] = left;
    mergedNodes[index+1] = right;
    
    for (int i=index+1; i<max+1; i++) {
        merged[i] = keys[i-1];
        mergedNodes[i+1] = C[i];
    }
    
    int half = (max+1)/2; // max+1 immer ungerade
    middle = merged[half];
    for (int i=0; i<half; i++) {
        keys[i] = merged[i];
        C[i] = mergedNodes[i];
    }
    C[half] = mergedNodes[half];
    for (int i=half+1; i<max+1; i++) {
        C[i] = NULL;
    }
    setCount(half);
    BloomFilterIndexNode *s = new BloomFilterIndexNode(getOrder(), getFilterSize());
    int *sKeys = s->getKeys();
    BloomFilterNode **sChildren = s->C;
    for (int i=half+1; i<max+2; i++) {
        sKeys[i-(half+1)] = merged[i];
        sChildren[i-(half+1)] = mergedNodes[i];
        sChildren[i-(half+1)]->setParent(s);
        s->increment();
    }
    int pos = s->getCount()+1;
    sChildren[pos] = mergedNodes[max+2];
    sChildren[pos]->setParent(s);
    delete[] merged;
    delete[] mergedNodes;
    return s;
}

BloomFilterIndexNode * BloomFilterIndexNode::splitKey(int k, BloomFilterNode *left, BloomFilterNode *right, int &middle) {
    assert(getCount() == getMax());
    int max = getMax();
    int *merged = new int[max+1];
    int index = indexOfKey(k);
    int *keys = getKeys();
    BloomFilterNode **mergedNodes = new BloomFilterNode *[max+2];
    for (int i=0; i<index; i++) {
        merged[i] = keys[i];
        mergedNodes[i] = C[i];
    }
    
    merged[index] = k;
    mergedNodes[index] = left;
    mergedNodes[index+1] = right;
    
    for (int i=index+1; i<max+1; i++) {
        merged[i] = keys[i-1];
        mergedNodes[i+1] = C[i];
    }
    
    int half = (max+1)/2; // max+1 immer ungerade
    middle = merged[half];
    for (int i=0; i<half; i++) {
        keys[i] = merged[i];
        C[i] = mergedNodes[i];
    }
    C[half]=mergedNodes[half];
    for (int i=half+1; i<max+1; i++) {
        C[i] = NULL;
    }
    setCount(half);
    BloomFilterIndexNode *s = new BloomFilterIndexNode(getOrder(), getFilterSize());
    int *sKeys = s->getKeys();
    BloomFilterNode **sChildren = s->C;
    for (int i=half+1; i<max+2; i++) {
        sKeys[i-(half+1)] = merged[i];
        sChildren[i-(half+1)] = mergedNodes[i];
        sChildren[i-(half+1)]->setParent(s);
        s->increment();
    }
    int pos = s->getCount()+1;
    sChildren[pos] = mergedNodes[max+2];
    sChildren[pos]->setParent(s);
    delete[] merged;
    delete[] mergedNodes;
    return s;
}

void BloomFilterIndexNode::traverse() {
    for (int i=0; i<getCount()+1; i++) {
        C[i]->traverse();
    }
}

void BloomFilterIndexNode::traverseFilters() {
    for (int i=0; i<getCount()+1; i++) {
        C[i]->traverseFilters();
    }
}
