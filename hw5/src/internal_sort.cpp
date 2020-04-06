#include "internal_sort.h"

void mergeSort(std::string &s, int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        // Sort first and second halves
        mergeSort(s, l, m);
        mergeSort(s, m + 1, r);
        merge(s, l, m, r);
    }
}
void merge(std::string &s, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2]; // temp array

    for (i = 0; i < n1; i++)
        L[i] = s[l + i];
    for (j = 0; j < n2; j++)
        R[j] = s[m + 1 + j];

    i = 0; // index for first subarray
    j = 0; // index for second subarray
    k = l; // index for merged subarray

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            s[k] = L[i];
            i++;
        }
        else
        {
            s[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        s[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        s[k] = R[j];
        j++;
        k++;
    }
}

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