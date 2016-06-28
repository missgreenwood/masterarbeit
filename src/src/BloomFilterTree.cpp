//  BloomFilterTree.cpp, Judith Greif
//  Description: Implementation of class BloomFilterTree

#include <algorithm>
#include "BloomFilterTree.hpp"


// Constructor with parameters order and size
// Initializes tree as empty
BloomFilterTree::BloomFilterTree(int _t, int _s): t(_t), filtersize(_s), root(NULL) {}

BloomFilterTree::~BloomFilterTree() {
    delete root;
}

// Determine if key is present in tree
// Return false otherwise
bool BloomFilterTree::contains(int k) {
    
    // If tree is empty return false
    if (root == NULL) {
        cout << "Tree is empty!\n";
        return false;
    }
    else {
        return root->contains(k);
    }
}

BloomFilterNode * BloomFilterTree::search(int k) {
    if (root == NULL) {
        cout << "Tree is empty!\n";
        return NULL;
    }
    else return root->search(k);
}

BloomFilterNode * BloomFilterTree::getRoot() {
    return root;
}

void BloomFilterTree::traverse() {
    if (root == NULL) {
        cout << "Tree is empty!\n";
        return;
    }
    else {
        root->traverse();
    }
}

void BloomFilterTree::traverseFilters() {
    if (root == NULL) {
        cout << "Tree is empty!\n";
        return;
    }
    else {
        root->traverseFilters(); 
    }
}

double BloomFilterTree::computeMinJaccard(BloomFilter *filter) {
    if (root == NULL) {
        cout << "Tree is empty!\n";
        return 0;
    }
    else {
        return root->computeMinJaccard(filter);
    }
}

double BloomFilterTree::computeMaxJaccard(BloomFilter *filter) {
    if (root == NULL) {
        cout << "Tree is empty!\n";
        return 0;
    }
    else {
        return root->computeMaxJaccard(filter); 
    }
}

int BloomFilterTree::getMinJaccardKey(BloomFilter *filter) {
    if (root == NULL) {
        cout << "Tree is empty!\n";
        return filter->getId();
    }
    else {
        return root->getMinJaccardKey(filter); 
    }
}

BloomFilter * BloomFilterTree::getMinJaccardFilter(BloomFilter *filter) {
    if (root == NULL) {
        cout << "Tree is empty!\n";
        return filter;
    }
    else {
        return root->getMinJaccardFilter(filter);
    }
}

int BloomFilterTree::getMinKey() {
    if (root == NULL) {
        cout << "Tree is emtpy!\n";
        return 0;
    }
    else {
        return root->getMinKey();
    }
}

int BloomFilterTree::getMaxKey() {
    if (root == NULL) {
        cout << "Tree is empty!";
        return 0;
    }
    else {
        return root->getMaxKey(); 
    }
}

// Compute best subset id for filter
// Treat filter as subset of tree filters
int BloomFilterTree::computeSubsetId(BloomFilter *filter) {
    if (root == NULL) {
        cout << "Tree is empty!";
        return filter->getId();
    }
    else {
        return root->computeSubsetId(filter); 
    }
}

// Compute best superset id for filter
// Treat filter as superset of tree filters
int BloomFilterTree::computeSupersetId(BloomFilter *filter) {
    if (root == NULL) {
        cout << "Tree is empty!\n";
        return filter->getId();
    }
    else {
        return root->computeSupersetId(filter); 
    }
}
    

vector<BloomFilter> BloomFilterTree::collectAllFilters() {
    if (root == NULL) {
        cout << "Tree is empty!\n";
        return {};
    }
    else {
        return root->collectAllFilters();
    }
}

int BloomFilterTree::countFilters() {
    if (root == NULL) {
        return 0;
    }
    else {
        return root->countFilters(); 
    }
}

int BloomFilterTree::countUnionFilters() {
    if (root == NULL) {
        cout << "Tree is empty!\n";
        return 0;
    }
    else {
        int count = root->countUnionFilters();
        return count;
    }
}

