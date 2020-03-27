#include "MyDiskBench.h"
#include "readFile.h"
#include "writeFile.h"

using namespace std;
using namespace std::chrono;

int main(){
    //int concurrency[7] = {1, 2, 4, 8, 12, 24, 48};
    //long recordSize[3] = {65536, 1048576, 16777216};
    write_bench(1, 1024 * 1024, false);
    // calling a function from workload.cpp
    workload::workload_test();
    return 0;
}