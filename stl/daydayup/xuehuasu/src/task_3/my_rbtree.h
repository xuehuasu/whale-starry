enum Color { RED, BLACK };  // 定义节点颜色

template <typename T>
struct RBTreeNode {
  T val;                              // 节点值
  Color color;                        // 节点颜色
  RBTreeNode *left, *right, *parent;  // 左右子节点和父节点

  RBTreeNode(T val = T(), Color color = BLACK, RBTreeNode* left = nullptr,
             RBTreeNode* right = nullptr, RBTreeNode* parent = nullptr)
      : val(val), color(color), left(left), right(right), parent(parent) {}
};

template <typename T>
class RBTree {
 public:
  RBTree() {
    root = nullptr;
    count = 0;
  }

  ~RBTree() { clear(root); }
  void clear(RBTreeNode<T>* node) {
    if (node == nullptr) {
      return;
    }
    clear(node->left);
    clear(node->right);
    delete node;
    node = nullptr;
  }
  void insert(const T& val);    // 插入元素
  void remove(const T& val);    // 删除元素
  bool contains(const T& val);  // 查找元素是否存在
  void print();                 // 打印树
  int size();                   // 返回树大小

 private:
  RBTreeNode<T>* root;  // 根节点
  int count;            // 树的大小

  void insertFixup(RBTreeNode<T>* node);                         // 插入修正
  void removeFixup(RBTreeNode<T>* node, RBTreeNode<T>* parent);  // 删除修正
  void leftRotate(RBTreeNode<T>* node);                          // 左旋
  void rightRotate(RBTreeNode<T>* node);                         // 右旋
  RBTreeNode<T>* findNode(const T& val);                         // 查找节点
  RBTreeNode<T>* getMinNode(RBTreeNode<T>* node);                // 获取最小节点
  void transplant(RBTreeNode<T>* u, RBTreeNode<T>* v);           // 替换节点
  int getMaxHeight(RBTreeNode<T>* node);
};

template <typename T>
RBTreeNode<T>* RBTree<T>::findNode(const T& val) {
  RBTreeNode<T>* node = root;
  while (node != nullptr) {
    if (val == node->val) {
      return node;
    } else if (val < node->val) {
      node = node->left;
    } else {
      node = node->right;
    }
  }
  return nullptr;
}

template <typename T>
void RBTree<T>::leftRotate(RBTreeNode<T>* node) {
  RBTreeNode<T>* right = node->right;
  node->right = right->left;
  if (right->left != nullptr) {
    right->left->parent = node;
  }
  right->parent = node->parent;
  if (node->parent == nullptr) {
    root = right;
  } else if (node == node->parent->left) {
    node->parent->left = right;
  } else {
    node->parent->right = right;
  }
  right->left = node;
  node->parent = right;
}

template <typename T>
void RBTree<T>::rightRotate(RBTreeNode<T>* node) {
  RBTreeNode<T>* left = node->left;
  node->left = left->right;
  if (left->right != nullptr) {
    left->right->parent = node;
  }
  left->parent = node->parent;
  if (node->parent == nullptr) {
    root = left;
  } else if (node == node->parent->left) {
    node->parent->left = left;
  } else {
    node->parent->right = left;
  }
  left->right = node;
  node->parent = left;
}

template <typename T>
RBTreeNode<T>* RBTree<T>::getMinNode(RBTreeNode<T>* node) {
  while (node->left != nullptr) {
    node = node->left;
  }
  return node;
}

template <typename T>
void RBTree<T>::transplant(RBTreeNode<T>* u, RBTreeNode<T>* v) {
  if (u->parent == nullptr) {
    root = v;
  } else if (u == u->parent->left) {
    u->parent->left = v;
  } else {
    u->parent->right = v;
  }
  v->parent = u->parent;
}

