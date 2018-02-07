#ifndef NODE_H
#define NODE_H
#include <iostream>

template <class T>
struct Node
{
    T data;
    Node<T>* next;
    public:
        Node(const T& t, Node<T>* n = NULL):data(t), next(n){};
};

#endif // NODE_H
