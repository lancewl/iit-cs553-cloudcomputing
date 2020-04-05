#include "internal_sort.h"
#include "external_sort.h"
#include "io.h"

#include <iostream>

#define MAX_MEM 64 // in GB

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
            std::string test_string = "asjdvmalsdjaasdcAASFSAC";
            std::cout << test_string << std::endl;
            mergeSort(test_string, 0, test_string.size());
            std::cout << test_string << std::endl;
        }else if(debugFlag==2){
            // debug branch for kevin
            // test your code here
            // ...

        }else if(debugFlag==3){
            // debug branch for justin
            // create a IO_Helper

            
        }else if(debugFlag==4){ // example usage of IO_Helper
            unsigned long memSize_B = (unsigned long) memSize*1000*1000*1000; // in bytes
            IO_Helper h1 (memSize_B, "data/gs.out.1"); // memSize: amount of memory available to use, and path to the gensort data file
            if(h1.fitInMem()){ // if the file is small enough
                std::string* strArr = h1.fileToStrArr(); // read the entire file to memory as string array
                std::cout << strArr[0] << std::endl << strArr[h1.getNumRecords()-1] << std::endl;
                delete[] strArr; // !! remember to free the memory !!
            }else{
                std::cout << "memSize available too small" << std::endl;
            }
            // write a strArr to file
            std::string outputfn = "out.txt";
            std::string strArr[5] = {"hi", "hello", "apple", "banana", "ok"};
            int numRecords = 5;
            h1.strArrToFile(outputfn, strArr, numRecords);            

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