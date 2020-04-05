#include "sort.h"
#include "merge.h"
#include "io.h"

#define AVAILABLE_MEM 16 // in GB

int main(int argc, char *argv[]){
    // cmd line arg parsing
    std::string filename;
    int memSize = AVAILABLE_MEM; // amount of memory availble in 

    // check filesize using function in io.cpp, in namespace io.

    // if size is smaller than memSize, do simple in-memory sort

    // otherwise call function in merge.cpp to do external sort i.e. k-way merge


    cout << "IMPLEMENTATION INCOMPLETE." << endl;
    return 0;    
}