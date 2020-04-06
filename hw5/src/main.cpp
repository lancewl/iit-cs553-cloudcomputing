#include "internal_sort.h"
#include "external_sort.h"
#include "io.h"

#include <iostream>

#define MAX_MEM 8 // in GB
#define REC_SIZE 100 // in bytes
// run instructions
// ./prog [gensort-filename] [memSize] [debugFlag(0/1/2/3/4)]

int main(int argc, char *argv[]){
    // cmd line arg parsing. Can add more user input sanitization if needed.
    int numArgs = 3;
    
    if(argc != numArgs+1){
        fprintf(stderr, "Incorrect args. Usage: %s [gensort-filename] [memSize]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    std::string filename = argv[1];
    int debugFlag = atoi(argv[3]);
    int memSize = atoi(argv[2]); // user specified memSize, GB
    if(memSize > MAX_MEM){ // mem specified too large
        fprintf(stderr, "User specified %dGB of memory. Too large (MAX_MEM=%dGB)\n", memSize, MAX_MEM);
        exit(EXIT_FAILURE);
    }

    if(debugFlag!=0){ // debug runs
        std::cout << "DEBUG BRANCH " << debugFlag << std::endl;
        if(debugFlag==1){
            std::string test_string[] = {"AsfAGHM5om 00000000000000000000000000000000", "_sHd0jDv6X 00000000000000000000000000000001", "uI^EYm8s=| 00000000000000000000000000000002", "Q)JN)R9z-L 00000000000000000000000000000003"};
            int size = sizeof(test_string) / sizeof(test_string[0]);
            std::cout << size << std::endl;
            for(int i = 0; i < size; i++)
                std::cout << test_string[i] << std::endl;
            heapSort(test_string, size);
            std::cout << test_string << std::endl;
            for (int i = 0; i < size; i++)
                std::cout << test_string[i] << std::endl;
        }else if(debugFlag==2){
            // debug branch for kevin
            // test your code here
            // ...

        }else if(debugFlag==3){
            // debug branch for justin
            // create a IO_Helper
            

        }else if(debugFlag==4){ // example usage of IO_Helper
        // readChunk
            std::string test_filename = "data/gs.out.test";
            int numRecordsPerChunk = 3;
            IO_Helper h1(test_filename, numRecordsPerChunk*REC_SIZE); // 100bytes per record. 
            std::string* chunk;
            std::cout << "h1.getNumChunks(): " << h1.getNumChunks() << std::endl;
            unsigned long currChunkIndex;
            while(h1.isChunkAvailable()){
                currChunkIndex = h1.getCurrChunkIndex();
                chunk = h1.readChunk();
                std::cout << "chunk(" << currChunkIndex << ") \t: chunk[0]\t:\t" << chunk[0] << std::endl;
                std::cout << "\t\t: chunk[" << numRecordsPerChunk << "-1]\t:\t" << chunk[h1.getRecordsPerChunk()-1] << std::endl;
                delete[] chunk;
            }
            std::cout << "readChunk example done." << std::endl;
        }else if(debugFlag==5){ // example usage of IO_Helper
        // writeChunk
            std::string outputFilename = "test.out";
            int numRecords = 3;
            IO_Helper h1(outputFilename, 9999); // for writeChunk, chunkSize arg does not matter.
            std::string* strArr = new std::string[numRecords];
            strArr[0] = "Hello";
            strArr[1] = "from";
            strArr[2] = "Mars";
            // write twice
            h1.writeChunk(strArr, numRecords);
            h1.writeChunk(strArr, numRecords);
            delete[] strArr;
            std::cout << "writeChunk example done." << std::endl;
        }else{
            fprintf(stderr, "DEBUGFLAG ERROR\n"); exit(EXIT_FAILURE);
        }
        return 1;
    }

    // normal runs
    // check filesize using function in io.cpp, in namespace io.

    // if size is smaller than memSize, do simple in-memory sort

    // otherwise call function in merge.cpp to do external sort i.e. k-way merge

    std::cout << "IMPLEMENTATION INCOMPLETE." << std::endl;
    return 0;    
}