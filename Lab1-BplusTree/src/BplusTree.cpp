#include "BplusTree.h"

Nodo::Nodo(){
    esHoja = false;
}

BplusTree::BplusTree(){
    this->root = nullptr;
}

BplusTree::~BplusTree(){
    if (root = nullptr)
        return;
    else
        clear(root);
}

void BplusTree::clear(Nodo* nodo){
    if (nodo)
    {
        for(auto x: nodo->hijos) clear(x);
        delete nodo;
    }
}

void BplusTree::insertar(int val){
    // Caso 0: Root es null, 
    if(root == nullptr)
    {
        
        root = new Nodo;
        root->keys.push_back(val);
        root->esHoja = true;
    } 
    else 
    {   // Recorremos el arbol buscando el nodo al que corresponde
        // el valor a ingresar
        Nodo *curr = root;
        Nodo *padre;

        while(!curr->esHoja){
            padre = curr;
            for (int i = 0; i < curr->keys.size(); i++)
            {
                // Encontrar posición
                if(val < curr->keys[i]){
                    curr = curr->hijos[i];
                    break;
                }
                // Se llega al final
                if(i < curr->keys.size() - 1){
                    curr = curr->hijos[i+1];
                    break;
                }
                
            }
        }

        // CASO 1: No hay overflow
        if(curr->keys.size()<ind-1)
        {
            int i = 0;
            while (val > curr->keys[i] && i < curr->keys.size())
                i++;
            curr->keys.insert(curr->keys.begin() + i, val);
        } 
        else 
        {
            // CASO 2: Hay overflow, toca split

            // creamos un nuevo nodo hoja
            Nodo *nLeaf = new Nodo;
            nLeaf->esHoja = true;

            curr->split(nLeaf,val);

            if (curr == root) 
            {
                Nodo* nParent = new Nodo();
                nParent->keys.push_back(nLeaf->keys[0]);
                nParent->hijos.push_back(curr);
                nParent->hijos.push_back(nLeaf);
                root = nParent;
            }
            else 
            {
                insertInternal(nLeaf->keys[0], padre, nLeaf);
            } 
        }
    }
  
}

void BplusTree::insertInternal(int val, Nodo* curr, Nodo* child){
    if(curr->keys.size() < ind){
        int i = 0;
        while (val > curr->keys[i] && i < curr->keys.size())
            i++;
        for (int j = curr->keys.size(); j > i; j--) {
            curr->keys[j] = curr->keys[j - 1];
        }
 
        for (int j = curr->keys.size() + 1; j > i + 1; j--) {
            curr->hijos[j] = curr->hijos[j - 1];
        }

        curr->keys.push_back(val);
        curr->hijos.push_back(child);
    }
    else 
    {
        Nodo* nIntern = new Nodo;
        vector<int> tempK[ind + 1];
        vector<Nodo*> tempN[ind + 2];
 
        for (int i = 0; i < ind; i++) {
            tempK->push_back(curr->keys[i]);
        }
 
        for (int i = 0; i < ind + 1; i++) {
            tempN->push_back(curr->hijos[i]);
        }
 
        int i = 0, j;
        while (val > tempK->at(i) && i < ind) i++;

        for (int j = ind + 1; j > i; j--) {
            tempK[j]= tempK[j - 1];
        }
 
        tempK->at(i) = val;
 
        for (int j = ind+2; j > i+1; j--) {
            tempN[j] = tempN[j - 1];
        }
 
        tempN->at(i + 1) = child;
        nIntern->esHoja = false;
 
        for (i=0,j=curr->keys.size()+1; i<nIntern->keys.size(); i++,j++) 
        {
            nIntern->keys.at(i) = tempK->at(j);
        }
 
        for (i=0,j=curr->hijos.size()+1; i<nIntern->hijos.size()+1; i++,j++)
        {
            nIntern->hijos.at(i) = tempN->at(j);
        }
 
        if (curr == root) {
            Nodo* nRoot = new Nodo;
            nRoot->keys[0] = curr->keys[curr->keys.size()];
 
            nRoot->hijos[0] = curr;
            nRoot->hijos[1] = nIntern;
            nRoot->esHoja = false;
            root = nRoot;
        }
 
        else {
            insertInternal(curr->keys[curr->keys.size()],findParent(root,curr), nIntern);
        }
    }
}

Nodo* BplusTree::findParent(Nodo* curr, Nodo* child){
    Nodo* parent;
 
    if (curr->esHoja || (curr->hijos[0])->esHoja) {
        return nullptr;
    }

    for (int i = 0;
         i < curr->keys.size() + 1; i++) {
 
        if (curr->hijos[i] == child) {
            parent = curr;
            return parent;
        }
        else {
            parent = findParent(curr->hijos[i], child);
            if (parent != nullptr)
                return parent;
        }
    }
    return parent;
}

void Nodo::split(Nodo* newLeaf, int val){
    std::vector<int> temp = keys;
    int i = 0;
    while (temp[i] < val && i < temp.size())
        i++;
    temp.insert(temp.begin()+i, val);

    keys.clear();

    for (int i = 0; i < floor(ind/2); i++) 
        keys.push_back(temp[i]);

    for (int i = floor(ind/2); i < temp.size(); i++) 
        keys.push_back(temp[i]);
}

void BplusTree::borrar(int val){

}

vector<int> BplusTree::bfs(){
    std::vector<int> result;
        if(root == nullptr) return result;
        queue<Nodo*> q;
        q.push(root);
        while(!q.empty()){
            const Nodo* curr = q.front();
            if (!curr->esHoja) {
                for(int i = 0; i< curr->keys.size()+1; ++i){
                    if(curr->hijos[i] != nullptr){
                        q.push(curr->hijos[i]);
                    } 
                }
            }
            for(int i = 0; i<curr->keys.size(); ++i){
                result.push_back(curr->keys[i]);
            }
            q.pop();
        }
        return result;
}

void BplusTree::print(){
    if (root == nullptr)
        return;
    else
        for(auto x: root->keys)
            cout << x << " - ";
        cout << endl;
}