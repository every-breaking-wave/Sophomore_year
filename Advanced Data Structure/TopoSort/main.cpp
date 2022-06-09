
#include <iostream>
#include <fstream>
#include "Graph.h"

void build_Graph(Graph *graph,  string input_file_path)
{
    ifstream inputData;
    inputData.open(input_file_path, ios::in);
    if(!inputData) {
        cout << "[error]: file " << input_file_path << " not found." << endl;
        inputData.close();
        return ;
    }
    string line;
    while (inputData >> line)
    {
        int bracketPos = line.find(',');
        string from = line.substr(0, bracketPos);
        string to = line.substr(bracketPos + 1, line.size() - bracketPos - 1);
        int From = atoi(from.c_str());
        int To = atoi(to.c_str());
        graph->insert(From,To);
    }
    inputData.close();
}



int main() {
    Graph *graph = new Graph();
    build_Graph(graph,"../input");
    graph->tSort();
    return 0;
}
