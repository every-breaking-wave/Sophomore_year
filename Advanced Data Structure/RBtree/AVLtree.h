//
// Created by 16541 on 2022/3/26.
//

#ifndef AVLTREE_AVLTREE_H
#define AVLTREE_AVLTREE_H
#include <iostream>

struct AVLNode {
    int key;
    int val;
    AVLNode *left;
    AVLNode *right;
    int height; // 结点的高度

    AVLNode(int _key, int _val, AVLNode *_left, AVLNode *_right, int h)
            : key(_key), val(_val), left(_left), right(_right),height(h) {
    }

    void updateHeight(){
        if(right && left) height = std::max(right->height, left->height) + 1;
        else if(right) height = right->height + 1;
        else if(left)  height = left->height + 1;
        else height = 1;
    }

    bool isBalanced(){
        int a = (left == NULL)?0:left->height;
        int b = (right == NULL)?0:right->height;
        return (std::abs(a - b) <= 1);
    }
};

class AVLtree {

private:

public:
    AVLNode* root = NULL;

    AVLtree();
    void Insert(int key, int val);
    void Insert(int key, int val, AVLNode * &t);
    AVLNode* search(int key);
    void display();
    int getHeight(AVLNode *  t);
    bool isBalanced(AVLNode * t);
    void updateHeight(AVLNode * t);
    void LL(AVLNode * & t);
    void RR(AVLNode * & t);
    void LR(AVLNode * & t);
    void RL(AVLNode * & t);
    int max(int a, int b ){return (a < b)? b:a;}
    int time;

};


#endif //AVLTREE_AVLTREE_H
