/*
 * C++ Program to Implement Threaded Binary Tree
 */
#include <cstdlib>
#include <iostream>
#define MAX_VALUE 65536
using namespace std;
#include "threaded_binary_tree.h"


int main() {
  /*ThreadedBinarySearchTree tbst;
  tbst.insert(1);
  tbst.insert(2);
  tbst.insert(3);
  tbst.insert(4);
  tbst.insert(5);
  ThreadedBinarySearchTree copy(tbst);
  cout << "\nTree = ";
  cout << tbst << endl;
  tbst.remove(2);
  cout << tbst.search(4)->key << endl;

  //cout << tbst.contains(4) << endl;
  //cout << tbst.contains(10) << endl;
  cout << "\nAfter removal, Tree = ";
  cout << tbst << endl;
  

  cout << "Test with input" << endl;
  ThreadedBinarySearchTree tree(10);
  tree.remove(5);
  cout << tree << endl;
  cout << "Copy!!" << endl;
  cout << copy << endl;

  return 0; */
  int input;
  cout << "Enter number of nodes in tree: ";
  cin >> input;
  //cout << input << endl;

  ThreadedBinarySearchTree test(input);
  ThreadedBinarySearchTree copy(test);
  int highest = copy.getHighest();

  for(int i = 1; i <= highest; i++) {
    if(copy.contains(i) && i % 2 == 0) {
      copy.remove(i);

    }
  }
  cout << "Original: " << test << endl;
  cout << "Copy without evens: " << copy << endl;
}
