#ifndef STACK_H
#define STACK_H

#include <iostream>

template<typename T>
class Stack{
public:
    Stack();
    ~Stack();
    bool isEmpty() const;
    void push(T value);
    T pop();
    T top() const;
private:
    struct Node
    {
        T data;
        Node * next;
        Node(T value): data(value), next(nullptr){}
    };
    
    Node * topNode;
};

template<typename T>
Stack<T>::Stack() : topNode(nullptr){}

template<typename T>
Stack<T>::~Stack() {
    while (!isEmpty())
    {
        pop();
    }
    
}

template<typename T>
bool Stack<T>::isEmpty() const {
    return topNode==nullptr;
}

template<typename T>
void Stack<T>::push(T value) {
    Node * newNode = new Node(value);
    newNode->next = topNode;
    topNode = newNode;
}

template<typename T>
T Stack<T>::pop() {
    if (isEmpty())
    {
        throw std::underflow_error("Stack underflow! Cannot pop from an empty stack.");
    }
    Node * temp = topNode;
    T pop_value = topNode->data;
    topNode = topNode->next;
    delete temp;
    return pop_value;
}

template<typename T>
T Stack<T>::top() const {
    if (isEmpty())
    {
        throw std::underflow_error("Stack underflow! Cannot peek into an empty stack.");
    }
    return topNode->data;
}

#endif // STACK_H