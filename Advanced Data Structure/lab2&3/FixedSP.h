#include <vector>
#include <string>
#include <string.h>
#include <stack>
#include <algorithm>

using namespace std;

#define INF 1e8

class FixedSP
{
    private:
    vector<int> sortVec;
    vector<int> pathVec;
    int Distance;
    vector<int> path;
    vector<vector<int>> paths;
    vector<bool> visited;
    vector<int> dis;
public:
    vector<vector<int>> matrix;
    vector<pair<pair<int,int>,vector<int>>> vec;
    FixedSP(vector<vector<int>> matrix) {
        for (size_t i = 0; i < matrix.size(); i++)
        {
            vector<int> vec;
            paths.emplace_back(vec);
            for (size_t j = 0; j < matrix.size(); j++)
            {
                paths[i].emplace_back(-1);
            }
            
        }
        this->matrix = matrix;
        Distance = INF;
    }
    ~FixedSP() {}

    vector<int> getFixedPointShortestPath(int source, vector<int> intermediates);

    vector<vector<int>> getFullGraph();

    vector<int> sort(int * a, int size, int source);

};
