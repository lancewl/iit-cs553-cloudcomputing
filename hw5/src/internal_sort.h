#ifndef SORT_H
#define SORT_H

#include <string>

void mergeSort(std::string &s, int l, int r);
void merge(std::string &s, int l, int m, int r);
void heapSort(std::string strarr[], int n);
void heapify(std::string strarr[], int n, int i);

#endif