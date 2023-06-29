## 介绍
### 红黑树概念
红黑树，是一种二叉搜索树，但在每个结点上增加一个存储位表示结点的颜色，可以是Red或Black。 通过对任何一条从根到叶子的路径上各个结点着色方式的限制，红黑树确保没有一条路径会比其他路径长出俩倍，因而是接近平衡的。
### 性质
1. 每个结点不是红色就是黑色
2. 根节点是黑色的
3. 如果一个节点是红色的，则它的两个孩子结点是黑色的
4. 对于每个结点，从该结点到其所有后代叶结点的简单路径上，均包含相同数目的黑色结点
5. 每个叶子结点都是黑色的(此处的叶子结点指的是空结点)  
6. 新加入到红黑树的节点为红色节点  
满足上面的性质，红黑树就能保证，从根节点到叶子节点的最长路径不大于最短路径的2倍

## 剖析
### 红黑树的节点设计
```
  enum _Rb_tree_color { _S_red = false, _S_black = true };

  struct _Rb_tree_node_base {
    typedef _Rb_tree_node_base* _Base_ptr;
    typedef const _Rb_tree_node_base* _Const_Base_ptr;

    _Rb_tree_color _M_color;
    _Base_ptr _M_parent;
    _Base_ptr _M_left;
    _Base_ptr _M_right;

    static _Base_ptr _S_minimum(_Base_ptr __x) _GLIBCXX_NOEXCEPT {
      while (__x->_M_left != 0) __x = __x->_M_left;
      return __x;
    }

    static _Const_Base_ptr _S_minimum(_Const_Base_ptr __x) _GLIBCXX_NOEXCEPT {
      while (__x->_M_left != 0) __x = __x->_M_left;
      return __x;
    }

    static _Base_ptr _S_maximum(_Base_ptr __x) _GLIBCXX_NOEXCEPT {
      while (__x->_M_right != 0) __x = __x->_M_right;
      return __x;
    }

    static _Const_Base_ptr _S_maximum(_Const_Base_ptr __x) _GLIBCXX_NOEXCEPT {
      while (__x->_M_right != 0) __x = __x->_M_right;
      return __x;
    }
  };
```


## 参考
[C++ STL源码剖析之红黑树 - 知乎](https://zhuanlan.zhihu.com/p/87469768)
[C++手撕红黑树_神之子-小佳的博客-CSDN博客](https://blog.csdn.net/m0_69787428/article/details/131355298)
[[C/C++]详解STL容器7--红黑树的介绍及部分模拟实现_TT在长大的博客-CSDN博客](https://blog.csdn.net/RMA515T/article/details/121654417)
[STL map / set 底层机制: 红黑树完全剖析_set底层数据结构为红黑树_Handling[韩镇江]的博客-CSDN博客](https://blog.csdn.net/chongzi_daima/article/details/107849493)
