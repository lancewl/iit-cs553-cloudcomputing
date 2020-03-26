#include <iostream>
#include <fstream>
#include <chrono>
#include <pthread.h>

using namespace std;
using namespace std::chrono;

#define dataSize 10*1024*1024*1024 //10 GB

void *create_files(int recordSize, bool random);
void write_bench(int threads, int recordSize, bool random);