template <typename T>
void RBTree<T>::insertFixup(RBTreeNode<T>* node) {
  while (node->parent != nullptr && node->parent->color == RED) {
    if (node->parent == node->parent->parent->left) {
      RBTreeNode<T>* uncle = node->parent->parent->right;
      if (uncle != nullptr && uncle->color == RED) {
        // case 1: 叔叔节点为红色
        node->parent->color = BLACK;
        uncle->color = BLACK;
        node->parent->parent->color = RED;
        node = node->parent->parent;
      } else {
        if (node == node->parent->right) {
          // case 2: 叔叔节点为黑色，且当前节点为其父节点的右子节点
          node = node->parent;
          leftRotate(node);
        }
        // case 3: 叔叔节点为黑色，且当前节点为其父节点的左子节点
        node->parent->color = BLACK;
        node->parent->parent->color = RED;
        rightRotate(node->parent->parent);
      }
    } else {
      RBTreeNode<T>* uncle = node->parent->parent->left;
      if (uncle != nullptr && uncle->color == RED) {
        // case 1: 叔叔节点为红色
        node->parent->color = BLACK;
        uncle->color = BLACK;
        node->parent->parent->color = RED;
        node = node->parent->parent;
      } else {
        if (node == node->parent->left) {
          // case 2: 叔叔节点为黑色，且当前节点为其父节点的左子节点
          node = node->parent;
          rightRotate(node);
        }
        // case 3: 叔叔节点为黑色，且当前节点为其父节点的右子节点
        node->parent->color = BLACK;
        node->parent->parent->color = RED;
        leftRotate(node->parent->parent);
      }
    }
  }
  root->color = BLACK;
}

template <typename T>
void RBTree<T>::removeFixup(RBTreeNode<T>* node, RBTreeNode<T>* parent) {
  while (node != root && (node == nullptr || node->color == BLACK)) {
    if (node == parent->left) {
      RBTreeNode<T>* sibling = parent->right;
      if (sibling->color == RED) {
        // case 1: 兄弟节点为红色
        sibling->color = BLACK;
        parent->color = RED;
        leftRotate(parent);
        sibling = parent->right;
      }
      if ((sibling->left == nullptr || sibling->left->color == BLACK) &&
          (sibling->right == nullptr || sibling->right->color == BLACK)) {
        // case 2: 兄弟节点的两个子节点都是黑色
        sibling->color = RED;
        node = parent;
        parent = node->parent;
      } else {
        if (sibling->right == nullptr || sibling->right->color == BLACK) {
          // case 3: 兄弟节点的左子节点是红色，右子节点是黑色
          sibling->left->color = BLACK;
          sibling->color = RED;
          rightRotate(sibling);
          sibling = parent->right;
        }
        // case 4: 兄弟节点的右子节点是红色
        sibling->color = parent->color;
        parent->color = BLACK;
        sibling->right->color = BLACK;
        leftRotate(parent);
        node = root;
      }
    } else {
      RBTreeNode<T>* sibling = parent->left;
      if (sibling->color == RED) {
        // case 1: 兄弟节点为红色
        sibling->color = BLACK;
        parent->color = RED;
        rightRotate(parent);
        sibling = parent->left;
      }
      if ((sibling->left == nullptr || sibling->left->color == BLACK) &&
          (sibling->right == nullptr || sibling->right->color == BLACK)) {
        // case 2: 兄弟节点的两个子节点都是黑色
        sibling->color = RED;
        node = parent;
        parent = node->parent;
      } else {
        if (sibling->left == nullptr || sibling->left->color == BLACK) {
          // case 3: 兄弟节点的右子节点是红色，左子节点是黑色
          sibling->right->color = BLACK;
          sibling->color = RED;
          leftRotate(sibling);
          sibling = parent->left;
        }
        // case 4: 兄弟节点的左子节点是红色
        sibling->color = parent->color;
        parent->color = BLACK;
        sibling->left->color = BLACK;
        rightRotate(parent);
        node = root;
      }
    }
  }
  if (node != nullptr) {
    node->color = BLACK;
  }
}

