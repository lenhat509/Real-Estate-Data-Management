/*
lab number: 05
authors: Nguyen Cong Nhat Le, Kevin Jin
description: Implement a BST with the usual operations and four traversal methods, reading Currency objects from an input file with data validation; performed operations will output to both the console and an output file.
*/

#ifndef BSTNODE_H
#define BSTNODE_H

template<typename T>
class BSTNode {
private:
    T* data;
    BSTNode<T>* leftChild;
    BSTNode<T>* rightChild;
public:
    //constructor
    BSTNode() {
        leftChild = nullptr;
        rightChild = nullptr;
    }
    /*
    Return data of the BSTNode
    Pre: None
    Post: None
    return: T object
    */
    T* getData() {
        if(data != nullptr)
            return data;
        return nullptr;
    }
    /*
    Set data of the BSTNode
    Pre: const T& nData
    Post: None
    return: None
    */
    void setData(T* nData)
    {
        data = nData;
    }
    /*
    Return the left child of BSTNode
    Pre: None
    Post: None
    return: BSTNode<T>
    */
    BSTNode<T>* getLeftChild() {
        return leftChild;
    }
    /*
    Set the left child of BSTNode
    Pre: BSTNode<T>* left
    Post: None
    return: None
    */
    void setLeftChild(BSTNode<T>* left)
    {
        leftChild = left;
    }
    /*
    Return the right child of BSTNode
    Pre: None
    Post: None
    return: BSTNode<T>
    */
    BSTNode<T>* getRightChild() {
        return rightChild;
    }
    /*
    Set the right child of BSTNode
    Pre: BSTNode<T>* right
    Post: None
    return: None
    */
    void setRightChild(BSTNode<T>* right)
    {
        rightChild = right;
    }
};
#endif // !BSTNODE_H

