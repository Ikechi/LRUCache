#include "DLList.h"
#include <iostream>
#include <cstdio>

template<class T>
Node<T>::Node(){
    next = nullptr;
    prev = nullptr;
}

template<class T>
Node<T>::Node(T val){
    setValue(val);
    next = nullptr;
    prev = nullptr;
}

template<class T>
Node<T>::~Node(){
    delete next;
    delete prev;
}

template<class T>
void Node<T>::setValue(T val){
    value = val;
}

template<class T>
T Node<T>::getValue(){
    return value;
}

template<class T>
bool Node<T>::hasNext(){
    return next != nullptr;
}

template<class T>
bool Node<T>::hasPrev(){
    return prev != nullptr;
}

template<class T>
DLList<T>::DLList(){
    head = new Node<T>();
    tail = new Node<T>();
    head->next = tail;
    tail->prev = head;
    _size = 0;
}

template<class T>
DLList<T>::~DLList(){
    while(!empty()){
        popFront();
    }
    head->next = tail->prev = nullptr;
    delete head;
    delete tail;
}

template<class T>
Node<T>* DLList<T>::insert(const T &val, Node<T> *node){
    Node<T> * temp = nullptr;
    if(node == 0){
        //std::cout << "Should be added right after head\n";
        pushFront(val);
        return head->next;
    }
    else{
        //std::cout << "now here\n";
        temp = new Node<T>(val);
        temp->next = node;
        temp->prev = node->prev;
        node->prev->next = node->prev = temp;
    }
    _size++;
    return temp;
}

template<class T>
void DLList<T>::printList(){
    Node<T> *current = head->next;
    while(current != tail){
        std::cout << current->value << " ";
        current = current->next;
    }
    std::cout << std::endl;
    //std::cout << "Size is now " << _size << std::endl;
}

template<class T>
void DLList<T>::printListwithAddr(){
    Node<T> *current = head->next;
    while(current != tail){
        std::cout << current->value << "\t" << current << "\n";
        current = current->next;
    }
    std::cout << std::endl;
    //std::cout << "Size is now " << _size << std::endl;
}

template<class T>
T DLList<T>::deleteNode(Node<T> * node){
    T node_value = node->getValue();
    Node<T> *front = node->prev;
    Node<T> *back = node->next;
    front->next = back;
    back->prev = front;

    _size--;
    node->prev = node->next = 0;
    //std::cout << "pointers of node to be deleted:   " << node->prev << "\t" << node << "\t" << node->next << std::endl;
    delete node;//remember to free memory
    return node_value;
}


template<class T>
T DLList<T>::remove(const T &val){
    Node<T> *temp = head;
    while(temp->value != val && temp){
        temp = temp->next;
    }
    if(temp != nullptr)
        T result = deleteNode(temp);
}

template<class T>
int DLList<T>::size(){
    return _size;
}

template <class T>
bool DLList<T>::empty(){
    return _size == 0;
}

template<class T>
struct pair<bool, T> DLList<T>::getElementAt(int i){
    struct pair<bool, T> result;
    /*make sure index is within bounds...if out of bounds, result.first = false,
    if within bounds, result.first = true & result.second = element at index*/
    if(i > _size - 1){
        result.first = false;
        return result;
    }
    result.first = true;
    Node<T> *temp = head->next;
    for(int i = 0; i < i; ++i)
        temp = temp->next;
    result.second = temp->getValue();
    return result; 
}

template<class T>
Node<T>* DLList<T>::getElementAddr(T elem){
    if(empty()){
        std::cout << "List is empty\n";
        return nullptr;
    }
    bool found = false;
    Node<T> *temp = head->next;
    while(temp != tail){
        if(temp->getValue() == elem){
            found = true;
            break;
        }
        temp = temp->next;
    }
    if(found){
        return temp;
    }
    else{
        std::cout << "Element not in list\n";
        return nullptr;
    }
}

template<class T>
T DLList<T>::getFront(){
    if(empty()){
        std::cout << "Empty List\n";
        return -1;
    }
    return head->next->getValue();
}

template<class T>
T DLList<T>::getBack(){
    if(empty()){
        std::cout << "Empty List\n";
    }
    return tail->prev->getValue();
}

template<class T>
void DLList<T>::pushFront(const T &val){
    insert(val, head->next);
}


template<class T>
void DLList<T>::pushBack(const T &val){
    insert(val, tail);
}

template<class T>
T DLList<T>::popFront(){
    return deleteNode(head->next);
}

template<class T>
T DLList<T>::popBack(){
    return deleteNode(tail->prev);
}

/*
int main(){
    Node<int>p;
    p.setValue(5);
    printf("%d\t%d\t%d\n\n",p.getValue(),p.hasNext(), p.hasPrev());

    DLList<int> *list = new DLList<int>(), list2;
    list->insert(6);
    list->insert(65);
    Node<int> * res = list->insert(16);
    list->printList();
    std::cout << res->getValue() << std::endl;
    list->remove(16);
    list->printList();
    std::cout << "list size & empty? :\t" << list->size() << " \t" << list->empty() << std::endl;  

    std::cout << list->getElementAt(2).first << " " << list->getElementAt(0).first << " " << list->getElementAt(0).second <<std::endl;

    list->insert(60);
    list->insert(73);
    list->printList();

    std::cout << list2.getFront() << " " << list->getFront() << std::endl;

    std::cout << list2.getBack() << " " << list->getBack() << std::endl;

    list->pushBack(10);
    list->pushFront(2);

    list->printList();
    std::cout << "List size:\t" << list->size() << std::endl;

    list->popFront();
    list->popBack();
    list->printList();

    std::cout << "List size:\t" << list->size() << std::endl;
}*/
