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
    if (tree->current == NULL) printf("Este es un null\n");
    while (tree->current != NULL)
    {
        
        void* auxkey = (void*) (tree->current)->pair->key;
        if (is_equal(tree,auxkey,key)) return tree->current->pair;
        //lower_than retorna 1 si key1<key2, y 0 sino
        if (tree->lower_than(auxkey,key))
            tree->current = tree->current->left;
        else
            tree->current = tree->current->right;        
    }

    return NULL;
}




void insertTreeMap(TreeMap * tree, void* key, void * value) {

}

TreeNode * minimum(TreeNode * x){

    return NULL;
}


void removeNode(TreeMap * tree, TreeNode* node) {

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
