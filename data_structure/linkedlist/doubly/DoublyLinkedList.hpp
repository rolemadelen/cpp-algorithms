#pragma once

#include <stdexcept>
#include <iostream>
using std::cerr;
using std::cout;
using std::endl;

template <typename T>
class LinkedList;

template <typename T>
class Node
{
public:
    Node(T data) : data(data), next(nullptr) {}
    ~Node() = default;

private:
    T data;
    Node<T> *next;
    Node<T> *prev;

    friend class LinkedList<T>;
};

template <typename T>
class LinkedList
{
public:
    /* constructor */
    LinkedList<T>() : head(nullptr), tail(nullptr), size(0) {}

    /* destructor */
    ~LinkedList<T>()
    {
        while (!empty())
            pop_front();
        if (head)
            delete head;
        if (tail)
            delete tail;
    }

    int length();
    bool empty();
    T value_at(int index);
    int find(T);

    void insert(int index, T);
    void push_front(T);
    void push_back(T);

    T pop_front();
    T pop_back();
    void erase(int index);
    void remove_value(T);

    T front();
    T back();

    void print();

private:
    Node<T> *head;
    Node<T> *tail;
    int size;
};

template <typename T>
int LinkedList<T>::length()
{
    return size;
}

template <typename T>
bool LinkedList<T>::empty()
{
    return size == 0;
}

template <typename T>
T LinkedList<T>::value_at(int index)
{
    if (index < 0 || index > size)
        throw std::invalid_argument("Index out of bound");

    Node<T> *temp = head;
    for (int i = 0; i < index; ++i)
        temp = temp->next;

    return temp->data;
}

template <typename T>
int LinkedList<T>::find(T data)
{
    Node<T> *curr = head;
    int pos = 0;

    while (curr)
    {
        if (curr->data == data)
            return pos;
        curr = curr->next;
        ++pos;
    }

    return -1;
}

template <typename T>
void LinkedList<T>::insert(int index, T data)
{
    if (index < 0 || index > size)
        throw std::invalid_argument("Index out of bound");

    if (index == 0)
    {
        push_front(data);
    }
    else if (index == size)
    {
        push_back(data);
    }
    else
    {
        Node<T> *curr = head;

        for (int i = 1; i < index; ++i)
        {
            curr = curr->next;
        }

        Node<T> *newNode = new Node<T>(data);
        newNode->next = curr->next;
        curr->next->prev = newNode;
        newNode->prev = curr;
        curr->next = newNode;

        size += 1;
    }
}

template <typename T>
void LinkedList<T>::push_front(T data)
{
    if (!head)
    {
        head = new Node<T>(data);
        tail = head;
    }
    else
    {
        Node<T> *newNode = new Node<T>(data);
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }

    size += 1;
}

template <typename T>
void LinkedList<T>::push_back(T data)
{
    if (!head)
    {
        head = new Node<T>(data);
        tail = head;
    }
    else
    {
        Node<T> *newNode = new Node<T>(data);
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }

    size += 1;
}

template <typename T>
T LinkedList<T>::pop_front()
{
    if (empty())
        throw std::invalid_argument("List is empty");

    if (size == 1)
    {
        T data = head->data;
        delete head;
        head = tail = nullptr;
        size = 0;
        return data;
    }

    T data = head->data;
    Node<T> *temp = head;
    head = head->next;
    head->prev = nullptr;
    delete temp;

    size -= 1;

    return data;
}

template <typename T>
T LinkedList<T>::pop_back()
{
    if (empty())
        throw std::invalid_argument("List is empty");

    if (size == 1)
    {
        T data = head->data;
        head = tail = nullptr;
        size = 0;
        return data;
    }

    T data = tail->data;
    tail = tail->prev;
    delete tail->next;
    tail->next = nullptr;

    size -= 1;

    return data;
}

template <typename T>
void LinkedList<T>::erase(int index)
{
    if (index < 0 || index >= size)
    {
        cerr << "Index out of bound." << endl;
        return;
    }

    if (index == 0)
    {
        pop_front();
    }
    else if (index == size - 1)
    {
        pop_back();
    }
    else
    {
        Node<T> *curr = head;

        for (int i = 0; i < index; ++i)
            curr = curr->next;

        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        delete curr;
        size -= 1;
    }
}

template <typename T>
void LinkedList<T>::remove_value(T data)
{
    int pos;
    while ((pos = find(data)) != -1)
        erase(pos);
}

template <typename T>
T LinkedList<T>::front()
{
    if (empty())
        throw std::invalid_argument("List is empty");

    if (head)
        return head->data;
}

template <typename T>
T LinkedList<T>::back()
{
    if (empty())
        throw std::invalid_argument("List is empty");

    if (tail)
        return tail->data;
}

template <typename T>
void LinkedList<T>::print()
{
    if (empty())
        return;

    Node<T> *temp = head;

    while (temp->next)
    {
        cout << temp->data << " -> ";
        temp = temp->next;
    }

    cout << temp->data << endl;
}