#ifndef IO_H
#define IO_H

#include <pthread.h>

#include <iostream>
#include <fstream>


class IO_Helper{
    public:
        IO_Helper(int bs, std::string fn);
        ~IO_Helper();
        int setFileName(std::string fn); // open a new file
        long getFileSize(); // return the fileSize, in bytes
        long getNumRecords(); // return the number of records in the file
        std::string* fileToStrArr(); // read file to memory, and return as string array. Remember to clear memory with delete after use


    private:
        std::string filename;
        unsigned long bufSize; // in bytes
        const int chunksPerQueue = 4;
        int chunkSize;
        unsigned long fileSize;
        unsigned long numRecords;
        // internal sort, i.e. bufSize > fileSize
        std::string* strArr;

        // a private queue to store sorted chunks

        
        friend std::ostream& operator<<(std::ostream &strm, const IO_Helper &h);

};


#endif