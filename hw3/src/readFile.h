#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <chrono>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// #include <libexplain/read.h>

#include <thread>
#include <pthread.h>

using namespace std;
using namespace std::chrono;

namespace workload{
    int workload_test();

    void worker(int workerId, const string &filename, unsigned long recordSize, bool randFlag);
    
    int d1_rs();
    int d1_rr();

    int d2_rs();
    int d2_rr();

    int d3_rs();
    int d3_rr();

    int d4_rs();
    int d4_rr();

    int d5_rs();
    int d5_rr();

    int d6_rs();
    int d6_rr();

    int d7_rs();
    int d7_rr();

    int open_d1_rs();

}
