#ifndef DLLIST_H
#define DLLIST_H

#include "copyright.h"

template<class T, class C>
struct pair{
    T first;
    C second;
};

template<class T>
class DLList;

template<class T>
class Node{
public:
    Node();
    Node(T val);
    ~Node();
    void setValue(T val);
    T getValue();
    bool hasNext();
    bool hasPrev();

    friend class DLList<T>;

private:
    T value;
    Node<T> *next;
    Node<T> *prev;
};

template<class T>
class DLList{
public:
    DLList();
    ~DLList();
    Node<T>* insert(const T &val, Node<T> *node = 0);
    T deleteNode(Node<T> *node);
    T remove(const T &val);
    int size();
    bool empty();
    struct pair<bool, T> getElementAt(int i);
    Node<T>* getElementAddr(T elem);
    T getFront();
    T getBack();
    void pushFront(const T &val);
    void pushBack(const T &val);
    T popFront();
    T popBack();
    void printList();
    void printListwithAddr();
private:
    int _size;
    Node<T> *head;
    Node<T> *tail; 
};

#endif