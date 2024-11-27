#ifndef MYQUEUE_H
#define MYQUEUE_H
#include <iostream>
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
        Iterator(node<T>* p){
            _ptr = p;
        }                            //Point Iterator to where
                                                          //  p is pointing to
        T operator *(){
            return _ptr->_item;
        }    //dereference operator
        bool is_null(){
            return (_ptr == NULL|| _ptr == nullptr);
        }            //true if _ptr is NULL
        friend bool operator !=(const Iterator& left, const Iterator& right)  //true if left != right
        {
            return(left._ptr != right._ptr);
        }

        friend bool operator ==(const Iterator& left,
                                const Iterator& right)  //true if left == right
        {
            return(left._ptr == right._ptr);
        }


        Iterator& operator++(){                         //member operator ++it // or ++it = new_value
            _ptr = _ptr->_next;
            return Iterator(_ptr);
        }

        friend Iterator operator++(Iterator& it, int unused){         //friend operator: it++
            it._ptr= it._ptr->_next;
            return it;
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

    Iterator begin() const;                                     //Iterator to the head node
    Iterator end() const;                                       //Iterator to NULL
    void print_pointers();
    int size() const { return _size; }
    template<typename TT>
    friend ostream& operator << (ostream& outs, const Queue<TT>& printMe);
private:
    node<T>* _front;
    node<T>* _rear;
    int _size;
};


//----------------------------------------------------------------------------//
template <typename T>
Queue<T>::Queue(){
    _front = nullptr;
    _rear = nullptr;
    _size= 0;
}

template <typename T>
Queue<T>::Queue(const Queue<T>& copyMe){
  _size = copyMe._size;
  _front = nullptr;
  _rear = _copy_list(_front,copyMe._front);
}

template <typename T>
Queue<T>::~Queue(){
    if(_front != nullptr){
        _clear_list(_front);
    }
    _rear = nullptr;
    _size = 0;
}

template <typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& RHS){
    if(_front == RHS._front){
        return *this;
    }
    _size = RHS._size;
    
    if(_front != nullptr){
        _clear_list(_front);
    }
    _rear = _copy_list(_front,RHS._front);
    return *this;
}

template <typename T>
bool Queue<T>::empty(){
    return (_front==nullptr);
}

template <typename T>
T Queue<T>::front(){
    return (_front->_item);
}

template <typename T>
T Queue<T>::back(){
    return(_rear->_item);
}

template <typename T>
void Queue<T>::push(T item){
   _rear = _insert_after(_front,_rear,item);
    if(_rear != nullptr){
    _size++;
    }
}

template <typename T>
T Queue<T>::pop(){
    T value = _delete_node(_front,_front);
    _size--;
    return value;
}

template <typename T>
typename Queue<T>::Iterator Queue<T>::begin() const{
    Queue<T>::Iterator p(_front);
    return p;
}   //Iterator to the head node

template <typename T>
typename Queue<T>::Iterator Queue<T>::end() const{
    Queue<T>::Iterator p(nullptr);
    return p;
}                                     //Iterator to NULL

template <typename T>
void Queue<T>::print_pointers(){
    _print_list(_front);
}

template <typename TT>
ostream& operator << (ostream& outs, const Queue<TT>& printMe){
    _print_list(printMe._front);
    return outs;
}
#endif