#pragma once
/* some code from Libconio 1.0 (C) 2004 FSL A.C. */

#ifdef _WIN32
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
static void clrscr()
{
    system("cls");
}
#else
#include <termios.h>
#include <stdio.h>
#define ESC 033 /* Escape char */

static int getch()
{
    struct termios t;
    int c;

    tcgetattr(0, &t);
    t.c_lflag &= ~ECHO + ~ICANON;
    tcsetattr(0, TCSANOW, &t);
    fflush(stdout);
    c = getchar();
    t.c_lflag |= ICANON + ECHO;
    tcsetattr(0, TCSANOW, &t);
    return c;
}

static void clrscr()
{
    printf("%c[2J", ESC);
    printf("%c[%d;%dH", ESC, 0, 0);
}
#endif

#include <iostream>
#include <cstring>
using namespace std;


class stack{
private:


    int maxSize;
    void doubleSpace();
public:
    int top;
  int *size;
    stack(int initlSize=5);
    ~stack();
    bool isEmpty();
    void push(int x);
    int pop();
    int getTop();
    int getSize(int n);

};

stack::stack(int initSize)
{
    maxSize=initSize;
    size=new int [initSize];
    top=-1;
}

bool stack::isEmpty()
{
    if(top==-1) return true;
    else return false;
}

void stack::push(int x)
{
    if(top==maxSize-1) doubleSpace();
    top++;
    size[top]=x;
}

int stack::pop()
{
    if(top==-1) return 0;
    top--;
    return size[top+1];

}

int stack::getTop()
{     if(isEmpty()){return 0;}
    return size[top];
}
void  stack::doubleSpace()
{
    int *tem=size;
    size=new int[2*maxSize]
;
    for(int i=0;i<maxSize;i++)
    {
        size[i]=tem[i];

    }
    maxSize*=2;
    delete [] tem;
}

int stack::getSize(int n)
{
    if(n!=0)
    return size[n-1];
    else return 0;
}


stack::~stack()
{
    delete [] size;
}


class stackCmd{
private:
public:

        struct node
        {
            int start=0;
            int end=0;
            node *next;
            node(int a,int b,node *n=NULL)
            {
                start=a;end=b;next=n;
            }
            node():next(NULL){}
            ~node(){}
        };
    node *top_p;
    stackCmd();
    ~stackCmd();
    bool isEmpty();
    void push(int a,int b);
    void pop();

};

stackCmd::stackCmd()
{
   top_p=NULL;
}

bool stackCmd::isEmpty()
{
    if(top_p==NULL) return true;
    else return false;
}

void stackCmd::push(int a,int b)
{
    top_p=new node(a,b,top_p);

}

void stackCmd::pop()
{
  node *tmp=top_p;
  top_p=top_p->next;
  delete tmp;

}



stackCmd::~stackCmd()
{
    node *tmp;
    while(top_p!=NULL)
    {
        tmp=top_p;
        top_p=top_p->next;
        delete tmp;
    }

}


class Termio
{
public:
    // donot change the width and height
    static const int CANVAS_WIDTH = 41;
    static const int CANVAS_HEIGHT = 11;
    static char buffer[CANVAS_HEIGHT][CANVAS_WIDTH + 1];
    static stack buffers[3];
    static stackCmd cmd;

    static char GetChar() {
        return getch();
    }

    static void Clear() {
        clrscr();
    }

    static void Draw() {
        for (int i = 0; i < CANVAS_HEIGHT; i++)
        {
            buffer[i][CANVAS_WIDTH] = '\0';
            cout << buffer[i] << endl;
        }
    }

    static void ResetBuffer() {
        for (int i = 0; i < CANVAS_HEIGHT; i++)
            memset(buffer[i], ' ', CANVAS_WIDTH);
    }
};
