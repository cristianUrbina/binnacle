#ifndef Node_H
#define Node_H

/**
* A class template. It performs the tasks of being the container of LinkedList class
*/
template<typename T>
class Node{
  public:
    T content;
    Node<T> * prevboy; /**< this is a pointer to the prevoius element*/
    Node<T> * nextboy; /**< this is a pointer to the next element*/
    explicit Node(const T& data);
};

/** A constructor. It inizializes pointers with nullptr and content with the data value
* @param data an argument used for initilizing the content attribute
*/
template<typename T>
Node<T>::Node(const T& data):content(data),prevboy(nullptr),nextboy(nullptr){}
#endif
