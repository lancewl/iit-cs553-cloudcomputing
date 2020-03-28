#include "MyDiskBench.h"
#include "readFile.h"
#include "writeFile.h"

using namespace std;
using namespace std::chrono;

int main(){
    int concurrency[7] = {1, 2, 4, 8, 12, 24, 48};
    long recordSize[3] = {65536, 1048576, 16777216};
    bool workload[2] = {false, true};
    for(int k = 0; k < 2; k++)
    {
        for (int j = 0; j < 7; j++)
        {
            for (int i = 0; i < 3; i++)
            {
                if (workload[k])
                    cout << "WR => Threads: " << concurrency[j] << " Record Size: " << recordSize[i] << endl;
                else
                    cout << "WS => Threads: " << concurrency[j] << " Record Size: " << recordSize[i] << endl;
                write_bench(concurrency[j], recordSize[i], workload[k], false);
            }
        }
    }
    
    
    // calling a function from workload.cpp
    workload::workload_test();
    return 0;
}