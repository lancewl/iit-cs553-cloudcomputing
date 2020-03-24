#include "readFile.h"
using namespace std;
using namespace std::chrono;

unsigned long recordSizes[] = {64000, 1000000, 16000000};

// I'm too lazy to deal with arguments passing.
long d1_rs_results[3];
long d1_rr_results[3];
long d2_rs_results[3];
long d2_rr_results[3];
long d3_rs_results[3];
long d3_rr_results[3];
long d4_rs_results[3];
long d4_rr_results[3];
long d5_rs_results[3];
long d5_rr_results[3];
long d6_rs_results[3];
long d6_rr_results[3];
long d7_rs_results[3];
long d7_rr_results[3];

// tempory duration storage
long durations[48];

namespace workload{
    int workload_test(){
        // run the workload test for D1 to D7. 
        // workload types: RS, RR
        // sequential read, random read
        // save results to memory, and write it to "results.out" when the test is done.
        
        // run all the tests
        // D1
        d1_rs();
        d1_rr();
        // read from D2, 2 threads 2 files
        d2_rs();
        d2_rr();
        // D3, 4 threads
        d3_rs();
        d3_rr();
        // D4, 8 threads
        d4_rs();
        d4_rr();
        // D5, 12 threads
        d5_rs();
        d5_rr();
        // D6, 24 threads
        d6_rs();
        d6_rr();
        // D7, 48 threads
        d7_rs();
        d7_rr();

        // TODO: calculate, and save results to a file
        double fileSize = 10000*1000; // in MB/s
        ofstream resultFile;
        // RS
        resultFile.open("RS_result.txt");
        resultFile << "numThreads, recordSize(B), throughput(MB/s)" << endl;
        for(int i=0; i<3; i++){
            resultFile << 1 << ", " << recordSizes[i] << ", " << fileSize/(double)d1_rs_results[i] << endl;
        }
        for(int i=0; i<3; i++){
            resultFile << 2 << ", " << recordSizes[i] << ", " << fileSize/(double)d2_rs_results[i] << endl;
        }
        for(int i=0; i<3; i++){
            resultFile << 4 << ", " << recordSizes[i] << ", " << fileSize/(double)d3_rs_results[i] << endl;
        }
        for(int i=0; i<3; i++){
            resultFile << 8 << ", " << recordSizes[i] << ", " << fileSize/(double)d4_rs_results[i] << endl;
        }
        for(int i=0; i<3; i++){
            resultFile << 12 << ", " << recordSizes[i] << ", " << fileSize/(double)d5_rs_results[i] << endl;
        }
        for(int i=0; i<3; i++){
            resultFile << 24 << ", " << recordSizes[i] << ", " << fileSize/(double)d6_rs_results[i] << endl;
        }
        for(int i=0; i<3; i++){
            resultFile << 48 << ", " << recordSizes[i] << ", " << fileSize/(double)d7_rs_results[i] << endl;
        }
        resultFile.close();

        // RR
        resultFile.open("RR_result.txt");
        resultFile << "numThreads, recordSize(B), throughput(MB/s)" << endl;
        for(int i=0; i<3; i++){
            resultFile << 1 << ", " << recordSizes[i] << ", " << fileSize/(double)d1_rr_results[i] << endl;
        }
        for(int i=0; i<3; i++){
            resultFile << 2 << ", " << recordSizes[i] << ", " << fileSize/(double)d2_rr_results[i] << endl;
        }
        for(int i=0; i<3; i++){
            resultFile << 4 << ", " << recordSizes[i] << ", " << fileSize/(double)d3_rr_results[i] << endl;
        }
        for(int i=0; i<3; i++){
            resultFile << 8 << ", " << recordSizes[i] << ", " << fileSize/(double)d4_rr_results[i] << endl;
        }
        for(int i=0; i<3; i++){
            resultFile << 12 << ", " << recordSizes[i] << ", " << fileSize/(double)d5_rr_results[i] << endl;
        }
        for(int i=0; i<3; i++){
            resultFile << 24 << ", " << recordSizes[i] << ", " << fileSize/(double)d6_rr_results[i] << endl;
        }
        for(int i=0; i<3; i++){
            resultFile << 48 << ", " << recordSizes[i] << ", " << fileSize/(double)d7_rr_results[i] << endl;
        }
        resultFile.close();

        printf("workload_test() done.\n");
        return 0;
    }

