#ifndef MYSTACK_H
#define MYSTACK_H
#include <iostream>
#include "../../includes/linked_list_functions/linkedlistfunctionsTemplated.h"

using namespace std;
template <typename ITEM_TYPE>
class Stack{
public:
    class Iterator{
    public:
        friend class Stack;                 //give access to list to access _ptr
        Iterator(){_ptr = NULL;}            //default ctor
        Iterator(node<ITEM_TYPE>* p){
            _ptr = p;
        }      //Point Iterator to where
                                            //  p is pointing to
        ITEM_TYPE operator *(){
            return _ptr->_item;
        }    //dereference operator
        bool is_null(){return (_ptr == NULL || _ptr == nullptr);}            //true if _ptr is NULL
        friend bool operator !=(const Iterator& left, const Iterator& right)  //true if left != right
        {return left._ptr != right._ptr;}

        friend bool operator ==(const Iterator& left,const Iterator& right)  //true if left == right
        {return left._ptr == right._ptr;}


        Iterator& operator++(){                        //member operator ++it // or ++it =new_value
            assert(_ptr!= NULL);
            _ptr=_ptr->_next;
            return _ptr;
        }

        friend Iterator operator++(Iterator& it,
                                   int unused){        //friend operator: it++
            assert(it._ptr!=NULL);
            it._ptr = it._ptr->_next;
            return it;
        }

    private:
        node<ITEM_TYPE>* _ptr;    //pointer being encapsulated
    };

    Stack();
    Stack(const Stack<ITEM_TYPE>& copyMe);
    ~Stack();
    Stack<ITEM_TYPE>& operator=(const Stack<ITEM_TYPE>& RHS);
    ITEM_TYPE top();
    bool empty();
    void push(ITEM_TYPE item);
    ITEM_TYPE pop();
    template<typename T>
    friend ostream& operator<<(ostream& outs, const Stack<T>& printMe);
    Iterator begin() const;                   //Iterator to the head node
    Iterator end() const;                     //Iterator to NULL
    int size() const { return _size; }

private:
    node<ITEM_TYPE>* _top;
    int _size;
};

//----------------------------------------------------------------------------------------------------------------------------------------------------//
template<typename ITEM_TYPE>
Stack<ITEM_TYPE>::Stack(){
    _top = nullptr;
    _size = 0;
}
template<typename ITEM_TYPE>
Stack<ITEM_TYPE>::Stack(const Stack<ITEM_TYPE>& copyMe){
    _size = copyMe._size;
    _top = _copy_list(copyMe._top);
}
template<typename ITEM_TYPE>
Stack<ITEM_TYPE>::~Stack(){
    if(_top != nullptr){
        _clear_list(_top);
    }
    _size = 0;
}
template<typename ITEM_TYPE>
Stack<ITEM_TYPE>& Stack<ITEM_TYPE>::operator=(const Stack<ITEM_TYPE>& RHS){
    if(RHS._top == _top){
        return *this;
    }

    _size = RHS._size;
    if(_top != nullptr){
        _clear_list(_top);
    }

    _top = _copy_list(RHS._top);
    return *this;
}
template<typename ITEM_TYPE>
ITEM_TYPE Stack<ITEM_TYPE>::top(){
    return _top->_item;
}
template<typename ITEM_TYPE>
bool Stack<ITEM_TYPE>::empty(){
    return (_top == nullptr);
}
template<typename ITEM_TYPE>
void Stack<ITEM_TYPE>::push(ITEM_TYPE item){
   _top = _insert_head(_top,item);
   if(_top != nullptr){
    _size++;
   }
}
template<typename ITEM_TYPE>
ITEM_TYPE Stack<ITEM_TYPE>::pop(){
   ITEM_TYPE value = _delete_node(_top,_top);
   _size--;
    return value;
}

template<typename T>
ostream& operator<<(ostream& outs, const Stack<T>& printMe){
    cout << "Stack:";
    _print_list(printMe._top);
    return outs;
}
template<typename ITEM_TYPE>
typename Stack<ITEM_TYPE>::Iterator Stack<ITEM_TYPE>::begin() const{
    Iterator p(_top);
    return p;
}
                   //Iterator to the head node
template <typename ITEM_TYPE>
typename Stack<ITEM_TYPE>::Iterator Stack<ITEM_TYPE>::end() const{
    Iterator p(nullptr);
    return p;
}
                     //Iterator to NULL

#endif