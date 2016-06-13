//  BloomFilter.cpp, Judith Greif
//  Description: Implementation of class BloomFilter

#include "BloomFilter.hpp"


// Default constructor, sets size to 256
BloomFilter::BloomFilter(): id(rand()), count(0), size(256), d(NUM_HASH){
    data = new int[size];
    for (int i=0; i<size; i++) {
        data[i] = 0;
    }
};

// Copy constructor
// Usage: If a new object has to be created before the copying can occur
BloomFilter::BloomFilter(const BloomFilter& fSource) {
    id = fSource.id;
    count = fSource.count;
    size = fSource.size;
    d = fSource.d;
    
    // Allocate memory (deep copy)
    data = new int[fSource.size];
    for (int i=0; i<fSource.size; i++) {
        data[i] = fSource.data[i];
    }
};

// Constructor with parameters id and size
BloomFilter::BloomFilter(int _id, int _size): id(_id), count(0), size(_size), d(NUM_HASH) {
    data = new int[size];
    for (int i=0; i<size; i++) {
        data[i] = 0;
    }
}

// Constructor with parameters id, size, # of hash functions
BloomFilter::BloomFilter(int _id, int _size, int _d): id(_id), count(0), size(_size), d(_d) {
    data = new int[size];
    for (int i=0; i<size; i++) {
        data[i] = 0;
    }
}

BloomFilter::~BloomFilter() {}

// Overloaded assignment operator
// Usage: If a new object does not have to be created before the copying can occur
BloomFilter & BloomFilter::operator= (const BloomFilter &fSource) {
    
    // Check for self assignment
    if (this != &fSource) {
        id = fSource.id;
        count = fSource.count;
        size = fSource.size;
        d = fSource.d;
        
        // Allocate memory (deep copy)
        data = new int[fSource.size];
        for (int i=0; i<fSource.size; i++) {
            data[i] = fSource.data[i];
        }
    }
    return *this; 
}

void BloomFilter::setId(int value) {
    id = value;
}

int BloomFilter::getId() {
    return id;
}

int BloomFilter::getSize() {
    return size;
}

void BloomFilter::setValue(int index, int value) {
    data[index] = value;
}

int * BloomFilter::getData() {
    return data;
}

void BloomFilter::printData() {
    cout << "Bloom filter " << getId() << ": ";
    for (int i=0; i<size; i++) {
        cout << data[i];
    }
    cout << endl;
}

void BloomFilter::printArr() {
    for (int i=0; i<getSize(); i++) {
        cout << data[i]; 
    }
}

// Initialize Bloom Filter with values 0 or 1
// Max. 50% of the array elements may be 1
void BloomFilter::initRandom() {
    random_device seed;
    mt19937 gen(seed());
    uniform_int_distribution<int> dist(0, getSize());
    for (int i=0; i<getSize()/2; i++) {
        setValue(dist(gen), 1);
    }
}

double BloomFilter::fractionOfZeros() {
    int o = 0;
    for (int i=0; i<size; i++) {
        if (data[i] == 0) {
            o++;
        }
    }
    return (double)o/(double)size;
}

double BloomFilter::eSize() {
    return -log(fractionOfZeros()) * (double) size/(double) d;
}

BloomFilter * BloomFilter::logicalOr(BloomFilter *filter) {
    if (getSize() != filter->getSize()) {
        cout << "\nError! Filters don't have the same size\n";
        return this;
    }
    int *data2 = filter->getData();
    BloomFilter *result = new BloomFilter(rand(), getSize(), d);
    for (int i=0; i<getSize(); i++) {
        if ((data[i] == 1) || (data2[i] == 1 )) {
            result->setValue(i, 1);
        }
    }
    return result;
}

BloomFilter * BloomFilter::logicalAnd(BloomFilter *filter) {
    if (getSize() != filter->getSize()) {
        cout << "\nError! Filters don't have the same size\n";
        return this;
    }
    int *data2 = filter->getData();
    BloomFilter *result = new BloomFilter(rand(), getSize(), d);
    for (int i=0; i<getSize(); i++) {
        if (data[i] == 1 && data2[i] == 1) {
            result->setValue(i, 1);
        }
     }
    return result; 
}

