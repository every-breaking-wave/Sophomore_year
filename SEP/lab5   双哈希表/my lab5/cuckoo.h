#ifndef CUCKOO_H
#define CUCKOO_H

class hashNode{
private:
    struct node{
        int data;
        int state;
        int key;
        node(){state=0;}
    };

    node* hash1;
    node* hash2;

  //  int currentLen1,currentlen2;
    int maxSize1=8,maxSize2=8;
    int currenSize1=0,currenSize2=0;
 //   void doublespace();
public:
   hashNode();
    void insert(int key,int val);
    void look(int key);
    void remove(int key);
    void rehash();
    void kick();
    void showHash();


};


#endif // CUCKOO_H