    int d1_rs(){
        char * memblock;
        unsigned long recordSize;
        ifstream file;
        file.rdbuf()->pubsetbuf(0, 0);

        for(int i=0; i < 3; i++){
            recordSize = recordSizes[i];
            file.open("data/D1/0");
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
            delete[] memblock;
            file.close();
            // save the result to the array
            d1_rs_results[i] = duration.count();
        }
        return 0;
    }
    int d1_rr(){
        char * memblock;
        unsigned long recordSize;
        ifstream file;
        file.rdbuf()->pubsetbuf(0, 0);

        for(int i=0; i < 3; i++){
            recordSize = recordSizes[i];
            file.open("data/D1/0");
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
            // cleanup
            delete[] memblock;
            file.close();
            // save the result to the array
            cout << "(D1_RR)recordSize " << recordSize << " done. " << endl;
            d1_rr_results[i] = duration.count();
        }
        return 0;
    }

    int d2_rs(){
        int numFiles = 2;
        string prefix = "data/D2/";
        string filenames[2];
        for(int i=0; i<numFiles; i++){
            filenames[i] = prefix+to_string(i);
        }
        unsigned long recordSize;
        for(int i=0; i<3; i++){
            recordSize = recordSizes[i];
            thread w0 (worker, 0, cref(filenames[0]), recordSize, false);
            thread w1 (worker, 1, cref(filenames[1]), recordSize, false);
            w0.join();
            w1.join();
            // retrieve results from durations[]
            long res = 0;
            for(int n=0; n<numFiles; n++){
                if(durations[n] > res){res = durations[n];};
            }
            cout << "(D2_RS)recordSize " << recordSize << " done. " << endl;
            d2_rs_results[i] = res;
        }
        return 0;
    }
    int d2_rr(){
        int numFiles = 2;
        string prefix = "data/D2/";
        string filenames[2];
        for(int i=0; i<numFiles; i++){
            filenames[i] = prefix+to_string(i);
        }
        unsigned long recordSize;
        for(int i=0; i<3; i++){
            recordSize = recordSizes[i];
            thread w0 (worker, 0, cref(filenames[0]), recordSize, true);
            thread w1 (worker, 1, cref(filenames[1]), recordSize, true);
            w0.join();
            w1.join();
            // retrieve results from durations[]
            long res = 0;
            for(int n=0; n<numFiles; n++){
                if(durations[n] > res){res = durations[n];};
            }
            cout << "(D2_RR)recordSize " << recordSize << " done. " << endl;
            d2_rr_results[i] = res;
        }
        return 0;
    }

    int d3_rs(){
        int numFiles = 4;
        string prefix = "data/D3/";
        string filenames[numFiles];
        for(int i=0; i<numFiles; i++){
            filenames[i] = prefix+to_string(i);
        }
        unsigned long recordSize;
        for(int i=0; i<3; i++){
            recordSize = recordSizes[i];
            thread w0 (worker, 0, cref(filenames[0]), recordSize, false);
            thread w1 (worker, 1, cref(filenames[1]), recordSize, false);
            thread w2 (worker, 2, cref(filenames[2]), recordSize, false);
            thread w3 (worker, 3, cref(filenames[3]), recordSize, false);
            w0.join();
            w1.join();
            w2.join();
            w3.join();
            // retrieve results from durations[]
            long res = 0;
            for(int n=0; n<numFiles; n++){ // find the slowest thread
                if(durations[n] > res){res = durations[n];};
            }
            cout << "(D3_RS)recordSize " << recordSize << " done. " << endl;
            d3_rs_results[i] = res;
        }
        return 0;
    }
    int d3_rr(){
        int numFiles = 4;
        string prefix = "data/D3/";
        string filenames[numFiles];
        for(int i=0; i<numFiles; i++){
            filenames[i] = prefix+to_string(i);
        }
        unsigned long recordSize;
        for(int i=0; i<3; i++){
            recordSize = recordSizes[i];
            thread w0 (worker, 0, cref(filenames[0]), recordSize, true);
            thread w1 (worker, 1, cref(filenames[1]), recordSize, true);
            thread w2 (worker, 2, cref(filenames[2]), recordSize, true);
            thread w3 (worker, 3, cref(filenames[3]), recordSize, true);
            w0.join();
            w1.join();
            w2.join();
            w3.join();
            // retrieve results from durations[]
            long res = 0;
            for(int n=0; n<numFiles; n++){ // find the slowest thread
                if(durations[n] > res){res = durations[n];};
            }
            cout << "(D3_RR)recordSize " << recordSize << " done. " << endl;
            d3_rr_results[i] = res;
        }
        return 0;
    }

