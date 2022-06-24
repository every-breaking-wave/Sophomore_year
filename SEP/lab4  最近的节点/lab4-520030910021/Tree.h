//
// Created by Smile on 2019/4/8.
//

#ifndef C_BINARYDIMEN_TREE_H
#define C_BINARYDIMEN_TREE_H

#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

/****************************************************************
 *                    Write your code below
 ****************************************************************/

class TreeNode
{
  friend ostream &operator<<(ostream &out, const TreeNode &b);
  friend class BinaryTree;
  friend class BinaryDimonTree;

private:
  /* data */


public:
  /* methods */
  int data[2];
  int getX();  /* DO NOT CHANGE */
  int getY();  /* DO NOT CHANGE */
  ~TreeNode(); /* DO NOT CHANGE */
  TreeNode (int x,int y, TreeNode* node1,TreeNode *node2);
  TreeNode();
  TreeNode* left;
  TreeNode* right;
  int height;
};


class BinaryDimonTree
{
friend istream &operator>>(istream &in, BinaryDimonTree &tree); /* DO NOT CHANGE */

private:
  /* data */


public:
  /* methods */
  TreeNode *root;
  BinaryDimonTree();          /* DO NOT CHANGE */
  TreeNode *find_nearest_node(int x, int y);  /* DO NOT CHANGE */
   void findnext(int x,int y,TreeNode *&node);
  void recur_search(TreeNode *cur, int x, int y, long long int &min_distance, TreeNode **guess);
  long long int bestDis=1e9+7;
  TreeNode *Guess;
  void addNode(int x,int y,TreeNode* &node);
  void recur_find(TreeNode* &cur,TreeNode* &node);
  ~BinaryDimonTree();
  void clear(TreeNode* tmp);
  bool comX(int x,int y,TreeNode*&node);
    bool comY(int x,int y,TreeNode*&node);
};

#endif //C_BINARYDIMEN_TREE_H
