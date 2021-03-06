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

double BloomFilterIndexNode::computeMinJaccard(BloomFilter *filter) {
    return C[0]->computeMinJaccard(filter);
}

double BloomFilterIndexNode::computeMaxJaccard(BloomFilter *filter) {
    return C[0]->computeMaxJaccard(filter); 
}

int BloomFilterIndexNode::getMinJaccardKey(BloomFilter *filter) {
    return C[0]->getMinJaccardKey(filter);
}

void BloomFilterIndexNode::updateUnionFilter() {
    
    // Clear union filter
    for (int i=0; i<getFilterSize(); i++) {
        unionfilter->setValue(i, 0);
    }
    
    // Calculate union of all children union filters
    BloomFilter *newUnion = unionfilter;
    for (int i=0; i<getCount()+1; i++) {
        newUnion = newUnion->logicalOr(C[i]->unionfilter);
    }
    for (int i=0; i<getFilterSize(); i++) {
        unionfilter->setValue(i, newUnion->getData()[i]);
    }
}

BloomFilter * BloomFilterIndexNode::getMinJaccardFilter(BloomFilter *filter) {
    return C[0]->getMinJaccardFilter(filter);
}

int BloomFilterIndexNode::getMinKey() {
    return C[0]->getMinKey();
}

int BloomFilterIndexNode::getMaxKey() {
    return C[getCount()]->getMaxKey();
}

vector<BloomFilter> BloomFilterIndexNode::collectAllFilters() {
    return C[0]->collectAllFilters();
}

int BloomFilterIndexNode::countFilters() {
    return C[0]->countFilters();
}

int BloomFilterIndexNode::computeSubsetId(BloomFilter *filter) {
    return C[0]->computeSubsetId(filter);
}

int BloomFilterIndexNode::computeSupersetId(BloomFilter *filter) {
    return C[0]->computeSupersetId(filter);
}

// Return false if k is not in leaf of subtree, true otherwise
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

BloomFilterNode * BloomFilterIndexNode::search(int k) {
    int index = indexOfKey(k);
    return C[index]->search(k);
}

BloomFilterIndexNode * BloomFilterIndexNode::split(BloomFilter *filter, BloomFilterNode *left, BloomFilterNode *right, int &middle) {
    assert(getCount() == getMax());
    
    int *keys = getKeys();
    int max = getMax();
    int *merged = new int[max+1];
    
    BloomFilter **mergedFilters = new BloomFilter *[max+1];
    BloomFilterNode **mergedNodes = new BloomFilterNode *[max+2];
    
    int id = filter->getId();
    int index = indexOfKey(id);
    
    // Merge keys, filters and children together
    for (int i=0; i<index; i++) {
        merged[i] = keys[i];
        mergedFilters[i] = filters[i];
        mergedNodes[i] = C[i];
    }
    
    merged[index] = id;
    mergedFilters[index] = filter;
    mergedNodes[index] = left;
    mergedNodes[index+1] = right;
    
    for (int i=index+1; i<max+1; i++) {
        merged[i] = keys[i-1];
        mergedFilters[i] = filters[i-1];
        mergedNodes[i+1] = C[i];
    }
    
    BloomFilterIndexNode *s = new BloomFilterIndexNode(getOrder(), getFilterSize());
    
    int half = (max+1)/2;
    middle = merged[half];
    setCount(half);
    
    for (int i=0; i<half; i++) {
        keys[i] = merged[i];
        filters[i] = mergedFilters[i];
        C[i] = mergedNodes[i];
    }
    C[half] = mergedNodes[half];
    
    int *newNodeKeys = s->getKeys();
    
    // Hand over filters and children to new sibling
    for (int i=half+1; i<max+2; i++) {
        s->C[i-(half+1)] = mergedNodes[i];
        s->C[i-(half+1)]->setParent(s);
    }
    for (int i=half; i<max+1; i++) {
        newNodeKeys[i-half] = merged[i];
        s->filters[i-half] = mergedFilters[i];
        s->increment();
    }
    int pos = s->getCount()+1;
    s->C[pos] = mergedNodes[max+1];
    s->C[pos]->setParent(s);
    
    // Delete filters and children that have been handed over
    for (int i=half+1; i<max+1; i++) {
        C[i] = NULL;
    }
    for (int i=half; i<max; i++) {
        filters[i] = NULL;
    }
    
    // Update union filter
    updateUnionFilter(); 
    
    delete[] merged;
    delete[] mergedNodes;
    return s;
}