    int d4_rs(){
        int numFiles = 8;
        string prefix = "data/D4/";
        string filenames[numFiles];
        for(int i=0; i<numFiles; i++){
            filenames[i] = prefix+to_string(i);
        }
        unsigned long recordSize;
        for(int i=0; i<3; i++){
            recordSize = recordSizes[i];
            thread w0 (worker, 0, cref(filenames[0]), recordSize, false);
            thread w1 (worker, 1, cref(filenames[1]), recordSize, false);
            thread w2 (worker, 2, cref(filenames[2]), recordSize, false);
            thread w3 (worker, 3, cref(filenames[3]), recordSize, false);
            thread w4 (worker, 4, cref(filenames[4]), recordSize, false);
            thread w5 (worker, 5, cref(filenames[5]), recordSize, false);
            thread w6 (worker, 6, cref(filenames[6]), recordSize, false);
            thread w7 (worker, 7, cref(filenames[7]), recordSize, false);
            w0.join();
            w1.join();
            w2.join();
            w3.join();
            w4.join();
            w5.join();
            w6.join();
            w7.join();
            // retrieve results from durations[]
            long res = 0;
            for(int n=0; n<numFiles; n++){ // find the slowest thread
                if(durations[n] > res){res = durations[n];};
            }
            cout << "(D4_RS)recordSize " << recordSize << " done. " << endl;
            d4_rs_results[i] = res;
        }
        return 0;
    }
    int d4_rr(){
        int numFiles = 8;
        string prefix = "data/D4/";
        string filenames[numFiles];
        for(int i=0; i<numFiles; i++){
            filenames[i] = prefix+to_string(i);
        }
        unsigned long recordSize;
        for(int i=0; i<3; i++){
            recordSize = recordSizes[i];
            thread w0 (worker, 0, cref(filenames[0]), recordSize, true);
            thread w1 (worker, 1, cref(filenames[1]), recordSize, true);
            thread w2 (worker, 2, cref(filenames[2]), recordSize, true);
            thread w3 (worker, 3, cref(filenames[3]), recordSize, true);
            thread w4 (worker, 4, cref(filenames[4]), recordSize, true);
            thread w5 (worker, 5, cref(filenames[5]), recordSize, true);
            thread w6 (worker, 6, cref(filenames[6]), recordSize, true);
            thread w7 (worker, 7, cref(filenames[7]), recordSize, true);
            w0.join();
            w1.join();
            w2.join();
            w3.join();
            w4.join();
            w5.join();
            w6.join();
            w7.join();
            // retrieve results from durations[]
            long res = 0;
            for(int n=0; n<numFiles; n++){ // find the slowest thread
                if(durations[n] > res){res = durations[n];};
            }
            cout << "(D4_RR)recordSize " << recordSize << " done. " << endl;
            d4_rr_results[i] = res;
        }
        return 0;
    }
    
