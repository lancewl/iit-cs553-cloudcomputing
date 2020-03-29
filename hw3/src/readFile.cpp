#include "readFile.h"
using namespace std;
using namespace std::chrono;

#define ALIGN_BYTES 4096
unsigned long recordSizes[] = {4*1024, 64*1024, 1024*1024, 16*1024*1024};

// I'm too lazy to deal with arguments passing. Too bad we have to do it anyways.
long d1_rs_results[4];
long d1_rr_results[4];
long d2_rs_results[4];
long d2_rr_results[4];
long d3_rs_results[4];
long d3_rr_results[4];
long d4_rs_results[4];
long d4_rr_results[4];
long d5_rs_results[4];
long d5_rr_results[4];
long d6_rs_results[4];
long d6_rr_results[4];
long d7_rs_results[4];
long d7_rr_results[4];

// tempory duration storage
long durations[48];

namespace ReadTest{
    int read_test(bool randomFlag, long fileSize, int numThreads, int i_recordSize){
        // modular test calls for read_test

        return 0;
    }

    void workload_init(){
        system("bash src/scripts/createfiles.sh");
    }

    void workload_clean(){
        system("rm -rf data");
    }

    int rs_rr_test(){
        // run the workload test for 10G, D1 to D7. 
        // and 1G, D1 to D7

        // workload types: RS, RR
        // sequential read, random read
        // save results to memory, and write it to "results.out" when the test is done.
        int i_start = 1;
        int i_end = 4;
        bool bigFileFlag = true;
        for(int i=i_start; i<=i_end; i++){
            // run the test for record sizes 64k, 1m and 16m
            // D1
            d1_rs(bigFileFlag, i);
            d1_rr(bigFileFlag, i);
            // read from D2, 2 threads 2 files
            d2_rs(bigFileFlag, i);
            d2_rr(bigFileFlag, i);
            // D3, 4 threads
            d3_rs(bigFileFlag, i);
            d3_rr(bigFileFlag, i);
            // D4, 8 threads
            d4_rs(bigFileFlag, i);
            d4_rr(bigFileFlag, i);
            // D5, 12 threads
            d5_rs(bigFileFlag, i);
            d5_rr(bigFileFlag, i);
            // D6, 24 threads
            d6_rs(bigFileFlag, i);
            d6_rr(bigFileFlag, i);
            // D7, 48 threads
            d7_rs(bigFileFlag, i);
            d7_rr(bigFileFlag, i);
        }

	    // calculate, and save results to a file
        write_rs_rr_results("64k_1m_16m-",i_start, i_end);

        printf("rs_rr_test() done.\n");
        return 0;
    }

    int iops_rr_test(){
        bool bigFileFlag = false; // use 1G data
        int i_recordSize = 0; // index for 4k record size
        string prefix = "4k";
        d1_rr(bigFileFlag, i_recordSize);
        d2_rr(bigFileFlag, i_recordSize);
        d3_rr(bigFileFlag, i_recordSize);
        d4_rr(bigFileFlag, i_recordSize);
        d5_rr(bigFileFlag, i_recordSize);
        d6_rr(bigFileFlag, i_recordSize);
        d7_rr(bigFileFlag, i_recordSize);
        // write to result file
        write_iops_rr_results(prefix, 0);
        printf("iops_rr_test() done.\n");
        return 0;
    }


