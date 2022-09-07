#pragma once

#include <iostream>
#include <queue>
using namespace std;

template <typename T>
class BinaryTree;

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

    friend class BinaryTree<T>;
};

template <typename T>
class BinaryTree
{
public:
    BinaryTree<T>() : root(nullptr) {}
    ~BinaryTree<T>() = default;

    void insertLeverOrder(T data);

    void inorder();
    void postorder();
    void preorder();
    void levelOrderTraversal();

    bool isFullBinaryTree();

private:
    Node<T> *root;

    void inorderHelper(Node<T> *);
    void preorderHelper(Node<T> *);
    void postorderHelper(Node<T> *);
    bool isFullBinaryTreeHelper(Node<T> *);
};

template <typename T>
void BinaryTree<T>::insertLeverOrder(T data)
{
    if (!root)
    {
        root = new Node<T>(data);
        return;
    }
    queue<Node<T> *> q;
    q.push(root);

    while (!q.empty())
    {
        Node<T> *node = q.front();
        q.pop();

        if (node->left)
            q.push(node->left);
        else
        {
            node->left = new Node<T>(data);
            return;
        }

        if (node->right)
            q.push(node->right);
        else
        {
            node->right = new Node<T>(data);
            return;
        }
    }
}

template <typename T>
void BinaryTree<T>::levelOrderTraversal()
{
    queue<Node<T> *> q;
    q.push(root);

    while (!q.empty())
    {
        Node<T> *node = q.front();
        q.pop();
        cout << node->data << " ";

        if (node->left)
            q.push(node->left);
        if (node->right)
            q.push(node->right);
    }

    cout << endl;
}

template <typename T>
void BinaryTree<T>::inorder()
{
    inorderHelper(root);
    cout << endl;
}
template <typename T>
void BinaryTree<T>::preorder()
{
    preorderHelper(root);
    cout << endl;
}
template <typename T>
void BinaryTree<T>::postorder()
{
    postorderHelper(root);
    cout << endl;
}

template <typename T>
void BinaryTree<T>::inorderHelper(Node<T> *node)
{
    if (!node)
        return;

    inorderHelper(node->left);
    cout << node->data << " ";
    inorderHelper(node->right);
}

template <typename T>
void BinaryTree<T>::preorderHelper(Node<T> *node)
{
    if (!node)
        return;

    cout << node->data << " ";
    preorderHelper(node->left);
    preorderHelper(node->right);
}

template <typename T>
void BinaryTree<T>::postorderHelper(Node<T> *node)
{
    if (!node)
        return;

    postorderHelper(node->left);
    postorderHelper(node->right);
    cout << node->data << " ";
}

template <typename T>
bool BinaryTree<T>::isFullBinaryTree()
{
    return isFullBinaryTreeHelper(root);
}

template <typename T>
bool BinaryTree<T>::isFullBinaryTreeHelper(Node<T> *node)
{
    if (!node)
        return true;

    if (!(node->left) && !(node->right))
        return true;

    if (node->left && node->right)
        return (isFullBinaryTreeHelper(node->left) && isFullBinaryTreeHelper(node->right));

    return false;
}