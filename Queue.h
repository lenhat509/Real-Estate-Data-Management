/*
 Lab Number: 04
 Group members: Nguyen Cong Nhat Le, Kevin Jin
 Name: Nguyen Cong Nhat Le
 Description:
 The assignment is to demonstrate the use of a defined templated linked list, stack, and
 queue of integers with all methods of the ADTs through the console.

  Grade Kevin's effort: HIGH
*/

#ifndef QUEUE_H
#define Queue_h

#include "SinglyLinkedList.h"

template<class T>
class Queue : SinglyLinkedList<T> {
public:
    Queue() : SinglyLinkedList<T>() {}
    ~Queue();
    void enqueue(const T data);
    void dequeue();
    T peekFront() const;
    T peekRear() const;
    void clear();
    void printQueue();
};

template<class T>
Queue<T>::~Queue() {
    clear();
}

/*
Add node containing data of type T to queue.
Pre: data - data of type T to add
Post: node containing specified data added to queue
Return: None
*/
template<class T>
void Queue<T>::enqueue(const T data) {
    this->append(data);
}

/*
Remove node from queue.
Pre: None
Post: node removed from queue
Return: None
*/
template<class T>
void Queue<T>::dequeue() {
    this->removeStart();
}

/*
Retrieves data from start of queue
Pre: None
Post: None
Return: data of type T returned
*/
template<class T>
T Queue<T>::peekFront() const {
    return this->getStart();
}

/*
Retrieves data from back of queue
Pre: None
Post: None
Return: data of type T returned
*/
template<class T>
T Queue<T>::peekRear() const {
    return this->getEnd();
}

/*
Remove all nodes from queue; clear queue.
Pre: None
Post: all nodes removed from queue
Return: None
*/
template<class T>
void Queue<T>::clear() {
    while (!this->isEmpty())
        this->removeStart();
}

/*
Prints data of all nodes within the queue.
Pre: None
Post: data of all nodes within queue printed
Return: None
*/
template<class T>
void Queue<T>::printQueue() {
    this->printList();
}

#endif /* Queue_hpp */
