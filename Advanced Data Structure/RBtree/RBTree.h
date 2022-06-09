//
// Created by Feng on 2022/5/14.
//

#ifndef RBTREE_RBTREE_H
#define RBTREE_RBTREE_H
//#include "myBST.h"


#include <iostream>
#include <queue>
#include "RBNode.h"

#define BLACK true
#define RED false

class RB_Tree {

private:
    RB_Node *root;

public:
    int time;
    RB_Tree();
    void left_rotate(RB_Node *x);
    void right_rotate(RB_Node *x);
    RB_Node* min_node(RB_Node *x);
    void transplant(RB_Node *u, RB_Node *v);      // 移植函数
    RB_Node* find(int data);
    void insert(int data);
    void insert_fixup(RB_Node *x);       // 插入后调整

    ~RB_Tree();     // 析构函数
};


#endif //RBTREE_RBTREE_H