// Determine if argument filter is my subset
bool BloomFilter::isSubset(BloomFilter *filter) {
    int *arr2 = filter->getData();
    bool result = true;
    for (int i=0; i<getSize(); i++) {
        if ((arr2[i] == 1) && (data[i] != arr2[i])) {
            result = false;
            break;
        }
    }
    return result;
}

// Determine if argument filter is my superset
bool BloomFilter::isSuperset(BloomFilter *filter) {
    int *arr2 = filter->getData();
    bool result = true;
    for (int i=0; i<getSize(); i++) {
        if ((arr2[i] == 0) && (data[i] != arr2[i])) {
            result = false;
            break;
        }
    }
    return result;
}

// Return number of possible and valid supersets
int BloomFilter::mySupersetCount() {
    int result = 1;
    if (setZeros() != 0) {
        for (int i=1; i<=possibleAddedOnes(); i++) {
            result += binomialCoefficient(possibleFreeZeros(), i);
        }
    }
    return result;
}

// Return number of possible and valid subsets
int BloomFilter::mySubsetCount() {
    int result = 1;
    if (setOnes() != 0) {
        for (int i=1; i<=setOnes(); i++) {
            result += binomialCoefficient(setOnes(), i);
        }
    }
    return result;
}

int BloomFilter::binomialCoefficient(int n, int k) {
    if (n == k || k == 0) {
        return 1;
    }
    if (n < k) {
        return 0;
    }
    else {
        return binomialCoefficient(n-1, k-1) + binomialCoefficient(n-1, k);
    }
}

int BloomFilter::setOnes() {
    int ones = 0;
    for (int i=0; i<getSize(); i++) {
        if (data[i] == 1) {
            ones++;
        }
    }
    return ones;
}

int BloomFilter::setZeros() {
    int zeros = 0;
    for (int i=0; i<getSize(); i++) {
        if (data[i] == 0) {
            zeros++;
        }
    }
    return zeros;
}

int BloomFilter::validOnes() {
    return getSize()/2;
}

int BloomFilter::possibleFreeZeros() {
    return getSize() - setOnes();
}

int BloomFilter::possibleAddedOnes() {
    return validOnes() - setOnes();
}

// Compute the set union of two Bloom filters
double BloomFilter::setUnion(BloomFilter *filter) const {
    double result = 0;
    int *data2 = filter->getData();
    for (int i=0; i<size; i++) {
        if ((data[i] == 1) || (data2[i] == 1)) {
            result++;
        }
    }
    return result;
}

double BloomFilter::setIntersection(BloomFilter *filter) const {
    double result = 0;
    int *data2 = filter->getData();
    for (int i=0; i<size; i++) {
        if ((data[i] == 1) && (data2[i] == 1)) {
            result++;
        }
    }
    return result; 
}

double BloomFilter::computeAmbienceJaccard(BloomFilter *filter) {
    double intersect_size = eIntersect(filter);
    double union_size = eUnion(filter);
    return 1 - (intersect_size/union_size);
}

double BloomFilter::computeJaccard(BloomFilter *filter) const {
    return (double) 1-(setIntersection(filter)/setUnion(filter));
}

double BloomFilter::eUnion(BloomFilter *filter) {
    double dot = 0;
    int *arr2 = filter->getData();
    for (int i=0; i<size; i++) {
        if (data[i] == 1 || arr2[i] == 1) {
            dot++;
        }
    }
    return -log(1-dot / (double) size) * size/d;
}

double BloomFilter::eIntersect(BloomFilter *filter) {
    double unions_size = eUnion(filter);
    double e = eSize() - filter->eSize() - unions_size;
    return e; 
}

void BloomFilter::add(string &elem) {
    int max = size-1;
    for (int i=0; i<d; i++) {
        hash<string> hash_fn;
        int k = (int) hash_fn(elem) % max;
        setValue(k, 1);
    }
    increment();
}

void BloomFilter::increment() {
    count++;
}