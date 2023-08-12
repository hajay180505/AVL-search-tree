#include <vector>
#include "avl.h"
#include <iostream>
#include <queue>

using namespace std;
//node functions
template <typename T>
int node<T>::height(){
        if(!this) return 0;
        return 1+ max(this->left->height() , this->right->height());
}

template <typename T>
int node<T>::balanceFactor(){
        return ( (this->left->height()) - (this->right->height()) );
}

//avl functions
template <typename T>
avl<T>::avl(){
        cout<<"CALL insertRoot!!";
        count = 0;
}

template <typename T>
avl<T>::avl(T elt){
        node<T>* n = createNode(elt);
        root = n;
        count=1;
}

template <typename T>
void avl<T>::insertRoot(T elt){
        node<T>* n = createNode(elt);
        root = n;
        count++;

}

template <typename T>
node<T>* avl<T>::createNode(T elt){
        node<T>* n = new node<T>;
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

template <typename T>
void avl<T>::insert(T elt){
        vector<node<T>*> path;
        ptr = root;
        node<T>* prev = ptr;
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

        node<T>* n = checkImbalance(path);
        if(n) balance(n);
}

template <typename T>
node<T>* avl<T>::checkImbalance(const vector<node<T>*>& path){
        node<T>* A = nullptr;
        for(auto it=path.rbegin() ; it!=path.rend() ;  it++){
                int bf = (*it)->balanceFactor();
                if(bf<-1 or bf>1){
                        A = *it;
                        break;
                }
        }
        return A;
}

template <typename T>
void avl<T>::balance(node<T>* A){
        if(!A) return;
        node<T>* p = A->parent;
        node<T>* u = nullptr;
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

template <typename T>
void avl<T>::remove(T elt){
        vector<node<T>*> path;
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
        node<T>* p = ptr->parent;
        if(!ptr->left and !ptr->right){
                if(p){
                        path.pop_back();
                        if(p->left == ptr)
                                p->left = nullptr;
                        else
                                p->right = nullptr;
                        delete ptr;
                        node<T>* u  = checkImbalance(path);
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
                node<T>* u  = checkImbalance(path);
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
                node<T>* u  = checkImbalance(path);
                if(u) balance(u);

        }
        else{
                node<T>* s = inorder_successor(ptr);
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
                node<T>* u = checkImbalance(path);
                if(u) balance(u);
        }


}

//rotations

template <typename T>
node<T>* avl<T>::LL(node<T>* A){
        node<T>* k = new node<T>;
        k = A->left;
        A->left = k->right;
        if(A->left) A->left->parent = A;
        k->right = A;
        if(k->right) k->right->parent = k;
        return k;
}

template <typename T>
node<T>* avl<T>::LR(node<T>* A){
        A->left = RR(A->left);
        if(A->left) A->left->parent = A;
        return LL(A);
}

template <typename T>
node<T>* avl<T>::RL(node<T>* A){
        A->right = LL(A->right);
        if(A->right) A->right->parent = A;
        return RR(A);
}

template <typename T>
node<T>* avl<T>::RR(node<T>* A){
        node<T>* k = new node<T>;
        k = A->right;
        A->right = k->left;
        if(A->right) A->right->parent = A;
        k->left= A;
        if(k->left) k->left->parent = k;
        return k;

}

//non-member functions
template <typename T>
void inorder(node<T>* ptr){
        if(ptr){
                inorder(ptr->left);
                cout<<ptr->data<<" ";
                inorder(ptr->right);
        }
}

template <typename T>
void preorder(node<T>* ptr){
        if(ptr){
                cout<<ptr->data<<" ";
                preorder(ptr->left);
                preorder(ptr->right);
        }
}

template <typename T>
void postorder(node<T>* ptr){
        if(ptr){
                preorder(ptr->left);
                preorder(ptr->right);
                cout<<ptr->data<<" ";
        }
}

template <typename T>
vector<node<T>*> levelorder(node<T>* rt){
        vector<node<T>*> ans;
        queue<node<T>*> q;
        q.push(rt);
        while(!q.empty()){
                node<T>* curr = q.front();
                cout<<curr->data<<endl;
                ans.push_back(curr);
                q.pop();
                if(curr->left) q.push(curr->left);
                if(curr->right) q.push(curr->right);
        }
        return ans;
}

template <typename T>
void print(const string& prefix, node<T>* node, bool isLeft){
    if(node){
        cout << prefix;
        cout << (isLeft ? "├──" : "└──" );
        cout << node->data << endl;
        print( prefix + (isLeft ? "│   " : "    "), node->left, true);
        print( prefix + (isLeft ? "│   " : "    "), node->right, false);
    }
}

template <typename T>
void print(node<T>* n){
    print("", n, false);
}

template <typename T>
node<T>* inorder_successor(node<T>* u){
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

