#include "cuckoo.h"
#include<iostream>
using namespace std;
hashNode::hashNode()
{
    maxSize1=8;
    maxSize2=8;
    hash1=new node[maxSize1];
    hash2=new node[maxSize2];
    for(int i=0;i<maxSize2;i++)// 初始化
    {
        hash1[i].key=-1;
        hash2[i].key=-1;
        hash1[i].data=-1;
        hash2[i].data=-1;
    }
}


void hashNode::insert(int key,int val){

    int pos1,pos2;
    int rf=0;      //作为左右hash的判断
    bool kick_ok=false;//作为是否发生kick的判断
    int curVal=val;//被踢走的/被insert的
    int curKey=key;

    int curtime=0;
    if(currenSize1==maxSize1&&currenSize2==maxSize2) //表满了
    {
        rehash();
        insert(key,val);
    }

    int m=0;
    while(1){
        if(rf%2==0)     //当前在左边
        {       pos1=curKey%maxSize1;
                pos2=(curKey/maxSize2)%maxSize2;
               if(this->hash1[pos1].key==curKey)  //刷新相同key的值
               {this->hash1[pos1].data=curVal;
                   break;
               }

                if(this->hash1[pos1].state==0)//   blank space
                {
                    this->hash1[pos1].data=curVal;
                    this->hash1[pos1].state=1;//   not NULL
                    this->hash1[pos1].key=curKey;
                    currenSize1+=1;

                    break;
                }
                if(this->hash2[pos2].key==curKey) //刷新相同的key值
                {this->hash2[pos2].data=curVal;    
                    break;
                }
                if(this->hash2[pos2].state==0)//   blank space
                {
                    this->hash2[pos2].data=curVal;
                    this->hash2[pos2].state=1;//   not NULL
                    this->hash2[pos2].key=curKey;
                    currenSize2+=1;

                    break;
                }
                //若两边都没空位，kick
                else {
                    int temKey=curKey;
                    int tem=curVal;
                    curVal=hash1[pos1].data;
                    curKey=hash1[pos1].key;
                    hash1[pos1].key=temKey;
                    hash1[pos1].data=tem;
                    rf+=1;
                    m+=1;
                    kick_ok=true;
                    curtime+=1;

                    cout<<"Kick "<<curKey<<" with "<<temKey<<" in table "<<0<<' '<<pos1<<endl;
                    if(curtime==maxSize1+maxSize2)  {break;}
                }
        }
        else{//在右边
            pos2=(curKey/maxSize2)%maxSize2;
            if(this->hash2[pos2].state==0)
            {
                this->hash2[pos2].data=curVal;
                this->hash2[pos2].state=1;//   not NULL
                this->hash2[pos2].key=curKey;
                currenSize2+=1;

                break;
            }
             else{//kick
                int temKey=curKey;
                int tem=curVal;
                curVal=hash2[pos2].data;
                curKey=hash2[pos2].key;
                hash2[pos2].key=temKey;
                hash2[pos2].data=tem;
                rf+=1;
                m+=1;
                kick_ok=true;
                curtime+=1;

                 cout<<"Kick "<<curKey<<" with "<<temKey<<" in table "<<1<<' '<<pos2<<endl;
                if(curtime==(maxSize1+maxSize2)) break;
            }
        }
}


        if(curtime==maxSize1+maxSize2)
        {cout<<"Loop Detect"<<endl;
           rehash();
           curtime=0;
            insert(curKey,curVal);
        }
}



void hashNode::look(int key){
       int pos1=key%maxSize1;
       int pos2=(key/maxSize2)%maxSize2;


       if(hash1[pos1].state==1) {
           if(hash1[pos1].key==key)
          { cout<<hash1[pos1].data<<endl;return;}}

       if(hash2[pos2].state==1)
       {if (hash2[pos2].key==key)
          { cout<<hash2[pos2].data<<endl;return;}
        }
       cout<<"Key Not Found"<<endl;return;
}

void hashNode::remove(int key){
    int pos1=key%maxSize1;
    int pos2=(key/maxSize2)%maxSize2;
    if(hash1[pos1].key==key){ hash1[pos1].state=0; return;}
    if(hash2[pos2].key==key){ hash2[pos2].state=0; return;}
    cout<<"Key Not Found"<<endl;
}

void hashNode::rehash(){
    node *temhash1=this->hash1;
    node *temhash2=this->hash2;
    this->maxSize1*=2;
    this->maxSize2*=2;
    hash1=new node[maxSize1];
    hash2=new node[maxSize2];
    for(int i=0;i<maxSize2;i++)// 初始化
    {
        hash1[i].key=-1;
        hash2[i].key=-1;
        hash1[i].data=-1;
        hash2[i].data=-1;
    }

    for(int i=0;i<maxSize1/2;i++)
    {
           if(temhash1[i].key!=-1)
        insert(temhash1[i].key,temhash1[i].data);
    }
    for(int i=0;i<maxSize2/2;i++)
    {     if(temhash2[i].key!=-1)
        insert(temhash2[i].key,temhash2[i].data);
    }
    delete temhash1;
    delete temhash2;
}

void hashNode::showHash()
{
    for(int i = 0; i < maxSize1; i++){
        cout<<hash1[i].key<<' '<<hash1[i].data<<' '<<hash2[i].key<<' '<< hash2[i].data<<endl;
    }

}
