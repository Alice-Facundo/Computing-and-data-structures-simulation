#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <vector>
#include <string>
#include "Node.h"
#include <stdexcept>

template <typename T>
class LinkedList {
private:
    Node<T>* m_head {};
    unsigned m_size {};

public:
    void sort();
    LinkedList();
    LinkedList(const LinkedList& lst);
    bool empty() const;
    int size() const;
    void clear();
    ~LinkedList();
    void print() const;
    void push_front(const T& val);
    T& front();
    const T& front() const;
    void pop_front();
    T& back();
    const T& back() const;
    void push_back(const T& val);
    void pop_back();

    class Iterator {
    private:
        Node<T>* current;

    public:
        Iterator(Node<T>* node);

        T& operator*();

        Iterator& operator++();

        bool operator!=(const Iterator& other) const;
    };

    Iterator begin();

    Iterator end();

};

#endif