    int d5_rs(){
        int numFiles = 12;
        string prefix = "data/D5/";
        string filenames[numFiles];
        for(int i=0; i<numFiles; i++){
            filenames[i] = prefix+to_string(i);
        }
        unsigned long recordSize;
        for(int i=0; i<3; i++){
            recordSize = recordSizes[i];
            thread w0 (worker, 0, cref(filenames[0]), recordSize, false);
            thread w1 (worker, 1, cref(filenames[1]), recordSize, false);
            thread w2 (worker, 2, cref(filenames[2]), recordSize, false);
            thread w3 (worker, 3, cref(filenames[3]), recordSize, false);
            thread w4 (worker, 4, cref(filenames[4]), recordSize, false);
            thread w5 (worker, 5, cref(filenames[5]), recordSize, false);
            thread w6 (worker, 6, cref(filenames[6]), recordSize, false);
            thread w7 (worker, 7, cref(filenames[7]), recordSize, false);
            thread w8 (worker, 8, cref(filenames[8]), recordSize, false);
            thread w9 (worker, 9, cref(filenames[9]), recordSize, false);
            thread w10 (worker, 10, cref(filenames[10]), recordSize, false);
            thread w11 (worker, 11, cref(filenames[11]), recordSize, false);
            w0.join();
            w1.join();
            w2.join();
            w3.join();
            w4.join();
            w5.join();
            w6.join();
            w7.join();
            w8.join();
            w9.join();
            w10.join();
            w11.join();
            // retrieve results from durations[]
            long res = 0;
            for(int n=0; n<numFiles; n++){ // find the slowest thread
                if(durations[n] > res){res = durations[n];};
            }
            cout << "(D5_RS)recordSize " << recordSize << " done. " << endl;
            d5_rs_results[i] = res;
        }
        return 0;
    }
    int d5_rr(){
        int numFiles = 12;
        string prefix = "data/D5/";
        string filenames[numFiles];
        for(int i=0; i<numFiles; i++){
            filenames[i] = prefix+to_string(i);
        }
        unsigned long recordSize;
        for(int i=0; i<3; i++){
            recordSize = recordSizes[i];
            thread w0 (worker, 0, cref(filenames[0]), recordSize, true);
            thread w1 (worker, 1, cref(filenames[1]), recordSize, true);
            thread w2 (worker, 2, cref(filenames[2]), recordSize, true);
            thread w3 (worker, 3, cref(filenames[3]), recordSize, true);
            thread w4 (worker, 4, cref(filenames[4]), recordSize, true);
            thread w5 (worker, 5, cref(filenames[5]), recordSize, true);
            thread w6 (worker, 6, cref(filenames[6]), recordSize, true);
            thread w7 (worker, 7, cref(filenames[7]), recordSize, true);
            thread w8 (worker, 8, cref(filenames[8]), recordSize, true);
            thread w9 (worker, 9, cref(filenames[9]), recordSize, true);
            thread w10 (worker, 10, cref(filenames[10]), recordSize, true);
            thread w11 (worker, 11, cref(filenames[11]), recordSize, true);
            w0.join();
            w1.join();
            w2.join();
            w3.join();
            w4.join();
            w5.join();
            w6.join();
            w7.join();
            w8.join();
            w9.join();
            w10.join();
            w11.join();
            // retrieve results from durations[]
            long res = 0;
            for(int n=0; n<numFiles; n++){ // find the slowest thread
                if(durations[n] > res){res = durations[n];};
            }
            cout << "(D5_RR)recordSize " << recordSize << " done. " << endl;
            d5_rr_results[i] = res;
        }
        return 0;
    }
    
