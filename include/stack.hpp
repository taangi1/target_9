/**
 * @file stack.h
 * @brief A template-based stack implementation using a linked list.
 *
 * This file defines a generic stack class that uses a linked list
 * to store elements. The stack supports standard operations such as
 * push, pop, and top, and it can store any data type specified by
 * the user.
 *
 * @tparam T The type of elements stored in the stack. This can be
 *            any data type, including built-in types and user-defined
 *            types, e.g. Move.
 *
 * @author Ignat Romanov
 * @version 1.0
 * @date 20.11.2024
 */

#include <stdexcept>

#ifndef STACK_HPP
#define STACK_HPP

/**
 * @brief A template-based stack implementation using a linked list.
 *
 * @tparam T The type of elements stored in the stack. This can be any data type, including built-in types and user-defined types.
 */
template <typename T>
class Stack
{
public:
    /**
     * @brief Constructs an empty stack.
     *
     * Initializes the topNode pointer to nullptr, indicating that the
     * stack is empty.
     */
    Stack();

    /**
     * @brief Destroys the stack and frees allocated memory.
     *
     * This destructor will deallocate all nodes in the stack to
     * prevent memory leaks.
     */
    ~Stack();

    /**
     * @brief Checks if the stack is empty.
     *
     * @return true if the stack is empty, false otherwise.
     */
    bool isEmpty() const;

    /**
     * @brief Pushes a new value onto the top of the stack.
     *
     * @param value The value to be added to the stack.
     */
    void push(T value);

    /**
     * @brief Removes and returns the value at the top of the stack.
     *
     * @return The value at the top of the stack.
     * @throw std::underflow_error if the stack is empty.
     */
    T pop();

    /**
     * @brief Returns the value at the top of the stack without removing it.
     *
     * @return The value at the top of the stack.
     * @throw std::underflow_error if the stack is empty.
     */
    T top() const;

private:
    /**
     * @brief A private structure representing a node in the linked list.
     *
     * Each node contains a data element of type T and a pointer to the
     * next node in the stack.
     */
    struct Node
    {
        T data;
        Node *next;

        /**
         * @brief Constructs a new node with the given value.
         *
         * @param value The value to be stored in the node.
         */
        Node(T value) : data(value), next(nullptr) {}
    };

    Node *topNode;
};

template <typename T>
Stack<T>::Stack() : topNode(nullptr) {} // Assign top node to nullptr (empty).

template <typename T>
Stack<T>::~Stack()
{
    while (!isEmpty())
    {
        pop(); // Pop from the stack untill it's empty.
    }
}

template <typename T>
bool Stack<T>::isEmpty() const
{
    return topNode == nullptr; // Stack is empty when topNode==nullptr.
}

template <typename T>
void Stack<T>::push(T value)
{
    Node *newNode = new Node(value); // Create new node.
    newNode->next = topNode;         // Assign the next node after the newNode to be current topNode.
    topNode = newNode;               // Update the topNode with newNode.
}

template <typename T>
T Stack<T>::pop()
{
    if (isEmpty()) // If empty throw underflow_error.
    {
        throw std::underflow_error("Stack underflow! Cannot pop from an empty stack.");
    }
    Node *temp = topNode;        // Create temp node and point to current topNode.
    T pop_value = topNode->data; // Get value from current topNode.
    topNode = topNode->next;     // Update topNode to be the next node after the topNode.
    delete temp;                 // Free memory by removeing old topNode.
    return pop_value;            // Return value stored in old topNode.
}

template <typename T>
T Stack<T>::top() const
{
    if (isEmpty()) // If empty throw underflow_error.
    {
        throw std::underflow_error("Stack underflow! Cannot peek into an empty stack.");
    }
    return topNode->data; // Return value stored.
}

#endif // STACK_HPP