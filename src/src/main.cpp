//  main.cpp, Judith Greif
//  Description: Main executable for Bloom filter data structures


#include "BloomFilterTree.hpp"
#include "BloomFilterList.hpp"

using namespace std;


int main(int argc, const char *argv[]) {
    
    // Class BloomFilter
    
    cout << "CLASS BloomFilter\n";
    cout << "-----------------\n";
    
    cout << "Create 100 instances of BloomFilter with random ids, array length 256, random values";
    cout << "\nCreate new BloomFilter vector (v1) and insert all filters";
    BloomFilter *filter;
    int id;
    vector<BloomFilter> v1;
    for (int i=0; i<100; i++) {
        filter = new BloomFilter(256, rand());
        id = filter->getId();
        filter->initRandom();
        v1.push_back(*filter);
    }
    cout << "\nCreate 3 query filters f1, f2, f3 with ids 1, 2, 3, array length 256, random values";
    BloomFilter f1(256, 1);
    f1.initRandom();
    BloomFilter f2(256, 2);
    f2.initRandom();
    BloomFilter f3(256, 3);
    f3.initRandom();
    BloomFilter f4(64, 4);
    f4.initRandom();
    
    // Class BloomFilterTree
    
    cout << "\n\n\nCLASS BloomFilterTree";
    cout << "\n---------------------\n";
    
    cout << "Create instance of BloomFilterTree (b1) with minimum degree 3/max elements 6, filter size 256 and insert all filters in v1 as sets\n\n";
    BloomFilterTree b1(3, 256);
    for (int i=0; i<v1.size(); i++) {
        b1.insertAsSets(&v1[i]);
    }
    
    cout << "Create instance of BloomFilterTree (b2) with minimum degree 3/max elements 6, filter size 256 and insert every second filter in v1 as sets\n\n";
    BloomFilterTree b2(3, 256);
    for (int i=0; i<v1.size(); i+=2) {
        b2.insertAsSets(&v1[i]);
    }
    
    cout << "Count filters in b1: " << b1.countFilters();
    
    cout << "\n\nCount filters in b2: " << b2.countFilters();
    
    cout << "\n\n10 nearest neighbors of f1 in b1:\n\n";
    vector<pair<int, float>> res1 = b1.computekDistances(&f1, 10);
    
    cout << "\n10 nearest neighbors of f1 in b2:\n\n";
    vector<pair<int, float>> res2 = b2.computekDistances(&f1, 10);
    
    cout << "\n10 nearest neighbors of f2 in b1:\n\n";
    vector<pair<int, float>> res3 = b1.computekDistances(&f2, 10);
    
    cout << "\n10 nearest neighbors of f2 in b2:\n\n";
    vector<pair<int, float>> res4 = b2.computekDistances(&f2, 10);
    
    cout << "\n10 nearest neighbors of f3 in b1:\n\n";
    vector<pair<int, float>> res5 = b1.computekDistances(&f3, 10);
    
    cout << "\n10 nearest neighbors of f3 in b2:\n\n";
    vector<pair<int, float>> res6 = b2.computekDistances(&f3, 10);
    
    /* cout << "\n\nCheck subset insertion";
    cout << "\n----------------------";
    
    // Subset id for filter size 256
    cout << "\nComputed optimal subset id for f1 in b1: " << b1.computeSubsetId(&f1);
    cout << "\nComputed optimal subset id for f2 in b1: " << b1.computeSubsetId(&f2);
    cout << "\nComputed optimal subset id for f3 in b1: " << b1.computeSubsetId(&f3);
    
    cout << "\n\nComputed optimal subset id for f1 in b2: " << b2.computeSubsetId(&f1);
    cout << "\nComputed optimal subset id for f2 in b2: " << b2.computeSubsetId(&f2);
    cout << "\nComputed optimal subset id for f3 in b2: " << b2.computeSubsetId(&f3);
    
    cout << "\n\n\nCheck superset insertion";
    cout << "\n------------------------";
    
    // Superset id for filter size 256
    cout << "\nComputed optimal superset id for f1 in b1: " << b1.computeSupersetId(&f1);
    cout << "\nComputed optimal superset id for f1 in b1: " << b1.computeSupersetId(&f1);
    cout << "\nComputed optimal superset id for f1 in b1: " << b1.computeSupersetId(&f1);
    
    cout << "\n\nComputed optimal superset id for f1 in b2: " << b2.computeSupersetId(&f1);
    cout << "\nComputed optimal superset id for f1 in b2: " << b2.computeSupersetId(&f1);
    cout << "\nComputed optimal superset id for f1 in b2: " << b2.computeSupersetId(&f1); */
    
    // Set search queries
    cout << "\n\nCheck set queries";
    cout << "\n-----------------";
    
    cout << "\nTREE QUERY for nearest neighbor of f1 in b1";
    cout << "\nResult should be: " << res1[0].first;
    BloomFilter *result = b1.simQuery(&f1);
    cout << "\nComputed result: " << result->getId() << " (" << f1.computeJaccard(result) << ")";
    
    cout << "\n\nTREE QUERY for nearest neighbor of f1 in b2";
    cout << "\nResult should be: " << res2[0].first;
    result = b2.simQuery(&f1);
    cout << "\nComputed result: " << result->getId() << " (" << f1.computeJaccard(result) << ")";
    
    cout << "\n\nTREE QUERY for nearest neighbor of f2 in b1";
    cout << "\nResult should be: " << res3[0].first;
    result = b1.simQuery(&f2);
    cout << "\nComputed result: " << result->getId() << " (" << f2.computeJaccard(result) << ")";
    
    cout << "\n\nTREE QUERY for nearest neighbor of f2 in b2";
    cout << "\nResult should be: " << res4[0].first;
    result = b2.simQuery(&f2);
    cout << "\nComputed result: " << result->getId() << " (" << f2.computeJaccard(result) << ")";
    
    cout << "\n\nTREE QUERY for nearest neighbor of f3 in b1";
    cout << "\nResult should be: " << res5[0].first;
    result = b1.simQuery(&f3);
    cout << "\nComputed result: " << result->getId() << " (" << f3.computeJaccard(result) << ")";
    
    cout << "\n\nTREE QUERY for nearest neighbor of f3 in b2";
    cout << "\nResult should be: " << res6[0].first;
    result = b2.simQuery(&f3);
    cout << "\nComputed result: " << result->getId() << " (" << f3.computeJaccard(result) << ")";
    
    cout << "\n\nTREE QUERY for 3 nearest neighbors of f1 in b1";
    cout << "\nResults should be: " << res1[0].first << ", " << res1[1].first << ", " << res1[2].first;
    vector<BloomFilter*> results = b1.simQueryVec(&f1, 3);
    cout << "\nComputed results:\n";
    cout << results[0]->getId() << " (" << f1.computeJaccard(results[0]) << ")\n";
    cout << results[1]->getId() << " (" << f1.computeJaccard(results[1]) << ")\n";
    cout << results[2]->getId() << " (" << f1.computeJaccard(results[2]) << ")";
    
    cout << "\n\nTREE QUERY for 3 nearest neighbors of f1 in b2";
    cout << "\nResults should be: " << res2[0].first << ", " << res2[1].first << ", " << res2[2].first;
    results = b2.simQueryVec(&f1, 3);
    cout << "\nComputed results:\n";
    cout << results[0]->getId() << " (" << f1.computeJaccard(results[0]) << ")\n";
    cout << results[1]->getId() << " (" << f1.computeJaccard(results[1]) << ")\n";
    cout << results[2]->getId() << " (" << f1.computeJaccard(results[2]) << ")";
    
    cout << "\n\nTREE QUERY for 3 nearest neighbors of f2 in b1";
    cout << "\nResults should be: " << res3[0].first << ", " << res3[1].first << ", " << res3[2].first;
    results = b1.simQueryVec(&f2, 3);
    cout << "\nComputed results:\n";
    cout << results[0]->getId() << " (" << f2.computeJaccard(results[0]) << ")\n";
    cout << results[1]->getId() << " (" << f2.computeJaccard(results[1]) << ")\n";
    cout << results[2]->getId() << " (" << f2.computeJaccard(results[2]) << ")";

    cout << "\n\nTREE QUERY for 3 nearest neighbors of f2 in b2";
    cout << "\nResults should be: " << res4[0].first << ", " << res4[1].first << ", " << res4[2].first;
    results = b2.simQueryVec(&f2, 3);
    cout << "\nComputed results:\n";
    cout << results[0]->getId() << " (" << f2.computeJaccard(results[0]) << ")\n";
    cout << results[1]->getId() << " (" << f2.computeJaccard(results[1]) << ")\n";
    cout << results[2]->getId() << " (" << f2.computeJaccard(results[2]) << ")";
    
    cout << "\n\nTREE QUERY for 3 nearest neighbors of f3 in b1";
    cout << "\nResults should be: " << res5[0].first << ", " << res5[1].first << ", " << res5[2].first;
    results = b1.simQueryVec(&f3, 3);
    cout << "\nComputed results:\n";
    cout << results[0]->getId() << " (" << f3.computeJaccard(results[0]) << ")\n";
    cout << results[1]->getId() << " (" << f3.computeJaccard(results[1]) << ")\n";
    cout << results[2]->getId() << " (" << f3.computeJaccard(results[2]) << ")";
    
    cout << "\n\nTREE QUERY for 3 nearest neighbors of f3 in b2";
    cout << "\nResults should be: " << res6[0].first << ", " << res6[1].first << ", " << res6[2].first;
    results = b2.simQueryVec(&f3, 3);
    cout << "\nComputed results:\n";
    cout << results[0]->getId() << " (" << f3.computeJaccard(results[0]) << ")\n";
    cout << results[1]->getId() << " (" << f3.computeJaccard(results[1]) << ")\n";
    cout << results[2]->getId() << " (" << f3.computeJaccard(results[2]) << ")";

    /* // Class BloomFilterListNode
    
    cout << "\n\n\nCLASS BloomFilterListNode";
    cout << "\n-------------------------\n";
    
    cout << "Create instance of BloomFilterListNode (n1) and test all methods\n\n";
    BloomFilterListNode n1;
    n1.setPosition(2);
    cout << "Position: " << n1.getPosition() << endl;
    for (int i=0; i<v1.size(); i++) {
        if (v1[i].getData()[2] == 0) {
            n1.zeroLinks.push_back(&v1[i]);
        }
        else {
            n1.oneLinks.push_back(&v1[i]);
        }
    }
    n1.printZeroLinks();
    n1.printOneLinks(); 
    
    // Class BloomFilterList
    
    cout << "\n\nCLASS BloomFilterList";
    cout << "\n---------------------\n";
    cout << "Create 3 instances of BloomFilterList (l1, l5, l6) and test all methods\n\n";
    BloomFilterList l1(10);
    for (int i=0; i<l1.getSize(); i++) {
        l1.updateNode(&f1, i);
    }
    l1.printAll();
    l1.clear();
    l1.printAll();
    BloomFilterList l5(4);
    BloomFilterList l6(6);
    l5.insert(&f600);
    
    // Section insertion
    cout << "\n\nCheck section insertion";
    cout << "\n-----------------------";
    cout << "\nInsert filters f101..f103, f105..f110 into l5";
    l5.insert(&f101);
    l5.insert(&f102);
    l5.insert(&f103);
    l5.insert(&f105);
    l5.insert(&f106);
    l5.insert(&f107);
    l5.insert(&f108);
    l5.insert(&f109);
    l5.insert(&f110);
    cout << "\nBloomFilterList l5:\n\n";
    // l5.printAll();
    cout << "Insert filters 601..604, 609..614, 619..624 into l6\n";
    l6.insert(&f601);
    l6.insert(&f602);
    l6.insert(&f603);
    l6.insert(&f604);
    l6.insert(&f609);
    l6.insert(&f610);
    l6.insert(&f611);
    l6.insert(&f612);
    l6.insert(&f613);
    l6.insert(&f614);
    l6.insert(&f619);
    l6.insert(&f620);
    l6.insert(&f621);
    l6.insert(&f622);
    l6.insert(&f623);
    l6.insert(&f624);
    l6.printAll();
    
    // Section search queries
    cout << "\nCheck section queries";
    cout << "\n---------------------\n";
    l5.compare(&f104, l5.countFilters());
    cout << endl;
    l6.compare(&f595, l6.countFilters());
    
    cout << "\nSection query for nearest neighbor of f104 (";
    f104.printArr();
    cout <<")\n";
    cout << "Result should be: 97, 93 or 98\n";
    result = l5.simQuery(&f104);
    cout << "Computed result: " << result->getId() << " (";
    result->printArr();
    cout << ")";
    
    cout << "\n\nSection query for nearest neighbor of f595 (";
    f595.printArr();
    cout << ")\n";
    cout << "Result should be: 595 (001001)";
    result = l6.simQuery(&f595);
    cout << "\nComputed result: " << result->getId() << " (";
    result->printArr();
    cout << ")";
    
    cout << "\n\nSection query for 3 nearest neighbors of f104 (";
    f104.printArr();
    cout << ")\n";
    cout << "Result should be: 93, 98, 97 in any order";
    vector<BloomFilter*> pResults = l5.simQueryVec(&f104, 3);
    cout << "\nComputed result: ";
    for (int i=0; i<pResults.size()-1; i++) {
        cout << pResults[i]->getId() << ", ";
    }
    cout << pResults[pResults.size()-1]->getId();
    
    cout << "\n\nSection query for 3 nearest neighbors of f595 (";
    f595.printArr();
    cout << ")\n";
    cout << "Result should be: 595 and two filters out of 593/585/591 in any order";
    pResults = l6.simQueryVec(&f595, 3);
    cout << "\nComputed result: ";
    for (int i=0; i<pResults.size()-1; i++) {
        cout << pResults[i]->getId() << ", ";
    }
    cout << pResults[pResults.size()-1]->getId(); */
    cout << endl;
    return 0;
}