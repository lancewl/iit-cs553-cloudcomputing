#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "sys/times.h"
#include "sys/vtimes.h"
#include "sys/types.h"
#include "sys/sysinfo.h"
#include <fstream>
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;
using namespace std::chrono;

/*
 * Disk I/O speed
 */



/*
 * Physical Memory currently
 */
long long memory(){
    struct sysinfo mem;
    sysinfo (&mem);
    long long pMUsed = mem.totalram - mem.freeram; //Multiply in next statement to avoid int overflow on right hand side...
    pMUsed *= mem.mem_unit;
    return pMUsed;
}


/*
 * CPU currently used
 */
static unsigned long long lastTotUser, lastTotUserLow, lastTotSys, lastTotIdle;

double getCurCpu(){
    double percent;
    FILE* file;
    unsigned long long totUser, totUserLow, totSys, totIdle, tot;

    file = fopen("/proc/stat", "r");
    fscanf(file, "cpu %llu %llu %llu %llu", &totUser, &totUserLow, &totSys, &totIdle);
    fclose(file);

    if (totUser < lastTotUser || totUserLow < lastTotUserLow || totSys < lastTotSys || totIdle < lastTotIdle){

        percent = -1.0;
    }
    else{
        tot = (totUser - lastTotUser) + (totUserLow - lastTotUserLow) + (totSys - lastTotSys);
        percent = tot;
        tot += (totIdle - lastTotIdle);
        percent /= tot;
        percent *= 100;
    }

    lastTotUser = totUser;
    lastTotUserLow = totUserLow;
    lastTotSys = totSys;
    lastTotIdle = totIdle;

    return percent;
}

/*
 * GRAPHS TABLES
 */
int graph(){

    int i = 0;
    string const cpu("CPU.txt"), memo("Mem.txt");
    ofstream cpuFlux(cpu.c_str(), ios::app);
    ofstream memoFlux(memo.c_str(), ios::app);

    if (cpuFlux && memoFlux)
    {
        while(i < 240){
                cpuFlux << getCurCpu() << ", ";
                memoFlux << memory() << ", ";
                std::this_thread::sleep_for(std::chrono::milliseconds(250));
                i++;
            }
    }
    else{
        cout << "Problem fichier" << endl;
    }
    return 0;
}


