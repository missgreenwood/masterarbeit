////  BloomFilterLeaf.cpp, Judith Greif
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
        /* cout << "\nKey to be inserted into parent: " << middle->getId();
        cout << "\nFilter to be inserted into parent: ";
        middle->printArr();
        cout << endl; */ 
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

// Function to return Bloom filter vector with k highest Jaccard coefficients in tree  
// If tree holds less than k filters, return them all sorted by Jaccard coefficient in descending order
vector<BloomFilter> BloomFilterLeaf::simpleSimQueryVec(BloomFilter *filter, int k) {
    vector<BloomFilter> results(k);
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
    results[0] = *filters[index];
    cout << "\nNearest neighbor: " << results[0].getId() << " (";
    results[0].printArr();
    cout << ")\n";
    
    // Determine k-1 nearest neighbors
    // Collect k-1 candidates with greater keys
    int *ids = new int[(k-1)*2];
    float *coefficients = new float[(k-1)*2];
    BloomFilter **candidates = new BloomFilter *[(k-1)*2];
    int count = 1;
    int first = 0;
    for (int i=0; i<k-1; i++) {
        if (getKeys()[index+1+i]) {
            candidates[i] = filters[index+1+i];
            count++;
        }
        
        // Evtl. TODO
        else if (next) {
            BloomFilterLeaf *tmp = next;
            while (tmp && count<k-1) {
                for (int j=0; j<tmp->getCount(); j++) {
                    candidates[i] = tmp->filters[first];
                    first++;
                    count++;
                }
                if (tmp->next) {
                    tmp = tmp->next;
                    first = 0;
                }
            }
        }
    }
    
    // Collect k-1 candidates with smaller keys
    for (int i=0; i<k-1; i++) {
        first = 0;
        if (getKeys()[index-1+i]) {
            candidates[count-1+i] = filters[index-1-i];
            count++;
        }
        
        // Evtl. TODO
        else if (prev) {
            BloomFilterLeaf *tmp = prev;
            while (tmp && count<(k-1)*2) {
                for (int j=0; j<tmp->getCount(); j++) {
                    candidates[count+i] = tmp->filters[first];
                    first++;
                    count++;
                }
                if (tmp->prev) {
                    tmp = tmp->prev;
                    first = 0;
                }
            }
        }
    }

    first = 0;
    // cout << "Candidates with greater keys: ";
    for (int i=first; i<k-1; i++) {
        if (candidates[i]) {
            // cout << candidates[i]->getId() << " ";
            first++; 
        }
    }
    
    // cout << "\nCandidates with smaller keys: ";
    for (int i=first; i<(k-1)*2; i++) {
        if (candidates[i]) {
            // cout << candidates[i]->getId() << " ";
        }
    }
    
    // Determine k-1 best candidates
    for (int i=0; i<(k-1)*2; i++) {
        if (candidates[i]) {
            coefficients[i] = computeJaccard(candidates[i], filter);
            ids[i] = candidates[i]->getId();
        }
    }
    
    cout << "Jaccard coefficients of candidates:\n";
    for (int i=0; i<(k-1)*2; i++) {
        if (coefficients[i]) {
            cout << coefficients[i] << " (" << ids[i] << ")\n";
        }
    }
    
    index = 0;
    int key = 0;
    for (int i=0; i<k-1; i++) {
        max = 0;
        for (int j=0; j<count-1; j++) {
            if (coefficients[j] > max) {
                max = coefficients[j];
                key = ids[j];
                index = j;
            }
        }
        // cout << "New maximum: " << max << " (" << key << ")" << endl;
        results[i+1] = *candidates[index];
        coefficients[index] = 0;
    }
    
    cout << "Result vector: ";
    for (int i=0; i<results.size()-1; i++) {
        cout << results[i].getId() << ", ";
    }
    cout << results[results.size()-1].getId();
    return results;
}

// TODO
vector<BloomFilter> BloomFilterLeaf::simQueryVec(BloomFilter *filter, int k) {
    vector<BloomFilter> results;
    return results; 
}