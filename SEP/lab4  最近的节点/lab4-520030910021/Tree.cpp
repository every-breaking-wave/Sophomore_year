
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <limits.h>
#include <vector>
#include <queue>
#include <algorithm>
#include "Tree.h"

using namespace std;

/****************************************************************
 *                    Write your code below
 ****************************************************************/
//void Redistance(int x,int y,BinaryDimonTree &tree,TreeNode* &node)//node:树种的节点，x，y待找节点
//{   if(node==NULL) return;
//    long long int dis=(x-node->getX())*(x-node->getX())+(y-node->getY())*(y-node->getY());
//    if(((tree.bestDis))>dis)
//    {
//        tree.bestDis=dis;
//        (tree.Guess)=node;
//    }
//}

BinaryDimonTree::BinaryDimonTree()
{
    root=NULL;
    Guess=NULL;
}

//void BinaryDimonTree::recur_search(TreeNode *cur, int x, int y, long long int &min_distance, TreeNode **guess)
//{

//}

//void BinaryDimonTree::recur_find(TreeNode* cur,TreeNode* node)
//{
//    if(cur==NULL||bestDis==0) return;
//    Redistance(node->getX(),node->getY(),*this,cur);
//    double dis=bestDis;

//}



 BinaryDimonTree::~BinaryDimonTree()
 {
    clear(root);
 }

int TreeNode::getX()
{
    return data[0];
}

int TreeNode::getY()
{
    return data[1];
}

TreeNode::TreeNode()
{
    this->left=NULL;
    this->right=NULL;
}

TreeNode::TreeNode(int x,int y,TreeNode* node1,TreeNode *node2)
{
    this->data[0]=x;
    this->data[1]=y;
    this->left=node1;
    this->right=node2;
}
TreeNode::~TreeNode() {}
 void BinaryDimonTree::addNode(int x,int y,TreeNode* &node)
 {
     if(node==NULL){node=new TreeNode(x,y,NULL,NULL);node->height=1;}
     else if(node->height%2==1){
      if(x<node->getX())
     {
         addNode(x,y,node->left);
         node->left->height=node->height+1;
     }
     else if(x>=node->getX())
     {
          addNode(x,y,node->right);
          node->right->height=node->height+1;
      }
 }
     else{
         if(y<node->getY())
        {
            addNode(x,y,node->left);
            node->left->height=node->height+1;
        }
        else if(y>=node->getY())
        {
             addNode(x,y,node->right);
             node->right->height=node->height+1;
        }
     }
}

 bool BinaryDimonTree:: comX(int x,int y,TreeNode*&node){
     if(node->getX()==x)
     {
         return y<node->getY();
     }
     return x<node->getX();
 }

 bool BinaryDimonTree:: comY(int x,int y,TreeNode*&node){
     if(node->getY()==y)
     {
         return x<node->getX();
     }
     return y<node->getY();
 }

 istream &operator>>(istream &in, BinaryDimonTree &tree)
 {
     int num;
     in>>num;
     for(int i=0;i<num;i++)
     {
         int x,y;
         in>>x;
         in>>y;
         tree.addNode(x,y,tree.root);
     }
     return in;
 }

 void BinaryDimonTree ::findnext(int x,int y,TreeNode *&node)
 {
     //if(node==NULL||(node->getX()==x&&node->getY()==y)) return Guess;
      if(node==NULL) return;
     long long int dis=(x-node->getX())*(x-node->getX())+(y-node->getY())*(y-node->getY());
     if(((this->bestDis))>dis)
     {
         this->bestDis=dis;
         (this->Guess)=node;
     }
     else if(this->bestDis==dis)
     {
         if(node->getX()<Guess->getX())
         {
             Guess=node;
         }
         else if(node->getX()==Guess->getX()&&node->getY()<Guess->getY())
         {
             Guess=node;
         }
     }

     if(node->height%2==1){
      if(x<node->getX())
     {
        findnext(x,y,node->left);
        if((node->getX()-x)*(node->getX()-x)<this->bestDis)
        {
                 findnext(x,y,node->right);
        }
        }

     else
     {
          findnext(x,y,node->right);
          if((node->getX()-x)*(node->getX()-x)<this->bestDis)
          {
                   findnext(x,y,node->left);
          }
          }
     }

     else {
         if(y<node->getY())
        {
              findnext(x,y,node->left);
              if((node->getY()-y)*(node->getY()-y)<this->bestDis)
              {
                findnext(x,y,node->right);
               }
              }

        else if(y>=node->getY())
        {
           findnext(x,y,node->right);
            if((node->getY()-y)*(node->getY()-y)<this->bestDis)
            {
               findnext(x,y,node->left);
             }
            }
        }
 }




  TreeNode* BinaryDimonTree::find_nearest_node(int x, int y)
  {
        this->Guess=NULL;
        if(root==NULL||(root->getX()==x&&root->getY()==y)) return root;
        this->bestDis=1e9+7;
        findnext(x,y,root);
        return Guess;
  }

  void BinaryDimonTree::clear(TreeNode *tmp){
      if(tmp) {
           clear(tmp->left);
           clear(tmp->right);
           delete tmp;
       } else {
           return;
       }
  }
