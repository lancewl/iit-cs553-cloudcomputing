#include "MyDiskBench.h"
#include "readFile.h"
#include "writeFile.h"

using namespace std;
using namespace std::chrono;

int main(){
    // thread_test(2, 1024 * 1024, true);
    // calling a function from workload.cpp
    workload::workload_test();
}