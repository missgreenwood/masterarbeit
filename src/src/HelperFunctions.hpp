//  HelperFunctions.hpp, Judith Greif
//  Description: Random number generation, wall clock and cpu clock time etc.

#ifndef HelperFunctions_h
#define HelperFunctions_h

#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

// Generate random int between 0..235886 (number of entries in dictionary)
int randomNumber() {
    random_device rd;
    mt19937 mt(rd());
    uniform_real_distribution<double> dist(0.0, 235886.0);
    return dist(mt);
}

// Measure cpu and wall clock time
// Use std::chrono::system_clock for wall clock and std::clock for cpu clock

#endif
