#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

//retorna 1 si las claves son iguales y 0 si no lo son
int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {

    TreeMap *new =malloc(sizeof(TreeMap));
    new->lower_than = lower_than; //Funcion inicializada

    new->root = NULL;
    new->current = NULL;

    return new;
}

Pair * searchTreeMap(TreeMap * tree, void* key) {

    /* Para hallar un valor es como una busqueda binaria
    Si current es el valor (saberlo con is_equal), entonces devolver current.
    Si current no es el valor, entonces compara si el valor
    es mayor o menor que current con la funcion lower_than()
    Si es mayor convertir current en el hijo derecho, sino en el hijo izquierdo
    repetir.*/

    tree->current = tree->root;

    while (tree->current != NULL)
    {
        
        void* auxkey = (void*) (tree->current)->pair->key;
        if (is_equal(tree,auxkey,key)) return tree->current->pair;
        //lower_than retorna 1 si key1<key2, y 0 sino
        if (tree->lower_than(auxkey,key))
            tree->current = tree->current->right; //key es mayor
        else
            tree->current = tree->current->left;  //key es menor      
    }

    return NULL;
}




void insertTreeMap(TreeMap * tree, void* key, void * value) {

    /* No puedo reutilizar search, ya que este no me devolvera
    info cuando no este dentro del mapa.
    
    Me conviene escribir directamente un algoritmo de busqueda que al
    encontrar procese de manera distinto los datos.
    
    Me puedo basar en la busqueda y sus comparaciones eso si.*/
    void* auxKey=NULL;
    TreeNode* auxNode = tree->root; //Usar un auxiliar para no apuntar mal si el dato ya existe
    
    while(1)
    {
        auxKey = auxNode->pair->key;
        
        if (is_equal(tree,key,auxKey)) return;

        if (tree->lower_than(key,auxKey)) 
        {
            if (auxNode->left != NULL)
                auxNode = auxNode->left;
            else{
                auxNode->left=createTreeNode(key,value);
                tree->current = auxNode->left;
                tree->current->parent= auxNode;
                return;
            }
        }
        else{
            if (auxNode->right != NULL)
                auxNode = auxNode->right;
            else{
                auxNode->right=createTreeNode(key,value);
                tree->current = auxNode->right;
                tree->current->parent= auxNode;
                return;
            }
        }
    } 
}

TreeNode * minimum(TreeNode * x){
    if (x == NULL) return NULL;
    while (x->left != NULL)
        x=x->left;

    return x;
}


void removeNode(TreeMap * tree, TreeNode* node) {
    /*
        Si el nodo encontrado:
                No tiene hijos
            {
                node->parent->child=NULL;
            }
                Tiene un hijo
            {
                node->child->parent = node->parent
                node->parent->child = node->child
            }
            Tiene dos hijos
            {
                buscar nodo menor del hijo derecho
                y cambiar pares luego eliminar ese nodo. 
            }
    */

   //Obtener cuantos hijos, y si tiene de que lado..

    int cantChilds =0;
    int childDirection;  // 1 left, 0 right
    TreeNode* aux = NULL;

    if (node->left !=NULL)
        {
            cantChilds++;
            childDirection=1;
        }
    else if (node->right != NULL)
        {
            cantChilds++;
            childDirection=0;
        }

    switch (cantChilds)
    {
        case 0:
            if ((node->parent)->left == node)
                (node->parent)->left = NULL;
            else
                (node->parent)->right = NULL;

            break;
        case 1:
            aux = (childDirection)?node->left:node->right; //Aux acts as child

            if ((node->parent)->left == node)
                (node->parent)->left = aux;
            else
                (node->parent)->right = aux;
            
            aux->parent=node->parent;
            free(aux);
            break;
        case 2:
            aux = minimum(node->right);
            //El nodo minimum solo puede tener un hijo a la derecha
            //o ninguno.
            node->pair=aux->pair;
            removeNode(tree,aux);
        break;
        default:
        break;
    }

    printf("Done removal\n");
}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}





Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
