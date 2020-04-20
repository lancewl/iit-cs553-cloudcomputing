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

int main(int argc, char *argv[])
{
    // cmd line arg parsing. Can add more user input sanitization if needed.
    int numArgs = 2;

    if (argc != numArgs + 1)
    {
        fprintf(stderr, "Incorrect args. Usage: %s [gensort-filename] [memSize]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    std::string filename = argv[1];
    std::ifstream f(filename);
    if (!f.good())
    {
        fprintf(stderr, "Filename not exist.\n");
        exit(EXIT_FAILURE);
    }
    f.close();
    long memSize = atoi(argv[2]); // user specified memSize, GB
    if (memSize > MAX_MEM)
    { // mem specified too large
        fprintf(stderr, "User specified %ldGB of memory. Too large (MAX_MEM=%dGB)\n", memSize, MAX_MEM);
        exit(EXIT_FAILURE);
    }
    unsigned long available_mem = memSize * 1000000000; // in bytes, for easier alignment with records

    std::string *chunk;
    IO_Helper r_helper(filename, available_mem);
    std::vector<IO_Helper *> ext_helperVec;
    IO_Helper *ext_helperPtr;

    // logs
    std::fstream logFile;
    if (r_helper.getFileSize() % 1000000000 != 0)
    {
        fprintf(stderr, "Filesize mismatch. Multiple of 1000000000 bytes?\n");
        exit(EXIT_FAILURE);
    }
    int fileSize = r_helper.getFileSize() / 1000000000;
    std::string logfilename = "logs/mySort" + std::to_string(fileSize) + "GB.log";
    logFile.open(logfilename, std::fstream::app);
    auto timenow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    logFile << std::ctime(&timenow);
    auto start = std::chrono::steady_clock::now();
    // Sorting
    //r_helper.start_thread(); // Start the queue handler
    logFile << "Input filename: " << r_helper.getFilename() << std::endl;
    if (r_helper.getNumChunks() == 1)
    {
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
    }
    else
    {
        // do chunked internal, then external
        logFile << "Does not fit in memory. available_mem=" << available_mem << ", fileSize=" << r_helper.getFileSize() << std::endl;
        logFile << "Proceeding with chunked internal heapSort(" << r_helper.getNumChunks() << "chunks), with external k-merge..." << std::endl;
        logFile << "chunked internal heapSort..." << std::endl;
        int i = 0;
        unsigned long input_buffer_size = available_mem / 2;
        unsigned long output_buffer_size = available_mem / 2;
        while (r_helper.isChunkAvailable())
        {
            chunk = r_helper.readChunk();
            int size = r_helper.getRecordsPerChunk();
            heapSort(chunk, size);
            std::string outputFilename = "data/in_sorted-" + std::to_string(i) + ".txt";
            IO_Helper w_helper(outputFilename, 9999); // for writeChunk, chunkSize arg does not matter.
            w_helper.clearFile();
            w_helper.writeChunk(chunk, size);
            //create IO Helper and store it into the helper vector
            ext_helperPtr = new IO_Helper(outputFilename, input_buffer_size / r_helper.getNumChunks());
            ext_helperVec.push_back(ext_helperPtr);
            i++;
        }
        logFile << "External k-way merge..." << std::endl;
        for (unsigned int i = 0; i < ext_helperVec.size(); i++)
        {
            //ext_helperVec[i]->start_thread(); // start to fill the buffers
        }
        externalSort(ext_helperVec, output_buffer_size);
        logFile << "External k-way merge done. (merge_output.txt)" << std::endl;
    }
    auto end = std::chrono::steady_clock::now();
    logFile << "Done. Elapsed time in milliseconds : " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms." << std::endl;
    logFile.close();
    return 0;
}