int BloomFilterIndexNode::countUnionFilters() {
    int res = 1;
    int childrenCount = getCount()+1;
    for (int i=0; i<childrenCount; i++) {
        res += C[i]->countUnionFilters();
    }
    return res;
}

int BloomFilterIndexNode::countComparisons(BloomFilter *filter) {
    double min = 1;
    double jacc;
    BloomFilterNode *path = C[0];
    bool set = false;
    int last;
    int res = 0;
    
    // Check if query filter is subset or superset of any child's union filter
    // If more than one: Determine best result
    for (int i=0; i<getCount()+1; i++) {
        if (C[i]->unionfilter->isSubset(filter)) {
            set = true;
            jacc = computeJaccard(C[i]->unionfilter, filter);
            if (jacc < min) {
                min = jacc;
                path = C[i];
            }
            res++;
        }
        res++;
        if (C[i]->unionfilter->isSuperset(filter)) {
            set = true;
            jacc = computeJaccard(C[i]->unionfilter, filter);
            if (jacc < min) {
                min = jacc;
                path = C[i];
            }
            res++; 
        }
        res++;
    }
    
    // If both false: Conduct normal subtree query
    res++;
    if (set == false) {
        if (getParent() != NULL) {
            last = getParent()->getKeys()[getParent()->getCount()-1];
        }
        else {
            last = getKeys()[getCount()-1];
        }
        last = getKeys()[getCount()-1];
        return res + path->allComparisons(filter, last);
    }
    else {
        return res + path->countComparisons(filter);
    }
}

int BloomFilterIndexNode::allComparisons(BloomFilter *filter, int last) {
    int res = 0;
    int childrenCount = getCount()+1;
    for (int i=0; i<childrenCount; i++) {
        res += C[i]->allComparisons(filter, last);
    }
    return res; 
}

int BloomFilterIndexNode::countLeaves() {
    return C[0]->countLeaves();
}

int BloomFilterIndexNode::countVecComparisons(BloomFilter *filter, int k) {
    double min = 1;
    double jacc;
    BloomFilterNode *path = C[0];
    bool set = false;
    int last;
    int res = 0;
    
    // Check if query filter is subset or superset of children's union filters
    // If more than one: Determine best result
    for (int i=0; i<getCount(); i++) {
        if (C[i]->unionfilter->isSubset(filter)) {
            set = true;
            jacc = computeJaccard(C[i]->unionfilter, filter);
            if (jacc < min) {
                min = jacc;
                path = C[i];
            }
            res++;
        }
        res++;
        if (C[i]->unionfilter->isSuperset(filter)) {
            set = true;
            jacc = computeJaccard(C[i]->unionfilter, filter);
            if (jacc < min) {
                min = jacc;
                path = C[i];
            }
            res++;
        }
        res++;
    }
    
    // If both false: Conduct normal subtree query
    res++;
    if (set == false) {
        res++;
        if (getParent() != NULL) {
            last = getParent()->getKeys()[getParent()->getCount()-1];
        }
        else {
            last = getKeys()[getCount()-1];
        }
        return res + path->allVecComparisons(filter, k, last);
    }
    else {
        return res + path->countVecComparisons(filter, k);
    }
}

int BloomFilterIndexNode::allVecComparisons(BloomFilter *filter, int k, int l) {
    int res = 0;
    int childrenCount = getCount()+1;
    for (int i=0; i<childrenCount; i++) {
        res += C[i]->allVecComparisons(filter, k, l);
    }
    return res;
}

void BloomFilterIndexNode::shiftAndInsert(BloomFilter *filter) {
    int id = filter->getId();
    int index = indexOfKey(id);
    BloomFilterNode::shiftAndInsert(filter);
    for (int i=getCount()-1; i>index; i--) {
        C[i+1] = C[i];
    }
}

void BloomFilterIndexNode::insert(BloomFilter *filter) {
    int id = filter->getId();
    BloomFilterNode *l = search(id);
    l->insert(filter);
}


