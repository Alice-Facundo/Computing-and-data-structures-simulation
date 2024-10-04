#include "FCFS.h"
#include "Node.h"

template <typename T>
Fifo<T>::Fifo() : m_first(nullptr), m_last(nullptr), m_size(0) {}

template <typename T>
unsigned Fifo<T>::size() const {
    return m_size;
}

template <typename T>
bool Fifo<T>::empty() const {
    return m_size == 0;
}

template <typename T>
void Fifo<T>::push(const T& elem) {
    Node<T>* newNode = new Node<T>(elem);
    if (m_last) {
        m_last->next = newNode;
        m_last = newNode;
    } else {
        m_first = m_last = newNode;
    }
    m_size++;
}

template <typename T>
void Fifo<T>::pop() {
    if (empty()) {
        throw std::runtime_error("Fifo is empty");
    }
    Node<T>* temp = m_first;
    m_first = m_first->next;
    delete temp;
    m_size--;
    if (m_size == 0) {
        m_last = nullptr;
    }
}

template <typename T>
T& Fifo<T>::front() {
    if (empty()) {
        throw std::runtime_error("Fifo is empty");
    }
    return m_first->data;
}

template <typename T>
const T& Fifo<T>::front() const {
    if (empty()) {
        throw std::runtime_error("Fifo is empty");
    }
    return m_first->data;
}

template <typename T>
T& Fifo<T>::back() {
    if (empty()) {
        throw std::runtime_error("Fifo is empty");
    }
    return m_last->data;
}

template <typename T>
const T& Fifo<T>::back() const {
    if (empty()) {
        throw std::runtime_error("Fifo is empty");
    }
    return m_last->data;
}

template <typename T>
Fifo<T>::~Fifo() {
    while (!empty()) {
        pop();
    }
}

template <typename T>
Fifo<T>& Fifo<T>::operator=(const Fifo& other) {
    if (this == &other) {
        return *this;
    }

    clear();
    for (Iterator it = other.begin(); it != other.end(); ++it) {
        push(*it);
    }

    return *this;
}

template <typename T>
Fifo<T>::Fifo(const Fifo& other) {
    m_first = m_last = nullptr;
    m_size = 0;
    *this = other;
}

template <typename T>
Fifo<T>::Iterator::Iterator(Node<T>* node) : current(node) {}

template <typename T>
T& Fifo<T>::Iterator::operator*() {
    return current->data;
}

template <typename T>
typename Fifo<T>::Iterator& Fifo<T>::Iterator::operator++() {
    current = current->next;
    return *this;
}

template <typename T>
bool Fifo<T>::Iterator::operator!=(const typename Fifo<T>::Iterator& other) const {
    return current != other.current;
}

template <typename T>
typename Fifo<T>::Iterator Fifo<T>::begin() {
    return Iterator(m_first);
}

template <typename T>
typename Fifo<T>::Iterator Fifo<T>::end() {
    return Iterator(nullptr);
}

template <typename T>
void Fifo<T>::clear() {
    while (m_size > 0) {
        pop();
    }
}
