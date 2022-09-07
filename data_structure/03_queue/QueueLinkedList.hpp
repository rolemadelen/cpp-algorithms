#pragma once

#include "../linkedlist/doubly/DoublyLinkedList.hpp"

#include <stdexcept>
#include <iostream>
using std::cerr;
using std::cout;
using std::endl;

template <typename T>
class Queue
{
public:
    /* constructor */
    Queue<T>()
    {
        queue = new LinkedList<T>();
    }

    /* destructor */
    ~Queue<T>()
    {
        delete queue;
    }

    /* common operations */
    void enqueue(T data);
    T dequeue();
    T front();
    bool isEmpty();
    int length();
    void print();

    /* advanced operations */
    // Rotate the array 'rotation' times to the right.
    void rotate(int rotation);

private:
    LinkedList<T> *queue;

    /* helper function for Rotate */
    void rotateOnce();
};

/* private methods */
template <typename T>
void Queue<T>::rotateOnce()
{
    T data = queue->pop_back();
    queue->push_front(data);
}

/* public methods */
template <typename T>
void Queue<T>::enqueue(T data)
{
    queue->push_back(data);
}

template <typename T>
T Queue<T>::dequeue()
{
    if (isEmpty())
    {
        throw std::invalid_argument("queue is empty... underflow");
    }

    T data = queue->pop_front();
    return data;
}

template <typename T>
T Queue<T>::front()
{
    if (isEmpty())
    {
        throw std::invalid_argument("queue is empty... underflow");
    }
    return queue->front();
}

template <typename T>
bool Queue<T>::isEmpty()
{
    return queue->length() == 0;
}

template <typename T>
int Queue<T>::length()
{
    return queue->length();
}

template <typename T>
void Queue<T>::print()
{
    queue->print();
}

template <typename T>
void Queue<T>::rotate(int rotation)
{
    for (int i = 0; i < rotation; ++i)
    {
        rotateOnce();
    }
}