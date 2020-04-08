#include "external_sort.h"

void externalSort(std::vector<IO_Helper *> helperVec, long bufferSize)
{
    int heap_size = helperVec.size();
    int arr_size[heap_size];
    std::string *arr[heap_size];
    IO_Helper w_helper("output.txt", 9999);
    std::cout << "test" << std::endl;
    std::string *output = new std::string [bufferSize / 100];
    MinHeapNode *harr = new MinHeapNode[heap_size];
    for (int i = 0; i < heap_size; i++)
    {
        arr[i] = helperVec[i]->readChunk();
        harr[i].element = arr[i][0]; // Store the first element
        harr[i].arr_idx = i;               // index of array
        harr[i].ele_idx = 1;               // Index of next element to be stored from array
        arr_size[i] = helperVec[i]->getRecordsPerChunk();
    }
    MinHeap hp(harr, heap_size); // Create the heap
    int count = 0;
    while(hp.getheapSize())
    {
        // Get the minimum element and store it in output
        MinHeapNode root = hp.getMin();
        output[count] = root.element;
        std::cout << output[count] << std::endl;
        // Find the next elelement that will replace current
        // root of heap. The next element belongs to same
        // array as the current root.
        if (root.ele_idx < arr_size[root.arr_idx])
        {
            root.element = arr[root.arr_idx][root.ele_idx];
            root.ele_idx += 1;
            // Replace root with next element of array
            hp.replaceMin(root);
        }
        // If root was the last element of its array
        else
        {
            if(helperVec[root.arr_idx]->isChunkAvailable())
            {
                arr[root.arr_idx] = helperVec[root.arr_idx]->readChunk();
                root.element = arr[root.arr_idx][0];
                root.ele_idx = 1;
                // Replace root with next element of array
                hp.replaceMin(root);
            }
            else
                hp.deleteMin();
        }
        count++;
        if (count == bufferSize)
        {
            w_helper.writeChunk(output, count);
            count = 0;
        }
    }
    w_helper.writeChunk(output, count);
}