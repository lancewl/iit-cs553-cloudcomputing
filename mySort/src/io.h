#ifndef IO_H
#define IO_H

#include <pthread.h>

#include <iostream>
#include <fstream>
#include <queue>

class IO_Helper{
    public:
        IO_Helper(std::string filename, unsigned long chunkSize);
        ~IO_Helper();
        std::string getFilename();
        unsigned long getFileSize(); // return the fileSize, in bytes
        unsigned long getRecordsPerChunk();
        unsigned long getNumChunks();
        unsigned long getCurrChunkIndex();

        void clearFile(); // clean up the opened file

        bool isChunkAvailable(); // true if there are chunks left
        std::string* readChunk(); // returns a string array of that chunk
        void writeChunk(std::string* strArr, unsigned long numRecords); // append chunk to eof

    private:
        std::string filename_;
        std::string log_filename_;
        std::fstream file_;
        unsigned long fileSize_;
        unsigned long numRecords_;
        unsigned long chunkSize_;
        unsigned long numChunks_;
        unsigned long recordsPerChunk_;
        unsigned long currChunkIndex_;
        std::string *chunk_;

        void openFile(std::string fn); // open a file, and check the fileSize
        void closeFile();
        
        friend std::ostream& operator<<(std::ostream &strm, const IO_Helper &h);
};

#endif