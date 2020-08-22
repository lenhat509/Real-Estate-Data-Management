/*
 Lab Number: 04
 Group members: Nguyen Cong Nhat Le, Kevin Jin
 Name: Nguyen Cong Nhat Le
 Description:
 The assignment is to demonstrate the use of a defined templated linked list, stack, and
 queue of integers with all methods of the ADTs through the console.

  Grade Kevin's effort: HIGH
*/

#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H

#include <iostream>
#include "LinkNode.h"

#include <type_traits>

template<class T>
class SinglyLinkedList {
private:
    LinkNode<T>* start;
    LinkNode<T>* end;
    int count;
    
public:
    // constructor and destructor
    SinglyLinkedList();
    virtual ~SinglyLinkedList();
    
    // SinglyLinkedList "getters"
    void printList() const;
    bool find(const T data);
    bool isEmpty() const;
    
    // Node "constructor and destructor" functions
    void append(const T data);
    void prepend(const T data);
    void insert(const T data, int index);
    bool removeStart();
    bool removeEnd();
    bool remove(const T data);
    virtual void clear();
    
    // Node "getters"
    T getStart() const;
    T getEnd() const;
    int getCount();
};

// constructor and destructor
template<class T>
SinglyLinkedList<T>::SinglyLinkedList() {
    start = end = nullptr;
    count = 0;
}

template<class T>
SinglyLinkedList<T>::~SinglyLinkedList() {
    clear();
}

/*
Adds a node to the end of the list.
Pre: data - data of any type to be added
Post: node containing data inserted at the end of the list
Return: None
*/
template<class T>
void SinglyLinkedList<T>::append(const T data) {
    LinkNode<T>* newNode = new LinkNode<T>();
    newNode->data = data;
    ++count;
    
    if (end != nullptr)            // if list is not empty
        end->next = newNode;   // assign newNode to next
    
    end = newNode;             // update end to newNode
    
    if (start == nullptr)            // if the list is empty
        start = end;                // assign start to end
}

/*
Adds a node to the start of the list.
Pre: data - data of type T to be added
Post: node containing data inserted at the start of the list
Return: None
*/
template<class T>
void SinglyLinkedList<T>::prepend(const T data)
{
    LinkNode<T>* newNode = new LinkNode<T>();
    newNode->data = data;
    newNode->next = start;
    start = newNode;
    ++count;
    
    if (end == nullptr)            // assign end to start if one item linked list
        end = start;                // created through prepend
}

/*
Removes a node from the start of the list.
Pre: None
Post: node removed from the start of the list
Return: true - node successfully removed
        false - empty list
*/
template<class T>
bool SinglyLinkedList<T>::removeStart() {
    if (start != nullptr)            // if list is not empty
    {
        LinkNode<T>* temp = start;
        start = start->next;          // update start to next node
        
        if (end == temp)           // if one item list
            end = start;            // update end to updated start
        
        delete temp;                // delete previous start
        
        --count;
        return true;
    } else
        return false;
}

/*
Removes a node from the end of the list.
Pre: None
Post: node removed from the end of the list
Return: true - node successfully removed
        false - empty list
*/
template<class T>
bool SinglyLinkedList<T>::removeEnd() {
    if (start != nullptr) {
        LinkNode<T> *temp = start;
        
        if (temp->next == nullptr) {            // if one item list
            delete temp;
            start = end = nullptr;              // assign start and end to null ptr
        }                                       // since last item deleted
        
        if (start != nullptr) {                  // if list has more than one item
            LinkNode<T>* secondToLast = start;
            while (secondToLast->next->next)
                secondToLast = secondToLast->next;
            
            secondToLast->next = nullptr;
            end = secondToLast;
        }
        
        --count;
        return true;
    } else
        return false;
}

/*
Inserts a node with data in the list.
Pre: data - data of type T to be added
     index - index to insert the data's node
Post: node inserted into list at specified index
Return: None
*/
template<class T>
void SinglyLinkedList<T>::insert(const T data, int index) {
    if (count >= index && index >= 0) {
        LinkNode<T>* previous = nullptr;
        LinkNode<T>* current = start;
        int curPosition = 0;
        
        while (curPosition != index)
        {
            previous = current;
            current = current->next;
            ++curPosition;
        }
        if (current == nullptr)
            append(data);
        else if (previous == nullptr)
            prepend(data);
        else {
            LinkNode<T>* newNode = new LinkNode<T>();
            newNode->data = data;
            previous->next = newNode;
            newNode->next = current;
            count++;
        }
    }
}

/*
Removes a node with specified data in the list.
Pre: data - data of type T to be removed
Post: node with specified data removed from the list
Return: true - node removed successfully from the list
        false - empty list
*/
template<class T>
bool SinglyLinkedList<T>::remove(const T data) {
    LinkNode<T>* current = start;
    LinkNode<T>* previous = nullptr;
    while (current != nullptr && current->data != data) {
        previous = current;
        current = current->next;
    }
    if (current == nullptr)             // if no items
        return false;
    else if (previous == nullptr)       // if one item
        return removeStart();
    else {
        previous->next = current->next;
        if (current == end)            // if current item to be removed is last item
            end = previous;
        delete current;
        count--;
        return true;
    }
}

/*
Removes nodes from the list.
Pre: None
Post: nodes cleared from the list and count set to 0
Return: None
*/
template<class T>
void SinglyLinkedList<T>::clear() {
    bool notNull = true;
    while (notNull)
        notNull = removeEnd();
    count = 0;
}

/*
Data of type T returned from start of the list.
Pre: None
Post: None
Return: data of type T
*/
template<class T>
T SinglyLinkedList<T>::getStart() const {
    if (start != nullptr)
        return start->data;
    return T();                             // TODO: Why is T() returned? Why not nullptr?
}

/*
Data of type T returned from end of the list.
Pre: None
Post: None
Return: data of type T
*/
template<class T>
T SinglyLinkedList<T>::getEnd() const {
    if (end != nullptr)
        return end->data;
    return T();
}

/*
Number of items in the list is returned.
Pre: None
Post: None
Return: number of items in the list
*/
template<class T>
int SinglyLinkedList<T>::getCount() {
    return count;
}

/*
Prints the contents of the list to the console.
Pre: None
Post: contents of list printed to console
Return: None
*/
template<class T>
void SinglyLinkedList<T>::printList() const {
    if (start != nullptr) {
        LinkNode<T>* current = start;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
            
            
        }
    }
}

/*
Determines whether the item containing specified data in the list.
Pre: data - data of type T to be found in the list
Post: None
Return: true - data is contained in the list
        false - data is not contained in the list
*/
template<class T>
bool SinglyLinkedList<T>::find(const T data) {
    LinkNode<T>* current = start;
    while (current != nullptr)
    {
        if (current->data == data)
            return true;
        current = current->next;
    }
    return false;
}

/*
Determines whether the list is empty.
Pre: None
Post: None
Return: true - list is empty
        false - list contains items
*/
template<class T>
bool SinglyLinkedList<T>::isEmpty() const {
    return count == 0;
}

#endif
