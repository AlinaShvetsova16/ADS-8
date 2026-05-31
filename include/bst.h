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

        Node(const T& k) : key(k), count(1), left(nullptr), right(nullptr) {}
    };

    Node* root;

    void insert(Node*& node, const T& value) {
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

    bool search(Node* node, const T& value) const {
        if (!node) return false;
        if (value == node->key) return true;
        if (value < node->key) return search(node->left, value);
        return search(node->right, value);
    }

    int depth(Node* node) const {
        if (!node) return 0;
        return 1 + std::max(depth(node->left), depth(node->right));
    }

    void inorder(Node* node, std::vector<std::pair<T, int>>& result) const {
        if (node) {
            inorder(node->left, result);
            result.push_back({node->key, node->count});
            inorder(node->right, result);
        }
    }

    void clear(Node* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

public:
    BST() : root(nullptr) {}

    ~BST() {
        clear(root);
    }

    void insert(const T& value) {
        insert(root, value);
    }

    bool search(T value) const {
        return search(root, value);
    }

    int depth() const {
        return depth(root);
    }

    std::vector<std::pair<T, int>> getWords() const {
        std::vector<std::pair<T, int>> result;
        inorder(root, result);
        return result;
    }
};

#endif  // INCLUDE_BST_H_
