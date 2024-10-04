#include "SJF.h"
#include "Node.h"

template <typename T>
void LinkedList<T>::sort() {
    if (m_head == nullptr || m_head->next == nullptr) {
        return;
    }

    Node<T>* current = m_head;

    while (current != nullptr) {
        Node<T>* min = current;
        Node<T>* next = current->next;

        while (next != nullptr) {
            if (next->data < min->data) {
                min = next;
            }
            next = next->next;
        }

        T temp = current->data;
        current->data = min->data;
        min->data = temp;

        current = current->next;
    }
}

template <typename T>
LinkedList<T>::LinkedList() : m_head(new Node<T>(T{}, nullptr)), m_size(0) {}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList& lst) {
    m_head = new Node<T>(T{}, nullptr);
    m_size = lst.m_size;
    Node<T>* lstCurrent = lst.m_head->next;
    Node<T>* thisLast = m_head;
    while (lstCurrent != nullptr) {
        thisLast->next = new Node<T>(lstCurrent->data, nullptr);
        lstCurrent = lstCurrent->next;
        thisLast = thisLast->next;
    }
}

template <typename T>
bool LinkedList<T>::empty() const {
    return m_head->next == nullptr;
}

template <typename T>
int LinkedList<T>::size() const {
    return m_size;
}

template <typename T>
void LinkedList<T>::clear() {
    while (m_head->next != nullptr) {
        Node<T>* aux = m_head->next;
        m_head->next = aux->next;
        delete aux;
    }
    m_size = 0;
}

template <typename T>
LinkedList<T>::~LinkedList() {
    clear();
    delete m_head;
}

template <typename T>
void LinkedList<T>::print() const {
    Node<T>* temp = m_head->next;
    while (temp != nullptr) {
        std::cout << temp->data << " ";
        temp = temp->next;
    }
    std::cout << '\n';
}

template <typename T>
void LinkedList<T>::push_front(const T& val) {
    Node<T>* newNode = new Node<T>(val, m_head->next);
    m_head->next = newNode;
    m_size++;
}

template <typename T>
T& LinkedList<T>::front() {
    if (empty()) {
        throw std::out_of_range("A lista está vazia.");
    }
    return m_head->next->data;
}

template <typename T>
const T& LinkedList<T>::front() const {
    if (empty()) {
        throw std::out_of_range("A lista está vazia.");
    }
    return m_head->next->data;
}

template <typename T>
void LinkedList<T>::pop_front() {
    if (!empty()) {
        Node<T>* temp = m_head->next;
        m_head->next = temp->next;
        delete temp;
        m_size--;
    }
}

template <typename T>
T& LinkedList<T>::back() {
    if (empty()) {
        throw std::out_of_range("A lista está vazia.");
    }
    Node<T>* temp = m_head->next;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    return temp->data;
}

template <typename T>
const T& LinkedList<T>::back() const {
    if (empty()) {
        throw std::out_of_range("A lista está vazia.");
    }
    Node<T>* temp = m_head->next;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    return temp->data;
}

template <typename T>
void LinkedList<T>::push_back(const T& val) {
    Node<T>* newNode = new Node<T>(val, nullptr);
    Node<T>* temp = m_head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->next = newNode;
    m_size++;
}

template <typename T>
void LinkedList<T>::pop_back() {
    if (!empty()) {
        Node<T>* temp = m_head;
        while (temp->next->next != nullptr) {
            temp = temp->next;
        }
        delete temp->next;
        temp->next = nullptr;
        m_size--;
    }
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList& other) {
    m_head = m_last = nullptr;
    m_size = 0;
    *this = other;
}

template <typename T>
LinkedList<T>::Iterator::Iterator(Node<T>* node) : current(node) {}

template <typename T>
T& LinkedList<T>::Iterator::operator*() {
    return current->data;
}

template <typename T>
typename LinkedList<T>::Iterator& LinkedList<T>::Iterator::operator++() {
    current = current->next;
    return *this;
}

template <typename T>
bool LinkedList<T>::Iterator::operator!=(const typename LinkedList<T>::Iterator& other) const {
    return current != other.current;
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::begin() {
    return Iterator(m_head);
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::end() {
    return Iterator(nullptr);
}


