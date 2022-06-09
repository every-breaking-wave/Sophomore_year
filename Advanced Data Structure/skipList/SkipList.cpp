#include <iostream>
#include <stdlib.h>
#include <vector>
#include "SkipList.h"
#include <time.h>
using namespace std;

double SkipList::my_rand()
{
    return (rand()% 10000);
}

int SkipList::randomLevel()
{
    int result = 1;
    while (result < level && my_rand() < (double )(this->p * 10000))
    {
        ++result;
    }
    return result;
}


void SkipList::Insert(int key, int value){

    //  std::vector<SKNode *> update;
    int i = level - 1;
    SKNode *node = head;
    if(head->forwards[0] == NIL){  // 还没有节点
        int newLevel = randomLevel();
        // this->level = level;
        SKNode * insertNode = new SKNode(key, value, NORMAL,newLevel);
        for(int i = 0; i < newLevel; i++){  // 改变原有指针结构
            insertNode->forwards[i] = NIL;
            head->forwards[i] = insertNode;
        }
        return;
    }
    for( i = level - 1; i >= 0; i--){
        while ( node->forwards[i]->key < key){
            node = node->forwards[i];   //  进行一次右移
        }
        // i-- 会导致一次下移
        update[i] = node;  // 每次下移记录一次路线便于insert后修改之前变量的forward指针
    }
    node = node->forwards[0];
    if(node->key == key){
        node->val = value;  // 更新node的值
        return;
    }
    else {   // 不等，则在后面插入新节点
        int level = randomLevel();
        if(level > this->level ){ // 需要更新level
            for(int l = this->level; l <= level - 1; l ++){
                update[l] = head;
            }
            this->level = level;
        }

        SKNode * insertNode = new SKNode(key, value, NORMAL,level);
        for(int i = 0; i < level; i++){  // 改变原有指针结构
            insertNode->forwards[i] = update[i]->forwards[i];
            update[i]->forwards[i] = insertNode;
        }
    }

}

int SkipList::Search(int key)
{
    // TODO
    int searchTime = 0;
    int i = level - 1;
    SKNode *node = head;
    for( i = level - 1; i >= 0; i--){
        while (node->forwards[i]->key < key)
        {
            searchTime++;
            node = node->forwards[i];   //  进行一次右移
        }
        searchTime++; //下移
    }
    i++;
//    searchTime++;
    node = node->forwards[0];
    return  searchTime;

}

void SkipList::continSearch(int beg, int end) {
    int i = level - 1;
    SKNode *node = head;
    int key = beg;
    for( i = level - 1; i >= 0; i--){
        while (node->forwards[i]->key < key)
        {
            node = node->forwards[i];   //  进行一次右移
        }
    }
    i++;
    node = node->forwards[0];    //  此时找到/没找到第一个node
    int findId = beg;
    while (node->key <= end){
        //  std::cout << node->key << " value " << node->val<<endl;
        node = node->forwards[0];
    }

}


void SkipList::Display()
{
    for (int i = level - 1; i >= 0; --i)
    {
        std::cout << "Level " << i + 1 << ":h";
        SKNode *node = head->forwards[i];
        while (node->type != SKNodeType::NIL)
        {
            std::cout << "-->(" << node->key << "," << node->val << ")";
            node = node->forwards[i];
        }
        std::cout << "-->N" << std::endl;
    }
}

void SkipList::setP(double p) {
    this->p = p;
}
