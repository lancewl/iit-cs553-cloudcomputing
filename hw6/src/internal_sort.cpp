#include "internal_sort.h"

void heapSort(std::string strarr[], int n)
{
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(strarr, n, i);

    // One by one extract an element from heap
    for (int i = n - 1; i >= 0; i--)
    {
        // Move current root to end
        std::swap(strarr[0], strarr[i]);

        // call max heapify on the reduced heap
        heapify(strarr, i, 0);
    }
}

void heapify(std::string strarr[], int n, int i)
{
    int largest = i;   // Initialize largest as root
    int l = 2 * i + 1; // left = 2*i + 1
    int r = 2 * i + 2; // right = 2*i + 2

    // If left child is larger than root
    if (l < n && strarr[l].substr(0, 10) > strarr[largest].substr(0, 10))
        largest = l;

    // If right child is larger than largest so far
    if (r < n && strarr[r].substr(0, 10) > strarr[largest].substr(0, 10))
        largest = r;

    // If largest is not root
    if (largest != i)
    {
        std::swap(strarr[i], strarr[largest]);

        // Recursively heapify the affected sub-tree
        heapify(strarr, n, largest);
    }
}