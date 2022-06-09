//
// Created by Feng on 2022/5/14.
//

#include "RBNode.h"
#include "RBTree.h"
RB_Node::RB_Node() = default;


RB_Node::RB_Node(int val) : father(nullptr), left(nullptr), right(nullptr), color(RED), value(val) {};


RB_Node::~RB_Node() = default;