/*
 Lab Number: 04
 Group members: Nguyen Cong Nhat Le, Kevin Jin
 Name: Nguyen Cong Nhat Le
 Description:
 The assignment is to demonstrate the use of a defined templated linked list, stack, and
 queue of integers with all methods of the ADTs through the console.

  Grade Kevin's effort: HIGH
*/

#ifndef LINKNODE_H
#define LINKNODE_H

template<class T>
class LinkNode {
public:
    T data;
    LinkNode<T>* next;
    LinkNode();
};

///*
//Base case when the passed in object is not a pointer.
//Pre: a - object of type T
//Post: None
//Return: None
//*/
//template<class T>
//void deleteElement(T a) {
//    return;
//}
//
///*
//Function to delete pointer to an object, pointer to a pointer to an object, etc.
//Pre: a - pointer to object of type T
//Post: None
//Return: None
//*/
//template<class T>
//void deleteElement(T* a) {
//    // dereferences
//    deleteElement(*a);
//    delete a;
//}

template<class T>
LinkNode<T>::LinkNode() {
    next = nullptr;
}

//template<class T>
//LinkNode<T>::~LinkNode() {
//    /*deleteElement(data);*/
//    delete next;
//}

#endif

