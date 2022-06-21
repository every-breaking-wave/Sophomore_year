#include "ScapegoatTree.h"
#include <iostream>
#include <cmath>
#include <stack>

int ScapegoatTree::GetRebalanceTimes() {
    // TODO
    return times;
}

void ScapegoatTree::Search(int key) {
    // TODO

    int height = 0;
    goatNode *node = this->root;
    while (node) {
        if (key > node->key) {
            node = node->right;
        } else if (key < node->key) {
            node = node->left;
        } else if (key == node->key) {
            cout << height << endl;
            return;
        }
        height++;
    }
    cout << "Not Found" << endl;
}

void ScapegoatTree::Insert(int key) {
    goatNode *node, *p;
    int dep = 0;
    if (!root) {
        root = new goatNode(NULL, NULL, NULL, key);
        maxNum = 1;
        nodeNum = 1;
        return;
    }
    node = root;
    p = NULL;
    while (node) {
        if (node->key == key)
            break;
        else if (node->key < key) {
            p = node;
            node = node->right;
        } else if (node->key > key) {
            p = node;
            node = node->left;
        }
        dep++;
    }
    if (!node) {
        node = new goatNode(NULL, NULL, p, key);
        if (p->key > node->key)
            p->left = node;
        else
            p->right = node;
        nodeNum++;
    }
    maxNum = max(nodeNum,maxNum);
    if (dep > (int) (log((getNodeNum(root))) / log(1 / ALPHA))) {
        int limitSize = ALPHA * getNodeNum(node);
        while (getNodeNum(node->left) <= limitSize &&
               getNodeNum(node->right) <= limitSize) {
            node = node->parent;
        }
        rebalance(node);
    }
}

void ScapegoatTree::Delete(int key) {
    remove(key, root);
    if (nodeNum <= maxNum * ALPHA) {
        rebalance(root);  // 以根结点进行重构
        maxNum = getNodeNum(root);
    }
}

void ScapegoatTree::remove(int key, goatNode *&node) {
    if (node == NULL) return;
    if (key < node->key) remove(key, node->left);
    else if (key > node->key) remove(key, node->right);
    else if (node->left && node->right) {
        goatNode *tmp = node->right;
        while (tmp->left) {
            tmp = tmp->left;
        }
        node->key = tmp->key;
        remove(node->key, node->right);
    } else {
        goatNode *oldNode = node;
        node = (node->left) ? node->left : node->right;
        if (node)
            node->parent = oldNode->parent;
        oldNode = NULL;
        delete oldNode;
        nodeNum--;
    }


}

/**
 * 一段有问题但是值得反思的代码
 */
//void ScapegoatTree::Delete(int key)
//{
//    // TODO
//    if(key == 21){
//        cout<<1;
//    }
//    goatNode* node = root;
//    while (node){
//        if(key < node->key) node = node->left;
//        else if(key > node->key)
//            node = node->right;
//        else if(key == node->key)
//            break;
//    }
//    if(!node){
//        return;
//    }
//    if((!node->left || !node->right) && node != root){  // 被删除结点有0，1个子节点且不为根
//        if(node->parent->key > node->key){
//            node->parent->left = node->left ? node->left : node->right;
//        }
//        else if(node->parent->key < node->key){
//            node->parent->right = node->left ? node->left : node->right;
//        }
//    }
//    else if(node == root && (!root->left) || (!node->right)){  // 若被删结点为根，且根只有0，1个子节点
//        root = root->left ? root->left : root->right;
//        if(root) root->parent = NULL;
//    }
//
//    else if(node->left && node->right){   // 被删结点有2个子节点
//        goatNode * rightMinNode = node->right;
//        while (rightMinNode->left){
//            rightMinNode = rightMinNode->left;
//        }
//        if(rightMinNode->right){
//            if(rightMinNode->parent != node){
//                rightMinNode->parent->left = rightMinNode->right;
//                rightMinNode->right->parent = rightMinNode->parent;
//            }
//            else {
//                rightMinNode->right->parent = rightMinNode->parent;
//                rightMinNode->parent->right = rightMinNode->right;
//            }
//        }
//        else {
//            if(rightMinNode->parent != node){
//                rightMinNode->parent->left = NULL;
//            }
//            else {
//                rightMinNode->parent->right = NULL;
//            }
//        }
//            node->key = rightMinNode->key;
//    }
//    if(getNodeNum(root) < maxNum * ALPHA){
//        rebalance(root);  // 以根结点进行重构
//        return;
//    }
//}


int ScapegoatTree::getHeight() {
    return height;
}


int ScapegoatTree::curHeight(goatNode *node) {
    if (!node) return 0;
    int maxHeight = max(curHeight(node->left), curHeight(node->right)) + 1;
    return maxHeight;
}

void ScapegoatTree::rebalance(goatNode *node) {
    this->times++;
    if (!root) return;
    root->parent = NULL;
    while (!isGoatNode(node) && node && node != root) {
        node = node->parent;
    }
    // 中序遍历

    vector<goatNode *> res;
    if (!root) return;

    stack<goatNode *> s;
    goatNode *cur = node;
    while (!s.empty() || cur) {
        // 沿着当前节点cur的左分支一直走到底
        while (cur) {
            s.push(cur);
            cur = cur->left;
        }
        goatNode *node = s.top();
        s.pop();
        res.emplace_back(node);
        cur = node->right;
    }
    goatNode *parent = node->parent;
    for (int i = 0; i < res.size(); i++) {
        res[i]->right = NULL;
        res[i]->left = NULL;
    }

    goatNode *newNode = buildAVL(0, res.size() - 1, res);
    if (parent) {   // 替罪羊节点不为根节点，需要更新父节点的子节点位置
        if (newNode->key < parent->key) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }
        newNode->parent = parent;
    } else {
        root = newNode;
    }

}

bool ScapegoatTree::isGoatNode(goatNode *node) {
    int nodeSum = getNodeNum(node);
    if (getNodeNum(node->left) <= ALPHA * nodeSum && getNodeNum(node->right) <= ALPHA * nodeSum)
        return false;
    return true;
}

int ScapegoatTree::getNodeNum(goatNode *node) {
//    if (!node) return 0;
//    int num = 1 + getNodeNum(node->left) + getNodeNum(node->right);
//    return num;

    queue<goatNode *> q;
    //树为空，直接返回
    if (node == NULL) {
        return 0;
    }
    while (!q.empty()) {
        q.pop();
    }
    int num = 0;
    //先将根节点入队
    q.push(node);
    while (!q.empty()) {
        int size = q.size();
        for (int i = 0; i < size; ++i) {
            //出队保存队头并访问
            goatNode *front = q.front();
            q.pop();
            //将出队结点的左子树根入队
            if (front->left) {
                q.push(front->left);
            }

            if (front->right) {
                q.push(front->right);
            }
            //将出队结点的右子树根入队
        }
        num += size;
    }
    return num;

}


goatNode *ScapegoatTree::buildAVL(int beg, int end, vector<goatNode *> vec) {
    // 递归生成AVL树
    if (beg > end) return NULL;
    int mid = (beg + end) / 2;
    if (beg == end) return vec[beg];
    goatNode *node = vec[mid];
    node->left = buildAVL(beg, mid - 1, vec);
    node->right = buildAVL(mid + 1, end, vec);
    if (node->left)
        node->left->parent = node;
    if (node->right)
        node->right->parent = node;
    return node;
}











