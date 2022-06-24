#include "termio.h"
#include<iostream>
using namespace  std;
// Do not delete the following line
char Termio::buffer[Termio::CANVAS_HEIGHT][Termio::CANVAS_WIDTH + 1];
 stack Termio::buffers[3];
 stackCmd Termio::cmd;
 void clearBuffer(){
     for(int i=0;i<3;i++)
     {
             Termio::buffers[i].top=-1;
     }
    while(!Termio::cmd.isEmpty()){
        Termio::cmd.pop();
    }
 }

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

void write()
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



    int level=0;
    int k=0;
    for(int i=5-(Termio::buffers[0].top+1); i<5;i++){

        while(level<=Termio::buffers[0].getSize(Termio::buffers[0].top+1-k))
        {
            Termio::buffer[2*i+1][5+level]='*';
            Termio::buffer[2*i+1][5-level]='*';
            level++;
        }
        level=0;
        k++;
     }

     level=0;
      k=0;
     for(int i=5-(Termio::buffers[1].top+1); i<5;i++){

         while(level<=Termio::buffers[1].getSize(Termio::buffers[1].top+1-k))
         {
             Termio::buffer[2*i+1][20+level]='*';
             Termio::buffer[2*i+1][20-level]='*';
             level++;
         }
         level=0;
         k++;
      }

     level=0;
      k=0;
     for(int i=5-(Termio::buffers[2].top+1); i<5;i++){

         while(level<=Termio::buffers[2].getSize(Termio::buffers[2].top+1-k))
         {
             Termio::buffer[2*i+1][35+level]='*';
             Termio::buffer[2*i+1][35-level]='*';
             level++;
         }
         level=0;
         k++;
      }


}

void move(int x,int y)
{
    int tem=Termio::buffers[x-1].getTop();
    Termio::buffers[x-1].pop();
    Termio::buffers[y-1].push(tem);
    Termio::ResetBuffer();
    write();
    Termio::Draw();

}

void hanoi(int n,int x,int y,int z)
{   if(n<=0){return;}

     hanoi(n - 1, x,z,y);
      cout<<"Auto moving:"<<x<<"->"<<y<<endl;
     move(x,y); // move the nth disk from rod A to rod B

     hanoi(n - 1, z,y,x);
}

void autoHanoi(int n)
{   while(!Termio::cmd.isEmpty())
   {    int x=1;
        cout<<"Auto moving:"<<Termio::cmd.top_p->end<<"->"<<Termio::cmd.top_p->start<<endl;
        move(Termio::cmd.top_p->end,Termio::cmd.top_p->start);

        Termio::cmd.pop();
    }


}

void enhanHanoi(int x,int y,int z,int n)
{
    autoHanoi(n);
    hanoi(n+x,1,2,3);
    hanoi(-z,2,3,1);
      std::cout << "Congratulations! You win!" << std::endl;
      return;
}


int main() {

    // ---- Example: how to use termio.h ----
    // clear screen
   Termio::Clear();
    // reset buffer
   Termio::ResetBuffer();
    bool isStart=true;
    bool isQuit=false;
    while (true) {
        static int n;
          while(isStart)
          {
              std::cout << "How many disks do you want? (1 ~ 5)" << std::endl;
              char cmd;
              cin>>cmd;
              // Termio::Clear();
               Termio::ResetBuffer();
              if(cmd=='Q'){isQuit=true;break;}
              int numDisk=cmd-'0';
              n=numDisk;
              if(n>5){continue;}
              initializer(numDisk);
              while(numDisk>0)
              {
                  Termio::buffers[0].push(numDisk);
                  numDisk--;}            
              Termio::Draw();
              isStart=false;
              continue;
          }
          if(isQuit==true) break;
          if(Termio::buffers[1].top==n-1)
          {
              std::cout << "Congratulations! You win!" << std::endl;
              clearBuffer();
              isStart = true;
                  continue;
          }
          std::cout << "Move a disk. Format: x y" << std::endl;
          int x,y;
          cin>>x>>y;
             if(x>=4||y>=4) { write();Termio::Draw(); continue;}
          if(x==0&&y==0)
            {
             autoHanoi(n);
             hanoi(n,1,2,3);
             std::cout << "Congratulations! You win!" << std::endl;
             isStart=true;
             clearBuffer();
             continue;
          }


         if(x<=0||y<=0)
         {int z;cin>>z;
        if(Termio::cmd.isEmpty())
        {
            hanoi(n+x,1,2,3);
            hanoi(-z,2,3,1);
            std::cout << "Congratulations! You win!" << std::endl;
            isStart=true;
            clearBuffer();
            continue;
        }
        enhanHanoi(x,y,z,n);
         isStart=true;
         clearBuffer();
         continue;}

            if(Termio::buffers[x-1].isEmpty()){ write();Termio::Draw();continue;}

            if(Termio::buffers[x-1].getTop()>Termio::buffers[y-1].getTop()&&!Termio::buffers[y-1].isEmpty())
            {
                write();
                Termio::Draw();
                continue;
            }


          move(x,y);
          Termio::cmd.push(x,y);
          Termio::ResetBuffer();
    }

    return 0;
}
