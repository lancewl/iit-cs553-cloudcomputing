#include <iostream>
#include <fstream>
#include <chrono>
#include <pthread.h>

using namespace std;
using namespace std::chrono;

#define dataSize 1024* 1024

void *create_files(int recordSize, bool random);
void thread_test(int threads, int recordSize, bool random);