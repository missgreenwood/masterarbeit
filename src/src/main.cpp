//  main.cpp, Judith Greif
//  Description: Main executable for Bloom filter data structures


#include "BloomFilterTree.hpp"
#include "BloomFilterList.hpp"

using namespace std;


int main(int argc, const char *argv[]) {
    
    // Class BloomFilter
    
    cout << "CLASS BloomFilter\n";
    cout << "-----------------\n";
    
    cout << "Create 100 instances of BloomFilter with random ids, array length 256 and random values";
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
    cout << "\nCreate 3 query filters f1, f2, f3 with ids 1, 2, 3, array length 256 and random values";
    BloomFilter f1(256, 1);
    f1.initRandom();
    BloomFilter f2(256, 2);
    f2.initRandom();
    BloomFilter f3(256, 3);
    f3.initRandom();
    
    cout << "\n\nCreate 100 instances of BloomFilter with random ids, array length 512 and random values";
    cout << "Create new BloomFilter vector (v2) and insert all filters";
    BloomFilter *filter512;
    int id512;
    vector<BloomFilter> v2;
    for (int i=0; i<100; i++) {
        filter512 = new BloomFilter(512, rand());
        id512 = filter512->getId();
        filter512->initRandom();
        v2.push_back(*filter512);
    }
    
    cout << "Create 3 query filters f4, f5, f6 with ids 4, 5, 6, array length 512 and random values";
    BloomFilter f4(512, 4);
    BloomFilter f5(512, 5);
    BloomFilter f6(512, 6);
    
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
    
    cout << "Create instance of BloomFilterTree (b3) with minimum degree 3/max elements 6, filter size 512 and insert all filters in v2 as sets\n\n";
    BloomFilterTree b3(3, 512);
    for (int i=0; i<v2.size(); i++) {
        b3.insertAsSets(&v2[i]);
    }
    
    cout << "Create instance of BloomFilterTree (b4) with minimum degree 3/max elements 6, filter size 512 and insert every second filter in v2 as sets\n\n"; 
    
    cout << "10 nearest neighbors of f1 in b1:\n\n";
    vector<pair<int, double>> res1 = b1.computekDistances(&f1, 10);

    cout << "\n10 nearest neighbors of f1 in b2:\n\n";
    vector<pair<int, double>> res2 = b2.computekDistances(&f1, 10);
    
    cout << "\n10 nearest neighbors of f2 in b1:\n\n";
    vector<pair<int, double>> res3 = b1.computekDistances(&f2, 10);
    
    cout << "\n10 nearest neighbors of f2 in b2:\n\n";
    vector<pair<int, double>> res4 = b2.computekDistances(&f2, 10);
    
    cout << "\n10 nearest neighbors of f3 in b1:\n\n";
    vector<pair<int, double>> res5 = b1.computekDistances(&f3, 10);
    
    cout << "\n10 nearest neighbors of f3 in b2:\n\n";
    vector<pair<int, double>> res6 = b2.computekDistances(&f3, 10);
    
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
    BloomFilter *r1 = b1.simQuery(&f1);
    cout << "\nComputed result: " << r1->getId() << " (" << f1.computeJaccard(r1) << ")";
    
    cout << "\n\nTREE QUERY for nearest neighbor of f1 in b2";
    cout << "\nResult should be: " << res2[0].first;
    BloomFilter *r2 = b2.simQuery(&f1);
    cout << "\nComputed result: " << r2->getId() << " (" << f1.computeJaccard(r2) << ")";
    
    cout << "\n\nTREE QUERY for nearest neighbor of f2 in b1";
    cout << "\nResult should be: " << res3[0].first;
    BloomFilter *r3 = b1.simQuery(&f2);
    cout << "\nComputed result: " << r3->getId() << " (" << f2.computeJaccard(r3) << ")";
    
    cout << "\n\nTREE QUERY for nearest neighbor of f2 in b2";
    cout << "\nResult should be: " << res4[0].first;
    BloomFilter* r4 = b2.simQuery(&f2);
    cout << "\nComputed result: " << r4->getId() << " (" << f2.computeJaccard(r4) << ")";
    
    cout << "\n\nTREE QUERY for nearest neighbor of f3 in b1";
    cout << "\nResult should be: " << res5[0].first;
    BloomFilter* r5 = b1.simQuery(&f3);
    cout << "\nComputed result: " << r5->getId() << " (" << f3.computeJaccard(r5) << ")";
    
    cout << "\n\nTREE QUERY for nearest neighbor of f3 in b2";
    cout << "\nResult should be: " << res6[0].first;
    BloomFilter* r6 = b2.simQuery(&f3);
    cout << "\nComputed result: " << r6->getId() << " (" << f3.computeJaccard(r6) << ")";
    
    cout << "\n\nTREE QUERY for 3 nearest neighbors of f1 in b1";
    cout << "\nResults should be: " << res1[0].first << ", " << res1[1].first << ", " << res1[2].first;
    vector<BloomFilter*> r7 = b1.simQueryVec(&f1, 3);
    cout << "\nComputed results:\n";
    cout << r7[0]->getId() << " (" << f1.computeJaccard(r7[0]) << ")\n";
    cout << r7[1]->getId() << " (" << f1.computeJaccard(r7[1]) << ")\n";
    cout << r7[2]->getId() << " (" << f1.computeJaccard(r7[2]) << ")";
    
    cout << "\n\nTREE QUERY for 3 nearest neighbors of f1 in b2";
    cout << "\nResults should be: " << res2[0].first << ", " << res2[1].first << ", " << res2[2].first;
    vector<BloomFilter*> r8 = b2.simQueryVec(&f1, 3);
    cout << "\nComputed results:\n";
    cout << r8[0]->getId() << " (" << f1.computeJaccard(r8[0]) << ")\n";
    cout << r8[1]->getId() << " (" << f1.computeJaccard(r8[1]) << ")\n";
    cout << r8[2]->getId() << " (" << f1.computeJaccard(r8[2]) << ")";
    
    cout << "\n\nTREE QUERY for 3 nearest neighbors of f2 in b1";
    cout << "\nResults should be: " << res3[0].first << ", " << res3[1].first << ", " << res3[2].first;
    vector<BloomFilter*> r9 = b1.simQueryVec(&f2, 3);
    cout << "\nComputed results:\n";
    cout << r9[0]->getId() << " (" << f2.computeJaccard(r9[0]) << ")\n";
    cout << r9[1]->getId() << " (" << f2.computeJaccard(r9[1]) << ")\n";
    cout << r9[2]->getId() << " (" << f2.computeJaccard(r9[2]) << ")";

    cout << "\n\nTREE QUERY for 3 nearest neighbors of f2 in b2";
    cout << "\nResults should be: " << res4[0].first << ", " << res4[1].first << ", " << res4[2].first;
    vector<BloomFilter*> r10 = b2.simQueryVec(&f2, 3);
    cout << "\nComputed results:\n";
    cout << r10[0]->getId() << " (" << f2.computeJaccard(r10[0]) << ")\n";
    cout << r10[1]->getId() << " (" << f2.computeJaccard(r10[1]) << ")\n";
    cout << r10[2]->getId() << " (" << f2.computeJaccard(r10[2]) << ")";
    
    cout << "\n\nTREE QUERY for 3 nearest neighbors of f3 in b1";
    cout << "\nResults should be: " << res5[0].first << ", " << res5[1].first << ", " << res5[2].first;
    vector<BloomFilter*> r11 = b1.simQueryVec(&f3, 3);
    cout << "\nComputed results:\n";
    cout << r11[0]->getId() << " (" << f3.computeJaccard(r11[0]) << ")\n";
    cout << r11[1]->getId() << " (" << f3.computeJaccard(r11[1]) << ")\n";
    cout << r11[2]->getId() << " (" << f3.computeJaccard(r11[2]) << ")";
    
    cout << "\n\nTREE QUERY for 3 nearest neighbors of f3 in b2";
    cout << "\nResults should be: " << res6[0].first << ", " << res6[1].first << ", " << res6[2].first;
    vector<BloomFilter*> r12= b2.simQueryVec(&f3, 3);
    cout << "\nComputed results:\n";
    cout << r12[0]->getId() << " (" << f3.computeJaccard(r12[0]) << ")\n";
    cout << r12[1]->getId() << " (" << f3.computeJaccard(r12[1]) << ")\n";
    cout << r12[2]->getId() << " (" << f3.computeJaccard(r12[2]) << ")";

    // Class BloomFilterList
    
    cout << "\n\n\nCLASS BloomFilterList";
    cout << "\n---------------------\n";
    cout << "Create instance of BloomFilterList (l1) with filtersize 256 and insert all filters in v1\n\n";
    BloomFilterList l1(256);
    for (int i=0; i<v1.size(); i++) {
        l1.insert(&v1[i]);
    }
    
    cout << "10 nearest neighbors of f1 in l1:\n\n";
    vector<pair<int, double>> res7 = l1.computekDistances(&f1, 10);
    
    cout << "\n10 nearest neighbors of f2 in l1:\n\n";
    vector<pair<int, double>> res8 = l1.computekDistances(&f2, 10);
    
    cout << "\n10 nearest neighbors of f3 in l1:\n\n";
    vector<pair<int, double>> res9 = l1.computekDistances(&f3, 10);
    
    // Section search queries
    cout << "\n\nCheck section queries";
    cout << "\n---------------------\n";
    
    cout << "\nLIST QUERY for nearest neighbor of f1 in l1";
    cout << "\nResult should be: " << res7[0].first;
    BloomFilter *ra = l1.simQuery(&f1);
    cout << "\nComputed result: " << ra->getId() << " (" << ra->computeJaccard(&f1) << ")";
    
    cout << "\n\nLIST QUERY for nearest neighbor of f2 in l1";
    cout << "\nResult should be: " << res8[0].first;
    BloomFilter *rb = l1.simQuery(&f2);
    cout << "\nComputed result: " << rb->getId() << " (" << rb->computeJaccard(&f2) << ")";
    
    cout << "\n\nLIST QUERY for nearest neighbor of f3 in l1";
    cout << "\nResult should be: " << res9[0].first;
    BloomFilter *rc = l1.simQuery(&f3);
    cout << "\nComputed result: " << rc->getId() << " (" << rc->computeJaccard(&f3) << ")";
    
    cout << "\n\nLIST QUERY for 3 nearest neighbors of f1 in l1";
    vector<BloomFilter*> rd = l1.simQueryVec(&f1, 3);
    cout << "\nResults should be: " << res7[0].first << ", " << res7[1].first << ", " << res7[2].first;
    cout << "\nComputed results:\n";
    cout << rd[0]->getId() << " (" << f1.computeJaccard(rd[0]) << ")\n";
    cout << rd[1]->getId() << " (" << f1.computeJaccard(rd[1]) << ")\n";
    cout << rd[2]->getId() << " (" << f1.computeJaccard(rd[2]) << ")";
    
    cout << "\n\nSection query for 3 nearest neighbors of f2 in l1";
    vector<BloomFilter*> re = l1.simQueryVec(&f2, 3);
    cout << "\nResults should be: " << res8[0].first << ", " << res8[1].first << ", " << res8[2].first;
    cout << "\nComputed results:\n";
    cout << re[0]->getId() << " (" << f1.computeJaccard(re[0]) << ")\n";
    cout << re[1]->getId() << " (" << f1.computeJaccard(re[1]) << ")\n";
    cout << re[2]->getId() << " (" << f1.computeJaccard(re[2]) << ")";
    
    cout << "\n\nSection query for 3 nearest neighbors of f3 in l1";
    vector<BloomFilter*> rf = l1.simQueryVec(&f3, 3);
    cout << "\nResults should be: " << res9[0].first << ", " << res9[1].first << ", " << res9[2].first;
    cout << "\nComputed results:\n";
    cout << rf[0]->getId() << " (" << f1.computeJaccard(rf[0]) << ")\n";
    cout << rf[1]->getId() << " (" << f1.computeJaccard(rf[1]) << ")\n";
    cout << rf[2]->getId() << " (" << f1.computeJaccard(rf[2]) << ")";

    cout << endl;
    return 0;
}