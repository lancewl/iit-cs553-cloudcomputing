#include "readFile.h"
using namespace std;
using namespace std::chrono;

namespace workload{
    int workload_test(){
        // run the workload test for D1 to D7. 
        // workload types: RS, WS, RR, WR
        // sequential read, random read, sequential write, random write
        // save results to memory, and write it to "results.out" when the test is done.
        
        // D1
        milliseconds d1_ws_results[3];
        workload::d1_rs(d1_ws_results);
        milliseconds d1_rs_results[3];
        workload::d1_rr(d1_rs_results);
        /*
        cout << "64KB :" <<  d1_ws_results[0].count() << endl;
        cout << "1MB :" << d1_ws_results[1].count() << endl;
        cout << "16MB :" << d1_ws_results[2].count() << endl;

        cout << "64KB :" <<  d1_rs_results[0].count() << endl;
        cout << "1MB :" << d1_rs_results[1].count() << endl;
        cout << "16MB :" << d1_rs_results[2].count() << endl;
        */

        // read from D2, two threads

        printf("workload_test() NOT IMPLEMENTED YET.\n");
        return -1;   
    }

    int d1_rs(milliseconds *results){
        char * memblock;
        unsigned long recordSizes[] = {64000, 1000000, 16000000};
        unsigned long recordSize;
        ifstream file;

        for(int i=0; i < 3; i++){
            recordSize = recordSizes[i];
            file.open("data/D1/1");
            if(!file.is_open()){ printf("File err\n"); exit(-1);}
            file.seekg(0, ios::end);
            unsigned long fileSize = file.tellg();
            file.seekg(0, ios::beg);
            memblock = new char[recordSize];

            auto start = high_resolution_clock::now();
            // ----- vvvTIME THIS CHUNKvvv -----
            while((unsigned long)file.tellg()+recordSize < fileSize){
                file.read(memblock, recordSize);
            }
            long rem = fileSize - file.tellg();
            if(rem > 0){
                file.read(memblock, rem);
            }
            // ----- ^^^TIME THIS CHUNK^^^ -----
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<milliseconds>(stop - start);
            cout << "(D1)recordSize " << recordSize << " done. " << "fileSize=" << fileSize << endl;
            delete[] memblock;
            file.close();
            // save the result to the array
            results[i] = duration;
        }
        return 0;
    }
    int d1_rr(milliseconds *results){
        char * memblock;
        unsigned long recordSizes[] = {64000, 1000000, 16000000};
        unsigned long recordSize;
        ifstream file;

        for(int i=0; i < 3; i++){
            recordSize = recordSizes[i];
            file.open("data/D1/1");
            if(!file.is_open()){ printf("File err\n"); exit(-1);}
            file.seekg(0, ios::end);
            unsigned long fileSize = file.tellg();
            file.seekg(0, ios::beg);
            memblock = new char[recordSize];
            // create a list of random positions
            long numPos = fileSize/recordSize;
            long posRange = fileSize-recordSize; // make sure it doesn't reach eof
            unsigned long posList[numPos];
            for(int i=0; i<numPos; i++){
                posList[i] = (unsigned long)rand()%posRange;
            }
            auto start = high_resolution_clock::now();
            // ----- vvvTIME THIS CHUNKvvv -----
            for(unsigned long pos: posList){
                file.seekg(pos); // seek to a random-ish position
                file.read(memblock, recordSize); // and read the block
            }
            // ----- ^^^TIME THIS CHUNK^^^ -----
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<milliseconds>(stop - start);
            cout << "(D1)recordSize " << recordSize << " done. " << "fileSize=" << fileSize << endl;
            // cleanup
            delete[] memblock;
            file.close();
            // save the result to the array
            results[i] = duration;
        }
        return 0;
    }

    int stdlib_rs(char *filename){
        size_t recordSize = 64000; // 64KB(64000), 1MB(1000000), 16MB(16000000) 
        FILE * pFile;
        char * memblock;
        // read from D1, 1
        pFile = fopen(filename, "rb");
        if(pFile == NULL){ fputs("File not found", stderr); exit(-1);}
        fseek (pFile , 0 , SEEK_END);
        unsigned long fileSize = ftell (pFile);
        rewind (pFile);
        memblock = (char *) malloc(sizeof(char)*recordSize);

        // ----- vvvTIME THIS CHUNKvvv -----
        while(ftell(pFile)+recordSize < fileSize){
            fread(memblock, recordSize, 1, pFile); 
            // cout << ftell(pFile) << endl;
        }
        // read the remaining bytes if there is any.
        long rem = fileSize - ftell(pFile);
        if(rem > 0){
            fread(memblock, rem, 1, pFile);
        }
        // ----- ^^^TIME THIS CHUNK^^^ -----
        free(memblock);
        return 0;
    }
}
