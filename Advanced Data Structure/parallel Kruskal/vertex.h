//
// Created by Feng on 2022/6/11.
//

#ifndef UNTITLED2_VERTEX_H
#define UNTITLED2_VERTEX_H
#include "edge.h"
class vertex {
public:
    explicit vertex(int v):vid (v), next(nullptr) {}
    int vid;
    edge *next;
};


#endif //UNTITLED2_VERTEX_H
