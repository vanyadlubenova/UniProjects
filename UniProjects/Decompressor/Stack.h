#ifndef STACK_H
#define STACK_H
#include "Node.h"

template <class T>
class Stack
{
    Node<T>* tos;
    public:
        Stack():tos(NULL){};
        Stack(const Stack<T>& other)
        {
            tos = copy(other.tos);
        }
        Stack<T>& operator=(const Stack<T>& other)
        {
            if(this != &other)
            {
                clear(tos);
                tos = copy(other.tos);
            }

            return *this;
        }
        bool isEmpty() const
        {
            return !tos;
        }
        const T& top() const
        {
            return tos->data;
        }
        T pop()
        {
            Node<T>* n = tos;
            tos = tos->next;
            T data = n->data;
            delete n;
            return data;
        }
        void push(const T& data)
        {
            Node<T>* n = new Node<T>(data, tos);
            tos = n;
        }
    private:
        Node<T>* copy(Node<T>* n)
    {
        if(!n)
        {
            return NULL;
        }
        Node<T>* un = copy(n->next);
        try{
            Node<T>* ts = new Node<T>(n->data, un);
            return ts;
        }catch(std::bad_alloc)
        {
            clear(un);
            throw;
        }

            return NULL;

        }
        void clear(Node<T>* n)
        {
            if(!n)
            {
                return;
            }
            clear(n->next);
            delete n;
        }

};

#endif // STACK_H
