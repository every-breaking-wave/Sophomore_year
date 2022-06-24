#include "termio.h"
#include<iostream>
using namespace  std;
// Do not delete the following line
char Termio::buffer[Termio::CANVAS_HEIGHT][Termio::CANVAS_WIDTH + 1];
 stack Termio::buffers[3];
 stackCmd Termio::cmd;


//void write_hi() {
//    for (int i = 0; i < 5; i++) {
//        Termio::buffer[i][0] = '|';
//        Termio::buffer[i][5] = '|';
//        Termio::buffer[i][9] = '|';
//        Termio::buffer[i][13] = '*';
//    }
//    Termio::buffer[3][13] = ' ';
//    Termio::buffer[1][9] = ' ';
//    for (int i = 1; i < 5; i++) {
//        Termio::buffer[2][i] = '-';
//    }
//}


void initializer(int n)
{

    for(int i=0;i<Termio::CANVAS_WIDTH;i++)
    {
        Termio::buffer[10][i]='-';
    }
    for(int i=0;i<Termio::CANVAS_HEIGHT;i++)//获得支架
    {
        Termio::buffer[i][5]='|';
        Termio::buffer[i][20]='|';
        Termio::buffer[i][35]='|';
    }

    int start=11-n*2;
    for(int i=0;i<n;i++)
    {
        int len=i+1;
        while(len>=0)
        {
            Termio::buffer[start][5+len]='*';
            Termio::buffer[start][5-len]='*';
            len--;

        }
        start+=2;
    }
}
int charToNum(char A)
{
    switch (A) {
        case 'A':return 5;
        case 'B':return 20;
        case 'C':return 35;
    }
}

int getBlank(char A){
    int a=charToNum(A);
    for(int i=1;i<=9;i+=2)
    {
        if(Termio::buffer[i][a]=='*')
        {
           return i-2;
        }
        if(i==9){return 9;}
    }
}

char numToChar(int x)
{
    switch (x) {
    case 1:return 'A';
    case 2:return 'B';
    case 3:return 'C';
    }
}
int getFirst(char A){
    int a=charToNum(A);
    for(int i=1;i<=9;i+=2)
    {
        if(Termio::buffer[i][a]=='*')
        {
           return i;
    }
    }
}

void clearOne(char A)
{
      int high=getFirst(A);

     for(int i=0;i<=Termio::buffers[A-65].getTop();i++)
     {
        if(i==0)  Termio::buffer[high][charToNum(A)+i]='|';
       else{ Termio::buffer[high][charToNum(A)+i]=' ';
        Termio::buffer[high][charToNum(A)-i]=' ';}
     }

}

void addOne(char A)
{   int high=getBlank(A);
    for(int i=0;i<=Termio::buffers[A-65].getTop();i++)
    {
       Termio::buffer[high][charToNum(A)+i]='*';
       Termio::buffer[high][charToNum(A)-i]='*';

    }
}
void move(int n,char A,char B)
{
    clearOne(A);
    Termio::buffers[B-65].push(Termio::buffers[A-65].pop());
    addOne(B);

    //Termio::ResetBuffer();
    Termio::Draw();

}

void hanoi(int n,char A,char B,char C)
{   if(n==0){return;}

     hanoi(n - 1, A, C, B);
     move(n, A, B); // move the nth disk from rod A to rod B
      cout<<"Auto moving:"<<charToNum(A-65)<<"->"<<charToNum(B-65)<<endl;
     hanoi(n - 1, C, B, A);
}

void autoHanoi(stackCmd st,int n)
{   while(!st.isEmpty())
   {    int x=1;
        move(x,numToChar(st.top_p->end),numToChar(st.top_p->start));
        cout<<"Auto moving:"<<st.top_p->end<<"->"<<st.top_p->start<<endl;
        st.pop();
    }


}

void enhanHanoi(stackCmd st,int x,int y,int z,int n)
{
    autoHanoi(st,n);
    hanoi(n+x,'A','B','C');
    hanoi(-z,'B','C','A');
}
int main() {

    // ---- Example: how to use termio.h ----
    // clear screen
   Termio::Clear();
    // reset buffer
   Termio::ResetBuffer();
   // write_hi();
   // Termio::Draw();
    // ----------- End of example -----------
    // Your code here

   // char Termio::buffer[Termio::CANVAS_HEIGHT][Termio::CANVAS_WIDTH + 1];
    stackCmd Cmd;
    bool isStart=true;
    while (true) {
        int n;
          if(isStart)
          {
              std::cout << "How many disks do you want? (1 ~ 5)" << std::endl;
              char cmd;
              cin>>cmd;
               Termio::Clear();
                Termio::ResetBuffer();
              if(cmd=='Q'){break;}
              int numDisk=cmd-'0';
              n=numDisk;
              initializer(numDisk);
              while(numDisk>0)
              {
                  Termio::buffers[0].push(numDisk);
                  numDisk--;}

              Termio::Draw();
              isStart=false;
              continue;
          }
           bool isTrue=false;
           bool isWrong=false;
           while(!isTrue){

           if(!isWrong)std::cout << "Move a disk. Format: x y" << std::endl;
           int x,y;
           cin>>x>>y;
           if(x>=4||y>=4){isWrong=true;Termio::Clear(); Termio::Draw(); std::cout << "Move a disk. Format: x y" << std::endl;continue;}
           if(Termio::buffers[x-1].getTop()>Termio::buffers[y-1].getTop())
           {    isWrong=true;
               Termio::Clear(); Termio::Draw(); std::cout << "Move a disk. Format: x y" << std::endl;
               continue;
           }
           if(Termio::buffers[x-1].isEmpty()){isWrong=true;
               Termio::Clear(); Termio::Draw(); std::cout << "Move a disk. Format: x y" << std::endl;
               continue;}
           if(x==0&&y==0)
                {autoHanoi(Cmd,n);  hanoi(n,'A','B','C');
                 std::cout << "Congratulations! You win!" << std::endl;
                 isStart=true; break;}
           if(x<=0)
                {int z;cin>>z;enhanHanoi(Cmd,x,y,z,n);
                std::cout << "Congratulations! You win!" << std::endl;
                isStart=true; break;}
           Cmd.push(x,y);
             Termio::Clear();
           move(getFirst(numToChar(x)),numToChar(x),numToChar(y));
           isTrue=true;}

}

//    // some output hints that you should use.
//    std::cout << "How many disks do you want? (1 ~ 5)" << std::endl;
//    std::cout << "Move a disk. Format: x y" << std::endl;
//    std::cout << "Auto moving:1->2" << std::endl;
//    std::cout << "Congratulations! You win!" << std::endl;

    return 0;
}
