#include "internal_sort.h"
#include "external_sort.h"
#include "io.h"

#include <vector>

#include <iostream>
#include <pthread.h>

#include <chrono>
#include <ctime>

#define MAX_MEM 8    // in GB
#define REC_SIZE 100 // in bytes
// run instructions
// ./prog [gensort-filename] [memSize] [debug(0/1/2/3/4)]

void debugger(int debug)
{
    switch (debug)
    {
    case 1:
    {
        std::string test_filename = "data/test_in.txt";
        int numRecordsPerChunk = 1;

        std::string *chunk;
        IO_Helper r_helper(test_filename, numRecordsPerChunk * REC_SIZE);
        int i = 0;
        while (r_helper.isChunkAvailable())
        {
            chunk = r_helper.readChunk();
            int size = r_helper.getRecordsPerChunk();
            heapSort(chunk, size);
            std::string outputFilename = "data/test_out" + std::to_string(i) + ".txt";
            IO_Helper w_helper(outputFilename, 9999); // for writeChunk, chunkSize arg does not matter.
            w_helper.writeChunk(chunk, size);
            delete[] chunk;
            i++;
        }
        break;
    }
    case 2:
    {
        //externalSort();
         break;
    }
    case 3:
    {   
        // Idle...
        unsigned long g = 1000000000;
        int numChunks = 2;
        unsigned long available_mem = numChunks * g;
        std::vector<Buffered_IO_Helper *> ext_helperVec;
        Buffered_IO_Helper *ext_helperPtr;
        ext_helperPtr = new Buffered_IO_Helper("data/in_sorted-0.txt",  available_mem / numChunks, available_mem);
        ext_helperVec.push_back(ext_helperPtr);
        ext_helperPtr = new Buffered_IO_Helper("data/in_sorted-1.txt",  available_mem / numChunks, available_mem);
        ext_helperVec.push_back(ext_helperPtr);
        externalSort(ext_helperVec, available_mem);
        
        // code block
        break;
    }
    case 4: // readChunk
    {
        std::string test_filename = "data/gs.out.test";
        int numRecordsPerChunk = 3;
        IO_Helper h1(test_filename, numRecordsPerChunk * REC_SIZE); // 100bytes per record.
        std::string *chunk;
        std::cout << "h1.getNumChunks(): " << h1.getNumChunks() << std::endl;
        unsigned long currChunkIndex;
        while (h1.isChunkAvailable())
        {
            currChunkIndex = h1.getCurrChunkIndex();
            chunk = h1.readChunk();
            std::cout << "chunk(" << currChunkIndex << ") \t: chunk[0]\t:\t" << chunk[0] << std::endl;
            std::cout << "\t\t: chunk[" << numRecordsPerChunk << "-1]\t:\t" << chunk[h1.getRecordsPerChunk() - 1] << std::endl;
            delete[] chunk;
        }
        std::cout << "readChunk example done." << std::endl;
        break;
    }
    case 5: // writeChunk
    {
        std::string outputFilename = "test.out";
        int numRecords = 3;
        IO_Helper h1(outputFilename, 9999); // for writeChunk, chunkSize arg does not matter.
        std::string *strArr = new std::string[numRecords];
        strArr[0] = "Hello";
        strArr[1] = "from";
        strArr[2] = "Mars";
        // write twice
        h1.writeChunk(strArr, numRecords);
        h1.writeChunk(strArr, numRecords);
        delete[] strArr;
        std::cout << "writeChunk example done." << std::endl;
        break;
    }
    case 6: // dynamic IO_Helper
    {
        std::vector<IO_Helper*> helperVec;
        IO_Helper* helperPtr;
        for(int i = 0; i<3; i++){
            helperPtr = new IO_Helper("data/"+std::to_string(i)+".txt", 9999);
            helperVec.push_back(helperPtr);
        }
        std::string* strArr = new std::string[2];
        strArr[0] = "hello";
        strArr[1] = "world";
        helperVec[0]->writeChunk(strArr, 2);
        helperVec[1]->writeChunk(strArr, 2);
        // clean up
        
        for(unsigned int i = 0; i<helperVec.size(); i++){
            delete helperVec[i];
        }
        // code block
        break;
    }
    case 8: // Buffered_IO_Helper
    {
        // Declaring Buffered_IO_Helper
        std::string test_filename = "data/gs.out.test2";
        int numRecordsPerChunk = 2;
        unsigned long chunkSize = numRecordsPerChunk*REC_SIZE; // The size of each chunk (in bytes)
        int bufSize = 5*chunkSize; // Specify the size of the queue (in bytes)
        Buffered_IO_Helper* bioh = new Buffered_IO_Helper(test_filename, chunkSize, bufSize);  
        bioh->start_thread();
        // Using Buffered_IO_Helper
        while(bioh->isChunkAvailable()){
            std::string *chunk = bioh->readChunk();
            unsigned long currChunkIndex = bioh->getCurrChunkIndex();
            std::cout << "chunk(" << currChunkIndex << ") \t: chunk[0]\t:\t" << chunk[0] << std::endl;
            std::cout << "\t\t: chunk[" << numRecordsPerChunk << "-1]\t:\t" << chunk[bioh->getRecordsPerChunk() - 1] << std::endl;
            delete[] chunk;
        }
        
        delete bioh;
        // code block
        break;
    }
    case 9: // Dynamic Buffered_IO_Helper, declaration and usage
    {
        int numRecordsPerChunk = 2;
        unsigned long chunkSize = numRecordsPerChunk*REC_SIZE; // The size of each chunk (in bytes)
        int bufSize = 3*chunkSize; // Specify the size of the queue (in bytes)
        std::vector<Buffered_IO_Helper*> helperVec;
        Buffered_IO_Helper* helperPtr;
        for(int i = 0; i<3; i++){
            helperPtr = new Buffered_IO_Helper("data/gs.out.test"+std::to_string(i), chunkSize, bufSize);
            helperPtr->start_thread();
            helperVec.push_back(helperPtr);
        }
        // usage:
        for(unsigned int i=0; i<helperVec.size(); i++){ // read all the chunks from all 3 helper pointers
            std::cout << "Reading file:" << helperVec[i]->getFilename() << std::endl;
            while(helperVec[i]->isChunkAvailable()){
                std::string *chunk = helperVec[i]->readChunk();
                unsigned long currChunkIndex = helperVec[i]->getCurrChunkIndex();
                std::cout << "chunk(" << currChunkIndex << ") \t: chunk[0]\t:\t" << chunk[0] << std::endl;
                std::cout << "\t\t: chunk[" << numRecordsPerChunk << "-1]\t:\t" << chunk[helperVec[i]->getRecordsPerChunk() - 1] << std::endl;
                delete[] chunk;
            }
        }
        // clean up
        for(unsigned int i = 0; i<helperVec.size(); i++){
            delete helperVec[i];
        }
        // code block
        break;
    }
    default:
    {
        fprintf(stderr, "DEBUGFLAG ERROR\n");
        exit(EXIT_FAILURE);
    }
    }
}

