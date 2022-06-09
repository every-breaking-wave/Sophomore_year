#include "FixedSP.h"
#include <iostream>
#include <stack>




vector<int> FixedSP::sort(int * a, int size, int source) {
    vector<int> vec;
    Distance = INF;
    int distance = 0;
    do
    {
        distance = 0;
        distance += matrix[source][a[0]];
        for (int i = 0; i < size - 1; ++i) {
            distance += matrix[a[i]][a[i+1]];
        }
        distance += matrix[a[size-1]][source];
        if(distance < this->Distance){
            Distance = distance;
            vec.clear();
            for (int j = 0; j < size; ++j) {
                vec.emplace_back(a[j]);
            }
        }
    }
    while ( next_permutation(a,a+size) );
    return vec;
}

vector<int> FixedSP::getFixedPointShortestPath(int source, vector<int> intermediates)
{
    vector<int> path;

    this->Distance = INF;
    vector<vector<int>> oldGraph = matrix;
    vector<vector<int>> fullGraph;
    fullGraph = getFullGraph();
    matrix = fullGraph;
    std::sort(intermediates.begin(), intermediates.end());
    int * a = new int [intermediates.size()];
    for (int i = 0; i < intermediates.size(); ++i) {
        a[i] = intermediates[i];
    }
    sortVec.clear();
    sortVec = sort(a, intermediates.size(), source);
    sortVec.insert(sortVec.begin(), source);

    vector<int> fullVec;

    matrix = oldGraph;
    stack<int> pathStack;
    for (size_t i = 0; i < sortVec.size(); i++)
    {
        int p = sortVec[(i+1)%sortVec.size()];
        while (paths[sortVec[i]][p] != -1)
        {
            pathStack.push(p);
            p = paths[sortVec[i]][p];
        }
        pathStack.push(p);
        while (!pathStack.empty())
        {
            fullVec.emplace_back(pathStack.top());
            pathStack.pop();
        }
    }

    for (size_t i = 0; i < fullVec.size(); i++)
    {
        if (fullGraph[fullVec[i]][fullVec[(i + 1) % fullVec.size()]] == INF || fullGraph[fullVec[i]][fullVec[(i + 1) % fullVec.size()]] < 0)
        {
            fullVec.clear();
            return fullVec;
        }
    }
    return fullVec;
}

vector<vector<int>> FixedSP::getFullGraph()
{
    // 初始化 以求出最短路径的点 result[]
    int length = matrix.size();

    vector<vector<int>> newMatrix;
    newMatrix = matrix;
    int n = matrix.size();
    for (int source = 0; source < n; ++source) {
        dis.clear();
        visited.clear();
        paths[source].clear();
        for (int i = 0; i < n; i++)
        {
            dis.emplace_back(matrix[source][i]);
            visited.emplace_back(false);
            paths[source].emplace_back(-1);
        }
        visited[source] = 1;
        for (int i = 0; i < n; i++)
        {
            if (i == source)
            {
                continue;
            }
            int p, minn = INF;
            for (int j = 0; j < n; j++)
            {
                if (!visited[j] && dis[j] < minn)
                {
                    p = j;
                    minn = dis[j];
                }
            }
            visited[p] = true;
            for (int j = 0; j < n; j++)
            {
                if (!visited[j] && dis[p] + matrix[p][j] < dis[j])
                {
                    newMatrix[source][j] = dis[p] + matrix[p][j];
                    dis[j] = dis[p] + matrix[p][j];
                    paths[source][j] = p;
                }
            }
        }
    }
    return newMatrix;
}


