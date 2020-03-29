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

namespace ReadTest{
    void workload_init();
    void workload_clean();

    int rs_rr_test();
    int write_rs_rr_results(const string &fileprefix, int start, int end);

    int iops_rr_test();
    int write_iops_rr_results(const string &rsize_prefix, int i_recordSize);

    void worker(int workerId, const string &filename, unsigned long recordSize, bool randFlag);
    
    

    int d1_rs(bool bigFileFlag, int i_recordSize);
    int d1_rr(bool bigFileFlag, int i_recordSize);

    int d2_rs(bool bigFileFlag, int i_recordSize);
    int d2_rr(bool bigFileFlag, int i_recordSize);

    int d3_rs(bool bigFileFlag, int i_recordSize);
    int d3_rr(bool bigFileFlag, int i_recordSize);

    int d4_rs(bool bigFileFlag, int i_recordSize);
    int d4_rr(bool bigFileFlag, int i_recordSize);

    int d5_rs(bool bigFileFlag, int i_recordSize);
    int d5_rr(bool bigFileFlag, int i_recordSize);

    int d6_rs(bool bigFileFlag, int i_recordSize);
    int d6_rr(bool bigFileFlag, int i_recordSize);

    int d7_rs(bool bigFileFlag, int i_recordSize);
    int d7_rr(bool bigFileFlag, int i_recordSize);

}
