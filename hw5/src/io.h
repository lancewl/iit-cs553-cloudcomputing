#ifndef IO_H
#define IO_H

#include <pthread.h>

#include <iostream>
#include <fstream>


// TODO:
// setup queues for memory chunks. c++ templates or maybe vectors.
// make sure the queue behaves correctly,
// then do multithreading with pthreads

class IO_Helper{
    public:
        IO_Helper(unsigned long memSize, std::string filename);
        ~IO_Helper();
        int setFileName(std::string fn); // open a new file
        unsigned long getFileSize(); // return the fileSize, in bytes
        unsigned long getNumRecords(); // return the number of records in the file
        bool fitInMem(); // returns true if the entire file fits in memory, else returns false
        // for in-memory sort
        std::string* fileToStrArr(); // read file to memory, and return as string array. Remember to free memory with delete after use
        int strArrToFile(std::string outputFilename, std::string* strArr, unsigned long numRecords); // write string array to file
        
        // for external sort k-way merge
        // note: logically chunkSize MUST be larger than bufSize, otherwise we should be using in-memory sort IO instead

        void setChunkIndex(unsigned long chunkIndex); // set the current chunk index
        unsigned long getNumChunks(); // get the total number of chunks
        unsigned long currentChunkIndex; // 0 means working on chunk0 and chunk1. 2 mean working on chunk2 and chunk3.
        
        // ready up two queues, chunkAQ, chunkBQ
        // queue access functions
        void chunkQInit(); // initialize the threads that does disk io
        
        void setChunkAQIndex(int i); // sets where to read from the file
        void setChunkBQIndex(int i);
        bool chunkAQIsEmpty(); // true if queue is empty
        bool chunkBQIsEmpty();
        std::string* getNextFromChunkAQ();
        std::string* getNextFromChunkBQ();

        static std::string* readChunk(std::string filename, unsigned long chunkIndex); // returns a string array of that chunk


    private:
        std::string filename_;
        unsigned long memSize_; // in bytes
        unsigned long chunkSize_;
        unsigned long numChunks_;
        unsigned long fileSize_;
        unsigned long numRecords_;
        // two private queue to store sorted loaded chunks

        
        friend std::ostream& operator<<(std::ostream &strm, const IO_Helper &h);

};


#endif