//
// Created by Feng on 2022/6/14.
//
#include <iostream>
#include <ctime>
#include <vector>
#include <list>
#include <thread>

#define N 30000000

int src[N];
int temp[N];

using namespace std;

void merge(int src[], int temp[], int start, int mid, int end) {
    int i = start, j = mid + 1, k = start;
    while (i <= mid && j <= end) {
        if (src[i] > src[j])
            temp[k++] = src[j++];
        else
            temp[k++] = src[i++];
    }
    while (i != mid + 1)
        temp[k++] = src[i++];
    while (j != end + 1)
        temp[k++] = src[j++];
    for (i = start; i <= end; i++)
        src[i] = temp[i];
}

void mergeSortR(int src[], int temp[], int start, int end) {
    if (start >= end)
        return;
    int mid;
    mid = (start + end) / 2;
    mergeSortR(src, temp, start, mid);
    mergeSortR(src, temp, mid + 1, end);
    merge(src, temp, start, mid, end);

}

void mergeSort(int src[], int size, int threadNum) {
    vector<thread> threads;
    list<int> sections;
    int step = (size + threadNum - 1) / threadNum;
    int first = 0;
    int last = step;

    sections.emplace_back(0);
    for (int i = 0; i < threadNum; ++i) {
        threads.emplace_back(thread(mergeSortR, src, temp, first, last - 1));
        sections.emplace_back(last);
        first += step;
        last += step;
        if (last >= size)
            last = size;
    }

    for (int i = 0; i < threadNum; ++i) {
        if (threads[i].joinable())
            threads[i].join();
    }

    while (sections.size() > 2) {
        auto iter0 = sections.begin();
        while (true) {
            if (++iter0 == sections.end())
                break;
            if (++iter0 == sections.end())
                break;
            auto iter2 = iter0--;
            auto iter1 = iter0--;
            int start = *iter0;
            int mid = *iter1 - 1;
            int end = *iter2 - 1;
            sections.erase(iter1);
            iter0 = iter2;
            thread t(merge, src, temp, start, mid, end);
            t.join();
        }
    }
}


int main() {
    srand(time(0));
    for (int &i: src) {
        i = rand();
    }
    for (int i = 1; i <= 8; ++i) {
        clock_t start = clock();
        mergeSort(src, N, i);
        clock_t end = clock();
        cout<<"when thread is "<<i<<" consume time is: ";
        cout << (double) (end - start) / CLOCKS_PER_SEC << endl;
    }

    return 0;
}