/*LRU Cache implementation in C++
We want access, search and other operations like adding and removing to and from
the Cache to be as fast as possible...so think O(1)
for this, I used the C++ unordered_map STL container for constant access and search
I didn't use the map STL because the underlying data structure is a tree with offers
logarithmic access, which is fast...but since we don't care about order for the map
since it's values are mapped to a Doubly Linked List which we use for ordering, the 
unordered_map is the better container

The key of the map is the element contained in the cache and the value is a pointer
to a node of a doubly linked list of said elements

We keep track of the Least Recently Used Element in the Cache by adding an element 
to the front of the Doubly Linked List when it's used...this makes removal and
insertion into the DoublyLinked List and this entire structure constant
*/

//more comments coming later

#ifndef LRUCACHE_H
#define LRUCACHE_H

#include <unordered_map>
#include "copyright.h"
#include "DLList.h"

template<class T>
class LRUCache{
public:
    LRUCache();
    LRUCache(int num);
    ~LRUCache();
    bool add(const T &elem);
    bool remove(const T &elem);
    T getLRU();
    T removeLRU();
    bool setCapacity(const int num);
    bool resizeCache(const int num);
    int size();
    int getCapacity();
    void displayCacheList();
    void displayCacheMap();
    bool clearCache();
    bool empty();
    bool verifyCacheMapping();

private:
    int capacity;
    int _size;
    std::unordered_map<T, Node<T>*> cache_map;
    DLList<T> cache_list;
};

#endif