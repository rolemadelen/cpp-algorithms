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
    bool isPerfectBinaryTree();

private:
    Node<T> *root;

    void inorder(Node<T> *);
    void preorder(Node<T> *);
    void postorder(Node<T> *);

    int depth(Node<T> *);
    bool isFullBinaryTree(Node<T> *);
    bool isPerfectBinaryTree(Node<T> *, int, int);
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
    inorder(root);
    cout << endl;
}
template <typename T>
void BinaryTree<T>::preorder()
{
    preorder(root);
    cout << endl;
}
template <typename T>
void BinaryTree<T>::postorder()
{
    postorder(root);
    cout << endl;
}

template <typename T>
void BinaryTree<T>::inorder(Node<T> *node)
{
    if (!node)
        return;

    inorder(node->left);
    cout << node->data << " ";
    inorder(node->right);
}

template <typename T>
void BinaryTree<T>::preorder(Node<T> *node)
{
    if (!node)
        return;

    cout << node->data << " ";
    preorder(node->left);
    preorder(node->right);
}

template <typename T>
void BinaryTree<T>::postorder(Node<T> *node)
{
    if (!node)
        return;

    postorder(node->left);
    postorder(node->right);
    cout << node->data << " ";
}

template <typename T>
bool BinaryTree<T>::isFullBinaryTree()
{
    return isFullBinaryTree(root);
}

template <typename T>
bool BinaryTree<T>::isFullBinaryTree(Node<T> *node)
{
    if (!node)
        return true;

    if (!(node->left) && !(node->right))
        return true;

    if (node->left && node->right)
        return (isFullBinaryTree(node->left) && isFullBinaryTree(node->right));

    return false;
}

template <typename T>
int BinaryTree<T>::depth(Node<T> *node)
{
    int d = 0;
    while (node)
    {
        d++;
        node = node->left;
    }
    return d;
}

template <typename T>
bool BinaryTree<T>::isPerfectBinaryTree()
{
    int d = depth(root);
    int level = 0;
    return isPerfectBinaryTree(root, d, level);
}

template <typename T>
bool BinaryTree<T>::isPerfectBinaryTree(Node<T> *node, int d, int level)
{
    if (!node)
        return true;

    if (!(node->left) && !(node->right))
        return d == level + 1;

    if (!(node->left) || !(node->right))
        return d == level + 1;

    return isPerfectBinaryTree(node->left, d, level + 1) && 
           isPerfectBinaryTree(node->right, d, level + 1);
}