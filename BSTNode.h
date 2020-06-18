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
    ~BSTNode();
    /*
    Return data of the BSTNode
    Pre: None
    Post: None
    return: T object
    */
    T getData(bool isHouse) {
        if (isHouse) {
            if (data != nullptr)
                return data->getPrice();
        } else {
            if (data != nullptr)
                return data;
            return nullptr;
        }
    }
    T* getData() {
        if (data != nullptr)
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

template<class T>
BSTNode<T>::~BSTNode() {
    data = nullptr;
    leftChild = nullptr;
    rightChild = nullptr;
}

#endif // !BSTNODE_H



/*
Nguyen Nhat Cong Le

lab number: final project
authors: Kevin Jin, Lance Carrido, Jaymen Luther, Nguyen Nhat Cong Le
description: The project is a house listing service providing the address, price, beds, baths, type, and area of houses in San Jose, with options to filter by address and price.
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
    ~BSTNode();
    
    /*
    Return data of the BSTNode.
    Pre: None
    Post: None
    return: T object
    */
    T* BSTNode()::getData();
    
    /*
    Return data of the BSTNode, such as price.
    Pre: None
    Post: None
    return: T object
    */
    T getData(bool isHouse);
    
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
    void setLeftChild(BSTNode<T>* left) {
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
    void setRightChild(BSTNode<T>* right) {
        rightChild = right;
    }
};

template<class T>
BSTNode<T>::~BSTNode() {
    data = nullptr;
    leftChild = nullptr;
    rightChild = nullptr;
}

template<class T>
T BSTNode<T>::getData(bool isHouse) {
    if (isHouse) {
        if (data != nullptr)
            return data->getPrice();
    } else {
        if (data != nullptr)
            return data;
        return nullptr;
    }
}

template<class T>
T* BSTNode()::getData() {
    if (data != nullptr)
        return data;
    return nullptr;
}

#endif // !BSTNODE_H

