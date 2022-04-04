#include "libs.h"



// Ahí van a encontrar los datos (0-999999)
// La cantidad de indices por nodo es 20


#ifndef BPLUSTREE_H
#define BPLUSTREE_H


struct Nodo{
    // Constructor
    Nodo();
    bool esHoja;

    void split(Nodo *,int);

    vector<int> keys;
    vector<Nodo*> hijos;
};

class BplusTree
{
    Nodo* root;

public:
    BplusTree();
    void insertar(int);
    void borrar(int);

    void insertInternal(int, Nodo *, Nodo *);
    Nodo *findParent(Nodo *, Nodo *);

    vector<int> bfs();

    ~BplusTree();

    void clear(Nodo*);
    void print();
    void print2(Nodo*);
};

#endif