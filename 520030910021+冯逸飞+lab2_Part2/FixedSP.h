#include <vector>
#include <string>
#include <string.h>
#include <stack>
#include <algorithm>
#include <thread>
using namespace std;

#define INF 1e8

class FixedSP;

typedef struct threadArg
{
public:
    threadArg(FixedSP*fixedSp, int source) :fixedSp(fixedSp),source(source) {
    }
    FixedSP * fixedSp;
    int source;
} threadArg;


class FixedSP
{
    private:
    // TODO: ???
    vector<int> sortVec;
    vector<int> pathVec;
    int rank;
    vector<int> Distance;
    vector<vector<int>> paths;
    vector<vector<bool>>  visited;
    vector<vector<int>>  dis;
    int threadNum;
public:
     vector<vector<int>> matrix;
     vector<vector<int>> fullMatrix;
//    vector<pair<pair<int,int>,vector<int>>> vec;
    FixedSP(vector<vector<int>> matrix) {
        this->rank = matrix.size();
        this->matrix = matrix;
        this->fullMatrix = matrix;
        for (int i = 0; i < matrix.size(); ++i) {
            Distance.emplace_back(INF);
            vector<int> vec;
            vector<bool> boolVec;
            paths.emplace_back(vec);
            visited.emplace_back(boolVec);
            dis.emplace_back(vec);
        }
    }
    ~FixedSP() {}


    vector<int> getFixedPointShortestPath(int source, vector<int> intermediates);

    void multiDijkstra(int source, vector<int> intermediates);

    static void *dijkstra_thread(void *arg);


    vector<int> sort(int * a, int size, int source);

    void setThreadNum(int threadNUm) {this->threadNum = threadNUm;}

    int getThreadNum() {return  this->threadNum;}

     int getRank() { return  rank; }

};
