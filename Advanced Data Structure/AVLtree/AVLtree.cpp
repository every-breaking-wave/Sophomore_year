//
// Created by 16541 on 2022/3/26.
//

#include "AVLtree.h"
#include <iostream>



AVLtree::AVLtree() {

}

// 默认插在root上
void AVLtree::Insert(int key, int val) {
    Insert(key,val,root);
}

//用于递归，插在t上
void AVLtree::Insert(int key, int val, AVLNode * &t){
    AVLNode * searchNode = search(key);
    if(searchNode != NULL) {  // 更新key值
        searchNode->val = val;
        return;
    }
    if(t == NULL)
        t = new AVLNode(key,val,NULL,NULL,1);
    else if(key < t->key){ // 插在左子树上
        this->Insert(key,val,t->left);
        if( !isBalanced(t)){
            if(key < t->left->key) LL(t);
            else LR(t);
        }
    } else{
        this->Insert(key,val,t->right);
        if(!isBalanced(t)){
            if(key < t->right->key) RL(t);
            else RR(t);
        }
    }
    // 更新结点的高度
    t->updateHeight();
}

/**
 *
 * @param key
 * @return  被找到的节点或NULL
 */
AVLNode* AVLtree::search(int key) {
    AVLNode * t = this->root;
    while (t && t->key != key){
        if(t->key > key) t = t->left;
        else  t = t->right;
    }
    // 若找不到，返回NULL
    return t;
}
int AVLtree::getHeight(AVLNode * t){
    return t == NULL ? 0:t->height;
}

bool AVLtree::isBalanced(AVLNode * t){
    return (std::abs(getHeight(t->left) - getHeight(t->right)) <= 1);
}

void AVLtree::updateHeight(AVLNode *t) {
    t->height = max(getHeight(t->left), getHeight(t->right)) + 1;
}

void AVLtree::LL(AVLNode * & t){
    AVLNode * newRoot = t->left;
    t->left = newRoot->right;
    newRoot->right = t;
    // 更新height
    t->height = max(getHeight(t->left), getHeight(t->right)) + 1;
    newRoot->height = max(getHeight(newRoot->left), getHeight(t)) + 1;
    t = newRoot;

}
void AVLtree::RR(AVLNode * & t){
    AVLNode * newRoot = t->right;
    t->right = newRoot->left;
    newRoot->left = t;
    //更新height
    t->height = max(getHeight(t->left), getHeight(t->right)) + 1;
    newRoot->height = max(getHeight(newRoot->right), getHeight(t)) + 1;
    t = newRoot;

/*
    以下为一个有问题的写法，问题在于，提前改变了 t 的指向，此时的t 和 newRoot 已经指向了同一个地方
    再更新t的高度也只是更新新的“根节点”的高度
    t = newRoot;
    t->height = max(getHeight(t->left), getHeight(t->right)) + 1;
    newRoot->height = max(getHeight(newRoot->right), getHeight(newRoot->left)) + 1;
*/
}
void AVLtree::LR(AVLNode * & t){
    RR(t->left);
    LL(t);
}
void AVLtree::RL(AVLNode * & t){
    LL(t->right);
    RR(t);
}

void AVLtree::display(){

}
