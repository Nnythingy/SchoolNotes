#include <bits/stdc++.h>
using namespace std;



// Every vertex in this BST is a C Struct (to expose all its members publicly)
struct BSTVertex {
  // all these attributes remain public to slightly simplify the code although this may not be the best practice
  BSTVertex* parent;
  BSTVertex* left;
  BSTVertex* right;
  int key;
  int height; // will be used in AVL lecture
};



// This is just a sample implementation
// There are other ways to implement BST concepts...
class BST {
protected:
  BSTVertex *root;

  BSTVertex* insert(BSTVertex* T, int v) {
    if (T == NULL) {                             // insertion point is found
      T = new BSTVertex;
      T->key = v;
      T->parent = T->left = T->right = NULL;
      T->height = 0;                             // used in AVL lecture
    }
    else if (T->key < v) {                       // search to the right
      T->right = insert(T->right, v);
      T->right->parent = T;
    }
    else {                                       // search to the left
      T->left = insert(T->left, v);
      T->left->parent = T;
    }
    return T;                                    // return the updated BST
  }

  void inorder(BSTVertex* T) {
    if (T == NULL) return;
    inorder(T->left);                            // recursively go to the left
    printf(" %d", T->key);                       // visit this BST node
    inorder(T->right);                           // recursively go to the right
  }

  void preorder(BSTVertex* T) {
    if (T == NULL) return;
    printf(" %d", T->key);                       // visit this BST node
    preorder(T->left);                           // recursively go to the left
    preorder(T->right);                          // recursively go to the right
  }

  int findMin(BSTVertex* T) {
         if (T == NULL)       return -1;         // BST is empty, no minimum
    else if (T->left == NULL) return T->key;     // this is the min
    else                      return findMin(T->left); // go to the left
  }

  int findMax(BSTVertex* T) {
         if (T == NULL)        return -1;        // BST is empty, no maximum
    else if (T->right == NULL) return T->key;    // this is the max
    else                       return findMax(T->right); // go to the right
  }

  BSTVertex* search(BSTVertex* T, int v) {
         if (T == NULL)   return T;              // not found
    else if (T->key == v) return T;              // found
    else if (T->key < v)  return search(T->right, v); // search to the right
    else                  return search(T->left, v); // search to the left
  }

  int successor(BSTVertex* T) {
    if (T->right != NULL)                        // we have right subtree
      return findMin(T->right);                  // this is the successor
    else {
      BSTVertex* par = T->parent;
      BSTVertex* cur = T;
      // if par(ent) is not root and cur(rent) is its right children
      while ((par != NULL) && (cur == par->right)) {
        cur = par;                               // continue moving up
        par = cur->parent;
      }
      return par == NULL ? -1 : par->key;        // this is the successor of T
    }
  }

  int predecessor(BSTVertex* T) {
    if (T->left != NULL)                         // we have left subtree
      return findMax(T->left);                   // this is the predecessor
    else {
      BSTVertex* par = T->parent;
      BSTVertex* cur = T;
      // if par(ent) is not root and cur(rent) is its left children
      while ((par != NULL) && (cur == par->left)) { 
        cur = par;                               // continue moving up
        par = cur->parent;
      }
      return par == NULL ? -1 : par->key;        // this is the successor of T
    }
  }

  BSTVertex* remove(BSTVertex* T, int v) {
    if (T == NULL)  return T;                    // cannot find the item

    if (T->key == v) {                           // the node to be deleted
      if (T->left == NULL && T->right == NULL)   // this is a leaf
        T = NULL;                                // simply erase this node
      else if (T->left == NULL && T->right != NULL) { // only one child at right
        T->right->parent = T->parent;            // ma, take care of my child
        T = T->right;                            // bypass T
      }
      else if (T->left != NULL && T->right == NULL) { // only one child at left
        T->left->parent = T->parent;             // ma, take care of my child
        T = T->left;                             // bypass T
      }
      else { // has two children, find successor to avoid quarrel
        int successorV = successor(v);           // predecessor is also OK btw
        T->key = successorV;                     // replace with successorV
        T->right = remove(T->right, successorV); // delete the old successorV
      }
    }
    else if (T->key < v)                         // search to the right
      T->right = remove(T->right, v);
    else                                         // search to the left
      T->left = remove(T->left, v);
    return T;                                    // return the updated BST
  }

  // will be used in AVL lecture
  int getHeight(BSTVertex* T) {
    if (T == NULL) return -1;
    else return max(getHeight(T->left), getHeight(T->right)) + 1;
  }

public:
  BST() { root = NULL; }

  void insert(int v) { root = insert(root, v); }

  void inorder() { 
    inorder(root);
    printf("\n");
  }

  void preorder() { 
    preorder(root);
    printf("\n");
  }

  int findMin() { return findMin(root); }

  int findMax() { return findMax(root); }

  int search(int v) {
    BSTVertex* res = search(root, v);
    return res == NULL ? -1 : res->key;
  }

  int successor(int v) { 
    BSTVertex* vPos = search(root, v);
    return vPos == NULL ? -1 : successor(vPos);
  }

  int predecessor(int v) { 
    BSTVertex* vPos = search(root, v);
    return vPos == NULL ? -1 : predecessor(vPos);
  }

  void remove(int v) { root = remove(root, v); }

  // will be used in AVL lecture
  int getHeight() { return getHeight(root); }
};


/*
// comment this int main() if you want to run AVLDemo

int main() {
  BST* T = new BST();                                            // an empty BST

  printf("%d\n", T->findMin());                                 // not found, -1
  printf("%d\n", T->findMax());                                 // not found, -1

  // Sample BST as shown in Lecture
  T->insert(15);
  T->insert(23);
  T->insert(6);
  T->insert(71);
  T->insert(50);
  T->insert(4);
  T->insert(7);
  T->insert(5);

  printf("%d\n", T->findMin());                                             // 4
  printf("%d\n", T->findMax());                                            // 71

  printf("%d\n", T->search(71));                                    // found, 71
  printf("%d\n", T->search(7));                                      // found, 7
  printf("%d\n", T->search(22));                                // not found, -1

  T->inorder();                           // The BST: 4, 5, 6, 7, 15, 23, 50, 71
  T->preorder();
  printf("%d\n", T->getHeight());                                           // 3

  printf("%d\n", T->successor(23));                                        // 50
  printf("%d\n", T->successor(7));                                         // 15
  printf("%d\n", T->successor(71));                                        // -1
  printf("%d\n", T->predecessor(23));                                      // 15
  printf("%d\n", T->predecessor(7));                                        // 6
  printf("%d\n", T->predecessor(71));                                      // 50

  printf("Removing 5\n");
  T->remove(5);
  printf("Removing 71\n");
  T->remove(71);
  printf("Removing 15\n");
  T->remove(15);

  T->inorder();                                      // The BST: 4, 6, 7, 23, 50
  printf("%d\n", T->getHeight());                                           // 2

  return 0;
}
*/
