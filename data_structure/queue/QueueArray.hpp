#pragma once

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
        pos = 0;
        capacity = 32;
        queue = new int[capacity];
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
    bool isFull();
    int size();
    void print();

    /* advanced operations */
    // copy the topmost item and push it to the queue.
    void duplicate();

    // if queue contains 2 or more items, swap 2 topmost items in the queue.
    void swap();

    // move the topmost elements in the queue 'rotation' times to the right.
    void rotate(int rotation);

private:
    int pos;      // tracks the top of the queue
    int capacity; // upper bound for bounded capacity queue
    int *queue;

    /* helper function for Rotate */
    void rotateOnce();
    void shiftLeft();
};

/* private methods */
template <typename T>
void Queue<T>::rotateOnce()
{
    T temp = queue[pos - 1];

    for (int i = pos - 1; i > 0; --i)
    {
        queue[i] = queue[i - 1];
    }

    queue[0] = temp;
}

template <typename T>
void Queue<T>::shiftLeft()
{
    for (int i = 0; i < pos; ++i)
    {
        queue[i] = queue[i + 1];
    }
}

/* public methods */
template <typename T>
void Queue<T>::enqueue(T data)
{
    if (isFull())
    {
        throw std::invalid_argument("queue is full... overflow");
    }

    queue[pos++] = data;
}

template <typename T>
T Queue<T>::dequeue()
{
    if (isEmpty())
    {
        throw std::invalid_argument("queue is empty... underflow");
    }

    T data = queue[0];
    shiftLeft();
    --pos;

    return data;
}

template <typename T>
T Queue<T>::front()
{
    if (isEmpty())
    {
        throw std::invalid_argument("queue is empty... underflow");
    }
    return queue[0];
}

template <typename T>
bool Queue<T>::isEmpty()
{
    return pos == 0;
}

template <typename T>
bool Queue<T>::isFull()
{
    return pos == capacity;
}

template <typename T>
int Queue<T>::size()
{
    return pos;
}

template <typename T>
void Queue<T>::print()
{
    for (int i = 0; i < pos; ++i)
    {
        cout << queue[i] << " ";
    }
    cout << endl;
}

template <typename T>
void Queue<T>::duplicate()
{
    if (!isEmpty())
    {
        queue[pos] = queue[pos - 1];
        ++pos;
    }
}

template <typename T>
void Queue<T>::swap()
{
    if (pos >= 2)
    {
        T temp = queue[pos - 2];
        queue[pos - 2] = queue[pos - 1];
        queue[pos - 1] = temp;
    }
}

template <typename T>
void Queue<T>::rotate(int rotation)
{
    for (int i = 0; i < rotation; ++i)
    {
        rotateOnce();
    }
}