vector<pair<int, double>> BloomFilterTree::computeAllDistances(BloomFilter *filter) {
    vector<BloomFilter> filters = collectAllFilters();
    vector<pair<int, double>> result;
    double jacc;
    for (int i=0; i<filters.size(); i++) {
        jacc = root->computeJaccard(&filters[i], filter);
        result.push_back(make_pair(filters[i].getId(), jacc));
    }
    return result;
}

vector<pair<int, double>> BloomFilterTree::computekDistances(BloomFilter *filter, int k) {
    vector<pair<int, double>> allDistances = computeAllDistances(filter);
    vector<pair<int, double>> result;
    sort(allDistances.begin(), allDistances.end(), [](const pair<int, double> &left, const pair<int, double> &right) {
        return left.second < right.second;
    });
    for (int i=0; i<k; i++) {
        result.push_back(allDistances[i]); 
    }
    return result;
}

int BloomFilterTree::countLeaves() {
    if (root == NULL) {
        cout << "Tree is empty!\n";
        return 0;
    }
    else {
        BloomFilterNode *first = search(getMinKey());
        BloomFilterNode *last = search(getMaxKey());
        if (first == last) {
            return 1;
        }
        else {
            return root->countLeaves();
        }
    }
}


vector<pair<BloomFilter, double>> BloomFilterTree::compare(BloomFilter *filter, int k) {
    vector<pair<BloomFilter, double>> distances;
    if (root == NULL) {
        cout << "Tree is empty!\n";
        distances.push_back(make_pair(*filter, 0));
    }
    else {
        vector<BloomFilter> allFilters = collectAllFilters();
        double jacc;
        for (int i=0; i<allFilters.size(); i++) {
            jacc = filter->computeJaccard(&allFilters[i]);
            distances.push_back(make_pair(allFilters[i], jacc));
        }
        
        // Sort all filters in tree by jaccard distance in ascending order
        sort(distances.begin(), distances.end(), [](const pair<BloomFilter, double> &left, const pair<BloomFilter, double> &right) {
            return left.second < right.second;
        });
        
        // Return Bloom filters with k smallest distances
        int diff = distances.size()-k;
        for (int i=0; i<diff; i++) {
            distances.pop_back();
        }
    }
    return distances;
}

// Compute memory allocated by BloomFilterTree object vs. std::vector
// First element of return vector: Memory consumption of std::vector with NUM_FILTERS
// Second element of return vector: Memory consumption of this BloomFilterTree
vector<int> BloomFilterTree::compareMem() {
    if (root == NULL) {
        cout << "Tree is empty!\n";
        return {};
    }
    else {
        vector<int> res;
        int memFilter = 0;
        int memVector = 0;
        int memTree = 0;
        
        // Count filters and union filters
        int allFilters = countFilters() + countUnionFilters();
        
        // Calculate size of one BloomFilter object
        for (int i=0; i<filtersize; i++) {
            memFilter += sizeof(int);
        }
        
        // Calculate size of std::vector with NUM_FILTERS
        for (int i=0; i<countFilters(); i++) {
            memVector += memFilter;
        }
         
        // Calculate size of BloomFilterTree with NUM_FILTERS
        for (int i=0; i<allFilters; i++) {
            memTree += memFilter;
        }
        res.push_back(memVector);
        res.push_back(memTree);
        return res; 
    }
}

// Compute construction cost for BloomFilterTree object vs. std::vector
// First element of result: Construction cost for std::vector with NUM_FILTERS
// Second element of result: Construction cost for BloomFilterTree with NUM_FILTERS
vector<double> BloomFilterTree::compareConstrCost() {
    if (root == NULL) {
        cout << "Tree is empty!\n";
        return {};
    }
    else {
        vector<double> res;
        
        // Calculate construction cost of std::vector with NUM_FILTERS
        res.push_back(1);
        
        // Calculate construction cost of BloomFilterTree with NUM_FILTERS
        int fanout = 2*t+1;
        
        // Collect subset filters in tree: O(n)
        // Collect free ids: O(n)
        // Sort free ids: O(n log n)
        // Determine best ids: O(n)
        // Sort good ids: O(n log n)
        // Complexity of subset id calculation = 3*O(n) 2*O(n log n) = O(n log n)
        
        // Collect superset filters in tree: O(n)
        // Collect free ids: O(n)
        // Sort free ids: O(n log n)
        // Determine best ids: O(n)
        // Sort good ids: O(n log n)
        // Complexity of superset id calculation = 3*O(n) 2*O(n log n) = O(n log n)
        
        // Complexity of id calculation + insertion = O(n log n) + O(log_b n) = O(n log n)
        
        double insertionCost = log(countFilters())/log(fanout);
        double idCost = countFilters() * log(countFilters());
        double treeCost = insertionCost + idCost;
        res.push_back(treeCost);
        return res;
    }
}

