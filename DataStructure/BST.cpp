#include <iostream>
#include <queue>
#include <vector>

template <class T>
struct Node {
  T value;
  int count;
  Node *left;
  Node *right;
  explicit Node(T v) {
    value = v;
    count = 1;
    left = NULL;
    right = NULL;
  }
};

template <class T>
class BinaryTree {
  typedef Node<T> *Ptr;

 public:
  explicit BinaryTree(std::vector<T> vec) {
    for (auto key : vec) {
      Insert(key);
    }
  }

  bool Search(T key) {
    std::function<bool(Ptr, T)> search = [&](Ptr node, T key) {
      if (node == NULL) {
        return false;
      } else if (key < node->value) {
        return search(node->left, key);
      } else if (key > node->value) {
        return search(node->right, key);
      }
      return true;
    };
    return search(root, key);
  }
  void Insert(T key) {
    std::function<void(Ptr &, T)> insert = [&](Ptr &node, T key) {
      if (node == NULL) {
        node = new Node<T>(key);
      } else if (key < node->value) {
        insert(node->left, key);
      } else if (key > node->value) {
        insert(node->right, key);
      } else {
        node->count++;
      }
    };
    insert(root, key);
  }
  void Delete(T key) {
    std::function<Ptr(Ptr, T)> del = [&](Ptr node, T key) -> Ptr {
      if (node == NULL) {
        return NULL;
      } else if (key < node->value) {
        node->left = del(node->left, key);
      } else if (key > node->value) {
        node->right = del(node->right, key);
      } else {
        if (node->right == NULL) {
          return node->left;
        }
        if (node->left == NULL) {
          return node->right;
        }
        auto succ = [](Ptr node) {
          node = node->right;
          while (node->left != NULL) {
            node = node->left;
          }
          return node->value;
        };
        T temp_value = succ(node);
        node = del(node, temp_value);
        node->value = temp_value;
      }
      return node;
    };
    root = del(root, key);
  }

  void Print() {
    std::function<void(Ptr)> print = [&](Ptr node) {
      if (node != NULL) {
        if (node->left == NULL && node->right == NULL) {
          std::cout << "\e[94m";
        }
        std::cout << node->value << " \e[0m";
        print(node->left);
        print(node->right);
      }
    };
    print(root);
    std::cout << std::endl;
  }
  void PrintLevel() {
    std::deque<Node<T> *> next_level;
    next_level.push_back(root);
    while (!next_level.empty()) {
      int n = next_level.size();
      while (n--) {
        Node<T> *node = next_level.front();
        next_level.pop_front();
        if (node->left != NULL) {
          next_level.push_back(node->left);
        }
        if (node->right != NULL) {
          next_level.push_back(node->right);
        }
        if (node->left == NULL && node->right == NULL) {
          std::cout << "\e[94m";
        }
        std::cout << node->value << " \e[0m";
      }
      std::cout << std::endl;
    }
  }

 private:
  Ptr root;
};

int main() {
  std::vector<int> s = {2, 1, 33, 0, 25, 40, 11, 34, 7, 12, 36, 13};
  BinaryTree<int> b(s);
  b.Print();
  b.Delete(33);
  b.Print();
}
