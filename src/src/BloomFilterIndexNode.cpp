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

BloomFilterNode * BloomFilterIndexNode::search(int k) {
    int index = indexOfKey(k);
    return C[index]->search(k);
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

float BloomFilterIndexNode::computeMinJaccard(BloomFilter *filter) {
    float min = 1;
    float jacc;
    for (int i=0; i<getCount()+1; i++) {
        jacc = C[i]->computeMinJaccard(filter);
        if (jacc < min) {
            min = jacc;
        }
    }
    return min;
}

int BloomFilterIndexNode::computeMinJaccardKey(BloomFilter *filter) {
    int index = 0;
    float min = 1;
    float jacc;
    for (int i=0; i<getCount()+1; i++) {
        jacc = C[i]->computeMinJaccard(filter);
        if (jacc < min) {
            min = jacc;
            index = i;
        }
    }
    return C[index]->computeMinJaccardKey(filter);
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

BloomFilter * BloomFilterIndexNode::simpleSimQuery(BloomFilter *filter) {
    int index = 0;
    float max = 0;
    float jacc;
    for (int i=0; i<getCount()+1; i++) {
        jacc = C[i]->computeMinJaccard(filter);
        if (jacc > max) {
            max = jacc;
            index = i;
        }
    }
    return C[index]->simpleSimQuery(filter); 
}

BloomFilter *BloomFilterIndexNode::simQuery(BloomFilter *filter) {
    int index = 0;
    float max = 0;
    float jacc;
    float bestMax1 = 0;
    float bestMax2 = 0;
    float bestJacc1;
    float bestJacc2;
    for (int i=0; i<getCount(); i++) {
        jacc = computeJaccard(filters[i], filter);
        if (jacc > max) {
            max = jacc;
            index = i;
        }
    }
    for (int i=0; i<C[index]->getCount(); i++) {
        bestJacc1 = C[index]->computeJaccard(C[index]->filters[i], filter);
        if (bestJacc1 > bestMax1) {
            bestMax1 = bestJacc1;
        }
    }
    for (int i=0; i<C[index+1]->getCount(); i++) {
        bestJacc2 = C[index+1]->computeJaccard(C[index+1]->filters[i], filter);
        if (bestJacc2 > bestMax2) {
            bestMax2 = bestJacc2;
        }
    }
    
    // Decide which child is better
    // Follow bigger child pointer if both are equally good
    if (bestMax1 > bestMax2) {
        return C[index]->simQuery(filter);
    }
    else {
        return C[index+1]->simQuery(filter);
    }
}

vector<BloomFilter> BloomFilterIndexNode::simpleSimQueryVec(BloomFilter *filter, int k) {
 
    // Select correct child
    int index = 0;
    float max = 0;
    float jacc;
    for (int i=0; i<getCount()+1; i++) {
        jacc = C[i]->computeMinJaccard(filter);
        if (jacc > max) {
            max = jacc;
            index = i;
        }
    }
    return C[index]->simpleSimQueryVec(filter, k); 
}

vector<BloomFilter> BloomFilterIndexNode::simQueryVec(BloomFilter *filter, int k) {
    int index = 0;
    float max = 0;
    float jacc;
    float bestMax1 = 0;
    float bestMax2 = 0;
    float bestJacc1;
    float bestJacc2;
    for (int i=0; i<getCount(); i++) {
        jacc = computeJaccard(filters[i], filter);
        if (jacc > max) {
            max = jacc;
            index = i;
        }
    }
    for (int i=0; i<C[index]->getCount(); i++) {
        bestJacc1 = C[index]->computeJaccard(C[index]->filters[i], filter);
        if (bestJacc1 > bestMax1) {
            bestMax1 = bestJacc1;
        }
    }
    for (int i=0; i<C[index+1]->getCount(); i++) {
        bestJacc2 = C[index+1]->computeJaccard(C[index+1]->filters[i], filter);
        if (bestJacc2 > bestMax2) {
            bestMax2 = bestJacc2;
        }
    }
    if (bestMax1 > bestMax2) {
        return C[index]->simQueryVec(filter, k);
    }
    else {
        return C[index+1]->simQueryVec(filter, k);
    }
}