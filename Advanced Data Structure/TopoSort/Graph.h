
#ifndef TOPOLOGICALSORT_GRAPH_H
#define TOPOLOGICALSORT_GRAPH_H

#include <vector>
#include <stack>

using namespace std;
//边节点
struct Vertex;

struct EdgeNode {
    Vertex *end;
    EdgeNode *next;

    EdgeNode(Vertex *to, EdgeNode *Next) :end(to),next(Next) {}
};

//节点
struct Vertex {
    int inDegree{};  // 入度
    int data{};
    EdgeNode *firstEdge{};

    explicit Vertex(int num):inDegree(0),data(num),firstEdge(nullptr) {}

    Vertex() = default;
};

//图
class Graph {
private:
    int countVertex;
    int countEdge;
    vector<Vertex *> vertexs;  // 存放出现过的vertex

public:
    Graph() {
        countVertex = 0;
        countEdge = 0;
    }

    ~Graph() = default;

    void insert(int, int);

    void tSort();
};


#endif //TOPOLOGICALSORT_GRAPH_H