int main(int argc, char *argv[])
{
    // cmd line arg parsing. Can add more user input sanitization if needed.
    int numArgs = 3;

    if (argc != numArgs + 1)
    {
        fprintf(stderr, "Incorrect args. Usage: %s [gensort-filename] [memSize]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    std::string filename = argv[1];
    std::ifstream f(filename);
    if(!f.good()){
        fprintf(stderr, "Filename not exist.\n");
        exit(EXIT_FAILURE);
    }
    f.close();
    int debug = atoi(argv[3]);
    long memSize = atoi(argv[2]); // user specified memSize, GB
    if (memSize > MAX_MEM)
    { // mem specified too large
        fprintf(stderr, "User specified %ldGB of memory. Too large (MAX_MEM=%dGB)\n", memSize, MAX_MEM);
        exit(EXIT_FAILURE);
    }
    unsigned long available_mem = memSize * 1000000000; // in bytes, for easier alignment with records

    if (debug)
    { // debug runs
        std::cout << "DEBUG BRANCH " << debug << std::endl;
        debugger(debug);
        return 1;
    }

    
    std::string *chunk;
    Buffered_IO_Helper r_helper(filename, available_mem, available_mem);
    std::vector<Buffered_IO_Helper *> ext_helperVec;
    Buffered_IO_Helper *ext_helperPtr;
    
    // logs
    std::fstream logFile;
    if(r_helper.getFileSize()%1000000000!=0){ fprintf(stderr, "Filesize mismatch. Multiple of 1000000000 bytes?\n"); exit(EXIT_FAILURE);}
    int fileSize = r_helper.getFileSize() / 1000000000;
    std::string logfilename = "logs/mySort"+std::to_string(fileSize)+"GB.log";
    logFile.open(logfilename, std::fstream::app);
    auto timenow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    logFile << std::ctime(&timenow);
    auto start = std::chrono::steady_clock::now();
    // Sorting
    r_helper.start_thread(); // Start the queue handler
    logFile << "Input filename: " << r_helper.getFilename() << std::endl;\
    if(r_helper.getNumChunks()==1){
        // only do internal
        logFile << "Fits in memory. Proceeding internal heapSort..." << std::endl;
        chunk = r_helper.readChunk();
        int numRecordsPerChunk = r_helper.getRecordsPerChunk();
        heapSort(chunk, numRecordsPerChunk);
        std::string outputFilename = r_helper.getFilename() + ".sorted";
        IO_Helper w_helper(outputFilename, 9999); // for writeChunk, chunkSize arg does not matter.
        w_helper.clearFile();
        w_helper.writeChunk(chunk, numRecordsPerChunk);
        logFile << "Internal heapSort done. (" << outputFilename << ")." << std::endl;
    }else{
        // do chunked internal, then external
        logFile << "Does not fit in memory. available_mem=" << available_mem << ", fileSize=" << r_helper.getFileSize() << std::endl;
        logFile << "Proceeding with chunked internal heapSort(" << r_helper.getNumChunks() << "chunks), with external k-merge..." << std::endl; 
        logFile << "chunked internal heapSort..." << std::endl;
        int i = 0;
        unsigned long input_buffer_size = available_mem / 2;
        unsigned long output_buffer_size = available_mem / 2;
        int queueSize = 5;
        while (r_helper.isChunkAvailable())
        {
            chunk = r_helper.readChunk();
            int size = r_helper.getRecordsPerChunk();
            heapSort(chunk, size);
            std::string outputFilename = "data/in_sorted-" + std::to_string(i) + ".txt";
            IO_Helper w_helper(outputFilename, 9999); // for writeChunk, chunkSize arg does not matter.
            w_helper.clearFile();
            w_helper.writeChunk(chunk, size);
            delete[] chunk;
            //create IO Helper and store it into the helper vector
            ext_helperPtr = new Buffered_IO_Helper(outputFilename, input_buffer_size / r_helper.getNumChunks() / queueSize, input_buffer_size / r_helper.getNumChunks());
            ext_helperVec.push_back(ext_helperPtr);
            i++;
            
        }
        logFile << "External k-way merge..." << std::endl;
        for(unsigned int i=0; i<ext_helperVec.size(); i++){
            ext_helperVec[i]->start_thread(); // start to fill the buffers
        }
        externalSort(ext_helperVec, output_buffer_size);
        logFile << "External k-way merge done. (merge_output.txt)" << std::endl;
    }
    auto end = std::chrono::steady_clock::now();
    logFile << "Done. Elapsed time in milliseconds : " << std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count() << "ms."<< std::endl;
    logFile.close();
    return 0;
}