#include "internal_sort.h"
#include "external_sort.h"
#include "io.h"

#include <vector>

#include <iostream>
#include <pthread.h>


#define MAX_MEM 8    // in GB
#define REC_SIZE 100 // in bytes
// run instructions
// ./prog [gensort-filename] [memSize] [debug(0/1/2/3/4)]
struct args
{
    int threadID;
    std::string filename;
    unsigned long chunkSize;
};


void *thread_func(void *input){
    std::cout << "Thread created." << std::endl;
    // do stuffs
    struct args* a = (struct args*)input;
    IO_Helper* h = new IO_Helper(a->filename, a->chunkSize);
    std::string *chunk;
    std::cout << "h1.getNumChunks(): " << h->getNumChunks() << std::endl;
    unsigned long currChunkIndex;
    while (h->isChunkAvailable())
    {
        currChunkIndex = h->getCurrChunkIndex();
        chunk = h->readChunk();
        std::cout << "chunk(" << currChunkIndex << ") \t: chunk[0]\t:\t" << chunk[0] << std::endl;
        std::cout << "\t\t: chunk[" << a->chunkSize/REC_SIZE << "-1]\t:\t" << chunk[h->getRecordsPerChunk() - 1] << std::endl;
        delete[] chunk;
    }
    delete h;
    std::cout << "readChunk done." << std::endl;
    std::cout << "Thread(" << a->threadID << ") done." << std::endl;
}

void debugger(int debug)
{
    switch (debug)
    {
    case 1:
    {
        std::string test_filename = "data/gs.out.test";
        std::string outputFilename = "data/gs.out.test.sorted";
        int numRecordsPerChunk = 10;
        std::string *chunk;
        IO_Helper r_helper(test_filename, numRecordsPerChunk * REC_SIZE);
        IO_Helper w_helper(outputFilename, 9999); // for writeChunk, chunkSize arg does not matter.

        while (r_helper.isChunkAvailable())
        {
            chunk = r_helper.readChunk();
            int size = r_helper.getRecordsPerChunk();
            heapSort(chunk, size);
            w_helper.writeChunk(chunk, size);
            delete[] chunk;
        }
        break;
    }
    case 2:
    {
        // code block
        break;
    }
    case 3:
    {
        // try threads and concurrent usage of IO_Helper.
        int numRecordsPerChunk = 3;
        // create 3 threads
        pthread_t tidArr[3];
        for(int i = 0; i < 3; i++){
            struct args *a = (struct args*)malloc(sizeof(struct args));
            a->threadID = i;
            a->chunkSize = numRecordsPerChunk*REC_SIZE;
            a->filename = "data/gs.out.test"+std::to_string(i);
            pthread_create(&tidArr[i], NULL, thread_func, (void *)a);
        }

        // join all threads
        for(int i = 0; i < 3; i++){
            pthread_join(tidArr[i], NULL);
        }
        // code block
        break;
    }
    case 4: // readChunk
    {
        std::string test_filename = "data/gs.out.test";
        int numRecordsPerChunk = 3;
        IO_Helper h1(test_filename, numRecordsPerChunk * REC_SIZE); // 100bytes per record.
        std::string *chunk;
        std::cout << "h1.getNumChunks(): " << h1.getNumChunks() << std::endl;
        unsigned long currChunkIndex;
        while (h1.isChunkAvailable())
        {
            currChunkIndex = h1.getCurrChunkIndex();
            chunk = h1.readChunk();
            std::cout << "chunk(" << currChunkIndex << ") \t: chunk[0]\t:\t" << chunk[0] << std::endl;
            std::cout << "\t\t: chunk[" << numRecordsPerChunk << "-1]\t:\t" << chunk[h1.getRecordsPerChunk() - 1] << std::endl;
            delete[] chunk;
        }
        std::cout << "readChunk example done." << std::endl;
        break;
    }
    case 5: // writeChunk
    {
        std::string outputFilename = "test.out";
        int numRecords = 3;
        IO_Helper h1(outputFilename, 9999); // for writeChunk, chunkSize arg does not matter.
        std::string *strArr = new std::string[numRecords];
        strArr[0] = "Hello";
        strArr[1] = "from";
        strArr[2] = "Mars";
        // write twice
        h1.writeChunk(strArr, numRecords);
        h1.writeChunk(strArr, numRecords);
        delete[] strArr;
        std::cout << "writeChunk example done." << std::endl;
        break;
    }
    case 6: // dynamic IO_Helper
    {
        std::vector<IO_Helper*> helperVec;
        IO_Helper* helperPtr;
        for(int i = 0; i<3; i++){
            
            helperPtr = new IO_Helper("data/"+std::to_string(i)+".txt", 9999);
            helperVec.push_back(helperPtr);
        }
        std::string* strArr = new std::string[2];
        strArr[0] = "hello";
        strArr[1] = "world";
        helperVec[0]->writeChunk(strArr, 2);
        helperVec[1]->writeChunk(strArr, 2);
        // clean up
        
        for(int i = 0; i<helperVec.size(); i++){
            delete helperVec[i];
        }
        // code block
        break;
    }
    default:
    {
        fprintf(stderr, "DEBUGFLAG ERROR\n");
        exit(EXIT_FAILURE);
    }
    }
}

int main(int argc, char *argv[])
{
    // cmd line arg parsing. Can add more user input sanitization if needed.
    int numArgs = 3;

    if (argc != numArgs + 1)
    {
        fprintf(stderr, "Incorrect args. Usage: %s [gensort-filename] [memSize]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    std::string filename = argv[1];
    int debug = atoi(argv[3]);
    int memSize = atoi(argv[2]); // user specified memSize, GB
    if (memSize > MAX_MEM)
    { // mem specified too large
        fprintf(stderr, "User specified %dGB of memory. Too large (MAX_MEM=%dGB)\n", memSize, MAX_MEM);
        exit(EXIT_FAILURE);
    }

    if (debug)
    { // debug runs
        std::cout << "DEBUG BRANCH " << debug << std::endl;
        debugger(debug);
        return 1;
    }

    // normal runs
    // check filesize using function in io.cpp, in namespace io.

    // if size is smaller than memSize, do simple in-memory sort

    // otherwise call function in merge.cpp to do external sort i.e. k-way merge

    std::cout << "IMPLEMENTATION INCOMPLETE." << std::endl;
    return 0;
}