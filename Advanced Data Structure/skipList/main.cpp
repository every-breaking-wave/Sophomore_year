#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <string.h>
#include <signal.h>
#include "HashTable.h"
#include "SkipList.h"
#include <time.h>
#include <windows.h>
#include <cmath>

using namespace std;

#define TEST_NUM    6

string search[TEST_NUM] = {
        "skiplist_search10",
        "skiplist_search50",
        "skiplist_search100",
        "skiplist_search200",
        "skiplist_search500",
        "skiplist_search1000",
};

string insert[TEST_NUM] = {
        "skiplist_create_input10",
        "skiplist_create_input50",
        "skiplist_create_input100",
        "skiplist_create_input200",
        "skiplist_create_input500",
        "skiplist_create_input1000",
};

double build_SkipList(SkipList *SkipList, string input_file_path)
{
    int searchTime = 0;
    ifstream inputData;
    inputData.open(input_file_path, ios::in);
    if(!inputData) {
        cout << "[error]: file " << input_file_path << " not found." << endl;
        inputData.close();
        return 0;
    }

    string line;
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
            searchTime += SkipList->Search(key);
        }
    }
    inputData.close();
    return  (double)searchTime/10000.0;
}

int main(){
    int test = 0;
    double p[6] = {0.5, (double )(exp(-1)), (1.0/4),(1.0/8),(1.0/16)};
    int size[6] = {10,50,100,200,500,1000};
    srand((int) time(0));
    for(int i = 0; i < 5; i++){  // i represnts p
        for(int j = 0; j < 6; j++){ // j represents size
            SkipList s(size[j]);
            s.setP(p[i]);
            build_SkipList(&s,"../input/" + insert[j]);
            int count = 0;
            for(int k = 0; k < 10000; k++){
                int key = rand()%size[j];
                count += s.Search(key);
            }
            cout<<"when size ="<<size[j]<<"p = "<<p[i]<<" average search time is "<<
                count/(10000.0)<<endl;
        }
    }
}
