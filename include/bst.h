// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <string>
#include <vector>
#include <algorithm>

template<typename T>
class BST {
 private:
  struct Node {
    T key;
    int count;
    Node* left;
    Node* right;

    explicit Node(const T& k) : key(k), count(1), left(nullptr), right(nullptr) {}
  };

  Node* root;

  void insert(Node*& node, const T& value);
  bool search(Node* node, const T& value) const;
  int depth(Node* node) const;
  void inorder(Node* node, std::vector<std::pair<T, int>>& result) const;
  void clear(Node* node);

 public:
  BST() : root(nullptr) {}
  ~BST();
  void insert(const T& value);
  bool search(T value) const;
  int depth() const;
  std::vector<std::pair<T, int>> getWords() const;
};

// Реализация шаблонных методов должна быть в заголовочном файле
template<typename T>
void BST<T>::insert(Node*& node, const T& value) {
  if (!node) {
    node = new Node(value);
  } else if (value < node->key) {
    insert(node->left, value);
  } else if (value > node->key) {
    insert(node->right, value);
  } else {
    node->count++;
  }
}

template<typename T>
bool BST<T>::search(Node* node, const T& value) const {
  if (!node) return false;
  if (value == node->key) return true;
  if (value < node->key) return search(node->left, value);
  return search(node->right, value);
}

template<typename T>
int BST<T>::depth(Node* node) const {
  if (!node) return 0;
  return 1 + std::max(depth(node->left), depth(node->right));
}

template<typename T>
void BST<T>::inorder(Node* node, std::vector<std::pair<T, int>>& result) const {
  if (node) {
    inorder(node->left, result);
    result.push_back({node->key, node->count});
    inorder(node->right, result);
  }
}

template<typename T>
void BST<T>::clear(Node* node) {
  if (node) {
    clear(node->left);
    clear(node->right);
    delete node;
  }
}

template<typename T>
BST<T>::~BST() {
  clear(root);
}

template<typename T>
void BST<T>::insert(const T& value) {
  insert(root, value);
}

template<typename T>
bool BST<T>::search(T value) const {
  return search(root, value);
}

template<typename T>
int BST<T>::depth() const {
  return depth(root);
}

template<typename T>
std::vector<std::pair<T, int>> BST<T>::getWords() const {
  std::vector<std::pair<T, int>> result;
  inorder(root, result);
  return result;
}

#endif  // INCLUDE_BST_H_
