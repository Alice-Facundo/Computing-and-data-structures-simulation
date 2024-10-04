#ifndef FCFS_H
#define FCFS_H
#include "Node.h"
#include <stdexcept>

template <typename T>
class Fifo {
private:
    Node<T>* m_first {};
    Node<T>* m_last {};
    unsigned m_size {};

public:
    Fifo();

    unsigned size() const;

    bool empty() const;

    void push(const T& elem);

    void pop();

    T& front();

    const T& front() const;

    T& back();

    const T& back() const;

    ~Fifo();

    Fifo& operator=(const Fifo& other);

    Fifo(const Fifo& other);

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

    void clear();
};

#endif
