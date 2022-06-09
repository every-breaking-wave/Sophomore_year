#include <iostream>
#include "AVLtree.h"
#include <time.h>
#include "SkipList.h"
#include <fstream>
#include<windows.h>
using namespace std;

double ave = 0;

string tests[]={
        "test0",
        "test50_random",
        "test100_random",
        "test500_random",
        "test1000_random",
        "test2000_random",
        "test2000_order",
        "test2000_nega_order"
};

void build_SkipList(SkipList *SkipList, string input_file_path)
{
    ifstream inputData;
    inputData.open(input_file_path, ios::in);
    if(!inputData) {
        cout << "[error]: file " << input_file_path << " not found." << endl;
        inputData.close();
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
            int commaPos = param.find(',');
            int key = atoi(param.substr(0, commaPos).c_str());
            int val = atoi(param.substr(commaPos + 1).c_str());
            SkipList->Insert(key, val);
        }
        else if (op == "Search")
        {
            int key = atoi(param.c_str());
        }
    }
    QueryPerformanceCounter(&t2);
    double time = ((t2.QuadPart - t1.QuadPart)*1000.0 / tc.QuadPart) ;

    cout <<" TimeConsume:" << time<< "ms"<<endl;
    inputData.close();
}

void build_AVL(AVLtree *avlTree, string input_file_path)
{
    ifstream inputData;
    inputData.open(input_file_path, ios::in);
    if(!inputData) {
        cout << "[error]: file " << input_file_path << " not found." << endl;
        inputData.close();
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
            int commaPos = param.find(',');
            int key = atoi(param.substr(0, commaPos).c_str());
            int val = atoi(param.substr(commaPos + 1).c_str());
            avlTree->Insert(key, val);
        }
        else if (op == "Search")
        {
            int key = atoi(param.c_str());
        }
    }
    QueryPerformanceCounter(&t2);
    double time = ((t2.QuadPart - t1.QuadPart)*1000.0 / tc.QuadPart) ;

    cout <<" TimeConsume:" << time<< "ms"<<endl;
    inputData.close();
}

int main() {

    SkipList s;
    AVLtree a;
    for (int i = 0; i < 31; ++i) {
        build_AVL(&a,"../test/"+tests[7]);
//        build_SkipList(&s,"../test/"+tests[7]);
    }

//    build_SkipList(&s,tests[0]);
//    s.Display();
//    srand(time(0));
//    for (int i = 0; i < 50000; ++i) {
//        int key = rand() % 500000;
//        std::cout<<"Insert("<< key<<","<<key << ")" <<std::endl;
//    }


//    for (int i = 0; i < 50000; ++i) {
//        std::cout<<"Insert("<<49999- i<<","<<49999- i << ")" <<std::endl;
//    }

    return 0;
}
