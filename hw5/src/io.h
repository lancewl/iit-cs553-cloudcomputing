#ifndef IO_H
#define IO_H

#include <pthread.h>

#include <iostream>
#include <fstream>
#include <queue>
#include <semaphore.h>

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
        

        void openFile(std::string fn); // open a file, and check the fileSize
        void closeFile();
        
        friend std::ostream& operator<<(std::ostream &strm, const IO_Helper &h);
};

class Buffered_IO_Helper{
    public:
        Buffered_IO_Helper(std::string filename, unsigned long chunkSize, unsigned long bufferSize);
        ~Buffered_IO_Helper();
        std::string getFilename();
        unsigned long getFileSize(); // return the fileSize, in bytes
        unsigned long getRecordsPerChunk();
        unsigned long getNumChunks();
        unsigned long getCurrChunkIndex();

        void clearFile(); // clean up the opened file

        bool isChunkAvailable(); // true if there are chunks left
        std::string* readChunk(); // returns a string array of that chunk
        void writeChunk(std::string* strArr, unsigned long numRecords); // append chunk to eof

        pthread_t tid_;
        void start_thread();
        
    private:
        unsigned long bufferSize_;
        unsigned int maxItems_;
        unsigned long headChunkIndex_;

        IO_Helper* ih_;
        
        std::queue<std::string*>* bufferQueue_;
        sem_t itemAvailable_;
        sem_t haveSpace_;

        sem_t isWriting_;

};

#endif