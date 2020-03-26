#include <iostream>
#include <fstream>
#include <chrono>
#include <pthread.h>

using namespace std;
using namespace std::chrono;

#define dataSize 10*1024*1024*1024 //10 GB

void *create_files(void *threadarg);
void write_bench(int threads, long recordSize, bool random);