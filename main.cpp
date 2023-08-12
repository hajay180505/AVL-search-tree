#include "avl.h"
#include "avl.cpp"
using namespace std;

int main(){

    avl<int> tree(1);
    for(int i=2;i<10;i++)
        tree.insert(i);
    print(tree.root);

    for(int i=10;i>1;i--){
        tree.remove(i);
        print(tree.root);
    }
    return 0;

}
