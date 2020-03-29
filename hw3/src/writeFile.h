#include <iostream>
#include <fstream>
#include <chrono>
#include <pthread.h>

using namespace std;
using namespace std::chrono;

void *create_files(void *threadarg);
void write_bench(int threads, long recordSize, bool random, bool debug);
