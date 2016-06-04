////  BloomFilterLeaf.cpp, Judith Greif
//  Description: Implementation of class BloomFilterLeaf


#include <algorithm>
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
    
    // Update union filters
    updateUnionFilter();
    l->updateUnionFilter();
    
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

void BloomFilterLeaf::updateUnionFilter() {
    
    // Clear union filter
    for (int i=0; i<getFilterSize(); i++) {
        unionfilter->setValue(i, 0);
    }
    
    // Calculate union of all key filters
    BloomFilter *newUnion = unionfilter;
    for (int i=0; i<getCount(); i++) {
        newUnion = newUnion->logicalOr(filters[i]);
    }
    for (int i=0; i<getFilterSize(); i++) {
        unionfilter->setValue(i, newUnion->getData()[i]);
    }
}

void BloomFilterLeaf::insert(BloomFilter *filter) {
    
    // Get Bloom filter values
    if (getCount() < getMax()) {
        shiftAndInsert(filter);
        updateUnionFilter();
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
        p->insert(middle, this, l);
    }    
    
    // Propagate insertion into union filter up to root node
    if (getParent() == NULL) {
        return;
    }
    else {
        getParent()->updateUnionFilter();
    }
}

float BloomFilterLeaf::computeMinJaccard(BloomFilter *filter) {
    float min = 1;
    float jacc;
    for (int i=0; i<getCount(); i++) {
        jacc = computeJaccard(filters[i], filter);
        if (jacc < min) {
            min = jacc;
        }
    }
    return min;
}

int BloomFilterLeaf::computeMinJaccardKey(BloomFilter *filter) {
    int index = 0;
    float min = 1;
    float jacc;
    for (int i=0; i<getCount(); i++) {
        jacc = computeJaccard(filters[i], filter);
        if (jacc < min) {
            min = jacc;
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

vector<BloomFilter> BloomFilterLeaf::collectAllFilters() {
    vector<BloomFilter> result;
    BloomFilterLeaf *tmp = this;
    while (tmp != NULL) {
        for (int i=0; i<tmp->getCount(); i++) {
            result.push_back(*tmp->filters[i]);
        }
        tmp = tmp->getNext();
    }
    return result;
}

int BloomFilterLeaf::computeSubsetId(BloomFilter *filter) {
    vector<pair<int, float>> subsets;
    vector<int> freeIds;
    vector<pair<int, int>> goodIds;
    BloomFilterLeaf *tmp = this;
    float jacc;
    int minId = filters[0]->getId()-1;
    int maxId;
    int optId;
    while (tmp != NULL) {
        
        // Collect all filters argument filter is subset of
        for (int i=0; i<tmp->getCount(); i++) {
            if ((tmp->filters[i])->isSubset(filter)) {
                jacc = computeJaccard(tmp->filters[i], filter);
                subsets.push_back(make_pair(tmp->filters[i]->getId(), jacc));
            }
        }
        maxId = tmp->filters[tmp->getCount()-1]->getId()+1;
        tmp = tmp->getNext();
    }
    
    // Sort subsets by jacc distances in ascending order
    sort(subsets.begin(), subsets.end(), [](const pair<int, float> &left, const pair<int, float> &right) {
        return left.second < right.second;
    });
    
    // Collect free ids
    tmp = this;
    freeIds.push_back(minId);
    freeIds.push_back(maxId);
    while (tmp != NULL) {
        for (int i=0; i<tmp->getCount()-2; i++) {
            for (int j=tmp->filters[i]->getId()+1; j<tmp->filters[i+1]->getId(); j++)
                if (j < tmp->filters[i]->getId()) {
                    freeIds.push_back(j);
                }
            }
        int start = tmp->filters[tmp->getCount()-1]->getId()+1;
        int last;
        if (tmp->getCount() < tmp->getMax()) {
            if (tmp->next != NULL) {
                last = tmp->getNext()->filters[0]->getId();
            }
            else {
                last = start + tmp->getMax() - tmp->getCount()-1;
            }
            for (int j=start; j<last; j++) {
                freeIds.push_back(j);
            }
        }
        tmp = tmp->getNext();
    }
    sort(freeIds.begin(), freeIds.end(), less<int>());
    for (int i=freeIds.size()-2; i>0; i--) {
        if (freeIds[i] == freeIds[i+1]) {
            freeIds.erase(freeIds.begin()+i+1);
        }
    }
    
    // Determine optimal id
    // Check subsets in ascending order
    // Get next greater and smaller id
    int distNeg = subsets[0].first - minId;
    int distPos = maxId - subsets[0].first;
    for (int i=0; i<subsets.size(); i++) {
        optId = subsets[i].first;
        int j=0;
        while ((freeIds[j] < subsets[i].first) && (j<freeIds.size())) {
            if (optId-freeIds[j] < optId-minId) {
                minId = freeIds[j];
                distNeg = optId-minId;
            }
            j++;
        }
        
        // TODO (class BloomFilterTree)
        j=freeIds.size()-1;
        while ((freeIds[j] > subsets[i].first) && (j>=0)) {
            if (freeIds[j]-optId < maxId-optId) {
                maxId = freeIds[i];
                distPos = maxId-optId;
            }
            j--;
        }
        goodIds.push_back(make_pair(minId, distNeg));
        goodIds.push_back(make_pair(maxId, distPos));
    }
    
    // Sort next smaller and greater ids by numerical distance in ascending order
    sort(goodIds.begin(), goodIds.end(), [](const pair<int, int> &left, const pair<int, int> &right) {
        return left.second < right.second;
    });
    
    // Return first element in list
    return goodIds[0].first;
}