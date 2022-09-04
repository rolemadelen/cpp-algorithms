#include "stack.hpp"

#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    unsigned seed = time(0);
    srand(seed);

    Stack<int> stack;
    cout << "Push" << endl;
    for(int i=0; i<10; ++i) {
        stack.push(rand()%32);
        stack.swap();
        stack.print();
    }

    cout << "Pop" << endl;
    for(int i=0; i<5; ++i) {
        stack.pop();
        stack.swap();
        stack.print();
    }

    cout << "Is stack empty? " << stack.isEmpty() << endl;
    cout << "Is stack full? " << stack.isFull() << endl;
    cout << "size: " << stack.size() << endl << endl;

    stack.print();
    stack.swap();
    stack.print();
    stack.duplicate();
    stack.print();
    stack.duplicate();
    stack.print();

    stack.pop();
    stack.pop();
    stack.print();
    cout << endl;

    stack.print();
    stack.rotate(4);
    stack.print();

    return 0;
}