    int d6_rs(){
        int numFiles = 24;
        string prefix = "data/D6/";
        string filenames[numFiles];
        for(int i=0; i<numFiles; i++){
            filenames[i] = prefix+to_string(i);
        }
        unsigned long recordSize;
        for(int i=0; i<3; i++){
            recordSize = recordSizes[i];
            thread w0 (worker, 0, cref(filenames[0]), recordSize, false);
            thread w1 (worker, 1, cref(filenames[1]), recordSize, false);
            thread w2 (worker, 2, cref(filenames[2]), recordSize, false);
            thread w3 (worker, 3, cref(filenames[3]), recordSize, false);
            thread w4 (worker, 4, cref(filenames[4]), recordSize, false);
            thread w5 (worker, 5, cref(filenames[5]), recordSize, false);
            thread w6 (worker, 6, cref(filenames[6]), recordSize, false);
            thread w7 (worker, 7, cref(filenames[7]), recordSize, false);
            thread w8 (worker, 8, cref(filenames[8]), recordSize, false);
            thread w9 (worker, 9, cref(filenames[9]), recordSize, false);
            thread w10 (worker, 10, cref(filenames[10]), recordSize, false);
            thread w11 (worker, 11, cref(filenames[11]), recordSize, false);
            thread w12 (worker, 12, cref(filenames[12]), recordSize, false);
            thread w13 (worker, 13, cref(filenames[13]), recordSize, false);
            thread w14 (worker, 14, cref(filenames[14]), recordSize, false);
            thread w15 (worker, 15, cref(filenames[15]), recordSize, false);
            thread w16 (worker, 16, cref(filenames[16]), recordSize, false);
            thread w17 (worker, 17, cref(filenames[17]), recordSize, false);
            thread w18 (worker, 18, cref(filenames[18]), recordSize, false);
            thread w19 (worker, 19, cref(filenames[19]), recordSize, false);
            thread w20 (worker, 20, cref(filenames[20]), recordSize, false);
            thread w21 (worker, 21, cref(filenames[21]), recordSize, false);
            thread w22 (worker, 22, cref(filenames[22]), recordSize, false);
            thread w23 (worker, 23, cref(filenames[23]), recordSize, false);
            w0.join();
            w1.join();
            w2.join();
            w3.join();
            w4.join();
            w5.join();
            w6.join();
            w7.join();
            w8.join();
            w9.join();
            w10.join();
            w11.join();
            w12.join();
            w13.join();
            w14.join();
            w15.join();
            w16.join();
            w17.join();
            w18.join();
            w19.join();
            w20.join();
            w21.join();
            w22.join();
            w23.join();
            // retrieve results from durations[]
            long res = 0;
            for(int n=0; n<numFiles; n++){ // find the slowest thread
                if(durations[n] > res){res = durations[n];};
            }
            cout << "(D6_RS)recordSize " << recordSize << " done. " << endl;
            d6_rs_results[i] = res;
        }
        return 0;
    }
    int d6_rr(){
        int numFiles = 24;
        string prefix = "data/D6/";
        string filenames[numFiles];
        for(int i=0; i<numFiles; i++){
            filenames[i] = prefix+to_string(i);
        }
        unsigned long recordSize;
        for(int i=0; i<3; i++){
            recordSize = recordSizes[i];
            thread w0 (worker, 0, cref(filenames[0]), recordSize, true);
            thread w1 (worker, 1, cref(filenames[1]), recordSize, true);
            thread w2 (worker, 2, cref(filenames[2]), recordSize, true);
            thread w3 (worker, 3, cref(filenames[3]), recordSize, true);
            thread w4 (worker, 4, cref(filenames[4]), recordSize, true);
            thread w5 (worker, 5, cref(filenames[5]), recordSize, true);
            thread w6 (worker, 6, cref(filenames[6]), recordSize, true);
            thread w7 (worker, 7, cref(filenames[7]), recordSize, true);
            thread w8 (worker, 8, cref(filenames[8]), recordSize, true);
            thread w9 (worker, 9, cref(filenames[9]), recordSize, true);
            thread w10 (worker, 10, cref(filenames[10]), recordSize, true);
            thread w11 (worker, 11, cref(filenames[11]), recordSize, true);
            thread w12 (worker, 12, cref(filenames[12]), recordSize, true);
            thread w13 (worker, 13, cref(filenames[13]), recordSize, true);
            thread w14 (worker, 14, cref(filenames[14]), recordSize, true);
            thread w15 (worker, 15, cref(filenames[15]), recordSize, true);
            thread w16 (worker, 16, cref(filenames[16]), recordSize, true);
            thread w17 (worker, 17, cref(filenames[17]), recordSize, true);
            thread w18 (worker, 18, cref(filenames[18]), recordSize, true);
            thread w19 (worker, 19, cref(filenames[19]), recordSize, true);
            thread w20 (worker, 20, cref(filenames[20]), recordSize, true);
            thread w21 (worker, 21, cref(filenames[21]), recordSize, true);
            thread w22 (worker, 22, cref(filenames[22]), recordSize, true);
            thread w23 (worker, 23, cref(filenames[23]), recordSize, true);
            w0.join();
            w1.join();
            w2.join();
            w3.join();
            w4.join();
            w5.join();
            w6.join();
            w7.join();
            w8.join();
            w9.join();
            w10.join();
            w11.join();
            w12.join();
            w13.join();
            w14.join();
            w15.join();
            w16.join();
            w17.join();
            w18.join();
            w19.join();
            w20.join();
            w21.join();
            w22.join();
            w23.join();
            // retrieve results from durations[]
            long res = 0;
            for(int n=0; n<numFiles; n++){ // find the slowest thread
                if(durations[n] > res){res = durations[n];};
            }
            cout << "(D6_RR)recordSize " << recordSize << " done. " << endl;
            d6_rr_results[i] = res;
        }
        return 0;
    }
    
