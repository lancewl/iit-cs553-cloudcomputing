#include "MyDiskBench.h"
#include "Workload.h"
#include "CreateFiles.h"

using namespace std;
using namespace std::chrono;

int main(){
    create_files(1024 * 1024);
    // calling a function from workload.cpp
    workload::workload_test();
}