//
// Created by Feng on 2022/5/14.
//

#ifndef RBTREE_RBNODE_H
#define RBTREE_RBNODE_H


class RB_Node {

public:
    RB_Node *father;
    RB_Node *left;
    RB_Node *right;
    int value;
    bool color{};     // 节点颜色， false 为 红色， true 为 黑色

    RB_Node();
    RB_Node(int val);
    ~RB_Node();
};


#endif //RBTREE_RBNODE_H
