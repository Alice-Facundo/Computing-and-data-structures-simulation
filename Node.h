#ifndef NODE_H
#define NODE_H
#include <iostream>

template <typename T>
class Fifo;

template <typename T>
class Iterator;

template <typename T>
class LinkedList;

template <typename T>
class Node {
    friend class Fifo<T>;
    friend class Iterator<T>;
    friend class LinkedList<T>;

    T data;     // valor guardado no nó
    Node<T>* next;  // ponteiro para o próximo nó

    Node(const T& val, Node<T>* ptrNext) : data(val), next(ptrNext) {}

    ~Node() {
        std::cout << "node " << data << " foi liberado" << std::endl;
    }
};

#endif
