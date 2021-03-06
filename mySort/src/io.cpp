#include "io.h"

IO_Helper::IO_Helper(std::string filename, unsigned long chunkSize){
    filename_ = filename;
    chunkSize_ = chunkSize;
    openFile(filename_);
    numRecords_ = fileSize_/100;
    numChunks_ = (fileSize_+chunkSize_-1)/chunkSize_; // quick ceiling 
    recordsPerChunk_ = chunkSize_/100;
    if (recordsPerChunk_ > numRecords_)
        recordsPerChunk_ = numRecords_;
    currChunkIndex_ = 0;
    chunk_ = new std::string[recordsPerChunk_];
}
IO_Helper::~IO_Helper(){
    delete[] chunk_;
    file_.close();
}

std::string IO_Helper::getFilename(){
    return filename_;
}
unsigned long IO_Helper::getFileSize(){
    return fileSize_;
}
unsigned long IO_Helper::getRecordsPerChunk(){
    return recordsPerChunk_;
}
unsigned long IO_Helper::getNumChunks(){
    return numChunks_;
}
unsigned long IO_Helper::getCurrChunkIndex(){
    return currChunkIndex_;
}

void IO_Helper::clearFile(){
    // close, remove the file, and reopen
    file_.close();
    remove(filename_.c_str());
    openFile(filename_);
    return;
}


bool IO_Helper::isChunkAvailable(){
    return currChunkIndex_ < numChunks_;
}

std::string* IO_Helper::readChunk(){
    unsigned long i = 0;
    char buf[128];
    while(i < recordsPerChunk_){
        file_.getline(buf, 100);
        std::string s((const char *)buf); // std::string constructor
        chunk_[i] = s;
        i++;
    }
    currChunkIndex_++;
    return chunk_;
}

void IO_Helper::writeChunk(std::string* strArr, unsigned long numRecords){
    unsigned long i = 0;
    while(i < numRecords){
        file_ << strArr[i] << std::endl;
        i++;
    }
    return;
}

// private function
void IO_Helper::openFile(std::string filename){
    file_.open(filename, std::fstream::in | std::fstream::out | std::fstream::app);
    if(!file_){ fprintf(stderr, "FILE OPEN ERROR\n"); exit(EXIT_FAILURE);}
    file_.seekg (0, file_.end);
    fileSize_ = file_.tellg();
    file_.seekg(0, file_.beg);
    return;
}

// for debug printing
std::ostream& operator<<(std::ostream &strm, const IO_Helper &h) {
            return strm << "filename{" << h.filename_ << "}" << std::endl 
            << "fileSize{" << h.fileSize_ << "}" << std::endl
            << "numRecords{" << h.numRecords_ << "}" << std::endl;
}