#include "MyDiskBench.h"
#include "readFile.h"
#include "writeFile.h"

using namespace std;
using namespace std::chrono;

int main(){
    int concurrency[7] = {1, 2, 4, 8, 12, 24, 48};
    long recordSize[3] = {65536, 1048576, 16777216};
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            cout << "WS => Threads: " << concurrency[j] << " Record Size: " << recordSize[i] << endl;
            write_bench(concurrency[j], recordSize[i], false, false);
            cout << "WR => Threads: " << concurrency[j] << " Record Size: " << recordSize[i] << endl;
            write_bench(concurrency[j], recordSize[i], true, false);
        }
    }
    
    // calling a function from workload.cpp
    workload::workload_test();
    return 0;
}