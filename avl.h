#include <vector>
#include <string>

struct node{
        int data;
        node* left, * right, *parent;
        int height();
        int balanceFactor();
};


class avl{
        public:
                node* ptr;
                node* root;
                int count;

                avl();
                avl(int elt);
                node* createNode(int);
                void insertRoot(int elt);
                void insert(int elt);
                node* checkImbalance(const std::vector<node*>&);
                void balance(node*);
                void remove(int elt);

                node* LL(node*);
                node* LR(node*);
                node* RL(node*);
                node* RR(node*);
};

void inorder(node*);
void preorder(node*);
void postorder(node*);
std::vector<node*> levelorder(node*);

void print(const std::string& prefix, node* node, bool isLeft);
void print(node* );

node* inorder_successor(node*);

