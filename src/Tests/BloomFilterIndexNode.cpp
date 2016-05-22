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
        int *parentKeys = getKeys();
        cout << "\nParent's new keys:";
        for (int i=0; i<getCount(); i++) {
            cout << " " << parentKeys[i];
        }
        cout << "\nParent's new filters: ";
        for (int i=0; i<getCount(); i++) {
            cout << "|";
            filters[i]->printArr();
        }
        cout << "|" << endl;
        
        C[index] = leftNode;
        C[index+1] = rightNode;
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
            cout << "\nKey to be inserted into parent: " << middle->getId();
            cout << "\nFilter to be inserted into parent: ";
            middle->printArr();
            cout << endl;
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
            
            // Delete dangeling pointers in root
            /* for (int i=p->getMax(); i>p->getCount(); i--) {
                p->C[i] = NULL;
            } */
        }
        else {
            BloomFilterNode *p = getParent();
            s->setParent(p);
            
            // Get middle filter
            BloomFilter *middle = s->filters[0];
            cout << "\nKey to be inserted into parent: " << middle->getId();
            cout << "\nFilter to be inserted into parent: ";
            middle->printArr();
            cout << endl;
            p->insert(middle, this, s);
            
            // Shift right index node's keys and filters
            int *rightIndexKeys = s->getKeys();
            BloomFilter **rightIndexFilters = s->filters;
            for (int i=0; i<s->getCount(); i++) {
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
            
            cout << "\nRight index node's new keys: ";
            for (int i=0; i<s->getCount(); i++) {
                cout << " " << rightIndexKeys[i];
            }
            
            cout << "\nRight index node's new filters: |";
            for (int i=0; i<s->getCount(); i++) {
                s->filters[i]->printArr();
                cout << "|";
            }
            
            cout << "\nRoot's new keys: ";
            for (int i=0; i<p->getCount(); i++) {
                cout << " " << p->getKeys()[i];
            }
            
            cout << "\nRoot's new filters: |";
            for (int i=0; i<p->getCount(); i++) {
                p->filters[i]->printArr();
                cout << "|";
            }
        }
    }
}