// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <string>

template<typename T>
class BST {
private:
    struct Node {
        T key;
        int count;
        Node* left;
        Node* right;

        Node(const T& k) : key(k), count(1), left(nullptr), right(nullptr) {}
    };

    Node* root;

    void insert(Node*& node, const T& value);
    bool search(Node* node, const T& value) const;
    int depth(Node* node) const;
    void inorderTraverse(Node* node, std::vector<std::pair<T, int>>& result) const;
    void clear(Node* node);

public:
    BST() : root(nullptr) {}
    ~BST() { clear(root); }

    void insert(const T& value);
    bool search(T value) const;
    int depth() const;
    void getFrequencies(std::vector<std::pair<T, int>>& freqs) const;
};

template<typename T>
void BST<T>::insert(Node*& node, const T& value) {
    if (!node) {
        node = new Node(value);
        return;
    }

    if (value == node->key) {
        node->count++;
    } else if (value < node->key) {
        insert(node->left, value);
    } else {
        insert(node->right, value);
    }
}

template<typename T>
void BST<T>::insert(const T& value) {
    insert(root, value);
}

template<typename T>
bool BST<T>::search(Node* node, const T& value) const {
    if (!node) return false;
    if (value == node->key) return true;
    return (value < node->key) ? search(node->left, value) : search(node->right, value);
}

template<typename T>
bool BST<T>::search(T value) const {
    return search(root, value);
}

template<typename T>
int BST<T>::depth(Node* node) const {
    if (!node) return 0;
    int leftDepth = depth(node->left);
    int rightDepth = depth(node->right);
    return 1 + std::max(leftDepth, rightDepth);
}

template<typename T>
int BST<T>::depth() const {
    return depth(root);
}

template<typename T>
void BST<T>::inorderTraverse(Node* node, std::vector<std::pair<T, int>>& result) const {
    if (node) {
        inorderTraverse(node->left, result);
        result.push_back(std::make_pair(node->key, node->count));
        inorderTraverse(node->right, result);
    }
}

template<typename T>
void BST<T>::getFrequencies(std::vector<std::pair<T, int>>& freqs) const {
    freqs.clear();
    inorderTraverse(root, freqs);
}

template<typename T>
void BST<T>::clear(Node* node) {
    if (node) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

#endif // INCLUDE_BST_H_
