//
// Created by 16541 on 2022/3/26.
//

#include <iostream>
#include <stdlib.h>
#include <vector>
#include "skipList.h"
#include <time.h>
using namespace std;

double SkipList::my_rand()
{
    s = (16807 * s) % 2147483647ULL;
    return (s + 0.0) / 2147483647ULL;
}

int SkipList::randomLevel()
{
    int result = 1;
    while (result < MaxLevel && my_rand() < 0.5)
    {
        ++result;
    }
    return result;
}


int SkipList::Insert(uint64_t key, const std::string &value){

    int curLevel = MaxLevel;
    for(int i = MaxLevel - 1; i >=0; i--){
        if(head->forwards[i] == NIL){
            curLevel--;
        }
    }
    std::vector<SKNode *> update;
    for(int i = 0; i < MaxLevel; i++){
        update.push_back(nullptr);
    }
    int i = MaxLevel - 1;
    SKNode *node = head;
    if(head->forwards[0] == NIL){  // 还没有节点
        int level = randomLevel();
        curLevel = level;
        SKNode * insertNode = new SKNode(key, value, NORMAL);
        for(int i = 0; i < curLevel; i++){  // 改变原有指针结构
            insertNode->forwards[i] = NIL;
            head->forwards[i] = insertNode;
        }
        return value.size() + 12;
    }
    for( i = MaxLevel - 1; i >= 0; i--){
        while ( node->forwards[i]->key < key){
            node = node->forwards[i];   //  进行一次右移
        }
        // i-- 会导致一次下移
        update[i] = node;  // 每次下移记录一次路线便于insert后修改之前变量的forward指针
    }
    node = node->forwards[0];
    if(node->key == key){
        int size;
        size = value.size() - node->val.size();
        node->val = value;  // 更新node的值
        return size;  // 把不应该产生的size变化修改回去
    }
    else {   // 不等，则在后面插入新节点
        int level = randomLevel();
        if(level > curLevel ){ // 需要更新level
            for(int l = curLevel; l <= level - 1; l ++){
                update[l] = head;
            }
            curLevel = level;
        }

        SKNode * insertNode = new SKNode(key, value, NORMAL);
        for(int i = 0; i < level; i++){  // 改变原有指针结构
            insertNode->forwards[i] = update[i]->forwards[i];
            update[i]->forwards[i] = insertNode;
        }
    }
    return  value.size() + 12;
}

string SkipList::Search(uint64_t key)
{
    // TODO
    int curLevel = 8;
    for(int i = 7; i >=0; i--){
        if(head->forwards[i] == NIL){
            curLevel--;
        }
    }
    int i = MaxLevel - 1;
    SKNode *node = head;
    for( i = MaxLevel - 1; i >= 0; i--){
        while (node->forwards[i]->key < key)
        {
            node = node->forwards[i];   //  进行一次右移
        }
        // i++ 会导致一次下移
    }
    i++;
    node = node->forwards[0];
    if(node->key ==  key && node->val != deleteMark){  // 找到了
        return node->val;
    } else if(node->key == key && node->val == deleteMark){ // deleted
        return deleteMark;
    }
    else {  // 没找到
        return "@NOT@FOUND";
    }

}

bool SkipList::Delete(uint64_t key)
{
    //   vector<SKNode *> update;
    int curLevel = this->MaxLevel;
    for(int i = MaxLevel - 1; i >= 0; i--){
        if(head->forwards[i] == NIL){
            curLevel--;
        }
    }
    std::vector<SKNode *> update;
    for(int i = 0; i < MaxLevel; i++){
        update.push_back(nullptr);
    }
    int i = MaxLevel - 1;
    SKNode *node = head;
    for( i = MaxLevel - 1; i >= 0; i--){
        while ( node->forwards[i]->key < key){
            node = node->forwards[i];   //  进行一次右移
        }
        // i++ 会导致一次下移
        update[i] = node;  // 每次下移记录一次路线便于insert后修改之前变量的forward指针
    }
    node = node->forwards[0];
    // 对跳表的删除改为 插入<key, ”~DELETE~">
    if(node->key == key && node->val != deleteMark)
    {
        this->Insert(key, deleteMark);
        return true;
    }

    //若不在 MEMTable, 需在 SSTable查找
    return false;
//    if(node->key == key){
//        for(int i  = 0; i < curLevel; i++){
//            if(update[i]->forwards[i] != node){  // 该节点的高度不够
//                break;
//            }
//            update[i]->forwards[i] = node->forwards[i];
//        }
//        //delete node;
//    }
//    while (curLevel > 1 && head->forwards[curLevel - 1]->type == SKNodeType::NIL)  {  // 调整lsit的高度
//        curLevel--;
//    }

}

void SkipList::Display()
{
    for (int i = MaxLevel - 1; i >= 0; --i)
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

void SkipList::clear() {
    for (int i = 0; i < MAX_LEVEL; ++i)
    {
        head->forwards[i] = NIL;
    }
}