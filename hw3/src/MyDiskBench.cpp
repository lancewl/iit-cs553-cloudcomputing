#include "MyDiskBench.h"
#include "readFile.h"
#include "writeFile.h"

using namespace std;
using namespace std::chrono;

int main()
{
    int concurrency[7] = {1, 2, 4, 8, 12, 24, 48};
    long recordSize[3] = {65536, 1048576, 16777216};
    bool workload[2] = {false, true};

    cout << "WR(IOPS) Benchmark" << endl
         << "numThreads    recordSize(B)	Throughput(OSP/s)" << endl;
    for (int j = 0; j < 7; j++)
    {
        cout << concurrency[j] << "    4KB    ";
        write_bench(1073741824, concurrency [j], 4096, true, true, false);
    }
    for (int k = 0; k < 2; k++)
    {
        if (workload[k])
            cout << "WR Benchmark" << endl
                 << "numThreads    recordSize(B)	Throughput(MB/s)" << endl;
        else
            cout << "WS Benchmark" << endl
                 << "numThreads    recordSize(B)	Throughput(MB/s)" << endl;
        for (int j = 0; j < 7; j++)
        {
            for (int i = 0; i < 3; i++)
            {
                cout << concurrency[j] << "    " << recordSize[i] << "    ";
                write_bench(10737418240, concurrency [j], recordSize[i], workload[k], false, false);
            }
        }
    }
    // calling a function from readFile.cpp
    //ReadTest::workload_init();
    ReadTest::rs_rr_test();
    ReadTest::iops_rr_test();
    //ReadTest::workload_clean();
    return 0;
}