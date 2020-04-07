#include "external_sort.h"

void externalSort()
{
    int heap_size = 3;
    int arr_size = 3;
    std::string arr[3][3] = {{"asdga", "lasdd", "nljsd"}, {"jgfdr", "kcrsd", "sjfrc"}, {"okmqe", "rsfhc", "plsaf"}};
    std::string output[heap_size * arr_size];
    MinHeapNode *harr = new MinHeapNode[heap_size];
    for (int i = 0; i < heap_size; i++)
    {
        harr[i].element = arr[i][0]; // Store the first element
        harr[i].arr_idx = i;               // index of array
        harr[i].ele_idx = 1;               // Index of next element to be stored from array
    }
    MinHeap hp(harr, heap_size); // Create the heap
    int count = 0;
    while(hp.getheapSize())
    {
        // Get the minimum element and store it in output
        MinHeapNode root = hp.getMin();
        output[count] = root.element;

        // Find the next elelement that will replace current
        // root of heap. The next element belongs to same
        // array as the current root.
        if (root.ele_idx < arr_size)
        {
            root.element = arr[root.arr_idx][root.ele_idx];
            root.ele_idx += 1;
            // Replace root with next element of array
            hp.replaceMin(root);
        }
        // If root was the last element of its array
        else
            hp.deleteMin();

        count++;
    }
    for (int i = 0; i < 9; i++){
        std::cout << output[i] << std::endl;
    }
}