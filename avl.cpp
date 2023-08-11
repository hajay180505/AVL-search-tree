#include <vector>
#include "avl.h"
#include <iostream>
#include <queue>

using namespace std;
//node functions
int node::height(){
        if(!this) return 0;
        return 1+ max(this->left->height() , this->right->height());
}

int node::balanceFactor(){
        return ( (this->left->height()) - (this->right->height()) );
}

//avl functions
avl::avl(){
        cout<<"CALL insertRoot!!";
}

avl::avl(int elt){
        node* n = new node;
        if(!n) { cout<<"No memory allocted!"<<endl; return;}
        n->data = elt;
        n->left = nullptr;
        n->right = nullptr;
        n->parent = nullptr;
        root = n;
        count++;
}

void avl::insertRoot(int elt){
        node* n = new node;
        if(!n) { cout<<"No memory allocted!"<<endl; return;}
        n->data = elt;
        n->left = nullptr;
        n->right = nullptr;
        n->parent = nullptr;
        root = n;
        count++;

}

node* avl::createNode(int elt){
        node* n = new node;
        if(!n) {
                cout<<"No memory allocted!"<<endl;
                return nullptr;
        }
        n->data = elt;
        n->left = nullptr;
        n->right = nullptr;
        n->parent = nullptr;
        return n;
}

void avl::insert(int elt){
        vector<node*> path;
        ptr = root;
        node* prev = ptr;
        while(ptr){
                path.push_back(ptr);
                if(elt > ptr->data){
                        prev = ptr;
                        ptr = ptr->right;
                }
                else{
                        prev = ptr;
                        ptr = ptr->left;
                }
        }
        if(elt > prev->data){
                prev->right = createNode(elt);
                prev->right->parent = prev;
        }
        else{
                prev->left = createNode(elt);
                prev->left->parent = prev;
        }

        node* n = checkImbalance(path);
        if(n) balance(n);
}

node* avl::checkImbalance(const vector<node*>& path){
        node* A = nullptr;
        for(auto it=path.rbegin() ; it!=path.rend() ;  it++){
                int bf = (*it)->balanceFactor();
                if(bf<-1 or bf>1){
                        A = *it;
                        break;
                }
        }
        return A;
}

void avl::balance(node* A){
        if(!A) return;
        node* p = A->parent;
        node* u = nullptr;
        if(A->balanceFactor()==-2){
                //R type
                int currBf = A->right->balanceFactor();
                if(currBf == -1 or currBf == 0) //RR
                        u = RR(A);
                else //RL
                        u = RL(A);

        }
        else{
                int currBf = A->left->balanceFactor();
                //L type
                if(currBf == 1 or currBf == 0) //LL
                        u = LL(A);
                else //LR
                        u = LR(A);
        }
        if(!p){
                root = u;
                root->parent = nullptr;
        }
        else if(p->left == A){
                p->left = u;
                u->parent = p;
        }
        else{
                p->right = u;
                u->parent = p;
        }
}

void avl::remove(int elt){
        vector<node*> path;
        ptr = root;
        while(ptr){
                path.push_back(ptr);
                if(elt> ptr->data) ptr = ptr->right;
                else if(elt< ptr->data) ptr = ptr->left;
                else break;
        }
        if(!ptr){
                cout<<"Element not found! So, not deleted."<<endl;
                return;
        }
        node* p = ptr->parent;
        if(!ptr->left and !ptr->right){
                if(p){
                        path.pop_back();
                        if(p->left == ptr)
                                p->left = nullptr;
                        else
                                p->right = nullptr;
                        delete ptr;
                        node* u  = checkImbalance(path);
                        if(u) balance(u);
                }
        }
        else if(!ptr->left){
                path.pop_back();
                if(p){
                        if(p->left == ptr)
                                p->left = ptr->right;
                        else
                                p->right = ptr->right;
                        ptr->right->parent = p;
                }
                else{
                        root = root->right;
                        root->parent = nullptr;
                }
                delete ptr;
                node* u  = checkImbalance(path);
                if(u) balance(u);
        }
        else if(!ptr->right){
                path.pop_back();
                if(p){
                        if(p->left == ptr)
                                p->left = ptr->left;
                        else
                                p->right = ptr->left;
                        ptr->left->parent = p;
                }
                else{
                        root = root->left;
                        root->parent = nullptr;
                }
                delete ptr;
                node* u  = checkImbalance(path);
                if(u) balance(u);

        }
        else{
                node* s = inorder_successor(ptr);
                if(ptr->right == s){
                        ptr->right = s->right;
                        if(s->right) s->right->parent = ptr;
                        ptr->data = s->data;
                }
                else{
                        s->parent->left = s->right;
                        if(s->right) s->right->parent = s->parent;
                        ptr->data = s->data;
                }
                delete s;
                path.pop_back();
                node* u = checkImbalance(path);
                if(u) balance(u);
        }


}

//rotations


node* avl::LL(node* A){
        node* k = new node;
        k = A->left;
        A->left = k->right;
        if(A->left) A->left->parent = A;
        k->right = A;
        if(k->right) k->right->parent = k;
        return k;
}

node* avl::LR(node* A){
        A->left = RR(A->left);
        if(A->left) A->left->parent = A;
        return LL(A);
}

node* avl::RL(node* A){
        A->right = LL(A->right);
        if(A->right) A->right->parent = A;
        return RR(A);
}

node* avl::RR(node* A){
        node* k = new node;
        k = A->right;
        A->right = k->left;
        if(A->right) A->right->parent = A;
        k->left= A;
        if(k->left) k->left->parent = k;
        return k;

}

//non-member functions
void inorder(node* ptr){
        if(ptr){
                inorder(ptr->left);
                cout<<ptr->data<<" ";
                inorder(ptr->right);
        }
}

void preorder(node* ptr){
        if(ptr){
                cout<<ptr->data<<" ";
                preorder(ptr->left);
                preorder(ptr->right);
        }
}

void postorder(node* ptr){
        if(ptr){
                preorder(ptr->left);
                preorder(ptr->right);
                cout<<ptr->data<<" ";
        }
}

vector<node*> levelorder(node* rt){
        vector<node*> ans;
        queue<node*> q;
        q.push(rt);
        while(!q.empty()){
                node* curr = q.front();
                cout<<curr->data<<endl;
                ans.push_back(curr);
                q.pop();
                if(curr->left) q.push(curr->left);
                if(curr->right) q.push(curr->right);
        }
        return ans;
}

void print(const string& prefix, node* node, bool isLeft){
    if(node){
        cout << prefix;
        cout << (isLeft ? "├──" : "└──" );
        cout << node->data << endl;
        print( prefix + (isLeft ? "│   " : "    "), node->left, true);
        print( prefix + (isLeft ? "│   " : "    "), node->right, false);
    }
}

void print(node* n){
    print("", n, false);
}

node* inorder_successor(node* u){
        if(!u) return nullptr;
        if(u->right){
                u = u->right;
                while(u->left) u = u->left;
                return u;
        }
        while(u->parent and u->parent->right == u)
                u = u->parent;
        return u->parent;
}

