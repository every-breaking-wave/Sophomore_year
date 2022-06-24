#ifndef LIST_H
#define LIST_H
#pragma once

#include <string>
#include<cstring>
#include<iostream>

using std::string;

class list
{
public:
    virtual void clear()=0;
    virtual int length()=0;
    virtual void insert(int i,const string &x)=0;
    virtual void remove(int i)=0;
    //virtual int search(const string &x)const=0;
    virtual string visit (int i)=0;
    //virtual void traverse()const =0;
    virtual ~list(){};
};

class seqList:public list
{
private:
    string *data;

    int maxSize;
    void doubleSpace();
public:
     int currentlen;
    seqList(int initSize=10);
    ~seqList();
    void clear()override;
    int length()override;
    void insert(int i, const string &x) override;
    void remove(int i) override;
   // void traverse() const override;
    string visit(int i) override;
    //int search(const string &x) const override;
};
class Buffer {
private:

    // TODO: add a List here for storing the input lines

public:
    int currentLineNum;
    Buffer();
    ~Buffer();
     seqList sl;
    void writeToFile(const string &filename);
    void change_line(int x);
    void moveToLine(int idx) ;

    void showLines(int from, int to) ;

    void deleteLines(int from, int to);
    void insertLine(const string &text);
    void appendLine(const string &text);
};
#endif // LIST_H
