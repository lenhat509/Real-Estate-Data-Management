/*
lab number: 05
authors: Nguyen Cong Nhat Le, Kevin Jin
description: Implement a BST with the usual operations and four traversal methods, reading Currency objects from an input file with data validation; performed operations will output to both the console and an output file.
*/

#ifndef BST_H
#define BST_H

#include "BSTNode.h"
#include "Queue.h"
#include <iostream>
#include <cctype>
template<typename T>
class BST {
private:
    BSTNode<T>* root;
    int size;
    void deleteAllNodesHelper(BSTNode<T>*);
    int insertCnt;
    int searchCnt;
public:
    //constructor
    BST();
    ~BST() {
        deleteAllNodes();
    }
    void setAllNullptr(BSTNode<T>*);
    void deleteAllNodes();
    void deleteSetNull(T*);
    /*
    Add object to the tree
    Pre: T object
    Post: current, curParent BSTNode pointers, root, size
    return: none
    */
    void insert(T*);
    int getInsertCnt() {
        return insertCnt;
    }
    /*
    Search for object in the tree
    Pre: T object
    Post: current BSTNode pointers, root
    Return: true if found, otherwise, return false
    */
    bool search(T*);
    int getSearchCnt() {
        return searchCnt;
    }
    /*
    Remove object from the tree
    Pre: T object
    Post: current, curParent, max, maxParent BSTNode pointers, root, size
    return: none
    */
    void remove(T*);
    /*
    Pass to ostream breath-first, pre-order, in-order, post-oder traversal
    Pre: ostream&
    Post: breadthFirst, inOrder, preOrder, postOrder functions
    return: none
    */
    void print(std::ostream&);
    /*
    Pre: None
    Post:  size
    return: size of the tree
    */
    int count() {
        return size;
    }
    /*
    Pre: None
    Post:  size
    return: true if the tree is empty, otherwise false
    */
    bool isEmpty() {
        return size == 0;
    }
    /*
    Empty the tree
    Pre: None
    Post:  root, remove(), isEmpty()
    return: None
    */
    void empty();
    /*
    Pass to ostream breath-first traversal
    Pre: ostream&, BSTNode<T>* node
    Post: Queue
    return: none
    */
    void breadthFirst(std::ostream&, BSTNode<T>* node);
    /*
    Pass to ostream in-order traversal
    Pre: ostream&, BSTNode<T>* node
    Post: Queue
    return: none
    */
    void printBySortedKey(std::ostream& out) {
        inOrder(out, root);
    }
    void inOrder(std::ostream&, BSTNode<T>* node);
    /*
    Pass to ostream pre-order traversal
    Pre: ostream&, BSTNode<T>* node
    Post: Queue
    return: none
    */
    void printIndentedTree(std::ostream& out) {
        preOrder(out, root, "\t");
    }
    void preOrder(std::ostream&, BSTNode<T>* node, std::string indent);
    /*
    Pass to ostream post-order traversal
    Pre: ostream&, BSTNode<T>* node
    Post: Queue
    return: none
    */
    void postOrder(std::ostream&, BSTNode<T>* node);
    void printInRange(BSTNode<T>* node, T min, T max);
    void printInRange(T min, T max);
};
template<typename T>
BST<T>::BST() {
    root = nullptr;
    size = 0;
    insertCnt = 0;
    searchCnt = 0;
}
template<typename T>
void BST<T>::printInRange(BSTNode<T>* node, T min, T max)
{
    if (node == nullptr)
        return;
    if (*node->getData() > min)
        printInRange(node->getLeftChild(), min, max);

    if (*node->getData() >= min && *node->getData() <= max)
        std::cout << *node->getData() << std::endl;

    if (*node->getData() < max)
        printInRange(node->getRightChild(), min, max);
}

template<typename T>
void BST<T>::printInRange(T min, T max)
{
    printInRange(root, min, max);
}
template<typename T>
void BST<T>::insert(T* data) {
    if (root != nullptr)
    {
        BSTNode<T>* curParent = nullptr;
        BSTNode<T>* current = root;
        
        while (current != nullptr)
        {
            if (*(current->getData()) <= *data)
            {
                curParent = current;
                current = current->getRightChild();
            }
            else // if (*(current->getData()) > *data)
            {
                curParent = current;
                current = current->getLeftChild();
            }
            insertCnt++;
        }
        
        BSTNode<T>* newNode = new BSTNode<T>();
        newNode->setData(data);
        
        if (*(curParent->getData()) < *data) {
            curParent->setRightChild(newNode);
        } else {
            curParent->setLeftChild(newNode);
        }
        insertCnt++;
        size++;
    }
    else {
        root = new BSTNode<T>();
        root->setData(data);
        size++;
    }
}
template<typename T>
void BST<T>::remove(T* data)
{
    if (root != nullptr)
    {
        BSTNode<T>* curParent = nullptr;
        BSTNode<T>* current = root;
        while (current != nullptr)
        {
            if (*(current->getData()) < *data)
            {
                curParent = current;
                current = current->getRightChild();
            }
            else if (*(current->getData()) > *data)
            {
                curParent = current;
                current = current->getLeftChild();
            }
            // the == operator in house is overloaded to compare address rather than price
            else if (*(current->getData()) == *data)
                break;
            else
                return;
        }
        if (current == nullptr)
            return;
        if (current->getLeftChild() == nullptr)
        {
            if (curParent != nullptr)
            {
                // TODO: if the address is the same, then delete; otherwise, return
                if (*curParent->getData() < *current->getData())
                    curParent->setRightChild(current->getRightChild());
                else
                    curParent->setLeftChild(current->getRightChild());
                delete current;
                size--;
            }
            else
            {
                BSTNode<T>* oldRoot = root;
                root = root->getRightChild();
                delete oldRoot;
                size--;
            }
        }
        else
        {
            BSTNode<T>* max = current->getLeftChild();
            BSTNode<T>* maxParent = current;
            while (max->getRightChild())
            {
                maxParent = max;
                max = max->getRightChild();
            }
            current->setData(max->getData());
            if (*max->getData() > *maxParent->getData())
                maxParent->setRightChild(max->getLeftChild());
            else
                maxParent->setLeftChild(max->getLeftChild());
            delete max;
            size--;
        }
    }
}
template<typename T>
void BST<T>::deleteAllNodesHelper(BSTNode<T>* node) {
    if (node != nullptr) {
        deleteAllNodesHelper(node->getLeftChild());
        deleteAllNodesHelper(node->getRightChild());
        delete node;
    }
}
template<typename T>
void BST<T>::deleteAllNodes() {
    deleteAllNodesHelper(root);
}
template<typename T>
bool BST<T>::search(T* data) {
    if (root != nullptr)
    {
        BSTNode<T>* current = root;
        while (current != nullptr)
        {
            if (*current->getData() < *data)
                current = current->getRightChild();
            else if (*current->getData() > *data)
                current = current->getLeftChild();
            else
                return true;
        }
    }
    return false;
}
template<typename T>
void BST<T>::inOrder(std::ostream& output, BSTNode<T>* node) {
    if (node != nullptr)
    {
        inOrder(output, node->getLeftChild());
        output << *node->getData() << std::endl;
        inOrder(output, node->getRightChild());
    }
}

