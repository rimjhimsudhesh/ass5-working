/*
 * C++ Program to Implement Threaded Binary Tree
 * 
 * Rimjhim Sudhesh and Michael Schwartz
 * 
 * 🐇🦒
 */
#include <iostream>
#include "threaded_binary_tree.h"
#define MAX_VALUE 65535;
using namespace std;

  /*
    Overloaded ostream operator to print out a TBST

    @param out as the ostream that the tree will be returned to
    @param tree as the tree being printed
    @return ostream to be printed
  */
  ostream& operator<<(ostream& out, const ThreadedBinarySearchTree& tree) {
    Node* temp = tree.root->left;
    while(temp != tree.root) {
      out << temp->key << " ";
      if(temp->rightThread) {
        temp = temp->right;
      } else {
        temp = temp->right;
        while(!temp->leftThread) {
          temp = temp->left;
        }
      }
    }
    return out;
  }


  /* 
    No Parameter constructor for ThreadeBinarySearchTree
  */
  ThreadedBinarySearchTree::ThreadedBinarySearchTree() {
    root = new Node();
    root->right = root->left = root;
    root->leftThread = true;
    root->key = MAX_VALUE;
  }

  /*
    One parameter constructor for ThreadedBinarySearchTree

    @param n as the number of nodes being added to the tree
  */
  ThreadedBinarySearchTree::ThreadedBinarySearchTree(int n) {
    root = new Node();
    root->right = root->left = root;
    root->leftThread = true;
    root->key = MAX_VALUE;
    for(int i = 1; i <= n; i++) {
      insert(i);
    }
  }
  
  /*
    Copy constructor for TBST

    @param other as the TBST being copied
  */
  ThreadedBinarySearchTree::ThreadedBinarySearchTree(const ThreadedBinarySearchTree &other){
    root = new Node();
    root->right = root->left = root;
    root->leftThread = true;
    root->key = MAX_VALUE;
    Node *temp = other.root->left;
    while(temp != other.root) {
      insert(temp->key);
      if(temp->rightThread) {
        temp = temp->right;
      } else {
        temp = temp->right;
        while(!temp->leftThread) {
          temp = temp->left;
        }
      }
    }
  }

  /*
    Destructor for the ThreadedBinarySearchTree class
  */
  ThreadedBinarySearchTree::~ThreadedBinarySearchTree() {
    makeEmpty();
    delete root;
  }

  /* 
    Makes the entire tree empty
  */
  void ThreadedBinarySearchTree::makeEmpty() {
    root = new Node();
    root->right = root->left = root;
    root->leftThread = true;
    root->key = MAX_VALUE;
  }

  /* 
    Inserts a new node with value key in the tree

    @param key as the value being inserted
   */
  void ThreadedBinarySearchTree::insert(int key) {
    Node *p = root;
    for (;;) {
      if (p->key < key) {
        if (p->rightThread)
          break;
        p = p->right;
      } else if (p->key > key) {
        if (p->leftThread)
          break;
        p = p->left;
      } else {
        /* redundant key */
        return;
      }
    }
    Node *tmp = new Node();
    tmp->key = key;
    tmp->rightThread = tmp->leftThread = true;
    if (p->key < key) {
      /* insert to right side */
      tmp->right = p->right;
      tmp->left = p;
      p->right = tmp;
      p->rightThread = false;
    } else {
      tmp->right = p;
      tmp->left = p->left;
      p->left = tmp;
      p->leftThread = false;
    }
  }

  /* Function to search for an element */
  Node* ThreadedBinarySearchTree::search(int key) {
    Node *tmp = root->left;
    for (;;) {
      if (tmp->key < key) {
        if (tmp->rightThread)
          return nullptr;
        tmp = tmp->right;
      } else if (tmp->key > key) {
        if (tmp->leftThread)
          return nullptr;
        tmp = tmp->left;
      } else {
        return tmp;
      }
    }
  }

  /*
    Checks the TBST and determines if the tree contains a node with value key

    @param key as the value being looked for
    @return true if TBST contains key, false otherwise
  */
  bool ThreadedBinarySearchTree::contains(int key) {
    return (search(key) != nullptr);
  }

  /*
    Returns the highest node value in the TBST

    @return int of the highest node value
  */
  int ThreadedBinarySearchTree::getHighest() {
    Node* cur = root;
    if(root == nullptr){
      return -1;
    }
    while(cur->rightThread) {
      cur = cur->right;
    }
    return cur->key;
  }

  /*
    Removes a node with value key from the tree

    @param key as the node being deleted
  */
  void ThreadedBinarySearchTree::remove(int key) {
    Node *dest = root->left, *p = root;
    for (;;) {
      if (dest->key < key) {
        /* not found */
        if (dest->rightThread)
          return;
        p = dest;
        dest = dest->right;
      } else if (dest->key > key) {
        /* not found */
        if (dest->leftThread)
          return;
        p = dest;
        dest = dest->left;
      } else {
        /* found */
        break;
      }
    }
    Node *target = dest;
    if (!dest->rightThread && !dest->leftThread) {
      /* dest has two children*/
      p = dest;
      /* find largest node at left child */
      target = dest->left;
      while (!target->rightThread) {
        p = target;
        target = target->right;
      }
      /* using replace mode*/
      dest->key = target->key;
    }
    if (p->key >= target->key) {
      if (target->rightThread && target->leftThread) {
        p->left = target->left;
        p->leftThread = true;
      } else if (target->rightThread) {
        Node *largest = target->left;
        while (!largest->rightThread) {
          largest = largest->right;
        }
        largest->right = p;
        p->left = target->left;
      } else {
        Node *smallest = target->right;
        while (!smallest->leftThread) {
          smallest = smallest->left;
        }
        smallest->left = target->left;
        p->left = target->right;
      }
    } else {
      if (target->rightThread && target->leftThread) {
        p->right = target->right;
        p->rightThread = true;
      } else if (target->rightThread) {
        Node *largest = target->left;
        while (!largest->rightThread) {
          largest = largest->right;
        }
        largest->right = target->right;
        p->right = target->left;
      } else {
        Node *smallest = target->right;
        while (!smallest->leftThread) {
          smallest = smallest->left;
        }
        smallest->left = p;
        p->right = target->right;
      }
    }
  }
