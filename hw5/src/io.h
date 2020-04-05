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
        IO_Helper(int bs, std::string fn);
        ~IO_Helper();
        int setFileName(std::string fn); // open a new file
        long getFileSize(); // return the fileSize, in bytes
        long getNumRecords(); // return the number of records in the file
        bool fitInMem(); // returns true if the entire file fits in memory, else returns false
        // for in-memory sort
        std::string* fileToStrArr(); // read file to memory, and return as string array. Remember to free memory with delete after use
        int strArrToFile(std::string outputfn, std::string* strArr, unsigned long numRecords); // write string array to file
        
        // for external sort k-way merge
        void setChunkSize(unsigned long cs); // set the chunk size, in bytes. i.e. what is the size of the currently sorted chunks
        // note: logically chunkSize MUST be larger than bufSize, otherwise we should be using in-memory sort IO instead
        void setChunkIndex(unsigned long ci); // set the current chunk index
        
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

        static std::string* readChunk(std::string fn, unsigned long cs, int ci); // filename chunksize chunkindex. returns a string array of that chunk


    private:
        std::string filename;
        unsigned long bufSize; // in bytes
        unsigned long chunkSize;
        unsigned long numChunks;
        unsigned long fileSize;
        unsigned long numRecords;
        // two private queue to store sorted loaded chunks

        
        friend std::ostream& operator<<(std::ostream &strm, const IO_Helper &h);

};


#endif