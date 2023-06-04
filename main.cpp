/*
 * C++ Program to Implement Threaded Binary Tree
 */
#include <cstdlib>
#include <iostream>
#define MAX_VALUE 65536
using namespace std;
//#include "menu_options.cpp"
#include "threaded_binary_tree.cpp"

/* Main Contains Menu */

int main() {
  // menu_options menu_options;
  ThreadedBinarySearchTree tbst;
  tbst.insert(1);
  tbst.insert(2);
  tbst.insert(3);
  tbst.insert(4);
  tbst.insert(5);
  tbst.insert(8);
  /*  Display tree  */
  cout << "\nTree = ";
  tbst.printTree();
  tbst.Delete(3);
  /*  Display tree  */
  cout << "\n After removal, Tree = ";
  tbst.printTree();

  return 0;
}