    int write_rs_rr_results(const string &fileprefix, int start, int end){
        double fileSize = 10*1000*1000; // in MB/s
        ofstream resultFile;
        // RS
        resultFile.open(fileprefix+"-RS_result.txt");
        resultFile << "numThreads, recordSize(B), throughput(MB/s)" << endl;
        for(int i=start; i<end; i++){
            resultFile << 1 << ", " << recordSizes[i] << ", " << fileSize/(double)d1_rs_results[i] << endl;
        }
        for(int i=start; i<end; i++){
            resultFile << 2 << ", " << recordSizes[i] << ", " << fileSize/(double)d2_rs_results[i] << endl;
        }
        for(int i=start; i<end; i++){
            resultFile << 4 << ", " << recordSizes[i] << ", " << fileSize/(double)d3_rs_results[i] << endl;
        }
        for(int i=start; i<end; i++){
            resultFile << 8 << ", " << recordSizes[i] << ", " << fileSize/(double)d4_rs_results[i] << endl;
        }
        for(int i=start; i<end; i++){
            resultFile << 12 << ", " << recordSizes[i] << ", " << fileSize/(double)d5_rs_results[i] << endl;
        }
        for(int i=start; i<end; i++){
            resultFile << 24 << ", " << recordSizes[i] << ", " << fileSize/(double)d6_rs_results[i] << endl;
        }
        for(int i=start; i<end; i++){
            resultFile << 48 << ", " << recordSizes[i] << ", " << fileSize/(double)d7_rs_results[i] << endl;
        }
        resultFile.close();

        // RR
        resultFile.open("RR_result.txt");
        resultFile << "numThreads, recordSize(B), throughput(MB/s)" << endl;
        for(int i=start; i<end; i++){
            resultFile << 1 << ", " << recordSizes[i] << ", " << fileSize/(double)d1_rr_results[i] << endl;
        }
        for(int i=start; i<end; i++){
            resultFile << 2 << ", " << recordSizes[i] << ", " << fileSize/(double)d2_rr_results[i] << endl;
        }
        for(int i=start; i<end; i++){
            resultFile << 4 << ", " << recordSizes[i] << ", " << fileSize/(double)d3_rr_results[i] << endl;
        }
        for(int i=start; i<end; i++){
            resultFile << 8 << ", " << recordSizes[i] << ", " << fileSize/(double)d4_rr_results[i] << endl;
        }
        for(int i=start; i<end; i++){
            resultFile << 12 << ", " << recordSizes[i] << ", " << fileSize/(double)d5_rr_results[i] << endl;
        }
        for(int i=start; i<end; i++){
            resultFile << 24 << ", " << recordSizes[i] << ", " << fileSize/(double)d6_rr_results[i] << endl;
        }
        for(int i=start; i<end; i++){
            resultFile << 48 << ", " << recordSizes[i] << ", " << fileSize/(double)d7_rr_results[i] << endl;
        }
        resultFile.close();
        return 0;
    }
    
    int write_iops_rr_results(const string &rsize_prefix, int i_recordSize){
        double fileSize = 1000*1000*1000; // 1G
        unsigned long recordSize = recordSizes[i_recordSize];
        unsigned long numOps = fileSize/recordSize;
        
        // ops/sec
        ofstream resultFile;
        // RS
        resultFile.open(rsize_prefix+"-iops_result.txt");
        resultFile << "numThreads, recordSize(B), ops/s" << endl;
        resultFile << 1 << ", " << recordSize << ", " << numOps/(double)d1_rr_results[i_recordSize]*1000 << endl;
        resultFile << 2 << ", " << recordSize << ", " << numOps/(double)d2_rr_results[i_recordSize]*1000 << endl;
        resultFile << 4 << ", " << recordSize << ", " << numOps/(double)d3_rr_results[i_recordSize]*1000 << endl;
        resultFile << 8 << ", " << recordSize << ", " << numOps/(double)d4_rr_results[i_recordSize]*1000 << endl;
        resultFile << 12 << ", " << recordSize << ", " << numOps/(double)d5_rr_results[i_recordSize]*1000 << endl;
        resultFile << 24 << ", " << recordSize << ", " << numOps/(double)d6_rr_results[i_recordSize]*1000 << endl;
        resultFile << 48<< ", " << recordSize << ", " << numOps/(double)d7_rr_results[i_recordSize]*1000 << endl;

        resultFile.close();
        return 0;
    }

