#include "io.h"


IO_Helper::IO_Helper(unsigned long memSize, std::string filename){
    memSize_ = memSize; // Gin bytes
    filename_ = filename;
    setFileName(filename);
}
IO_Helper::~IO_Helper(){
    // free allocated memory
}

int IO_Helper::setFileName(std::string filename){
    // use fstream to open the file
    std::ifstream file;
    file.open(filename, std::ifstream::in);
    if(!file){ fprintf(stderr, "FILE OPEN ERROR\n"); exit(EXIT_FAILURE);}
    file.seekg (0, file.end);
    fileSize_ = file.tellg();
    file.close();
    numRecords_ = fileSize_/100;
    return 0;
}

unsigned long IO_Helper::getFileSize(){
    return fileSize_;
}

unsigned long IO_Helper::getNumRecords(){
    return numRecords_;
}

bool IO_Helper::fitInMem(){
    return memSize_ > fileSize_;
}

std::string* IO_Helper::fileToStrArr(){
    // extra check for memSize
    if(!fitInMem()){ fprintf(stderr, "NOT ENOUGH MEMORY FOR fileToStrArr().\n"); exit(EXIT_FAILURE);}
    
    std::string* strArr = new std::string[numRecords_];

    std::ifstream file;
    file.open(filename_, std::ifstream::in);
    if(!file){ fprintf(stderr, "FILE OPEN ERROR\n"); exit(EXIT_FAILURE);}
    int i = 0;
    char buf[128];
    while(i < numRecords_){
        file.getline(buf, 100);
        std::string s((const char *)buf);
        strArr[i] = s;
        i++;
    }
    file.close();
    return strArr;
}
int IO_Helper::strArrToFile(std::string outputFilename, std::string* strArr, unsigned long numRecords){
    std::ofstream file;
    file.open(outputFilename, std::ofstream::out | std::ofstream::trunc);
    if(!file){ fprintf(stderr, "FILE OPEN ERROR\n"); exit(EXIT_FAILURE);}
    int i = 0;
    while(i < numRecords){
        file << strArr[i] << std::endl;
        i++;
    }
    file.close();
    return 0;
}

unsigned long IO_Helper::getNumChunks(){
    return numChunks_;
}


std::string* IO_Helper::readChunk(std::string filename, unsigned long chunkIndex){
    return NULL;
}

// for debug printing
std::ostream& operator<<(std::ostream &strm, const IO_Helper &h) {
            return strm << "filename{" << h.filename_ << "}" << std::endl 
            << "fileSize{" << h.fileSize_ << "}" << std::endl
            << "numRecords{" << h.numRecords_ << "}" << std::endl;
}