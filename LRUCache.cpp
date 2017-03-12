#include "copyright.h"
#include "LRUCache.h"
#include "DLList.h"
#include <iostream>
#include <unordered_map>

/*initialize the LRUCache and set it's capacity to desired limit
Default capacity is 10*/
template<class T>
LRUCache<T>::LRUCache(int num){
    capacity = num;
    _size = 0;
    //cache_list = new DLList<T>();
}

template<class T>
LRUCache<T>::LRUCache(){
    capacity = 10;
    _size = 0;
    //cache_list = new DLList<T>();
}

/*Destructor for LRUCache...hey! always clean up after yourself*/
template<class T>
LRUCache<T>::~LRUCache(){
    clearCache();
}

/*Add element to cache...add it to map and append it to the front of the Doubly Linked List
If capacity is reached, remove the least recently used Element (Element at back of Doubly Linked List) 
before adding the new element
Return true if operation was successful*/
template<class T>
bool LRUCache<T>::add(const T &elem){
    if(_size == capacity){
        std::cout << "removing LRU Element: " << getLRU() << std::endl;
        cache_map.erase(removeLRU());
    }
    if(cache_map[elem] != nullptr){
        std::cout << "Already exists, but replacing\n" << std::endl;
        cache_list.deleteNode(cache_map[elem]);
        _size--;
    }
    cache_map[elem] = cache_list.insert(elem);
    _size++;
    return true;
}

template<class T>
bool LRUCache<T>::remove(const T &elem){
    if(empty())
        return false;
    if(cache_list.getElementAddr(elem) == nullptr){
        std::cout << "Not in List\n";
        return false;
    }
    cache_map.erase(cache_list.remove(elem));
    _size--;
    return true;
}

template<class T>
void LRUCache<T>::displayCacheList(){
    cache_list.printListwithAddr();
}

template<class T>
void LRUCache<T>::displayCacheMap(){
    typename std::unordered_map<T, Node<T>*> :: iterator it;
    it = cache_map.begin();
    while(it != cache_map.end()){
        std::cout << it->first << "\t" << it->second << std::endl;
        it++;
    }
    std::cout << std::endl;
}

template<class T>
T LRUCache<T>::getLRU(){
    if(empty()){
        std::cout << "Cache is empty\n";
    }
    return cache_list.getBack();
}

template<class T>
T LRUCache<T>::removeLRU(){
    if(empty()){
        std::cout << "Cache is empty\n";
    }
    T result = cache_list.getBack();
    cache_map.erase(cache_list.popBack());
    _size--;
    return result;
}

template<class T>
bool LRUCache<T>::setCapacity(const int num){
    if(num < size()){
        std::cout << "cannot set capacity lower than current Cache size\n";
        std::cout << "Use \"resizeCache\" to force resize\n";
        return false;
    }
}

template<class T>
bool LRUCache<T>::empty(){
    if(cache_map.size() == cache_list.size() == 0){
        return true;
    }
    return false;
}

template<class T>
bool LRUCache<T>::verifyCacheMapping(){
    std::cout << "\t|| cache map verification ||\t\n";
    typename std::unordered_map<T, Node<T>*> :: iterator it;
    it = cache_map.begin();
    bool match = 1;
    while(it != cache_map.end() && match){
        std::cout << it->first << "\t" << it->second << "\t maps to \t";
        std::cout << cache_list.getElementAddr(it->first)->getValue() <<
        "\t" << cache_list.getElementAddr(it->first) << std::endl;
        if(it->second != cache_list.getElementAddr(it->first))
            match = false;
        it++;
    }
    std::cout << "\n";
}

template<class T>
int LRUCache<T>::size(){
    return (cache_list.size() == cache_map.size() ? cache_list.size() : -1);
}

template<class T>
bool LRUCache<T>::resizeCache(const int num){
    while(size() > num)
        removeLRU();
    capacity = num;
    return true;
}

template<class T>
int LRUCache<T>::getCapacity(){
    return capacity;
}

template<class T>
bool LRUCache<T>::clearCache(){
    return resizeCache(0);
}

/*
int main(){
    LRUCache<int> *lru = new LRUCache<int>(10);
}*/
