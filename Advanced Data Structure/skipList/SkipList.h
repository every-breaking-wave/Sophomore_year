#pragma once

#include <vector>
#include <climits>
#include <stdlib.h>
#include <math.h>

#define MAX_LEVEL 8

enum SKNodeType
{
    HEAD = 1,
    NORMAL,
    NIL
};

struct SKNode
{
    int key;
    int val;
    SKNodeType type;
    std::vector<SKNode *> forwards;
    SKNode(int _key, int _val, SKNodeType _type,int size)
            : key(_key), val(_val), type(_type)
    {
        for (int i = 0; i < size; ++i)
        {
            forwards.push_back(nullptr);
        }
    }
};

class SkipList
{
private:
    SKNode *head;
    SKNode *NIL;
    std::vector<SKNode *> update;
    int randomLevel();
    unsigned long long s = 1;
    double my_rand();
    int level;
    double p;
public:
    SkipList(int num)
    {
        level = log2(num);
        p = 0.5;
        head = new SKNode(0, 0, SKNodeType::HEAD,num);
        NIL = new SKNode(INT_MAX, 0, SKNodeType::NIL,num);
        for (int i = 0; i < level; ++i)
        {
            head->forwards[i] = NIL;
            update.push_back(nullptr);
        }
        srand(1);
    }
    void continSearch(int beg, int end);
    void Insert(int key, int value);
    int Search(int key);
    void setP(double p);
    // void Delete(int key);
    void Display();
    ~SkipList()
    {
        SKNode *n1 = head;
        SKNode *n2;
        while (n1)
        {
            n2 = n1->forwards[0];
            delete n1;
            n1 = n2;
        }
    }
};
