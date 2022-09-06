#pragma once

#include "../linkedlist/doubly/DoublyLinkedList.hpp"

#include <stdexcept>
#include <iostream>
using std::cerr;
using std::cout;
using std::endl;

template <typename T>
class Stack
{
public:
    /* constructor */
    Stack<T>()
    {
        size = 0;
        stack = new LinkedList<T>();
    }

    /* destructor */
    ~Stack<T>()
    {
        delete stack;
    }

    /* common operations */
    void push(T data);
    T pop();
    T peek();
    bool isEmpty();
    int length();
    void print();

    /* advanced operations */
    // copy the topmost item and push it to the stack.
    void duplicate();

    // if stack contains 2 or more items, swap 2 topmost items in the stack.
    void swap();

    // move the topmost elements in the stack 'rotation' times to the right.
    void rotate(int rotation);

private:
    int size; // number of items in stack
    LinkedList<T> *stack;

    /* helper function for Rotate */
    void rotateOnce();
};

template <typename T>
void Stack<T>::push(T data)
{
    stack->push_back(data);
    ++size;
}

template <typename T>
T Stack<T>::pop()
{
    if (isEmpty())
    {
        throw std::invalid_argument("stack is empty... underflowed");
    }

    --size;
    T data = stack->pop_back();
    return data;
}

template <typename T>
T Stack<T>::peek()
{
    if (isEmpty())
    {
        throw std::invalid_argument("stack is empty... underflowed");
    }

    return stack->back();
}

template <typename T>
bool Stack<T>::isEmpty()
{
    return size == 0;
}

template <typename T>
int Stack<T>::length()
{
    return size;
}

template <typename T>
void Stack<T>::print()
{
    stack->print();
}

template <typename T>
void Stack<T>::duplicate()
{
    if (isEmpty())
    {
        throw std::invalid_argument("stack is empty...");
    }
    push(stack->back());
}

template <typename T>
void Stack<T>::swap()
{
    if(size > 1) {
        T a = pop();
        T b = pop();
        push(a);
        push(b);
    }
}

template <typename T>
void Stack<T>::rotateOnce()
{
    T data = pop();
    stack->push_front(data);
}

template <typename T>
void Stack<T>::rotate(int rotation)
{
    for (int i = 0; i < rotation; ++i)
    {
        rotateOnce();
    }
}