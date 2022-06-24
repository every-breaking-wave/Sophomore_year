#ifndef CUCKOO_H
#define CUCKOO_H

#include <iostream>
using namespace std;
class cuckoo
{
private:
    int *table0,*table1,*record0,*record1;
    int H1(int key);
    int H2(int key);
    int size;
    void kick(int old_value,int old_key,int new_key,int table_no,int table_index,int times);
    void rehash(int key,int value);
public:
    void insert(int key,int value);
    void lookup(int key);
    void Delete(int key);
    cuckoo()
    {
        table0 = new int[16];
        table1 = new int[16];
        record0 = new int[8];
        record1 = new int[8];
        size = 8;
        for(int i = 0 ;i < size;++i)
        {
            record0[i] = record1[i] = 0;
        }
    }
    ~cuckoo();
};

#endif // CUCKOO_H
