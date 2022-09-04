#pragma once

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
    if (index >= size)
    {
        cerr << "Index out of bound." << endl;
        return static_cast<T>(-1);
    }

    Node<T> *temp = head;
    for (int i = 0; i < index; ++i)
    {
        temp = temp->next;
    }

    return temp->data;
}

template <typename T>
int LinkedList<T>::find(T data) {
    Node<T> *curr = head;
    int pos = 0;

    while(curr) {
        if(curr->data == data) {
            return pos;
        }
        curr = curr->next;
        ++pos;
    }

    return -1;
}

template <typename T>
void LinkedList<T>::insert(int index, T data)
{
    if (index < 0 || index > size)
    {
        cerr << "Index out of bound." << endl;
        return;
    }

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
        tail->next = new Node<T>(data);
        tail = tail->next;
    }

    size += 1;
}

template <typename T>
T LinkedList<T>::pop_front()
{
    if (empty())
    {
        cerr << "List is empty." << endl;
        return static_cast<T>(-1);
    }

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
    delete temp;

    size -= 1;

    return data;
}

template <typename T>
T LinkedList<T>::pop_back()
{
    if (empty())
    {
        cerr << "List is empty." << endl;
        return static_cast<T>(-1);
    }

    if (size == 1)
    {
        T data = head->data;
        head = tail = nullptr;
        size = 0;
        return data;
    }
    Node<T> *temp = head;

    while (temp->next != tail)
    {
        temp = temp->next;
    }

    T data = tail->data;
    if (tail)
        delete tail;
    temp->next = nullptr;
    tail = temp;

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

        for (int i = 1; i < index; ++i)
        {
            curr = curr->next;
        }

        Node<T> *temp = curr->next;
        curr->next = curr->next->next;
        size -= 1;
        delete temp;
    }
}

template <typename T>
void LinkedList<T>::remove_value(T data)
{
    while (1)
    {
        int pos = find(data);
        if (pos == -1)
        {
            break;
        }
        erase(pos);
    }
}

template <typename T>
T LinkedList<T>::front()
{
    if (empty())
    {
        cerr << "List is empty.." << endl;
        return static_cast<T>(-1);
    }

    if (head)
        return head->data;
}

template <typename T>
T LinkedList<T>::back()
{
    if (empty())
    {
        cerr << "List is empty.." << endl;
        return static_cast<T>(-1);
    }

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
        cout << temp->data << " ";
        temp = temp->next;
    }

    cout << temp->data << endl;
}