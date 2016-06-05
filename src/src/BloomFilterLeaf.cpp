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

int BloomFilterLeaf::countFilters() {
    int result = 0;
    BloomFilterLeaf *tmp = this;
    while (tmp != NULL) {
        result+=tmp->getCount();
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
    bool no_subsets = true;
    while (tmp != NULL) {
        
        // Collect all filters that filter is subset of
        for (int i=0; i<tmp->getCount(); i++) {
            if ((tmp->filters[i])->isSubset(filter)) {
                jacc = computeJaccard(tmp->filters[i], filter);
                subsets.push_back(make_pair(tmp->filters[i]->getId(), jacc));
                no_subsets = false;
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
            for (int j=tmp->filters[i]->getId()+1; j<tmp->filters[i+1]->getId(); j++) {
                if (j<tmp->filters[i+1]->getId()) {
                    freeIds.push_back(j);
                }
            }
            if (tmp->getCount() < tmp->getMax()) {
                if (tmp->getNext() != NULL) {
                    int start = tmp->filters[tmp->getCount()-1]->getId()+1;
                    int last = tmp->getNext()->filters[0]->getId();
                    for (int j=start; j<last; j++) {
                        freeIds.push_back(j);
                    }
                }
            }
            
        }
        tmp = tmp->getNext();
    }
    sort(freeIds.begin(), freeIds.end(), less<int>());
    
    // If there are no subsets, just return smallest free id as pair with numerical distance 0
    if (no_subsets == false) {
        
        // Determine optimal id
        // Check subsets in ascending order
        // Get next greater and smaller id
        int distNeg = subsets[0].first - minId;
        int distPos = maxId - subsets[0].first;
        for (int i=0; i<subsets.size(); i++) {
            optId = subsets[i].first;
            int j=0;
            while (freeIds[j] < subsets[i].first) {
                if (optId-freeIds[j] < optId-minId) {
                    minId = freeIds[j];
                    distNeg = optId-minId;
                }
                j++;
            }
            
            j=freeIds.size()-1;
            while (freeIds[j] > subsets[i].first) {
                if (freeIds[j]-optId < maxId-optId) {
                    maxId = freeIds[j];
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
    }
    else {
        goodIds.push_back(make_pair(freeIds[0], 0));
    }
        
    // Return first element
    return goodIds[0].first;
}

int BloomFilterLeaf::computeSupersetId(BloomFilter *filter) {
    vector<pair<int, float>> supersets;
    vector<int> freeIds;
    vector<pair<int, int>> goodIds;
    BloomFilterLeaf *tmp = this;
    float jacc;
    int minId = filters[0]->getId()-1;
    int maxId;
    int optId;
    bool no_supersets = true;
    while (tmp != NULL) {
        
        // Collect all filters that filter is superset of
        for (int i=0; i<tmp->getCount(); i++) {
            if (filter->isSuperset(tmp->filters[i])) {
                jacc = computeJaccard(tmp->filters[i], filter);
                supersets.push_back(make_pair(tmp->filters[i]->getId(), jacc));
                no_supersets = false;
            }
        }
        maxId = tmp->filters[tmp->getCount()-1]->getId()+1;
        tmp = tmp->getNext();
    }
    
    // Sort supersets by jacc distance in ascending order
    sort(supersets.begin(), supersets.end(), [](const pair<int, float> &left, const pair<int, float> &right) {
        return left.second < right.second;
    });
    
    // Collect free ids
    tmp = this;
    freeIds.push_back(minId);
    freeIds.push_back(maxId);
    while (tmp != NULL) {
        for (int i=0; i<tmp->getCount()-2; i++) {
            for (int j=tmp->filters[i]->getId()+1; j<tmp->filters[i+1]->getId(); j++) {
                if (j<tmp->filters[i+1]->getId()) {
                    freeIds.push_back(j);
                }
            }
            if (tmp->getCount() < tmp->getMax()) {
                if (tmp->getNext() != NULL) {
                    int start = tmp->filters[tmp->getCount()-1]->getId()+1;
                    int last = tmp->getNext()->filters[0]->getId();
                    for (int j=start; j<last; j++) {
                        freeIds.push_back(j);
                    }
                }
            }
        }
        tmp = tmp->getNext();
    }
    sort(freeIds.begin(), freeIds.end(), less<int>());
    
    // If there are no supersets, just return smallest id as pair with numerical distance 0
    if (no_supersets == false) {
        
        // Determine optimal id
        // Check supersets in ascending order
        // Get next greater and smaller id
        int distNeg = supersets[0].first - minId;
        int distPos = maxId - supersets[0].first;
        for (int i=0; i<supersets.size(); i++) {
            optId = supersets[i].first;
            int j=0;
            while ((freeIds[j] < supersets[i].first) && j<freeIds.size()) {
                if (optId-freeIds[i] < optId - minId) {
                    minId = freeIds[j];
                    distNeg = optId-minId;
                }
                j++;
            }
            
            j=freeIds.size()-1;
            while (freeIds[j] > supersets[i].first) {
                if (freeIds[j]-optId < maxId-optId) {
                    maxId = freeIds[j];
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
    }
    
    else {
        goodIds.push_back(make_pair(freeIds[0], 0));
    }
    
    // Return first element
    return goodIds[0].first;
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

BloomFilter * BloomFilterLeaf::simQuery(BloomFilter *filter) {
    
    // Check if leaf has only one filter
    if (getCount() == 0) {
        return filters[0];
    }
    else {
        // Find filter with smallest jacc distance
        float jacc;
        float min = 1;
        BloomFilter *result = filters[0];
        for (int i=0; i<getCount(); i++) {
            if (computeJaccard(filters[i], filter) < min) {
                min = jacc;
                result = filters[i];
            }
        }
        return result;
    }
}