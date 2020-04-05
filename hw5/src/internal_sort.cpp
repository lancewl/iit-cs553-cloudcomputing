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