    int d1_rs(bool bigFileFlag, int i_recordSize){
        char * memblock;
        unsigned long recordSize = recordSizes[i_recordSize];
        int fp;
        if(bigFileFlag){
            fp = open("data/10G/D1/0", O_RDONLY|O_DIRECT);
        }else{
            fp = open("data/1G/D1/0", O_RDONLY|O_DIRECT);
        }
        // read from D1, 1
        if(fp == -1){ fputs("File not found", stderr); exit(-1);}
        memblock = (char *) aligned_alloc(ALIGN_BYTES, sizeof(char)*recordSize); // malloc'd memory does not work with O_DIRECT
    
        auto start = high_resolution_clock::now();
        
        int n = 1;
        while(n > 0){
            n = read(fp, memblock, recordSize);
            lseek(fp, recordSize, SEEK_CUR);
        }
            
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);
        free(memblock);
        close(fp);
        // save the result to the array
        cout << "(D1_RS)recordSize " << recordSize << " done. " << endl;
        d1_rs_results[i_recordSize] = duration.count();
        return 0;
    }
    int d1_rr(bool bigFileFlag, int i_recordSize){
        char * memblock;
        unsigned long recordSize = recordSizes[i_recordSize];
        int fp;
        if(bigFileFlag){
            fp = open("data/10G/D1/0", O_RDONLY|O_DIRECT);
        }else{
            fp = open("data/1G/D1/0", O_RDONLY|O_DIRECT);
        }
        // read from D1, 0
        if(fp == -1){ fputs("File not found", stderr); exit(-1);}
        memblock = (char *) aligned_alloc(ALIGN_BYTES, sizeof(char)*recordSize); // malloc'd memory does not work with O_DIRECT

        unsigned long fileSize = lseek(fp, 0, SEEK_END);
        unsigned long numPos = fileSize/recordSize;
        unsigned long posRange = fileSize-recordSize; // make sure it doesn't reach eof
        unsigned long posList[numPos];
        unsigned long rem;
        for(long i=0; i<(long)numPos; i++){
            posList[i] = (unsigned long)rand()%posRange;
            rem = posList[i]%ALIGN_BYTES;
            posList[i] = posList[i] - rem;
        }

        auto start = high_resolution_clock::now();
        for(unsigned long pos: posList){
            lseek(fp, pos, SEEK_SET); // seek to random position
            read(fp, memblock, recordSize); // read a block
        }
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);
        free(memblock);
        close(fp);    
        
        // save the result to the array
        cout << "(D1_RR)recordSize " << recordSize << " done. " << endl;
        d1_rr_results[i_recordSize] = duration.count();
        return 0;
    }

    int d2_rs(bool bigFileFlag, int i_recordSize){
        int numFiles = 2;
        string prefix;
        if(bigFileFlag){
            prefix = "data/10G/D2/";
        }else{
            prefix = "data/1G/D2/";
        }
        string filenames[numFiles];
        for(int i=0; i<numFiles; i++){
            filenames[i] = prefix+to_string(i);
        }
        unsigned long recordSize = recordSizes[i_recordSize];
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
        d2_rs_results[i_recordSize] = res;
        return 0;
    }
    int d2_rr(bool bigFileFlag, int i_recordSize){
        int numFiles = 2;
        string prefix;
        if(bigFileFlag){
            prefix = "data/10G/D2/";
        }else{
            prefix = "data/1G/D2/";
        }
        string filenames[numFiles];
        for(int i=0; i<numFiles; i++){
            filenames[i] = prefix+to_string(i);
        }
        unsigned long recordSize = recordSizes[i_recordSize];
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
        d2_rr_results[i_recordSize] = res;
        return 0;
    }

    int d3_rs(bool bigFileFlag, int i_recordSize){
        int numFiles = 4;
        string prefix;
        if(bigFileFlag){
            prefix = "data/10G/D3/";
        }else{
            prefix = "data/1G/D3/";
        }
        string filenames[numFiles];
        for(int i=0; i<numFiles; i++){
            filenames[i] = prefix+to_string(i);
        }
        unsigned long recordSize = recordSizes[i_recordSize];
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
        d3_rs_results[i_recordSize] = res;
        return 0;
    }
    int d3_rr(bool bigFileFlag, int i_recordSize){
        int numFiles = 4;
        string prefix;
        if(bigFileFlag){
            prefix = "data/10G/D3/";
        }else{
            prefix = "data/1G/D3/";
        }
        string filenames[numFiles];
        for(int i=0; i<numFiles; i++){
            filenames[i] = prefix+to_string(i);
        }
        unsigned long recordSize = recordSizes[i_recordSize];
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
        d3_rr_results[i_recordSize] = res;
        return 0;
    }

    int d4_rs(bool bigFileFlag, int i_recordSize){
        int numFiles = 8;
        string prefix;
        if(bigFileFlag){
            prefix = "data/10G/D4/";
        }else{
            prefix = "data/1G/D4/";
        }
        string filenames[numFiles];
        for(int i=0; i<numFiles; i++){
            filenames[i] = prefix+to_string(i);
        }
    unsigned long recordSize = recordSizes[i_recordSize];
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
        d4_rs_results[i_recordSize] = res;
        return 0;
    }
    int d4_rr(bool bigFileFlag, int i_recordSize){
        int numFiles = 8;
        string prefix;
        if(bigFileFlag){
            prefix = "data/10G/D4/";
        }else{
            prefix = "data/1G/D4/";
        }
        string filenames[numFiles];
        for(int i=0; i<numFiles; i++){
            filenames[i] = prefix+to_string(i);
        }
        unsigned long recordSize = recordSizes[i_recordSize];
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
        d4_rr_results[i_recordSize] = res;
        return 0;
    }
    
    int d5_rs(bool bigFileFlag, int i_recordSize){
        int numFiles = 12;
        string prefix;
        if(bigFileFlag){
            prefix = "data/10G/D5/";
        }else{
            prefix = "data/1G/D5/";
        }
        string filenames[numFiles];
        for(int i=0; i<numFiles; i++){
            filenames[i] = prefix+to_string(i);
        }
        unsigned long recordSize = recordSizes[i_recordSize];
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
        d5_rs_results[i_recordSize] = res;
        return 0;
    }
    int d5_rr(bool bigFileFlag, int i_recordSize){
        int numFiles = 12;
        string prefix;
        if(bigFileFlag){
            prefix = "data/10G/D5/";
        }else{
            prefix = "data/1G/D5/";
        }
        string filenames[numFiles];
        for(int i=0; i<numFiles; i++){
            filenames[i] = prefix+to_string(i);
        }
        unsigned long recordSize = recordSizes[i_recordSize];
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
        d5_rr_results[i_recordSize] = res;
        return 0;
    }
    
    int d6_rs(bool bigFileFlag, int i_recordSize){
        int numFiles = 24;
        string prefix;
        if(bigFileFlag){
            prefix = "data/10G/D6/";
        }else{
            prefix = "data/1G/D6/";
        }
        string filenames[numFiles];
        for(int i=0; i<numFiles; i++){
            filenames[i] = prefix+to_string(i);
        }
        unsigned long recordSize = recordSizes[i_recordSize];
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
        d6_rs_results[i_recordSize] = res;
        return 0;
    }
    int d6_rr(bool bigFileFlag, int i_recordSize){
        int numFiles = 24;
        string prefix;
        if(bigFileFlag){
            prefix = "data/10G/D6/";
        }else{
            prefix = "data/1G/D6/";
        }
        string filenames[numFiles];
        for(int i=0; i<numFiles; i++){
            filenames[i] = prefix+to_string(i);
        }
        unsigned long recordSize = recordSizes[i_recordSize];
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
        d6_rr_results[i_recordSize] = res;
        return 0;
    }
    
    int d7_rs(bool bigFileFlag, int i_recordSize){
        int numFiles = 48;
        string prefix;
        if(bigFileFlag){
            prefix = "data/10G/D7/";
        }else{
            prefix = "data/1G/D7/";
        }
        string filenames[numFiles];
        for(int i=0; i<numFiles; i++){
            filenames[i] = prefix+to_string(i);
        }
        unsigned long recordSize = recordSizes[i_recordSize];
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
        d7_rs_results[i_recordSize] = res;
        return 0;
    }
    int d7_rr(bool bigFileFlag, int i_recordSize){
        int numFiles = 48;
        string prefix;
        if(bigFileFlag){
            prefix = "data/10G/D7/";
        }else{
            prefix = "data/1G/D7/";
        }
        string filenames[numFiles];
        for(int i=0; i<numFiles; i++){
            filenames[i] = prefix+to_string(i);
        }
        unsigned long recordSize = recordSizes[i_recordSize];
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
        d7_rr_results[i_recordSize] = res;
        return 0;
    }

    void worker(int workerId, const string &filename, unsigned long recordSize, bool randFlag){
        const char * fn = filename.c_str();
        if(!randFlag){ // rs
            char * memblock;
            int fp = open(fn, O_RDONLY|O_DIRECT); // O_DIRECT flag for direct disk io
            // read from D1, 1
            if(fp == -1){ fputs("File not found", stderr); exit(-1);}
            memblock = (char *) aligned_alloc(ALIGN_BYTES, sizeof(char)*recordSize); // malloc'd memory does not work with O_DIRECT
        
            auto start = high_resolution_clock::now();
            
            int n = 1;
            while(n > 0){
                n = read(fp, memblock, recordSize);
                lseek(fp, recordSize, SEEK_CUR);
            }
                
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<milliseconds>(stop - start);
            free(memblock);
            close(fp);
            // save the result to a temporary array
            durations[workerId] = duration.count();
        }else{ // rr
            char * memblock;
            int fp = open(fn, O_RDONLY|O_DIRECT);
            // read from D1, 0
            if(fp == -1){ fputs("File not found", stderr); exit(-1);}
            memblock = (char *) aligned_alloc(ALIGN_BYTES, sizeof(char)*recordSize); // malloc'd memory does not work with O_DIRECT

            unsigned long fileSize = lseek(fp, 0, SEEK_END);
            unsigned long numPos = fileSize/recordSize;
            unsigned long posRange = fileSize-recordSize; // make sure it doesn't reach eof
            unsigned long posList[numPos];
            unsigned long rem;
            for(long i=0; i<(long)numPos; i++){
                posList[i] = (unsigned long)rand()%posRange;
                rem = posList[i]%ALIGN_BYTES;
                posList[i] = posList[i] - rem;
            }

            auto start = high_resolution_clock::now();
            for(unsigned long pos: posList){
                lseek(fp, pos, SEEK_SET); // seek to random position
                read(fp, memblock, recordSize); // read a block
            }
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<milliseconds>(stop - start);
            free(memblock);
            close(fp);    
            // save the result to a temporary array
            durations[workerId] = duration.count();
        }
        return;
    }

}
