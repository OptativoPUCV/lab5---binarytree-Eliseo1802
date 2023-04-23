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
  TreeMap * root = (TreeMap*)malloc(sizeof(TreeMap));
  root->lower_than = lower_than;
  return root;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
  TreeNode * new = createTreeNode(key,value);
  tree->current = tree->root;

  while(tree->current!=NULL){
    if(is_equal(tree,new->pair->key,tree->current->pair->key) == 1){
      
      break;
    }
    if(tree->lower_than(new->pair->key,tree->current->pair->key) == 1)
      tree->current = tree->current->left;
    else
      tree->current = tree->current->right;
  }
  tree->current = new;
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

Pair * searchTreeMap(TreeMap * tree, void* key) {
  Pair * p = firstTreeMap(tree);
  
  while(is_equal(tree, p->key, key) == 0){
    p = nextTreeMap(tree);
    if(p==NULL) return NULL;
  }
  return p;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
  tree->current = tree->root;
  TreeNode * aux = tree->current;
  while(aux!=NULL){
    tree->current = tree->current->left;
    if(tree->current==NULL){
      tree->current = aux;
      return aux->pair; 
    }
    aux = tree->current;
  }
  return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
  TreeNode * aux = tree->current;
  
  if(tree->current!=NULL){

    while(tree->current!=NULL){
      if(tree->current->right!=NULL){
        tree->current = tree->current->right;
        if(tree->current->left!=NULL){
          while(tree->current!=NULL){
            aux = tree->current;
            tree->current = tree->current->left;  
          }
          tree->current = aux;
          return tree->current->pair;
        }
        else
          return tree->current->pair;
      }
      else{
        //if((int*)tree->current->pair->key > (int*)aux->pair->key)
        if(tree->lower_than(aux->pair->key, tree->current->pair->key) == 1)
          return tree->current->pair;
        else{
          while(tree->lower_than(tree->current->pair->key, aux->pair->key) == 1
            || is_equal(tree,tree->current->pair->key, aux->pair->key) == 1){
            tree->current = tree->current->parent;
            if(tree->current==NULL)
              return NULL;
          }
          return tree->current->pair;
        }
      }
    }
  }
  return NULL;
}