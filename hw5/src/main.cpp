#include "internal_sort.h"
#include "external_sort.h"
#include "io.h"

#include <iostream>

#define MAX_MEM 8    // in GB
#define REC_SIZE 100 // in bytes
// run instructions
// ./prog [gensort-filename] [memSize] [debug(0/1/2/3/4)]

void debugger(int debug)
{
    switch (debug)
    {
    case 1:
    {
        std::string test_filename = "data/test_in.txt";
        int numRecordsPerChunk = 1;
        std::string *chunk;
        IO_Helper r_helper(test_filename, numRecordsPerChunk * REC_SIZE);
        int i = 0;
        while (r_helper.isChunkAvailable())
        {
            chunk = r_helper.readChunk();
            int size = r_helper.getRecordsPerChunk();
            heapSort(chunk, size);
            std::string outputFilename = "data/test_out" + std::to_string(i) + ".txt";
            IO_Helper w_helper(outputFilename, 9999); // for writeChunk, chunkSize arg does not matter.
            w_helper.writeChunk(chunk, size);
            delete[] chunk;
            i++;
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
        // code block
        break;
    }
    case 4:
    {
        // readChunk
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
    case 5:
    {
        // writeChunk
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