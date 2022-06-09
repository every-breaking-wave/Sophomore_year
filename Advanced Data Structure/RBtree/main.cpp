#include <iostream>
#include "RBTree.h"
#include <fstream>
#include <windows.h>
#include "AVLtree.h"
#include <time.h>
#include <random>
using namespace std;

string testFile []={
        "../test/test1000_order_insert",
        "../test/test2000_order_insert",
        "../test/test5000_order_insert",
        "../test/test10000_order_insert",
        "../test/test20000_order_insert",
};

string testFile1 []={
        "../test/test1000_inorder_insert",
        "../test/test2000_inorder_insert",
        "../test/test5000_inorder_insert",
        "../test/test10000_inorder_insert",
        "../test/test20000_inorder_insert",
};

void build_RBTree(RB_Tree *rbtree, string input_file_path)
{
    int searchTime = 0;
    ifstream inputData;
    inputData.open(input_file_path, ios::in);
    if(!inputData) {
        cout << "[error]: file " << input_file_path << " not found." << endl;
        inputData.close();
        return ;
    }
    string line;
    LARGE_INTEGER t1, t2, tc;
    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&t1);
    while (inputData >> line)
    {
        int bracketPos = line.find('(');
        string op = line.substr(0, bracketPos);
        string param = line.substr(bracketPos + 1, line.size() - bracketPos - 2);
        if (op == "Insert")
        {
            int commaPos = param.find(')');
            int key = atoi(param.substr(0, commaPos).c_str());
            rbtree->insert(key);
        }
        else if (op == "Search")
        {
            int key = atoi(param.c_str());
            rbtree->find(key);
        }
    }
    QueryPerformanceCounter(&t2);
    cout << "TimeConsume:" << ((t2.QuadPart - t1.QuadPart)*1.0 * 1000/ tc.QuadPart)<<"ms";
    inputData.close();
}


void build_AVLTree(AVLtree *avLtree, string input_file_path)
{
    int searchTime = 0;
    ifstream inputData;
    inputData.open(input_file_path, ios::in);
    if(!inputData) {
        cout << "[error]: file " << input_file_path << " not found." << endl;
        inputData.close();
        return ;
    }
    string line;
    LARGE_INTEGER t1, t2, tc;
    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&t1);
    while (inputData >> line)
    {
        int bracketPos = line.find('(');
        string op = line.substr(0, bracketPos);
        string param = line.substr(bracketPos + 1, line.size() - bracketPos - 2);
        if (op == "Insert")
        {
            int commaPos = param.find(')');
            int key = atoi(param.substr(0, commaPos).c_str());
            avLtree->Insert(key,key);
        }
        else if (op == "Search")
        {
            int key = atoi(param.c_str());
            avLtree->search(key);
        }
    }
    QueryPerformanceCounter(&t2);
    cout << "TimeConsume:" << ((t2.QuadPart - t1.QuadPart)*1.0 * 1000/ tc.QuadPart)<<"ms";
    inputData.close();
}

int main() {


    for(int i = 0; i < 5; i++){
        RB_Tree* rbTree = new RB_Tree;
        cout<<"RBtree test"<<i<<" ";
        build_RBTree(rbTree,testFile1[i]);
        cout<<endl;
        cout<<rbTree->time<<endl;
        delete rbTree;
    }

    for(int i = 0; i < 5; i++){
        AVLtree* avLtree = new AVLtree;
        cout<<"AVLtree test"<<i<<" ";
        build_AVLTree(avLtree,testFile1[i]);
        cout<<endl;
        cout<<avLtree->time<<endl;
        delete avLtree;
    }

    return 0;
}