// Compute number of comparisons for NN-query on BloomFilterTree vs. unsorted list
// First element of result: Number of comparisons for std::vector with NUM_FILTERS
// Second element of result: Number of comparisons for BloomFilterTree with NUM_FILTERS
vector<int> BloomFilterTree::compareComplSimQuery(BloomFilter *filter) {
    if (root == NULL) {
        cout << "Tree is empty!\n";
        return {};
    }
    else {
        vector<int> res;
        
        // Compute max number of comparisons
        int max = countFilters() * 2;
        res.push_back(max);
        
        // Check if query filter is subset/superset of root's union filter
        if ((root->unionfilter->isSubset(filter) == false) && (root->unionfilter->isSuperset(filter) == false)) {
            res.push_back(max);
            return res;
        }
        else {
            int comp = 2 + root->countComparisons(filter);
            res.push_back(comp); 
            return res;
        }
    }
}

// Compute number of comparisons for kNN-query on BloomFilterTree vs. unsorted list
// First element of result: Number of comparisons for std::vector with NUM_FILTERS
// Second to last elements of result: Number of comparisons for BloomFilterTree with NUM_FILTERS
vector<int> BloomFilterTree::compareComplSimQueryVec(BloomFilter *filter, int k) {
    if (root == NULL) {
        cout << "Tree is empty!\n";
        return {};
    }
    else {
        vector<int> res;
        
        // Compute max number of comparisons
        int numFilters = countFilters();
        int max = numFilters * 2 + numFilters * (log(numFilters)/log(2));
        res.push_back(max);
        
        // Check if query filter is subset/superset of root's union filter
        if ((root->unionfilter->isSubset(filter) == false) && (root->unionfilter->isSuperset(filter) == false)) {
            res.push_back(max);
            return res;
        }
        else {
            int comp = 2 + root->countVecComparisons(filter, k);
            res.push_back(comp);
            return res;
        }
    }
}

void BloomFilterTree::insert(BloomFilter *filter) {
    if (root == NULL) {
        root = new BloomFilterLeaf(t, filtersize, NULL, NULL);
        root->insert(filter);
    }
    else {
        root->insert(filter);
        if (root->getParent() != NULL) {
            root = root->getParent();
        }
    }
}

void BloomFilterTree::insertAsSets(BloomFilter *filter) {
    if (root == NULL) {
        root = new BloomFilterLeaf(t, filtersize, NULL, NULL);
        root->insert(filter);
    }
    else {
        root->insertAsSets(filter);
        if (root->getParent() != NULL) {
            root = root->getParent();
        }
    }
}

BloomFilter * BloomFilterTree::simQuery(BloomFilter *filter) {
    if (root == NULL) {
        cout << "Tree is empty!\n";
        return filter;
    }
    else {

        // Check if query filter is subset/superset of root's union filter
        if ((root->unionfilter->isSubset(filter) == false) && (root->unionfilter->isSuperset(filter) == false)) {
            return getMinJaccardFilter(filter);
        }
        else {
            return root->simQuery(filter);
        }
    }
}

vector <BloomFilter*> BloomFilterTree::simQueryVec(BloomFilter *filter, int k) {
    vector<BloomFilter*> results;
    if (root == NULL) {
        cout << "Tree is empty!\n";
        results.push_back(filter);
    }
    else {
        return root->simQueryVec(filter, k);
    }
    return results; 
}