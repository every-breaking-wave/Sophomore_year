
#include "RBTree.h"
using std::cout;
using std::queue;


RB_Tree::RB_Tree() : root(nullptr) {
    time = 0;
}

void RB_Tree::left_rotate(RB_Node *x) {
    RB_Node *y = x->right;
    x->right = y->left;
    if (y->left != nullptr) {
        y->left->father = x;
    }
    y->left = x;
    y->father = x->father;
    if (x->father == nullptr) {
        this->root = y;
    }
    else if (x->father->left == x) {
        x->father->left = y;
    }
    else {
        x->father->right = y;
    }
    x->father = y;
}



void RB_Tree::right_rotate(RB_Node *x) {
    RB_Node *y = x->left;
    x->left = y->right;
    if (y->right != nullptr) {
        y->right->father = x;
    }
    y->right = x;
    y->father = x->father;
    if (x->father == nullptr) {
        this->root = y;
    }
    else if (x->father->left == x) {
        x->father->left = y;
    }
    else {
        x->father->right = y;
    }
    x->father = y;
}



RB_Node* RB_Tree::min_node(RB_Node *x) {
    RB_Node *res = x;
    while (res->left != nullptr) {
        res = res->left;
    }
    return res;
}



void RB_Tree::transplant(RB_Node *u, RB_Node *v) {
    v->father = u->father;
    if (u->father == nullptr) {
        this->root = v;
    }
    else if (u->father->left == u) {
        u->father->left = v;
    }
    else {      // u 是右孩子
        u->father->right = v;
    }
}


RB_Node* RB_Tree::find(int data) {
    RB_Node *q = this->root;
    while (q != nullptr && q->value != data) {
        if (q->value > data) {
            q = q->left;
        }
        else {
            q = q->right;
        }
    }
    return q;
}


void RB_Tree::insert(int data) {
    RB_Node *idx = this->root, *f = nullptr;
    while (idx != nullptr) {
        f = idx;
        if (idx->value > data) {
            idx = idx->left;
        }
        else {
            idx = idx->right;
        }
    }
    RB_Node *x = new RB_Node(data);
    x->father = f;
    if (f == nullptr) {
        this->root = x;
    }
    else if (f->value > x->value) {
        f->left = x;
    }
    else {
        f->right = x;
    }
    insert_fixup(x);
}


void RB_Tree::insert_fixup(RB_Node *x) {
    while (x->father != nullptr && x->father->color == RED) {
        if (x->father->father == nullptr) {
            break;
        }
        if (x->father->father->left == x->father) {
            RB_Node *uncle = x->father->father->right;
            if (uncle != nullptr && uncle->color == RED) {
                x->father->color = uncle->color = BLACK;
                x->father->father->color = RED;
                x = x->father->father;
                continue;
            }
            else if (x == x->father->right) {
                x = x->father;
                left_rotate(x);
                time++;
            }
            // 情况三
            x->father->color = BLACK;
            x->father->father->color = RED;
            right_rotate(x->father->father);
            time++;
        }
        else {
            RB_Node *uncle = x->father->father->left;
            if (uncle != nullptr && uncle->color == RED) {
                x->father->color = uncle->color = BLACK;
                x->father->father->color = RED;
                x = x->father->father;
                continue;
            }
            else if (x->father->left == x) {
                x = x->father;
                right_rotate(x);
                time++;
            }
            // 情况二
            x->father->color = BLACK;
            x->father->father->color = RED;
            left_rotate(x->father->father);
            time++;
        }
    }
    this->root->color = BLACK;
}


RB_Tree::~RB_Tree() = default;