#pragma once

#include <iostream>
using std::cerr;
using std::endl;
using std::cout;

template <typename T>
class Stack {
public:
    /* constructor */
    Stack<T>() {
        topPos = 0;
        capacity = 32;
        stack = new int[32];
    }

    /* destructor */
    ~Stack<T>() {
        delete stack;
    }

    /* common operations */
    void push(T data);
    T pop();
    T top();
    bool isEmpty();
    bool isFull();
    int size();
    void print();

    /* advanced operations */
    // copy the topmost item and push it to the stack.
    void duplicate();

    // if stack contains 2 or more items, swap 2 topmost items in the stack.
    void swap();

    // move the topmost elements in the stack 'rotation' times to the right.
    void rotate(int rotation);

private:
    int topPos;   // tracks the top of the stack
    int capacity; // upper bound for bounded capacity stack
    int *stack;
    
    /* helper function for Rotate */
    void rotateOnce();
};

template <typename T>
void Stack<T>::push(T data) {
    if(isFull()) {
        cerr << "[Overflow] Stack is full..." << endl;
        return;
    }

    stack[topPos++] = data;
}

template <typename T>
T Stack<T>::pop() {
    if(isEmpty()) {
        cerr << "[Underflow] Stack is empty..." << endl;
        return -1;
    }

    --topPos;
    T data = stack[topPos];

    return data;
}

template <typename T>
T Stack<T>::top() {
    return stack[topPos-1];
}

template <typename T>
bool Stack<T>::isEmpty() {
    return topPos == 0;
}

template <typename T>
bool Stack<T>::isFull() {
    return topPos == capacity;
}

template <typename T>
int Stack<T>::size() {
    return topPos;
}

template <typename T>
void Stack<T>::print() {
    for(int i=0; i<topPos; ++i) {
        cout << stack[i] << " ";
    }
    cout << endl;
}

template <typename T>
void Stack<T>::duplicate() {
    if(!isEmpty()) {
        stack[topPos] = stack[topPos-1];
        ++topPos;
    }
}

template <typename T>
void Stack<T>::swap() {
    if(topPos >= 2) {
        T temp = stack[topPos-2];
        stack[topPos-2] = stack[topPos-1];
        stack[topPos-1] = temp;
    }
}

template <typename T>
void Stack<T>::rotateOnce() {
    T temp = stack[topPos-1];

    for(int i=topPos-1; i>0; --i) {
        stack[i] = stack[i-1];
    }

    stack[0] = temp;
}

template <typename T>
void Stack<T>::rotate(int rotation) {
    for(int i=0; i<rotation; ++i) {
        rotateOnce();
    }
}