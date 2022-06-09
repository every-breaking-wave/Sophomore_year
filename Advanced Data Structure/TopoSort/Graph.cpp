//
// Created by Feng on 2022/5/16.
//


#include <iostream>
#include "Graph.h"

using namespace std;

Vertex* find(int key, vector<Vertex*> *vec) {
    for(Vertex* node: *vec) {
        if(node->data == key)
            return node;
    }
    return nullptr;
}

void Graph::insert(int from, int to) {
    Vertex *fromNode, *toNode;
    if(!(fromNode = find(from, &vertexs))) { // 新的起始顶点
        fromNode = new Vertex(from);
        vertexs.push_back(fromNode);
        countVertex++;
    }
    if(!(toNode = find(to, &vertexs))) {  // 新的目的顶点
        toNode = new Vertex(to);
        vertexs.push_back(toNode);
        countEdge++;
    }
    fromNode->firstEdge = new EdgeNode(toNode, fromNode->firstEdge);
    toNode->inDegree ++;
}

void Graph::tSort() {
    stack<Vertex *> s;
    for(Vertex* vertex: vertexs) {
        if(vertex->inDegree == 0) {
            s.push(vertex);
        }
    }
    Vertex* top;
    EdgeNode* edge;
    while(!s.empty()) {
        top = s.top();
        s.pop();
        cout<<top->data<<' ';
        for(edge = top->firstEdge;edge;edge = edge->next) {  // dfs遍历
            Vertex *toVertex = edge->end;
            if(!(--toVertex->inDegree)) {
                s.push(toVertex);
            }
        }
    }
}