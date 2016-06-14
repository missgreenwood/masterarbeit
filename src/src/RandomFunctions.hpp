//  RandomFunctions.hpp, Judith Greif
//  Description: Hashes and random functions

#ifndef RandomFunctions_h
#define RandomFunctions_h

#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int randomNumber() {
    random_device rd;
    mt19937 mt(rd());
    uniform_real_distribution<double> dist(0.0, 235886.0);
    return dist(mt);
}

#endif
