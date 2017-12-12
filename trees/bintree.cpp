#include <iostream>

template <typename T>
struct BinTreeNode {
  T data;
  BinTreeNode *left, *right;

  BinTreeNode(T const& _data = T(),
              BinTreeNode *_left = nullptr,
              BinTreeNode *_right = nullptr) :
    data(_data),
    left(_left),
    right(_right) {}
};

template <typename T>
class BinTree {
private:

  using BTN = BinTreeNode<T>;

  BTN* rootptr;

  int countNodes(BTN* node) const {
    if (node == nullptr)
      return 0;
    return 1 + countNodes(node->left) + countNodes(node->right);
  }

  BTN* copyNode(BTN* node) const {
    if (node == nullptr)
      return nullptr;
    return new BTN(node->data,
                   copyNode(node->left),
                   copyNode(node->right));
  }

  void eraseNode(BTN* node) {
    if (node != nullptr) {
      eraseNode(node->left);
      eraseNode(node->right);
      delete node;
    }
  }

  void printNodeDOT(BTN* node, std::ostream& os = std::cout) {
    if (node != nullptr) {
      if (node->left != nullptr) {
        os << node->data << " -> " << node->left->data << "\n";
        printNodeDOT(node->left, os);
      }
      if (node->right != nullptr) {
        os << node->data << " -> " << node->right->data << "\n";
        printNodeDOT(node->right, os);
      }
    }
  }

public:
  BinTree() : rootptr(nullptr) {}

  BinTree(BinTree const& bt) {
    rootptr = copyNode(bt.rootptr);
  }

  BinTree& operator=(BinTree const& bt) {
    if (this != &bt) {
      eraseNode(rootptr);
      rootptr = copyNode(bt.rootptr);
    }
    return *this;
  }

  ~BinTree() {
    eraseNode(rootptr);
  }

  BinTree(T const& data,
          BinTree const& lt,
          BinTree const& rt) {
    rootptr = new BTN(data,
                      copyNode(lt.rootptr),
                      copyNode(rt.rootptr));
  }

  bool empty() const {
    return rootptr == nullptr;
  }

  T root() const {
    return rootptr->data;
  }

  int count() const {
    countNodes(rootptr);
  }

  void printDOT(std::ostream& os = std::cout) {
    os << "digraph bintree {\n";
    printNodeDOT(rootptr, os);
    os << "}\n";
  }
};
