#include <math.h>
#include <string.h>

#include <iostream>
#include <queue>
#include <vector>

#include "my_rbtree.h"

int main() {
  RBTree<int> tree;

  for (int i = 0; i < 12; i++) {
    std::cout << "add: " << i << std::endl;
    tree.insert(i);
    tree.print();
    std::cout << std::endl;
  }

  std::cout << "size(): " << tree.size() << std::endl;
  std::cout << "Removing 8 and 9:" << std::endl;
  tree.remove(8);
  tree.remove(9);
  std::cout << "size(): " << tree.size() << std::endl;

  std::cout << "Contains 3: " << tree.contains(3) << std::endl;
  std::cout << "Contains 5: " << tree.contains(9) << std::endl;

  tree.print();

  return 0;
}