    int d7_rs(){
        int numFiles = 48;
        string prefix = "data/D7/";
        string filenames[numFiles];
        for(int i=0; i<numFiles; i++){
            filenames[i] = prefix+to_string(i);
        }
        unsigned long recordSize;
        for(int i=0; i<3; i++){
            recordSize = recordSizes[i];
            thread w0 (worker, 0, cref(filenames[0]), recordSize, false);
            thread w1 (worker, 1, cref(filenames[1]), recordSize, false);
            thread w2 (worker, 2, cref(filenames[2]), recordSize, false);
            thread w3 (worker, 3, cref(filenames[3]), recordSize, false);
            thread w4 (worker, 4, cref(filenames[4]), recordSize, false);
            thread w5 (worker, 5, cref(filenames[5]), recordSize, false);
            thread w6 (worker, 6, cref(filenames[6]), recordSize, false);
            thread w7 (worker, 7, cref(filenames[7]), recordSize, false);
            thread w8 (worker, 8, cref(filenames[8]), recordSize, false);
            thread w9 (worker, 9, cref(filenames[9]), recordSize, false);
            thread w10 (worker, 10, cref(filenames[10]), recordSize, false);
            thread w11 (worker, 11, cref(filenames[11]), recordSize, false);
            thread w12 (worker, 12, cref(filenames[12]), recordSize, false);
            thread w13 (worker, 13, cref(filenames[13]), recordSize, false);
            thread w14 (worker, 14, cref(filenames[14]), recordSize, false);
            thread w15 (worker, 15, cref(filenames[15]), recordSize, false);
            thread w16 (worker, 16, cref(filenames[16]), recordSize, false);
            thread w17 (worker, 17, cref(filenames[17]), recordSize, false);
            thread w18 (worker, 18, cref(filenames[18]), recordSize, false);
            thread w19 (worker, 19, cref(filenames[19]), recordSize, false);
            thread w20 (worker, 20, cref(filenames[20]), recordSize, false);
            thread w21 (worker, 21, cref(filenames[21]), recordSize, false);
            thread w22 (worker, 22, cref(filenames[22]), recordSize, false);
            thread w23 (worker, 23, cref(filenames[23]), recordSize, false);
            thread w24 (worker, 24, cref(filenames[24]), recordSize, false);
            thread w25 (worker, 25, cref(filenames[25]), recordSize, false);
            thread w26 (worker, 26, cref(filenames[26]), recordSize, false);
            thread w27 (worker, 27, cref(filenames[27]), recordSize, false);
            thread w28 (worker, 28, cref(filenames[28]), recordSize, false);
            thread w29 (worker, 29, cref(filenames[29]), recordSize, false);
            thread w30 (worker, 30, cref(filenames[30]), recordSize, false);
            thread w31 (worker, 31, cref(filenames[31]), recordSize, false);
            thread w32 (worker, 32, cref(filenames[32]), recordSize, false);
            thread w33 (worker, 33, cref(filenames[33]), recordSize, false);
            thread w34 (worker, 34, cref(filenames[34]), recordSize, false);
            thread w35 (worker, 35, cref(filenames[35]), recordSize, false);
            thread w36 (worker, 36, cref(filenames[36]), recordSize, false);
            thread w37 (worker, 37, cref(filenames[37]), recordSize, false);
            thread w38 (worker, 38, cref(filenames[38]), recordSize, false);
            thread w39 (worker, 39, cref(filenames[39]), recordSize, false);
            thread w40 (worker, 40, cref(filenames[40]), recordSize, false);
            thread w41 (worker, 41, cref(filenames[41]), recordSize, false);
            thread w42 (worker, 42, cref(filenames[42]), recordSize, false);
            thread w43 (worker, 43, cref(filenames[43]), recordSize, false);
            thread w44 (worker, 44, cref(filenames[44]), recordSize, false);
            thread w45 (worker, 45, cref(filenames[45]), recordSize, false);
            thread w46 (worker, 46, cref(filenames[46]), recordSize, false);
            thread w47 (worker, 47, cref(filenames[47]), recordSize, false);
            w0.join();
            w1.join();
            w2.join();
            w3.join();
            w4.join();
            w5.join();
            w6.join();
            w7.join();
            w8.join();
            w9.join();
            w10.join();
            w11.join();
            w12.join();
            w13.join();
            w14.join();
            w15.join();
            w16.join();
            w17.join();
            w18.join();
            w19.join();
            w20.join();
            w21.join();
            w22.join();
            w23.join();
            w24.join();
            w25.join();
            w26.join();
            w27.join();
            w28.join();
            w29.join();
            w30.join();
            w31.join();
            w32.join();
            w33.join();
            w34.join();
            w35.join();
            w36.join();
            w37.join();
            w38.join();
            w39.join();
            w40.join();
            w41.join();
            w42.join();
            w43.join();
            w44.join();
            w45.join();
            w46.join();
            w47.join();
            // retrieve results from durations[]
            long res = 0;
            for(int n=0; n<numFiles; n++){ // find the slowest thread
                if(durations[n] > res){res = durations[n];};
            }
            cout << "(D7_RS)recordSize " << recordSize << " done. " << endl;
            d7_rs_results[i] = res;
        }
        return 0;
    }
    int d7_rr(){
        int numFiles = 48;
        string prefix = "data/D7/";
        string filenames[numFiles];
        for(int i=0; i<numFiles; i++){
            filenames[i] = prefix+to_string(i);
        }
        unsigned long recordSize;
        for(int i=0; i<3; i++){
            recordSize = recordSizes[i];
            thread w0 (worker, 0, cref(filenames[0]), recordSize, true);
            thread w1 (worker, 1, cref(filenames[1]), recordSize, true);
            thread w2 (worker, 2, cref(filenames[2]), recordSize, true);
            thread w3 (worker, 3, cref(filenames[3]), recordSize, true);
            thread w4 (worker, 4, cref(filenames[4]), recordSize, true);
            thread w5 (worker, 5, cref(filenames[5]), recordSize, true);
            thread w6 (worker, 6, cref(filenames[6]), recordSize, true);
            thread w7 (worker, 7, cref(filenames[7]), recordSize, true);
            thread w8 (worker, 8, cref(filenames[8]), recordSize, true);
            thread w9 (worker, 9, cref(filenames[9]), recordSize, true);
            thread w10 (worker, 10, cref(filenames[10]), recordSize, true);
            thread w11 (worker, 11, cref(filenames[11]), recordSize, true);
            thread w12 (worker, 12, cref(filenames[12]), recordSize, true);
            thread w13 (worker, 13, cref(filenames[13]), recordSize, true);
            thread w14 (worker, 14, cref(filenames[14]), recordSize, true);
            thread w15 (worker, 15, cref(filenames[15]), recordSize, true);
            thread w16 (worker, 16, cref(filenames[16]), recordSize, true);
            thread w17 (worker, 17, cref(filenames[17]), recordSize, true);
            thread w18 (worker, 18, cref(filenames[18]), recordSize, true);
            thread w19 (worker, 19, cref(filenames[19]), recordSize, true);
            thread w20 (worker, 20, cref(filenames[20]), recordSize, true);
            thread w21 (worker, 21, cref(filenames[21]), recordSize, true);
            thread w22 (worker, 22, cref(filenames[22]), recordSize, true);
            thread w23 (worker, 23, cref(filenames[23]), recordSize, true);
            thread w24 (worker, 24, cref(filenames[24]), recordSize, true);
            thread w25 (worker, 25, cref(filenames[25]), recordSize, true);
            thread w26 (worker, 26, cref(filenames[26]), recordSize, true);
            thread w27 (worker, 27, cref(filenames[27]), recordSize, true);
            thread w28 (worker, 28, cref(filenames[28]), recordSize, true);
            thread w29 (worker, 29, cref(filenames[29]), recordSize, true);
            thread w30 (worker, 30, cref(filenames[30]), recordSize, true);
            thread w31 (worker, 31, cref(filenames[31]), recordSize, true);
            thread w32 (worker, 32, cref(filenames[32]), recordSize, true);
            thread w33 (worker, 33, cref(filenames[33]), recordSize, true);
            thread w34 (worker, 34, cref(filenames[34]), recordSize, true);
            thread w35 (worker, 35, cref(filenames[35]), recordSize, true);
            thread w36 (worker, 36, cref(filenames[36]), recordSize, true);
            thread w37 (worker, 37, cref(filenames[37]), recordSize, true);
            thread w38 (worker, 38, cref(filenames[38]), recordSize, true);
            thread w39 (worker, 39, cref(filenames[39]), recordSize, true);
            thread w40 (worker, 40, cref(filenames[40]), recordSize, true);
            thread w41 (worker, 41, cref(filenames[41]), recordSize, true);
            thread w42 (worker, 42, cref(filenames[42]), recordSize, true);
            thread w43 (worker, 43, cref(filenames[43]), recordSize, true);
            thread w44 (worker, 44, cref(filenames[44]), recordSize, true);
            thread w45 (worker, 45, cref(filenames[45]), recordSize, true);
            thread w46 (worker, 46, cref(filenames[46]), recordSize, true);
            thread w47 (worker, 47, cref(filenames[47]), recordSize, true);
            w0.join();
            w1.join();
            w2.join();
            w3.join();
            w4.join();
            w5.join();
            w6.join();
            w7.join();
            w8.join();
            w9.join();
            w10.join();
            w11.join();
            w12.join();
            w13.join();
            w14.join();
            w15.join();
            w16.join();
            w17.join();
            w18.join();
            w19.join();
            w20.join();
            w21.join();
            w22.join();
            w23.join();
            w24.join();
            w25.join();
            w26.join();
            w27.join();
            w28.join();
            w29.join();
            w30.join();
            w31.join();
            w32.join();
            w33.join();
            w34.join();
            w35.join();
            w36.join();
            w37.join();
            w38.join();
            w39.join();
            w40.join();
            w41.join();
            w42.join();
            w43.join();
            w44.join();
            w45.join();
            w46.join();
            w47.join();
            // retrieve results from durations[]
            long res = 0;
            for(int n=0; n<numFiles; n++){ // find the slowest thread
                if(durations[n] > res){res = durations[n];};
            }
            cout << "(D7_RR)recordSize " << recordSize << " done. " << endl;
            d7_rr_results[i] = res;
        }
        return 0;
    }

    void worker(int workerId, const string &filename, unsigned long recordSize, bool randFlag){
        if(!randFlag){ // rs
            char * memblock;
            ifstream file;
            file.rdbuf()->pubsetbuf(0, 0);
            file.open(filename);
            if(!file.is_open()){ 
                printf("worker%d File err\n", workerId); 
                exit(-1);
            }
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
            delete[] memblock;
            file.close();
            // save the result to a temporary array
            durations[workerId] = duration.count();
        }else{ // rr
            char * memblock;
            ifstream file;
            file.rdbuf()->pubsetbuf(0, 0);
            file.open(filename);
            if(!file.is_open()){ printf("File err\n"); exit(-1);}
            file.seekg(0, ios::end);
            unsigned long fileSize = file.tellg();
            file.seekg(0, ios::beg);
            memblock = new char[recordSize];
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
            delete[] memblock;
            file.close();
            // save the result to a temporary array
            durations[workerId] = duration.count();
        }
        return;
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