int indentCt = 0;
template<typename T>
void BST<T>::preOrder(std::ostream& output, BSTNode<T>* node, std::string indent){
    if (node != nullptr)
    {
        output << *node->getData() << std::endl;
        std::string indentLeft = indent;
        if ((node->getLeftChild() != nullptr) )
        {
            indentLeft += '\t';
            output << indent;
        }
        preOrder(output, node->getLeftChild(), indentLeft);
        std::string indentRight = indent;
        if ((node->getRightChild() != nullptr))
        {
            indentRight += '\t';
            output << indent;
        }
        preOrder(output, node->getRightChild(), indentRight);
    }
}
template<typename T>
void BST<T>::postOrder(std::ostream& output, BSTNode<T>* node) {
    if (node != nullptr)
    {
        postOrder(output, node->getLeftChild());
        postOrder(output, node->getRightChild());
        output << *node->getData() << std::endl;
    }
}
template<typename T>
void BST<T>::setAllNullptr(BSTNode<T>* node) {
    if (node != nullptr)
    {
        setAllNullptr(node->getLeftChild());
        setAllNullptr(node->getRightChild());
        node->setData(nullptr);
    }
}

template<typename T>
void BST<T>::deleteSetNull(T* data)
{
    if (root != nullptr)
    {
        BSTNode<T>* curParent = nullptr;
        BSTNode<T>* current = root;
        while (current != nullptr)
        {
            if (*(current->getData()) < *data)
            {
                curParent = current;
                current = current->getRightChild();
            }
            else if (*(current->getData()) > * data)
            {
                curParent = current;
                current = current->getLeftChild();
            }
            else
                break;
        }
        if (current == nullptr)
            return;
        if (current->getLeftChild() == nullptr)
        {
            if (curParent != nullptr)
            {
                if (*curParent->getData() < *current->getData())
                    curParent->setRightChild(current->getRightChild());
                else
                    curParent->setLeftChild(current->getRightChild());
                std::cout << current->getData() << std::endl;
                current->getData() = nullptr;
                delete current;
                size--;
            }
            else
            {
                BSTNode<T>* oldRoot = root;
                root = root->getRightChild();
                oldRoot->getData() = nullptr;
                delete oldRoot;
                size--;
            }
        }
        else
        {
            BSTNode<T>* max = current->getLeftChild();
            BSTNode<T>* maxParent = current;
            while (max->getRightChild())
            {
                maxParent = max;
                max = max->getRightChild();
            }
            current->setData(max->getData());
            if (*max->getData() > * maxParent->getData())
                maxParent->setRightChild(max->getLeftChild());
            else
                maxParent->setLeftChild(max->getLeftChild());
            max->getData() = nullptr;
            delete max;
            size--;
        }
    }
}

template<typename T>
void BST<T>::breadthFirst(std::ostream& output, BSTNode<T>* node){
    Queue<BSTNode<T>*> queue;
    while (node != nullptr)
    {
        output << *node->getData() << std::endl;
        if (node->getLeftChild())
            queue.enqueue(node->getLeftChild());
        if (node->getRightChild())
            queue.enqueue(node->getRightChild());
        if (queue.peekFront() != nullptr)
        {
            node = queue.peekFront();
            queue.dequeue();
        }
        else
            node = nullptr;
    }
}

template<typename T>
void BST<T>::empty() {
    while (!isEmpty())
        remove(root->getData());
}

template<typename T>
void BST<T>::print(std::ostream& output) {
    output <<"Breadth-first traversal: "<< std::endl;
    breadthFirst(output, root);
    output << std::endl;
    output << "Pre-order traversal: " << std::endl;
    preOrder(output, root,"\t");
    output << std::endl;
    output << "In-order traversal: " << std::endl;
    inOrder(output, root);
    output << std::endl;
    output << "Post-order traversal: " << std::endl;
    postOrder(output, root);
    output << std::endl;
}

#endif // !BST_H

