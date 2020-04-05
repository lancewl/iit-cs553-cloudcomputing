#include "sort.h"
#include "merge.h"
#include "io.h"

#include <iostream>

#define MAX_MEM 64 // in GB

// run instructions
// ./prog [gensort-filename] [memSize] [debugFlag(0/1/2/3)]


int main(int argc, char *argv[]){
    // cmd line arg parsing. Can add more user input sanitization if needed.
    int numArgs = 3;
    
    if(argc != numArgs+1){
        fprintf(stderr, "Incorrect args. Usage: %s [gensort-filename] [memSize]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    std::string filename = argv[1];
    int debugFlag = atoi(argv[3]);
    int memSize = atoi(argv[2]); // user specified memSize
    if(memSize > MAX_MEM){ // mem specified too large
        fprintf(stderr, "User specified %dGB of memory. Too large (MAX_MEM=%dGB)\n", memSize, MAX_MEM);
        exit(EXIT_FAILURE);
    }

    if(debugFlag!=0){ // debug runs
        std::cout << "DEBUG BRANCH " << debugFlag << std::endl;
        if(debugFlag==1){
            // debug branch for lance 
            // test your code here
            // ...

        }else if(debugFlag==2){
            // debug branch for kevin
            // test your code here
            // ...

        }else if(debugFlag==3){
            // debug branch for justin
            
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