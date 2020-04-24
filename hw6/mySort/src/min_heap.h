#ifndef MINHEAP_H
#define MINHEAP_H

#include <string>

struct MinHeapNode
{
    std::string element; // The element to be stored
    int arr_idx;       // index of the array from which the element is taken
    int ele_idx;       // index of the next element to be picked from array
};

class MinHeap
{
public:
    MinHeap(MinHeapNode node_arr[], int size); // Constructor: creates a min heap of given size
    void MinHeapify(int);               // to heapify a subtree with root at given index
    int left(int);                      // to get index of left child of node at index i
    int right(int);                     // to get index of right child of node at index i
    MinHeapNode getMin();               // to get the root
    int getheapSize();
    void replaceMin(MinHeapNode x);     // to replace root with new node x and heapify()
    void deleteMin();

private:
    MinHeapNode *heap_arr;
    int heap_size; // size of min heap
};

#endif