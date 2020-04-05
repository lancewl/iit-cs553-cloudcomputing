#include "io.h"


IO_Helper::IO_Helper(int bs, std::string fn){
    bufSize = bs*1000*1000*1000; // GB to bytes
    filename = fn;
    setFileName(filename);
}
IO_Helper::~IO_Helper(){
    // free the memory in the heap
    delete[] strArr;
}

int IO_Helper::setFileName(std::string fn){
    // use fstream to open the file
    std::ifstream file;
    file.open(fn, std::ifstream::in);
    if(!file){ fprintf(stderr, "FILE OPEN ERROR\n"); exit(EXIT_FAILURE);}
    file.seekg (0, file.end);
    fileSize = file.tellg();
    file.close();
    numRecords = fileSize/100;
    return 0;
}

long IO_Helper::getFileSize(){
    return fileSize;
}

long IO_Helper::getNumRecords(){
    return numRecords;
}

std::string* IO_Helper::fileToStrArr(){
    // extra check for memSize
    if(bufSize < fileSize){ fprintf(stderr, "NOT ENOUGH MEMORY FOR fileToStrArr().\n"); exit(EXIT_FAILURE);}
    
    strArr = new std::string[numRecords];

    std::ifstream file;
    file.open(filename, std::ifstream::in);
    if(!file){ fprintf(stderr, "FILE OPEN ERROR\n"); exit(EXIT_FAILURE);}
    int i = 0;
    char buf[128];
    while(i < numRecords){
        file.getline(buf, 100);
        std::string s((const char *)buf);
        strArr[i] = s;
        i++;
    }
    file.close();
    return strArr;
}


// for debug printing
std::ostream& operator<<(std::ostream &strm, const IO_Helper &h) {
            return strm << "filename{" << h.filename << "}" << std::endl 
            << "fileSize{" << h.fileSize << "}" << std::endl
            << "numRecords{" << h.numRecords << "}" << std::endl;
}