#include "FixedSP.h"
#include <iostream>
#include <stack>
#include <pthread.h>
#include <windows.h>

vector<int> FixedSP::sort(int * a, int size, int source) {
    vector<int> vec;
    Distance[source] = INF;
    int distance = 0;
    do{
        distance = 0;
        distance += matrix[source][a[0]];
        for (int i = 0; i < size - 1; ++i) {
            distance += matrix[a[i]][a[i+1]];
        }
        distance += matrix[a[size-1]][source];
        if(distance < this->Distance[source]){
            Distance[source] = distance;
            vec.clear();
            for (int j = 0; j < size; ++j) {
                vec.emplace_back(a[j]);
            }
        }
    }
    while ( next_permutation(a,a+size) );
    return vec;
}

vector<int> FixedSP::getFixedPointShortestPath(int source, vector<int> intermediates){
    this->Distance[source] = INF;
    vector<vector<int>> oldGraph = matrix;
    multiDijkstra(source, intermediates);
    matrix = fullMatrix;

    std::sort(intermediates.begin(), intermediates.end());
    int * a = new int [intermediates.size()];
    for (int i = 0; i < intermediates.size(); ++i) {
        a[i] = intermediates[i];
    }
    sortVec.clear();
//    sortVec = sort(a, (int)intermediates.size(), source);
//    sortVec.insert(sortVec.begin(), source);

    vector<int> fullVec;

    matrix = oldGraph;
    stack<int> pathStack;
    for (size_t i = 0; i < sortVec.size(); i++){
        int p = sortVec[(i+1)%sortVec.size()];
        while (paths[sortVec[i]][p] != -1){
            pathStack.push(p);
            p = paths[sortVec[i]][p];
        }
        pathStack.push(p);
        while (!pathStack.empty()){
            fullVec.emplace_back(pathStack.top());
            pathStack.pop();
        }
    }

    for (size_t i = 0; i < fullVec.size(); i++){
        if (fullMatrix[fullVec[i]][fullVec[(i + 1) % fullVec.size()]] == INF || fullMatrix[fullVec[i]][fullVec[(i + 1) % fullVec.size()]] < 0){
            fullVec.clear();
            return fullVec;
        }
    }
    return fullVec;
}

void FixedSP::multiDijkstra(int source, vector<int> intermediates){
    int threadNum = getThreadNum();
    pthread_t tid[threadNum];
    int pathLength = 1 + intermediates.size();
    int count = 0;
    vector<int> pathVec = intermediates;
    pathVec.insert(pathVec.begin(), source);

    LARGE_INTEGER t1, t2, tc;
    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&t1);
    while (count < pathLength){
        int threads_per_loop = min(pathLength - count, threadNum);  //
        for(int i = 0; i < threads_per_loop; i++){
            threadArg * arg = new threadArg (this,pathVec[count + i]);
            pthread_create(tid+i,nullptr,dijkstra_thread, arg);
        }
        for (int i = 0; i < threads_per_loop; ++i) {
            pthread_join(tid[i],nullptr);
        }
        count += threads_per_loop;
    }
    QueryPerformanceCounter(&t2);
    cout << "thread = "<<threadNum<< " TimeConsume:" << ((t2.QuadPart - t1.QuadPart) * 1.0 * 1000 / tc.QuadPart)<<endl;

}


void *FixedSP::dijkstra_thread(void *arg) {

    threadArg* threadArg1 = (threadArg*) arg;
//    delete arg;
    FixedSP* fixedSp = threadArg1->fixedSp;
    int n = fixedSp->matrix.size();
    int source = threadArg1->source;
//    fixedSp->paths[source].clear();
    fixedSp->paths[source].clear();
    fixedSp->dis[source].clear();
    fixedSp->visited[source].clear();
    // initial vectors
    for (int i = 0; i < n; i++){
        fixedSp->dis[source].emplace_back(fixedSp->matrix[source][i]);
        fixedSp->visited[source].emplace_back(false);
        fixedSp->paths[source].emplace_back(-1);
    }

    fixedSp->visited[source][source] = true;
    for (int i = 0; i < n; i++){
        if (i == source){
            continue;
        }
        int p, minn = INF;
        for (int j = 0; j < n; j++){
            if (!fixedSp->visited[source][j] && fixedSp->dis[source][j] < minn){
                p = j;
                minn = fixedSp->dis[source][j];
            }
        }
        fixedSp->visited[source][p] = true;
        for (int j = 0; j < n; j++){
            if (!fixedSp->visited[source][j] && fixedSp->dis[source][p] + fixedSp->matrix[p][j] < fixedSp->dis[source][j]){
                fixedSp->fullMatrix[source][j] = fixedSp->dis[source][p] + fixedSp->matrix[p][j];
                fixedSp->dis[source][j] = fixedSp->dis[source][p] + fixedSp->matrix[p][j];
                fixedSp->paths[source][j] = p;
            }
        }
    }
}


