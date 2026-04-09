#ifndef LUNG__LINKEDLISTFUNCTIONSTEMPLATED_H
#define LUNG__LINKEDLISTFUNCTIONSTEMPLATED_H
#include <iostream>
#include "../../includes/node/node.h"
#include <assert.h>

using namespace std;

template <typename T>
void _print_list(node<T>* head);

//recursive fun! :)
template <typename T>
void _print_list_backwards(node<T> *head);

//return ptr to key or NULL
template <typename T>
node<T>* _search_list(node<T>* head, T key);

template <typename T>
node<T>* _insert_head(node<T> *&head, T insert_this);

//insert after ptr: insert head if marker null
template <typename T>
node<T>* _insert_after(node<T>*& head, node<T> *after_this, T insert_this);

//insert before ptr: insert head if marker null
template <typename T>
node<T>* _insert_before(node<T>*& head, node<T>* before_this, T insert_this);

//ptr to previous node
template <typename T>
node<T>* _previous_node(node<T>* prev_to_this);

//delete, return item
template <typename T>
T _delete_node(node<T>*& head, node<T>* delete_this);

//duplicate the list...
template <typename T>
node<T>* _copy_list(node<T>* head);

//duplicate the list, return pointer to last node in dest... 
//     use this function in your queue big three 
template <typename T>
node<T> *_copy_list(node<T> *&dest, node<T> *src);

//delete all the nodes
template <typename T>
void _clear_list(node<T>*& head);

//_item at this position
template <typename T>
T& _at(node<T>* head, int pos);


template<typename T>
void _print_list(node<T>* head){
    node<T>* w = head;
    cout << "Head->";
    if(w == nullptr){
        cout << "NULL\n";
        return;
    }
    while(w != nullptr){
        cout << *w;
        w = w->_next;
    }
    cout << "|||\n";
}

template <typename T>
node<T>* _search_list(node<T>* head, T key){
    assert(head != nullptr);
    node<T>* w = head;
    while(w != nullptr){
        if(w->_item == key){
            return w;
        }
        w = w->_next;
    }
    return nullptr;
}

template <typename T>
node<T>* _insert_head(node<T> *&head, T insert_this){
    node<T> *_newone = new node<T>(insert_this);
    if(head == nullptr){
        head = _newone;
        return _newone;
    } else{
        _newone->_next = head;
        head->_prev = _newone;
        head = _newone;
        return _newone;
    }
    
}

template <typename T>
node<T>* _insert_after(node<T>*& head, node<T> *after_this, T insert_this){
    if(head == nullptr){
        return _insert_head(head, insert_this);
    }
    node<T> *_newone = new node<T>(insert_this, after_this->_next, after_this);
    after_this->_next = _newone;
    if(after_this->_next != nullptr){
        after_this->_next->_prev = _newone;
    }
    return _newone;
}

template <typename T>
node<T>* _insert_before(node<T>*& head, node<T>* before_this, T insert_this){
    if(head == nullptr){
        return _insert_head(head, insert_this);
    }
    return _insert_after(head, before_this->_prev, insert_this);
}

template <typename T>
node<T>* _previous_node(node<T>* prev_to_this){
    assert(prev_to_this != nullptr);
    return prev_to_this->_prev;
}

template <typename T>
T _delete_node(node<T>*& head, node<T>* delete_this){
    assert(delete_this && "remove(): marker for remove() cannot be null.");
    T item_removed = delete_this->_item;
    if(head == delete_this){
        delete_this->_next->_prev == nullptr;
        head = delete_this->_next;
        delete delete_this;
        return item_removed;
    } else{
        if(delete_this->_next != nullptr){
            delete_this->_next->_prev = delete_this->_prev;
        }
        delete_this->_prev->_next = delete_this->_next;
        delete delete_this;
        return item_removed;
    }
}

template <typename T>
node<T>* _copy_list(node<T>* head){
    node<T>* copy = nullptr;
    _copy_list(copy, head);
    return copy;
}

template <typename T>
node<T> *_copy_list(node<T> *&dest, node<T> *src){
    // assert(src != nullptr && "Cannot copy an empty list.(Linked list is empty)");
    node<T>* srcwalker = src;
    node<T>* destwalker = dest;
    while(srcwalker){
        destwalker = _insert_after(dest, destwalker, srcwalker->_item);
        srcwalker = srcwalker->_next;
    }
    return destwalker;
}

template <typename T>
void _clear_list(node<T>*& head){
    while(head != nullptr){
        _delete_node(head, head);
    }
}

template <typename T>
T& _at(node<T>* head, int pos){
    node<T>* walker = head;
    for(int i = 0; i < pos; i++){
        walker = walker->_next;
    }
    return walker->_item;
}

#endif