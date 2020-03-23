#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <chrono>
using namespace std;
using namespace std::chrono;

namespace workload{
    int workload_test();
    int d1_rs(milliseconds *results);
    int d1_rr(milliseconds *results);
}