template <typename T>
void RBTree<T>::insert(const T& val) {
  RBTreeNode<T>* node = new RBTreeNode<T>(val, RED);
  RBTreeNode<T>* parent = nullptr;
  RBTreeNode<T>* cur = root;

  // 找到插入位置
  while (cur != nullptr) {
    parent = cur;
    if (val < cur->val) {
      cur = cur->left;
    } else if (val > cur->val) {
      cur = cur->right;
    } else {
      // 如果已经存在节点，则直接返回
      delete node;
      return;
    }
  }

  // 插入新节点
  node->parent = parent;
  if (parent == nullptr) {
    root = node;
  } else if (val < parent->val) {
    parent->left = node;
  } else {
    parent->right = node;
  }

  // 修正颜色和旋转，保证红黑树性质
  insertFixup(node);
  count++;
}

template <typename T>
void RBTree<T>::remove(const T& key) {
  RBTreeNode<T>* node = findNode(key);
  if (node == nullptr) {
    return;
  }

  RBTreeNode<T>* child = nullptr;
  RBTreeNode<T>* parent = nullptr;
  Color color;

  // 如果节点有两个子节点，则找到右子树的最小节点，并用其代替要删除的节点
  if (node->left != nullptr && node->right != nullptr) {
    RBTreeNode<T>* min_node = node->right;
    while (min_node->left != nullptr) {
      min_node = min_node->left;
    }
    child = min_node->right;
    parent = min_node->parent;
    color = min_node->color;

    if (child != nullptr) {
      child->parent = parent;
    }

    if (parent == node) {
      parent = min_node;
    } else {
      if (child != nullptr) {
        child->parent = parent;
      }
      parent->left = child;
      min_node->right = node->right;
      node->right->parent = min_node;
    }

    min_node->parent = node->parent;
    min_node->color = node->color;
    min_node->left = node->left;
    node->left->parent = min_node;

    if (node == root) {
      root = min_node;
    } else if (node == node->parent->left) {
      node->parent->left = min_node;
    } else {
      node->parent->right = min_node;
    }
    delete node;
    node = nullptr;
  } else {
    if (node->left != nullptr) {
      child = node->left;
    } else {
      child = node->right;
    }

    parent = node->parent;
    color = node->color;

    if (child != nullptr) {
      child->parent = parent;
    }

    if (node == root) {
      root = child;
    } else {
      if (node == node->parent->left) {
        node->parent->left = child;
      } else {
        node->parent->right = child;
      }
    }

    delete node;
    node = nullptr;

    // 如果要删除的节点是黑色节点，则需要进行删除修正操作
    if (color == BLACK) {
      removeFixup(child, parent);
    }
  }
}

template <typename T>
bool RBTree<T>::contains(const T& val) {
  RBTreeNode<T>* cur = root;
  while (cur != nullptr) {
    if (val == cur->val) {
      return true;
    } else if (val < cur->val) {
      cur = cur->left;
    } else {
      cur = cur->right;
    }
  }
  return false;
}

template <typename T>
int RBTree<T>::size() {
  return count;
}

template <typename T>
int RBTree<T>::getMaxHeight(RBTreeNode<T>* node) {
  if (node == nullptr) {
    return 0;
  }

  int leftHeight = getMaxHeight(node->left);
  int rightHeight = getMaxHeight(node->right);
  return std::max(leftHeight, rightHeight) + 1;
}

template <typename T>
void RBTree<T>::print() {
  if (root == nullptr) {
    std::cout << "Empty tree." << std::endl;
    return;
  }

  std::queue<RBTreeNode<T>*> q;
  q.push(root);
  while (!q.empty()) {
    int levelSize = q.size();
    for (int i = 0; i < levelSize; i++) {
      RBTreeNode<T>* cur = q.front();
      q.pop();

      std::cout << cur->val << (cur->color == RED ? "R" : "B") << ": ";

      if (cur->left != nullptr) {
        q.push(cur->left);
        std::cout << cur->left->val << (cur->left->color == RED ? "R" : "B") << " ";
      }
      if (cur->right != nullptr) {
        q.push(cur->right);
        std::cout << cur->right->val << (cur->right->color == RED ? "R" : "B") << " ";
      }
      std::cout << std::endl;
    }
  }
  std::cout << std::endl;
}