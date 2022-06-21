//
// Created by Feng on 2022/6/11.
//

#ifndef UNTITLED2_EDGE_H
#define UNTITLED2_EDGE_H

class edge {
public:
    edge() = default;
    edge(int a, int b, int c) : v1 (a), v2(b), w(c), next(NULL) {}

    int v1, v2;
    int w{}, tid{};
    edge *next{};
};


#endif //UNTITLED2_EDGE_H
