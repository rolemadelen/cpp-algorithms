#pragma once

#include <iostream>
using namespace std;

template <typename T>
class BinarySearchTree;

template <typename T>
class Node
{
public:
    Node<T>(T _data)
    {
        data = _data;
        left = nullptr;
        right = nullptr;
    }

private:
    T data;
    Node<T> *left;
    Node<T> *right;

    friend class BinarySearchTree<T>;
};

template <typename T>
class BinarySearchTree
{
public:
    BinarySearchTree() : root(nullptr) {}
    ~BinarySearchTree() = default;

    void insertNode(T data);
    Node<T> *searchNode(T data);
    Node<T> *deleteNode(T data);

    void inorder();

private:
    Node<T> *root;

    void insertNode(T data, Node<T> *);
    Node<T> *searchNode(T data, Node<T> *);
    Node<T> *deleteNode(T data, Node<T> *);
    Node<T> *getInorderSuccessor(Node<T> *);

    void inorder(Node<T> *);
};

template <typename T>
void BinarySearchTree<T>::insertNode(T data)
{
    insertNode(data, root);
}

template <typename T>
void BinarySearchTree<T>::insertNode(T data, Node<T> *node)
{
    if (!node)
    {
        root = new Node<T>(data);
        return;
    }

    if (data < node->data)
    {
        if (!(node->left))
        {
            node->left = new Node<T>(data);
            return;
        }
        insertNode(data, node->left);
    }
    else
    {
        if (!(node->right))
        {
            node->right = new Node<T>(data);
            return;
        }
        insertNode(data, node->right);
    }
}

template <typename T>
Node<T> *BinarySearchTree<T>::searchNode(T data)
{
    return searchNode(data, root);
}

template <typename T>
Node<T> *BinarySearchTree<T>::searchNode(T data, Node<T> *node)
{
    if (!node)
        return nullptr;

    if (data < node->data)
        return searchNode(data, node->left);
    else if (data > node->data)
        return searchNode(data, node->right);
    else
        return node;
}

template <typename T>
Node<T> *BinarySearchTree<T>::getInorderSuccessor(Node<T> *node)
{
    while (node && node->left)
        node = node->left;

    return node;
}

template <typename T>
Node<T> *BinarySearchTree<T>::deleteNode(T data)
{
    return deleteNode(data, root);
}

template <typename T>
Node<T> *BinarySearchTree<T>::deleteNode(T data, Node<T> *node)
{
    if (!node)
        return node;

    if (data < node->data)
        node->left = deleteNode(data, node->left);
    else if (data > node->data)
        node->right = deleteNode(data, node->right);
    else
    {
        // if a target node has a single child
        if (!(node->left))
        {
            Node<T> *temp = node->right;
            delete node;
            return temp;
        }
        else if (!(node->right))
        {
            Node<T> *temp = node->left;
            delete node;
            return temp;
        }

        // if a target node has 2 children
        Node<T> *successor = getInorderSuccessor(root->right);

        // place the inorder successor in position of the node to be deleted
        node->data = successor->data;
        // delete the inorder successor
        node->right = deleteNode(successor->data, node->right);
    }

    return node;
}

template <typename T>
void BinarySearchTree<T>::inorder()
{
    inorder(root);
    cout << endl;
}

template <typename T>
void BinarySearchTree<T>::inorder(Node<T> *node)
{
    if (!node)
        return;

    inorder(node->left);
    cout << node->data << " ";
    inorder(node->right);
}