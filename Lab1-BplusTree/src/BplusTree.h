#include "libs.h"

#define MAX (10>>17)
#define ind 20

// Ahí van a encontrar los datos (0-999999)
// La cantidad de indices por nodo es 20


#ifndef BPLUSTREE_H
#define BPLUSTREE_H


struct Nodo{
    // Constructor
    Nodo();
    bool hoja;
    int *key, size;
    Nodo **ptr;
};

class BplusTree
{
    Nodo* root;

public:
    BplusTree();
    void insertar(int);
    void borrar(int);
    // extraído 
    void insertInternal(int, Nodo*, Nodo*);
    Nodo *findParent(Nodo *, Nodo *);
    //
    void bfs();

    ~BplusTree();
};






#endif