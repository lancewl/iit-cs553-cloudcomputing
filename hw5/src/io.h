#ifndef IO_H
#define IO_H

#include <pthread.h>

#include <iostream>
#include <fstream>
#include <queue>

// TODO:
// setup queues for memory chunks. c++ templates or maybe vectors.
// make sure the queue behaves correctly,
// then do multithreading with pthreads

class IO_Helper{
    public:
        IO_Helper(std::string filename, unsigned long chunkSize);
        ~IO_Helper();
        unsigned long getFileSize(); // return the fileSize, in bytes
        unsigned long getRecordsPerChunk();
        unsigned long getNumChunks();
        unsigned long getCurrChunkIndex();

        bool isChunkAvailable(); // true if there are chunks left
        std::string* readChunk(); // returns a string array of that chunk
        void writeChunk(std::string* strArr, unsigned long numRecords); // append chunk to eof

    private:
        std::string filename_;
        std::fstream file_;
        unsigned long fileSize_;
        unsigned long numRecords_;
        unsigned long chunkSize_;
        unsigned long numChunks_;
        unsigned long recordsPerChunk_;
        unsigned long currChunkIndex_;
        

        void openFile(std::string fn); // open a file, and check the fileSize
        void closeFile();
        
        friend std::ostream& operator<<(std::ostream &strm, const IO_Helper &h);
};


#endif