#include "MyDiskBench.h"
#include "readFile.h"
#include "writeFile.h"

using namespace std;
using namespace std::chrono;

int main(){
    write_bench(1, 64 * 1024, true);
    // calling a function from workload.cpp
    //workload::workload_test();
}