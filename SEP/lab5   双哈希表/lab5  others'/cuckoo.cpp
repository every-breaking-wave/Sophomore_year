#include "cuckoo.h"
using namespace std;

int cuckoo::H1(int key)
{
    return key % size;
}

int cuckoo::H2(int key)
{
    return (key / size) % size;
}

cuckoo::~cuckoo()
{
    delete [] table0;
    delete [] table1;
    delete [] record0;
    delete [] record1;
}

void cuckoo::Delete(int key)
{
    int temp;
    temp = H1(key);
    if(table0[temp] == key)
    {
        record0[temp] = 0;
        table0[temp] = table0[temp + size] = 0;
        return;
    }
    temp = H2(key);
    if(table1[temp] == key)
    {
        record1[temp] = 0;
        table1[temp] =  table1[temp + size] = 0;
        return;
    }
    cout << "Key Not Found" << endl;
}

void cuckoo::lookup(int key)
{
    int temp;
    temp = H1(key);
    if(table0[temp] == key && record0[temp] == 1)
    {
        cout << table0[temp + size] << endl;
        return;
    }
    temp = H2(key);
    if(table1[temp] == key && record1[temp] == 1)
    {
        cout << table1[temp + size] << endl;
        return;
    }
    cout << "Key Not Found" << endl;
}

void cuckoo::rehash(int key,int value)
{
     int *temp1,*temp2,*temp1_book,*temp2_book;
     temp1 = new int[size * 2];
     temp2 = new int[size * 2];
     temp1_book = new int[size];
     temp2_book = new int[size];
     for(int i = 0 ;i < size;++i)
     {
         temp1_book[i] = record0[i];
         temp2_book[i] = record1[i];
     }
     for(int i = 0;i < 2 * size;++i)
     {
        temp1[i] = table0[i];
        temp2[i] = table1[i];
     }
     delete [] table0;
     delete [] table1;
     delete [] record0;
     delete [] record1;
     size = size * 2;
     table0 = new int[size * 2];
     table1 = new int[size * 2];
     record0 = new int[size];
     record1 = new int[size];
     for(int i = 0 ;i < size;++i)
     {
         record0[i] = record1[i] = 0;
     }
     for(int i = 0;i < size / 2;++i)
     {
         if(temp1_book[i] == 1)
             insert(temp1[i],temp1[i + size / 2]);
     }
     for(int i = 0;i < size / 2;++i)
     {
         if(temp2_book[i] == 1)
             insert(temp2[i],temp2[i + size / 2]);
     }
     insert(key,value);
}

void cuckoo::kick(int old_value,int old_key, int new_key, int table_no, int table_index,int times)
{
        int temp,key0,value0;
        if(times > size * 2)
        {
            cout << "Loop Detect" << endl;
            rehash(old_key,old_value);
            return;
        }
        cout << "Kick " << old_key <<  " with " << new_key <<" in table " << table_no << " " << table_index << endl;
        if(table_no == 0)
        {
            temp = H2(old_key);
            if(record1[temp] == 0)
            {
                record1[temp] = 1;
                table1[temp] = old_key;
                table1[temp + size] = old_value;
                return;
            }
            else
            {
                key0 = table1[temp];
                value0 =  table1[temp + size];
                table1[temp] = old_key;
                table1[temp + size] = old_value;
                kick(value0,key0,old_key,1,temp,times + 1);
            }
        }
        else
        {
            temp = H1(old_key);
            if(record0[temp] == 0)
            {
                record0[temp] = 1;
                table0[temp] = old_key;
                table0[temp + size] = old_value;
                return;
            }
            else
            {
                key0 = table0[temp];
                value0 =  table0[temp + size];
                table0[temp] = old_key;
                table0[temp + size] = old_value;
                kick(value0,key0,old_key,0,temp,times + 1);
            }
        }
}

void cuckoo::insert(int key, int value)
{
    int temp;
    temp = H1(key);
    if(record0[temp] == 0)
    {
        record0[temp] = 1;
        table0[temp] = key;
        table0[temp + size] = value;
        return;
    }
    if(table0[temp] == key)
    {
        table0[temp + size] = value;
        return;
    }
    temp = H2(key);
    if(record1[temp] == 0)
    {
        record1[temp] = 1;
        table1[temp] = key;
        table1[temp + size] = value;
        return;
    }
    if(table1[temp] == key)
    {
        table1[temp + size] = value;
        return;
    }
    int key0,value0;
    temp = H1(key);
    key0 = table0[temp];
    value0 = table0[temp + size];
    table0[temp] = key;
    table0[temp + size] = value;
    kick(value0,key0,key,0,temp,1);
}
