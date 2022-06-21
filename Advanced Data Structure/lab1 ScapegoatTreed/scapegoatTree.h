#include <vector>
#include <iostream>
#include <queue>
using namespace std;

#define ALPHA 0.6


typedef struct goatNode
{
    goatNode *left, *right, *parent;
    int key;
    int height;
    int childNum;
    goatNode(goatNode* l,goatNode* r,goatNode* p,int k){
        left = l; right = r; parent = p; key = k;
    }
}goatNode;

class ScapegoatTree
{
public:
    int height;
    int maxNum;
    int nodeNum;

    int times = 0;

    goatNode * root;
    ScapegoatTree() {
        root = NULL;
        nodeNum = 0;
        maxNum = 0;
        height = 0;
    }
    ~ScapegoatTree() {}

    /**
     * @brief Get the Rebalance Times
     *
     * @return int
     */
    int GetRebalanceTimes();


    /**
     * @brief Look up a key in scapegoat tree. Same as trivial binary search tree
     *
     * @param key
     */
    void Search(int key);

    /**
     * @brief Insert a new node into the tree. If the key is already in the tree, then do nothing
     *
     * @param key
     */
    void Insert(int key);

    /**
     * @brief Delete a node of the tree. If the key is not in the tree, do nothing.
     *
     * @param key
     */
    void Delete(int key);


    int getHeight();

    int curHeight(goatNode* node);
    /**
     * 对替罪羊节点进行重构
     * @param node
     */
    void rebalance(goatNode* node);

    /**
     * 判断当前节点是否为替罪羊节点
     * @param node
     * @return
     */
    bool isGoatNode(goatNode* node);

    /**
     * 递归产生一颗AVL树，每次递归将中位数结点作为根节点返回
     * @param beg 起始节点
     * @param end 终止节点
     * @param vec 有序节点vec
     * @return
     */
    goatNode* buildAVL(int beg, int end, vector<goatNode*> vec );


    /**
     * 获取当前节点及其所有后继节点的总数量
     * @param node
     * @return
     */
    int getNodeNum(goatNode* node);

    void remove(int key, goatNode* & node);
    void BinaryTreeLevelOrder(goatNode * root)
    {
        queue<goatNode*> q;
        //树为空，直接返回
        if (root == NULL)
        {
            return;
        }
        while (!q.empty()){
            q.pop();
        }
        //先将根节点入队
        q.push(root);
        int height = 1;
        while (!q.empty())
        {
            int size = q.size();
            for (int i = 0; i < size; ++i) {
                //出队保存队头并访问
                goatNode* front = q.front();
//                cout<<front->key<<' ';
                q.pop();
                //将出队结点的左子树根入队
                if (front->left)
                    q.push(front->left);
                if (front->right)
                    q.push(front->right);
                //将出队结点的右子树根入队

            }
            cout<<"height is "<<height<<"size is "<< size<<endl;
            height++;
            cout<<endl;
        }
        cout<<endl;
    }
};