void BloomFilterIndexNode::insert(BloomFilter *filter, BloomFilterNode *leftNode, BloomFilterNode *rightNode) {
    
    int id = filter->getId();
    
    if (getCount()<getMax()) {
        int index = indexOfKey(id);
        shiftAndInsert(filter);
        C[index] = leftNode;
        C[index+1] = rightNode;
        updateUnionFilter();
    }
    else {
        int mid;
        BloomFilterIndexNode *s = split(filter, leftNode, rightNode, mid);
        if (getParent() == NULL) {
            BloomFilterIndexNode *p = new BloomFilterIndexNode(getOrder(), getFilterSize());
            p->C[0] = this;
            p->C[1] = s;
            setParent(p);
            s->setParent(p);
            
            // Get middle filter
            BloomFilter *middle = s->filters[0];
            p->insert(middle, this, s);
            
            // Shift right index node's keys and filters
            int *rightIndexKeys = s->getKeys();
            BloomFilter **rightIndexFilters = s->filters;
            for (int i=1; i<s->getCount(); i++) {
                rightIndexKeys[i-1] = rightIndexKeys[i];
                rightIndexFilters[i-1] = rightIndexFilters[i];
            }
            
            // Adjust filters and children in right index node
            rightIndexFilters[s->getCount()-1] = NULL;
            s->decrement();
            for (int i=s->getMax(); i>s->getCount(); i--) {
                s->C[i] = NULL;
            }
            for (int i=s->getMax()-1; i>s->getCount()-1; i--) {
                s->filters[i] = NULL;
            }
        }
        else {
            BloomFilterNode *p = getParent();
            s->setParent(p);
            
            // Get middle filter
            BloomFilter *middle = s->filters[0];
            p->insert(middle, this, s);
            
            // Shift right index node's keys and filters
            int *rightIndexKeys = s->getKeys();
            BloomFilter **rightIndexFilters = s->filters;
            for (int i=1; i<s->getCount(); i++) {
                rightIndexKeys[i-1] = rightIndexKeys[i];
                rightIndexFilters[i-1] = rightIndexFilters[i];
            }
            
            // Adjust keys and filters in right index node
            rightIndexFilters[s->getCount()-1] = NULL;
            s->decrement();
            for (int i=s->getMax(); i>s->getCount(); i--) {
                s->C[i] = NULL;
            }
            for (int i=s->getMax()-1; i>s->getCount()-1; i--) {
                s->filters[i] = NULL;
            }
            
        }
        
        // Update union filters
        s->updateUnionFilter();
        getParent()->updateUnionFilter();
    }
}

BloomFilter * BloomFilterIndexNode::simQuery(BloomFilter *filter) {
    double min = 1;
    double jacc;
    BloomFilterNode *path = C[0];
    bool set = false;
    int last;
    
    // Check if query filter is subset or superset of any child's union filter
    // If more than one: Determine best result
    for (int i=0; i<getCount()+1; i++) {
        if (C[i]->unionfilter->isSubset(filter)) {
            set = true;
            jacc = computeJaccard(C[i]->unionfilter, filter);
            if (jacc < min) {
                min = jacc;
                path = C[i];
            }
        }
        if (C[i]->unionfilter->isSuperset(filter)) {
            set = true;
            jacc = computeJaccard(C[i]->unionfilter, filter);
            if (jacc < min) {
                min = jacc;
                path = C[i];
            }
        }
    }
    
    // If both false: Conduct normal subtree query
    if (set == false) {
        if (getParent() != NULL) {
            last = getParent()->getKeys()[getParent()->getCount()-1];
        }
        else {
            last = getKeys()[getCount()-1];
        }
        return path->simSubtreeQuery(filter, last);
    }
    else {
        return path->simQuery(filter);
    }
}

BloomFilter * BloomFilterIndexNode::simSubtreeQuery(BloomFilter *filter, int l) {
    return C[0]->simSubtreeQuery(filter, l);
}

vector<BloomFilter*> BloomFilterIndexNode::simQueryVec(BloomFilter *filter, int k) {
    double min = 1;
    double jacc;
    BloomFilterNode *path = C[0];
    bool set = false;
    int last;
    
    // Check if query filter is subset or superset of childrens' union filters
    // If more than one: Determine best result
    for (int i=0; i<getCount(); i++) {
        if (C[i]->unionfilter->isSubset(filter)) {
            set = true;
            jacc = computeJaccard(C[i]->unionfilter, filter);
            if (jacc < min) {
                min = jacc;
                path = C[i];
            }
        }
        if (C[i]->unionfilter->isSuperset(filter)) {
            set = true;
            jacc = computeJaccard(C[i]->unionfilter, filter);
            if (jacc < min) {
                min = jacc;
                path = C[i];
            }
        }
    }
    
    // If both false: Conduct normal subtree query
    if (set == false) {
        if (getParent() != NULL) {
            last = getParent()->getKeys()[getParent()->getCount()-1];
        }
        else {
            last = getKeys()[getCount()-1];
        }
        return path->simSubtreeQueryVec(filter, k, last);
    }
    else {
        return path->simQueryVec(filter, k);
    }
}

vector <BloomFilter*> BloomFilterIndexNode::simSubtreeQueryVec(BloomFilter *filter, int k, int l) {
    return C[0]->simSubtreeQueryVec(filter, k, l); 
}