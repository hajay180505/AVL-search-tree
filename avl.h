#pragma once
#include <vector>
#include <string>
template <typename T>
struct node{
        T data;
        node* left, * right, *parent;
        int height();
        int balanceFactor();
};

template <typename T>
class avl{
        public:
                node<T>* ptr;
                node<T>* root;
                int count;

                avl();
                avl(T elt);
                node<T>* createNode(T);
                void insertRoot(T elt);
                void insert(T elt);
                node<T>* checkImbalance(const std::vector<node<T>*>&);
                void balance(node<T>*);
                void remove(T elt);

                node<T>* LL(node<T>*);
                node<T>* LR(node<T>*);
                node<T>* RL(node<T>*);
                node<T>* RR(node<T>*);
};
template <typename T>
void inorder(node<T>*);
template <typename T>
void preorder(node<T>*);
template <typename T>
void postorder(node<T>*);
template <typename T>
std::vector<node<T>*> levelorder(node<T>*);
template <typename T>
void print(const std::string& prefix, node<T>* node, bool isLeft);
template <typename T>
void print(node<T>* );
template <typename T>
node<T>* inorder_successor(node<T>*);

