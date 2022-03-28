#include "rbtree.h"

int main(){

    cout << "siuu\n";
    int val;
    RBtree *tree = new RBtree();
    // for (int i = 0; i < 6; i++)
    // {
    //     cin >> val;
    //     tree->insertar(val);
    // }
    // cout << "black = " << BLACK << endl;
    // cout << "red = " << RED << endl;

    tree->insertar(4);
    tree->insertar(12);
    tree->insertar(16);
    tree->insertar(9);
    tree->insertar(2);
    tree->insertar(3);
    cout << "------DISPLAY------ \n";
    tree->displayInOrder();
    cout <<"------------------- \n";
    tree->displayPreOrder();
    cout <<"------------------- \n";
    tree->displayPostOrder();
}