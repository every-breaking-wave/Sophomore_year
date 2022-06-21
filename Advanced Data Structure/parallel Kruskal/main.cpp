#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <windows.h>
#include <mutex>
#include <map>
#include <thread>
#include <list>
#include <condition_variable>
#include "vertex.h"

#define MAX_WEIGHT 100

using namespace std;

int n_array[3] = {1000, 2000, 5000};
int e_array[3] = {5, 50, 200};
int thread_num = 1;//线程数量
vector<vertex> graph;//图邻接表
vector<edge> mst;//结果集
vector<thread> subthreads;//线程向量
mutex mut;//互斥锁
vector<vector<int>> edgeMatrix;

//condition_variable cond_v[thread_num];//条件变量
//condition_variable cond[1];

template<typename P>
struct Cmp {
    bool operator()(const P &p1, const P &p2) {
        if (p1.w < p2.w) return true;
        return false;
    }
};


vector<vector<edge>> globalEdges;

//typedef struct MGraph {//邻接矩阵表示法的结构和类型声明
//    MGraph(int n, int e) : n(n), e(e) {}
//    vector<Edge> edges;
//    vector<vector<int>> edgeMatrix;
//    int n, e;//顶点数，边数
//    static bool compare(Edge first,Edge second){
//        return first.w < second.w;
//    }
//} MGraph;

int randomNum(int max) { //返回一个0 - max-1 之间的随机数
    return rand() % max;
}

void construct(int v_num, int a_num) {
    mst.clear();
    graph.clear();
    edgeMatrix.clear();
    vector<edge> edges;
    globalEdges.resize(thread_num, edges);
    for (auto &globalEdge: globalEdges) {
        globalEdge.clear();
    }
    edgeMatrix.resize(v_num, vector<int>(v_num, 0));
    for (int i = 0; i < v_num; i++)
        graph.emplace_back(i);
    for (int i = 0; i < a_num; i++) {
        edge *temp1 = new edge();
        edge *temp2;
        temp1->v1 = randomNum(v_num);
        temp1->v2 = randomNum(v_num);
        while (edgeMatrix[temp1->v1][temp1->v2]) {   // 若生成重复边，重新生成
            temp1->v1 = randomNum(v_num);
            temp1->v2 = randomNum(v_num);
        }
        temp1->w = randomNum(MAX_WEIGHT);
        temp2 = new edge(*temp1);
        temp1->next = graph[temp1->v1].next;
        graph[temp1->v1].next = temp1;
        temp2->next = graph[temp2->v2].next;
        graph[temp2->v2].next = temp2;
        edgeMatrix[temp1->v1][temp1->v2] = 1;
    }
}

void merge() {
    int ptr[thread_num];
    for (int i = 0; i < thread_num; ++i) {
        ptr[i] = 0;
    }
    int min = MAX_WEIGHT + 1;
    bool flag = true;
    while (flag) {
        min = MAX_WEIGHT;
        for (int i = 0; i < thread_num; ++i) {
            if (globalEdges[i][ptr[i]].w < min) {
                min = globalEdges[i][ptr[i]].w;
            }
        }
        for (int i = 0; i < thread_num; ++i) {
            int size = globalEdges[i].size();
            while (ptr[i] < size && globalEdges[i][ptr[i]].w == min) {
                mst.emplace_back(globalEdges[i][ptr[i]]);
                ptr[i]++;
            }
        }
        for (int i = 0; i < thread_num; ++i) {
            if (ptr[i] < globalEdges[i].size()) {
                flag = true;
                break;
            }
            flag = false;
        }
    }
}


void mergeSort(int tid) {
    mut.lock();
    vector<edge> newEdges;
    int index1 = 0;
    int index2 = 0;
    int size1 = mst.size();
    int size2 = globalEdges[tid].size();
    while (index1 < size1 && index2 < size2) {
        if (globalEdges[tid][index2].w < mst[index1].w) {
            newEdges.emplace_back(globalEdges[tid][index2]);
            index2++;
        } else {
            newEdges.emplace_back(mst[index1]);
            index1++;
        }
    }
    while (index1 < size1) {
        newEdges.emplace_back(globalEdges[tid][index1]);
        index1++;
    }
    while (index2 < size2) {
        newEdges.emplace_back(globalEdges[tid][index2]);
        index2++;
    }
    mst = newEdges;
    mut.unlock();
}


//线程函数，执行“部分算法”
void subthread_func(const vector<vertex> &v, int tid) {
    for (auto &i: v) {
        edge *temp = i.next;
        while (temp != nullptr) {
            temp->tid = tid;
            globalEdges[tid].emplace_back(*temp);
            temp = temp->next;
        }
    }
    std::sort(globalEdges[tid].begin(), globalEdges[tid].end(), Cmp<edge>());
//    mergeSort(tid);
}

void partition() {
    for (int i = 0; i < subthreads.size(); ++i) {
        subthreads.clear();
    }
    vector<vertex> temp[thread_num];
    for (int i = 0; i < graph.size(); i++)
        temp[i % thread_num].push_back(graph[i]);
    for (int i = 0; i < thread_num; i++)
        subthreads.emplace_back(subthread_func, temp[i], i);
}

/*
 * 创建并查集
 */
void MakeSet(vector<int> &uset, int n) {
    uset.assign(n, 0);
    for (int i = 0; i < n; ++i) {
        uset[i] = i;
    }
}

/*
 * 查找当前元素所在集合的代表元
 */
int FindSet(vector<int> &uset, int u) {
    int i = u;
    while (uset[i] != i)
        i = uset[i];
    return i;
}


int Kruskal(const vector<edge> &edges, int n) {
    for (int i = 0; i < thread_num; ++i) {
        if (subthreads[i].joinable())
            subthreads[i].join();
    }
    merge();
    vector<int> uset;
    vector<edge> SpanTree;
    int Cost = 0, e1, e2;
    MakeSet(uset, n);
    for (auto edge: edges) {
        e1 = FindSet(uset, edge.v1);
        e2 = FindSet(uset, edge.v2);
        if (e1 != e2) {
            SpanTree.emplace_back(edge);
            Cost += edge.w;
            uset[e1] = e2;
        }
    }
    return Cost;
}


int main() {
    srand(time(nullptr));
    LARGE_INTEGER t1, t2, tc;
    for (int k = 0; k < 8; ++k) {
        thread_num = k + 1;
        for (int i: n_array) {
            for (int j: e_array) {
                double averageTime = 0;
                construct(i, i * j);//构造图的邻接表
                QueryPerformanceFrequency(&tc);
                QueryPerformanceCounter(&t1);
                //待测代码
                partition();//图的划分，创建并发进程，执行“部分算法”
                Kruskal(mst, i);//全局进程执行“仲裁算法”
                //
                QueryPerformanceCounter(&t2);
                averageTime = ((t2.QuadPart - t1.QuadPart) * 1.0 * 1000 / tc.QuadPart);
                cout << "when  thread = " << thread_num << " n = " << i << " e = " << i * j << " ";
                cout << "TimeConsume:" << averageTime << "ms" << endl;
            }
        }
    }

//    construct(2000, 10000);//构造图的邻接表
//    QueryPerformanceFrequency(&tc);
//    QueryPerformanceCounter(&t1);
//    //待测代码
//    partition();//图的划分，创建并发进程，执行“部分算法”
//    Kruskal(mst, 2000);//全局进程执行“仲裁算法”
//    //
//    QueryPerformanceCounter(&t2);
//   cout<<((t2.QuadPart - t1.QuadPart) * 1.0 * 1000 / tc.QuadPart);


    return 0;
}





