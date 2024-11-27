#ifndef LINKEDLISTTEMPLATED_H
#define LINKEDLISTTEMPLATED_H
#include <iostream>
#include "../../includes/node/node.h"
#include "assert.h"
using namespace std;

//Linked List General Functions:
template <typename T>
void _print_list(node<T>* head);

//recursive fun! :)
template <typename T>
void _print_list_backwards(node<T> *head);

//return ptr to key or NULL
template <typename T>
node<T>* _search_list(node<T>* head,
                            T key);


template <typename T>
node<T>* _insert_head(node<T> *&head,
                            T insert_this);

//insert after ptr: insert head if marker null
template <typename T>
node<T>* _insert_after(node<T>*& head,
                                node<T> *after_this,
                                T insert_this);

//insert before ptr: insert head if marker null
template <typename T>
node<T>* _insert_before(node<T>*& head,
                                node<T>* before_this,
                                T insert_this);

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



//------------------------------------------------------------------------------------------//

template <typename T>
void _print_list(node<T>* head){
  node<T>* w = head;
  cout << "Head->";
  int count = 0;
  while(w!= nullptr){
    if(count != 0){
      cout << "<-";
    }
    cout << *w;
    cout << "-> ";
    w=w->_next;
    count++;
  }
  cout << "|||";
  cout << endl;
}

//recursive fun! :)
template <typename T>
void _print_list_backwards(node<T> *head){
  node<T>* w = head;
  while(w->_next != nullptr){
    w=w->_next;
  }
  
  while(w!= nullptr){
    cout << *w;
    if(w->_next != nullptr){
      cout << "->";
    }
    w=w->_prev;
  }
  cout << endl;
}

//return ptr to key or NULL
template <typename T>
node<T>* _search_list(node<T>* head, T key){
  node<T>* w = head;
  while(w!=nullptr){
    if(w->_item==key){
      return w;
    }
    w=w->_next;
  }
  return nullptr;
}


template <typename T>
node<T>* _insert_head(node<T> *&head,T insert_this){
  node<T>* p = new node<T>(insert_this);

  
  p->_next = head;
  head = p;
  p->_prev = nullptr;
  
  if(p->_next!= nullptr){
    node<T>* next_node = p->_next;
    next_node->_prev = p;
  }

  return head;
}

//insert after ptr: insert head if marker null
template <typename T>
node<T>* _insert_after(node<T>*& head, node<T> *after_this,T insert_this){
  bool debug = false;
  if(head==nullptr || after_this==nullptr){
    return _insert_head(head,insert_this);
  }

  // node<T>* w = head;

  // while(w!=nullptr){
  //   if(w==after_this){
  //     node<T>* next_node;
  //     node<T>* p = new node<T>(insert_this);
  //     p->_next = w->_next;
  //     if(after_this->_next != nullptr){
  //       next_node = after_this->_next;
  //       next_node->_prev = p;
  //     }
  //     p->_prev = after_this;
  //     after_this->_next = p;
  //     return p;
  //   }
  //   if(debug){
  //     _print_list(w);
  //   }
  //   w=w->_next;
  // }


  node<T>* p = new node<T>(insert_this);
  p->_next = after_this->_next;
  if(after_this->_next != nullptr){
    node<T>* next_node;
    next_node = after_this->_next;
    next_node->_prev = p;
  }
  p->_prev = after_this;
  after_this->_next = p;
  return p;
  // if(w==nullptr){
  //   assert("after_this was not found in head ptr");
  // }
}

//insert before ptr: insert head if marker null
template <typename T>
node<T>* _insert_before(node<T>*& head, node<T>* before_this, T insert_this){
  if(before_this == nullptr || head == nullptr){
    return _insert_head(head,insert_this);
  }

  node<T>* w = head;

  node<T>* prev_node = before_this->_prev;
  return _insert_after(head,prev_node,insert_this);
}

//ptr to previous node
template <typename T>
node<T>* _previous_node(node<T>* prev_to_this){
  return prev_to_this->_prev; 
}

//delete, return item
template <typename T>
T _delete_node(node<T>*& head, node<T>* delete_this){
  if(delete_this == nullptr){
    cout << "\ndelete_this is a nullptr\n";
    assert(0);
  }
  T item = delete_this->_item;

  node<T>* next_node = delete_this->_next;
  if(delete_this == head){
    head = delete_this->_next; 
    if(head!= nullptr){
      head->_prev = nullptr;
    }
  } else {
    node<T>* prev_node = delete_this->_prev;
    prev_node ->_next = next_node;
    if(next_node != nullptr){
      next_node->_prev = prev_node;
    }
  }
  

  delete delete_this;
  return item;
}

//duplicate the list...
template <typename T>
node<T>* _copy_list(node<T>* head){
  if(head == nullptr){
    return nullptr;
  }
  node<T>* w = head->_next;
  node<T>* list_copied = new node<T> (head->_item);
  node<T>* w_list_copied = list_copied;
  while(w!= nullptr){
    T item = w->_item;
    _insert_after(list_copied,w_list_copied,item);

    w_list_copied=w_list_copied->_next;
    w=w->_next;
  }


  return list_copied;
}

//duplicate the list, return pointer to last node in copied_list... 
//     use this function in your queue big three 
template <typename T>
node<T> *_copy_list(node<T> *&copied_list, node<T> *src){
  if(copied_list != nullptr || copied_list != NULL){
    cout << "\ndestination of copy is a filled list, when it suppose to be a clear list\n";
    assert(0);
  }

  if(src == nullptr){
    copied_list = nullptr;
    return copied_list;
  }

  copied_list = _copy_list(src);
  node<T>* w = copied_list;
  while(w->_next != nullptr){
    w=w->_next;
  }
  return w;
}



//delete all the nodes
template <typename T>
void _clear_list(node<T>*& head){
  node<T>* w = head;
  while(w!= nullptr){
    node<T>* next_node = w->_next;
    _delete_node(head,w);
    w = next_node;
  }
}

//_item at this position
template <typename T>
T& _at(node<T>* head, int pos){
  node<T>* w = head;

  for(int i = 0; i < pos; i++){
    w=w->_next;
  }
  return w->_item;
}
#endif