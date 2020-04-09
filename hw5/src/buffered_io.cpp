#include "io.h"

Buffered_IO_Helper::Buffered_IO_Helper(std::string filename, unsigned long chunkSize, unsigned long bufferSize){
    bufferSize_ = bufferSize;
    maxItems_ = bufferSize/chunkSize;
    headChunkIndex_ = 0;
    ih_ = new IO_Helper(filename, chunkSize);
    bufferQueue_ = new std::queue<std::string*>();
    sem_init(&itemAvailable_, 0, 0); // semaphore that is shared between threads pshared=0, init with value 0.
    sem_init(&haveSpace_, 0, maxItems_);
    sem_init(&isWriting_, 0, 1); // init value 1, so only 1 thread writes 
}

Buffered_IO_Helper::~Buffered_IO_Helper(){
    delete ih_;
    delete bufferQueue_;
    sem_destroy(&itemAvailable_);
    sem_destroy(&haveSpace_);
    sem_destroy(&isWriting_);
    
}

std::string Buffered_IO_Helper::getFilename(){
    return ih_->getFilename();
}
unsigned long Buffered_IO_Helper::getFileSize(){
    return ih_->getFileSize();
}

unsigned long Buffered_IO_Helper::getRecordsPerChunk(){
    return ih_->getRecordsPerChunk();
}

unsigned long Buffered_IO_Helper::getNumChunks(){
    return ih_->getNumChunks();
}

unsigned long Buffered_IO_Helper::getCurrChunkIndex(){
    // return the chunk index of the head item
    return headChunkIndex_;
}

void Buffered_IO_Helper::clearFile(){
    return ih_->clearFile();
}

bool Buffered_IO_Helper::isChunkAvailable(){

    return ih_->getNumChunks() > headChunkIndex_; // still have unread chunks on disk or chunks in queue
}

std::string* Buffered_IO_Helper::readChunk(){
    // get an item from the head of the queue
    sem_wait(&itemAvailable_);
    std::string* item;
    item = bufferQueue_->front();
    bufferQueue_->pop();
    sem_post(&haveSpace_);
    headChunkIndex_++;
    return item;
}

void Buffered_IO_Helper::writeChunk(std::string* strArr, unsigned long numRecords){
    // No threading support. Yet.
    ih_->writeChunk(strArr, numRecords);
    return;
}

struct args
{
    IO_Helper* ih;
    std::queue<std::string*>* bufferQueue;
    sem_t* itemAvailable;
    sem_t* haveSpace;
};

void *buffer_thread_func(void *input){
    struct args* a = (struct args*)input;
    while(a->ih->isChunkAvailable()){
        sem_wait(a->haveSpace);
        std::string* chunk = a->ih->readChunk();
        a->bufferQueue->push(chunk);
        sem_post(a->itemAvailable);
    }
    std::cout << "BufferThread(" << a->ih->getFilename() << ") done." << std::endl;
    free(input);
    return nullptr;
}

void Buffered_IO_Helper::start_thread(){
    // create a thread
    struct args* a = (struct args*)malloc(sizeof(struct args));
    a->ih = ih_;
    a->bufferQueue = bufferQueue_;
    a->itemAvailable = &itemAvailable_;
    a->haveSpace = &haveSpace_;
    pthread_create(&tid_, NULL, buffer_thread_func, a);
}