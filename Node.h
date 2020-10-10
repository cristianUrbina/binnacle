#ifndef Node_H
#define Node_H

template<typename T>
class Node{
  public:
    T content;
    Node<T> * prevboy; //this is a pointer to the prevoius element
    Node<T> * nextboy; //this is a pointer to the next element
    explicit Node(const T& data);
    //Node(T data, Node *next);
};
template<typename T>
Node<T>::Node(const T& data):content(data),prevboy(nullptr),nextboy(nullptr){}
#endif
