#include "min_heap.h"

MinHeap::MinHeap(MinHeapNode node_arr[], int size)
{
    heap_size = size;
    heap_arr = node_arr; // store address of array
    int i = (heap_size - 1) / 2;
    while (i >= 0)
    {
        MinHeapify(i);
        i--;
    }
}
void MinHeap::MinHeapify(int i)
{
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if (l < heap_size && heap_arr[l].element < heap_arr[i].element)
        smallest = l;
    if (r < heap_size && heap_arr[r].element < heap_arr[smallest].element)
        smallest = r;
    if (smallest != i)
    {
        std::swap(heap_arr[i], heap_arr[smallest]);
        MinHeapify(smallest);
    }
}

int MinHeap::left(int i)
{
    return (2 * i + 1);
}
int MinHeap::right(int i)
{
    return (2 * i + 2);
}
MinHeapNode MinHeap::getMin()
{
    return heap_arr[0];
}
int MinHeap::getheapSize()
{
    return heap_size;
}
void MinHeap::replaceMin(MinHeapNode x)
{
    heap_arr[0] = x;
    MinHeapify(0);
}
void MinHeap::deleteMin()
{
    heap_arr[0] = heap_arr[heap_size-1];
    heap_size--;
    MinHeapify(0);
}
