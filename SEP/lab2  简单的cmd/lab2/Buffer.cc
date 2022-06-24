#include <fstream>
#include <iostream>
#include "Buffer.h"

using namespace std;
//TODO: your code here
//implement the functions in ListBuffer

Buffer::Buffer() {}

Buffer::~Buffer() {}

void Buffer::writeToFile(const string &filename) {
    int storage=0;
    for(int i=1;i<=sl.length();i++)
   {    for(int j=0;j<sl.visit(i-1).size();j++)
        {
            if(sl.visit(i-1)[j]=='\t')
            {storage=storage+3;}
        }

        storage+=sl.visit(i-1).size();
        storage++;
}   cout<<storage<<' '<<"byte(s) written"<<endl;
}

void Buffer::showLines(int from, int to)  {

    if(from==-1)
    {for(int i=1;i<=sl.length();i++)
    {       cout<<i<<'\t';

          cout<<this->sl.visit(i-1)<<endl;

        }
        this->currentLineNum=sl.length();
        return;
        }
    for(int i=from;i<=to;i++)
    { cout<<i<<'\t';

   cout<<this->sl.visit(i-1)<<endl;

    }
    this->currentLineNum=to;

}

void Buffer::deleteLines(int from, int to){
   int i=(to-from)+1;

    while(i>0)
    {
        sl.remove(from-1);
    this->
        i--;

}
    this->currentLineNum=from;
    if(sl.length()<from){this->currentLineNum=sl.length();}
}

void Buffer::insertLine(const string &text){

    if(this->sl.length()==0){this->sl.insert((0),text);
       this->change_line(1);
        return;
        //cout<<"currentlinenum"<<currentLineNum<<endl;
    }
    this->sl.insert((this->currentLineNum-1),text);
    //cout<<"currentlinenum"<<currentLineNum<<endl;


}

void Buffer::appendLine(const string &text){
    if(sl.length()==0){

        this->currentLineNum=0;
        }

    this->sl.insert(this->currentLineNum,text);
    this->currentLineNum++;

}

 void Buffer::moveToLine(int idx) {
     change_line(idx);
   cout<<this->sl.visit(idx-1);


}
void Buffer::change_line(int x)
{
    this->currentLineNum=x;
}
int seqList::length()
{
    return currentlen;
}

string seqList::visit(int i)
{return data[i];}

seqList::seqList(int initSize)
{
    data=new string[initSize];
    maxSize=initSize;
    currentlen=0;
}
void seqList::insert(int i, const string &x)
{
    if(currentlen==maxSize){doubleSpace();}
    if(i==currentlen){
        data[i]=x;
        currentlen++;
         return;
    }

    for(int j=currentlen;j>i;j--)
    {
    data[j]=data[j-1];}//可以这样赋值吗
    data[i]=x;
     currentlen++;
   }
void seqList::remove(int i)
{     int len=currentlen;
    for(int j=i;j<len-1;j++)
    {
    data[j]=data[j+1];//可以这样赋值吗
  }

      currentlen--;


}
void seqList::doubleSpace()
{
    string *tem=data;
    maxSize*=2;
    data=new string[maxSize];
    for(int i=0;i<currentlen;i++)
    {
        data[i]=tem[i];
    }
    delete []tem;
}
seqList::~seqList()
{
    delete []data;
}
void seqList::clear()
{currentlen=0;}

