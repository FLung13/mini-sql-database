#ifndef QUEUE_LUNG_H__
#define QUEUE_LUNG_H__
#include "../../includes/linked_list_functions/linkedlistfunctionsTemplated.h"
using namespace std;

template <typename T>
class Queue
{
public:
    class Iterator{
    public:
        friend class Queue;                               //give access to list to access _ptr
        Iterator(){_ptr = NULL;}                          //default ctor
        Iterator(node<T>* p){_ptr = p;}                            //Point Iterator to where
                                                          //  p is pointing to
        T operator *(){
            assert(_ptr && "Iterator: attempted to dereference nullptr");
            return _ptr->_item;
        }    //dereference operator
        bool is_null(){
            if (_ptr == nullptr)
            {
                return true;
            }
            return false;
            
        }            //true if _ptr is NULL
        friend bool operator !=(const Iterator& left, const Iterator& right){  //true if left != right
            if(left._ptr != right._ptr){
                return true;
            }
            return false;
        }

        friend bool operator ==(const Iterator& left, const Iterator& right){  //true if left == right
              if(left._ptr == right._ptr){
                return true;
            }
            return false;      
        }

        Iterator& operator++(){                         //member operator:++it
                                                        // or ++it = new_value
            _ptr = _ptr->_next;
            return *this;
        }

        friend Iterator operator++(Iterator& it,
                                   int unused){         //friend operator: it++
            Iterator holder = it;
            it._ptr = it._ptr->_next;
            return holder;
        }

    private:
        node<T>* _ptr;                          //pointer being encapsulated
    };

    Queue();

    Queue(const Queue<T>& copyMe);
    ~Queue();
    Queue& operator=(const Queue<T>& RHS);

    bool empty();
    T front();
    T back();

    void push(T item);
    T pop();

    Iterator begin() const {return Iterator(_front);}                    //Iterator to the head node
    Iterator end() const {return Iterator();}                            //Iterator to NULL
    void print_pointers();
    int size() const { return _size; }
    friend ostream& operator << (ostream& outs, const Queue<T>& printMe){
        outs << "Queue:";
        _print_list(printMe._front);
        return outs;
    }
private:
    node<T>* _front;
    node<T>* _rear;
    int _size;
};

template<typename T>
Queue<T>::Queue(){
    _front = nullptr;
    _rear = nullptr;
    _size = 0;
}

template<typename T>
Queue<T>::Queue(const Queue<T> &copyMe){
    _front = nullptr;
    _size = copyMe._size;
    _rear = _copy_list(_front, copyMe._front);
}

template<typename T>
Queue<T>::~Queue(){
    _rear = nullptr;
    _clear_list(_front);
}

template<typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& RHS){
    if(this == &RHS){
        return *this;
    }
    _clear_list(_front);
    delete _front;
    _front = nullptr;
    _rear = _copy_list(_front, RHS._front);
    _size = RHS._size;
    return *this;
}

template<typename T>
bool Queue<T>::empty(){
    if (!_front)
    {
        return true;
    }
    return false;
}

template<typename T>
T Queue<T>::front(){
    assert(_front && "Queue is empty\n");
    return _front->_item;
}

template<typename T>
T Queue<T>::back(){
    assert(_front && "Queue is empty\n");
    return _rear->_item;
}

template<typename T>
void Queue<T>::push(T item){
    _size++;
    _rear = _insert_after(_front,_rear,item);
}

template<typename T>
T Queue<T>::pop(){
    _size--;
    T asd = _delete_node(_front,_front);
    if(!_front){
        _rear = nullptr;
    }
    if(_size == 1){
        _rear = _front;
    }
    return asd;
}

template<typename T>
void Queue<T>::print_pointers(){
    return;
}

#endif