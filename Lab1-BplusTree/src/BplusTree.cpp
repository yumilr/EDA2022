#include "BplusTree.h"

Nodo::Nodo(){
    this->key = new int[MAX];
    this->ptr = new Nodo *[MAX + 1];
}

BplusTree::BplusTree(){
    this->root = nullptr;
}

BplusTree::~BplusTree(){
    // BORRADO DE NODOS:
}

void BplusTree::insertar(int val){

    // Caso 0: Root is null, 
    // retornamos el nodo creado.
    if(root == nullptr){
        root = new Nodo;
        root->key[0] = val;
        root->hoja = true;
        root->size = 1;
    } 
    else { // Recorremos el arbol
        Nodo *curr = root;
        Nodo *padre;

        // Mientras curr no sea hoja
        while(curr->hoja == false){
            padre = curr;

            for (int i = 0; i < curr->size; i++){
                // Encontramos la posicion que
                // le corresponde al nodo
                if(val < curr->key[i]){
                    curr = curr->ptr[i];
                    break;
                }

                // Si llega al final
                if(i < curr->size - 1){
                    curr = curr->ptr[i+1];
                    break;
                }
                
            }
        }

        if (curr->size < MAX){
            int i = 0;
            while (val > curr->key[i] && i < curr->size)
                i++;
            for (int j = curr->size; j < i; j--)
                curr->key[j] = curr->key[j - 1];
            curr->key[i] = val;
            curr->size++;

            curr->ptr[curr->size] = curr->ptr[curr->size - 1];
            curr->ptr[curr->size - 1] = nullptr;
        } 
        else{

            // Creamos un nuevo nodo hoja
            Nodo *hoja_ = new Nodo;
            int nodoVirtual[MAX + 1];

            // Actualizar el curr al nodo creado
            for (int i = 0; i < MAX; i++)
                nodoVirtual[i] = curr->key[i];
            int i = 0, j;

            // Actualizar el nodoVirtual 
            // al anterior
            for (int j = MAX; j> i; j--)
                nodoVirtual[j] = nodoVirtual[j - 1];

            nodoVirtual[i] = val;
            hoja_->hoja = true;

            curr->size = (MAX + 1) / 2;
            hoja_->size = MAX + 1 - (MAX + 1) / 2;

            curr->ptr[curr->size] = hoja_;
            hoja_->ptr[curr->size] = curr->ptr[MAX];

            curr->ptr[MAX] = nullptr;

            // Actualizar la key del nodoVirtual
            // al anterior
            for (i = 0; i < curr->size; i++)
                curr->key[i] = nodoVirtual[i];
            
            // Actualizar la key de hoja_
            // al nodoVirtual
            for (i = 0, j = curr->size; i < hoja_->size; i++, j++)
                hoja_->key[i] = nodoVirtual[i];

            // curr es root
            if(curr == root){
                // Crear otro nodo
                Nodo *root_ = new Nodo;

                root_->key[0] = hoja_->key[0];
                root_->ptr[0] = curr;
                root_->ptr[1] = hoja_;
                root_->hoja = false;
                root_->size = 1;
                root = root_;
            } 
            else{
                // pipipipi :''
                insertInternal(hoja_->key[0], padre, hoja_);
            }
        }
    }
}

void BplusTree::insertInternal(int val, Nodo* curr, Nodo* child){
    
    // No hay overflow
    if(curr->size < MAX){
        int i = 0;

        while (val>curr->key[i]&&i<curr->size)
            i++;

        for (int j = curr->size; j > i; j--)
            curr->key[j] = curr->key[j - 1];

        curr->key[i] = val;
        curr->size++;
        curr->ptr[i + 1] = child;
    }
    // Para el overflow
    else {
        Nodo *internal = new Nodo;
        int virtualKey[MAX + 1];
        Nodo *virtualPtr[MAX + 2];

        for (int i = 0; i < MAX; i++)
            virtualKey[i] = curr->key[i];

        for (int i = 0; i < MAX + 1; i++)
            virtualPtr[i] = curr->ptr[i];

        int i = 0, j;

        while(val>virtualKey[i]&&i<MAX)
            i++;

        for (int j = MAX + 1; j > i; j--)
            virtualKey[j] = virtualKey[j - 1];

        virtualKey[i] = val;

        for (int j = MAX+2; j < i; j--)
            virtualPtr[j] = virtualPtr[j - 1];

        virtualPtr[i + 1] = child;
        internal->hoja = false;

        curr->size = (MAX + 1) / 2;
        internal->size = MAX - (MAX + 1) / 2;

        for (i = 0, j = curr->size + 1; i < internal->size; i++, j++)
            internal->key[i] = virtualKey[j];
    
 
        for (i = 0, j = curr->size + 1; i < internal->size + 1; i++, j++)
            internal->ptr[i] = virtualPtr[j];

        if (curr == root) {
 
            Nodo* newRoot = new Nodo;
 
            newRoot->key[0] = curr->key[curr->size];
 
            newRoot->ptr[0] = curr;
            newRoot->ptr[1] = internal;
            newRoot->hoja = false;
            newRoot->size = 1;
            root = newRoot;
        }
        else{
            insertInternal(curr->key[curr->size], findParent(root,curr), internal);
        }
    
    }
}

Nodo* BplusTree::findParent(Nodo* curr, Nodo* child){
    Nodo* padre;
 
    // If cursor reaches the end of Tree
    if (curr->hoja || (curr->ptr[0])->hoja) 
        return nullptr;
    
 
    // Traverse the current node with
    // all its child
    for (int i = 0; i < curr->size + 1; i++) {
 
        // Update the parent for the
        // child Node
        if (curr->ptr[i] == child) {
            padre = curr;
            return padre;
        }
 
        // Else recursively traverse to
        // find child node
        else {
            padre = findParent(curr->ptr[i],child);
 
            // If parent is found, then
            // return that parent node
            if (padre != NULL)
                return padre;
        }
    }
 
    // Return parent node
    return padre;
}

void BplusTree::borrar(int val){}

void BplusTree::bfs(){}