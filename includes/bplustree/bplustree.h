#ifndef BPLUSTREE_H
#define BPLUSTREE_H

#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <iomanip>
#include "assert.h"
#include "../../includes/bplustree/btree_array_funcs.h"
using namespace std;
template <class T>
class BPlusTree
{
public:
    class Iterator{
    public:
        friend class BPlusTree;
        Iterator(BPlusTree<T>* _it=NULL, int _key_ptr = 0):
                                                it(_it), key_ptr(_key_ptr){
                                            
                                                }

        T operator *(){
          return it->data[key_ptr];
        }

        Iterator operator++(int un_used){
            Iterator copy(it,key_ptr);
            key_ptr++;
            if(key_ptr >= it->data_count){
                key_ptr = 0;
                it=it->next;
            }
            return copy;
        }
        Iterator operator++(){
            key_ptr++;
            if(key_ptr >= it->data_count){
                key_ptr = 0;
                it=it->next;
            }
            
            return *this;
        }
        friend bool operator ==(const Iterator& lhs, const Iterator& rhs){

            if(lhs.it == rhs.it){
                if(lhs.key_ptr == rhs.key_ptr){
                    return true;
                }
                return false;
            }
            else {
                return false;
            }
        //   return (lhs.it == rhs.it);
        }
        friend bool operator !=(const Iterator& lhs, const Iterator& rhs){
          return !(lhs==rhs);
        }
        void print_Iterator(){
            if (it){
                cout<<"iterator: ";
                print_array(it->data, it->data_count, key_ptr);
            }
            else{
                cout<<"iterator: NULL, key_ptr: "<<key_ptr<<endl;
            }
        }
        bool is_null(){return !it;}
        void info(){
            cout<<endl<<"Iterator info:"<<endl;
            cout<<"key_ptr: "<<key_ptr<<endl;
            cout<<"it: "<<*it<<endl;
        }

    private:
        BPlusTree<T>* it;
        int key_ptr;
    };

    BPlusTree(bool dups = false);
    BPlusTree(T *a, int size, bool dups = false);

    //big three:
    BPlusTree(const BPlusTree<T>& other);
    ~BPlusTree();
    BPlusTree<T>& operator =(const BPlusTree<T>& RHS);

    void copy_tree(const BPlusTree<T>& other);  //copy other into this object
    void copy_tree(const BPlusTree<T>& other, BPlusTree<T>*& last_node);

    void insert(const T& entry);   //insert entry into the tree
    void remove(const T& entry);   //remove entry from the tree
    void clear_tree();             //clear this object (delete all nodes etc.)

    bool contains(const T& entry) const; //true if entry can be found
    T& get(const T& entry);              //return a reference to entry
    const T& get(const T& entry) const;   //return a reference to entry
    T& get_existing(const T& entry);     //return a reference to entry
    Iterator find(const T& key);         //return an iterator to this key.
                                         //     NULL if not there.

    Iterator lower_bound(const T& key);  //return first that goes NOT BEFORE
                                         // key entry or next if does not
                                         // exist: >= entry

    Iterator upper_bound(const T& key);  //return first that goes AFTER key
                                         //exist or not, the next entry  >entry
    
    int size() const;                    //count the number of elements

    bool empty() const;                  //true if the tree is empty

    void print_tree(int level = 0,
                    ostream &outs=cout) const;
    friend ostream& operator<<(ostream& outs,
                               const BPlusTree<T>& print_me){
        print_me.print_tree(0, outs);
        return outs;
    }

    bool is_valid();
    string in_order();
    string pre_order();
    string post_order();
    Iterator begin();
    Iterator end();
    ostream& list_keys(Iterator from = NULL, Iterator to = NULL){
        if (from == NULL) from = begin();
        if (to == NULL) to = end();
        for (Iterator it = from; it != to; it++)
            cout<<*it<<" ";
        return cout;

    }

private:
    static const int MINIMUM = 1;
    static const int MAXIMUM = 2 * MINIMUM;

    bool dups_ok;                        //true if duplicate keys are allowed
    int data_count;                      //number of data elements
    T data[MAXIMUM + 1];                 //holds the keys
    int child_count;                     //number of children
    BPlusTree* subset[MAXIMUM + 2];      //subtrees
    BPlusTree* next;
    bool is_leaf() const
    {return child_count==0;}             //true if this is a leaf node

    T* find_ptr(const T& entry);         //return a pointer to this key.
                                         // NULL if not there.

    //insert element functions
    void loose_insert(const T& entry);   //allows MAXIMUM+1 data elements in
                                         //   the root
    void fix_excess(int i);              //fix excess in child i

    //remove element functions:
    void loose_remove(const T& entry);  //allows MINIMUM-1 data elements
                                        //  in the root

    BPlusTree<T>* fix_shortage(int i);  //fix shortage in child i
    // and return the smallest key in this subtree
    BPlusTree<T>* get_smallest_node();
    void get_smallest(T& entry);      //entry := leftmost leaf
    void get_biggest(T& entry);       //entry := rightmost leaf
    void remove_biggest(T& entry);    //remove the biggest child of tree->entry
    void transfer_left(int i);        //transfer one element LEFT from child i
    void transfer_right(int i);       //transfer one element RIGHT from child i
    BPlusTree<T> *merge_with_next_subset(int i); //merge subset i with  i+1

};



//-----------------------------------------------------------------------------------------------------------------------------------------------//

template <class T>
BPlusTree<T>::BPlusTree(bool dups):dups_ok(dups){
    child_count = 0;
    data_count = 0;
    next = NULL;
    for(int i =0; i < MAXIMUM+2; i++){
        subset[i] = nullptr;
    }
}

template <class T>
void BPlusTree<T>::print_tree(int level, ostream &outs) const{
    if(is_leaf() && next!= NULL){
              cout << setw(7* level) << "^" << endl;
    }
    cout << setw(7*level) << "---" << endl;
    // cout << "dc: " << data_count << endl;
    bool debug = false;
    if(is_leaf() != true){
        subset[data_count]->print_tree(level+1,outs);
    }
    for(int i = data_count; i > -1; i--){
        
        if(i < data_count){
            cout << setw(7*level) << data[i];
            if(debug){
                cout << " | cc: " << child_count; 
                cout << " | dc: " << data_count;
            }
            cout << endl;
        }
    
        if(!is_leaf() && i != data_count){
            if(subset[i]){
            subset[i]->print_tree(level+1);
            }
        }
    } 
    cout << setw(7*level) << "---" << endl;
   
}

template <class T>
BPlusTree<T>::BPlusTree(T *a, int size, bool dups): dups_ok(dups){
    child_count = 0;
    data_count = 0;
    for(int i =0; i < MAXIMUM+2; i++){
        subset[i] = nullptr;
    }
    for(int i =0; i < size;i++){
        T* w = a+i;
        insert(*w);
    }
}
//big three:
template <class T>
BPlusTree<T>::BPlusTree(const BPlusTree<T>& other){
    copy_tree(other);
}
template <class T>
BPlusTree<T>::~BPlusTree(){
    if(size() != 0){
        clear_tree();
    }
}
template <class T>
BPlusTree<T>& BPlusTree<T>::operator =(const BPlusTree<T>& RHS){
    bool same = false;
    // for(int i =0; i < RHS.data_count;i++){
    //     if(RHS.data[i] ==data[i]){
            
    //         // cout << "BRUH\n";
    //         // cout << "current: ";
    //         // print_array(data,data_count);
    //         // cout << "right: ";
    //         // print_array(RHS.data,RHS.data_count);
    //         // cout << "here\n";
    //         same = true;
    //     } else if (!(RHS.data[i] == data[i])){
    //         same= false;
    //     }
    // }

    // if(same == true){
    //     return *this;
    // }

    if(this == &RHS){
        return *this;
    }
    if(this->size() != 0){
        this->clear_tree();
    }    

    this->copy_tree(RHS);
    return *this;
}

template <class T>
void BPlusTree<T>::insert(const T& entry){
    loose_insert(entry);
    
    if(data_count > MAXIMUM){
        BPlusTree<T>* copy = new BPlusTree<T>;
        copy_array(copy->data,data,copy->data_count,data_count);
        copy_array(copy->subset,subset,copy->child_count,child_count);
        data_count =0;
        child_count = 1;
        for(int i =0; i < MAXIMUM+2;i++){
            subset[i] = nullptr;
        }
        subset[0] = copy;
        fix_excess(0);
    }
    
    
}
                //insert entry into the tree
template <class T>
void BPlusTree<T>::remove(const T& entry){
    loose_remove(entry);

    if(data_count == 0 && child_count ==1){
        BPlusTree<T>* shrink_ptr = subset[0];
        copy_array(data,shrink_ptr->data,data_count,shrink_ptr->data_count);
        copy_array(subset,shrink_ptr->subset,child_count,shrink_ptr->child_count);
        shrink_ptr->child_count = 0;
        shrink_ptr->data_count =0;
        delete shrink_ptr;
    }
    // cout << *this << endl;
    if(data_count == 0){
        // cout << "sup\n";
        next = NULL;
    }
    return;
}                //remove entry from the tree

template <class T>
void BPlusTree<T>::clear_tree(){
    data_count = 0;
    for(int i =0; i < child_count;i++){
        subset[i]->clear_tree();
        delete subset[i];
    }
    child_count = 0;
    next=NULL;
}                          //clear this object
                                        //  (delete all nodes etc.)
template <class T>
void BPlusTree<T>::copy_tree(const BPlusTree<T>& other){
   BPlusTree<T>* pointer = nullptr;
   copy_tree(other,pointer);
}      //copy other into this object

template <class T>
void BPlusTree<T>::copy_tree(const BPlusTree<T>& other, BPlusTree<T>*& last_node){
    child_count = other.child_count;
    for(int i =0; i<child_count;i++){
        subset[i] = nullptr;
    }


    copy_array(data,other.data,data_count,other.data_count);
    if(is_leaf()){
        if(last_node != nullptr || last_node != NULL){
            last_node->next = this;
        }
        last_node = this;
    }


    if(!other.is_leaf()){
        for(int i =0; i <other.child_count;i++){
            subset[i] = new BPlusTree<T>(dups_ok);
            subset[i]->copy_tree(*(other.subset[i]), last_node);
        }
    }
    
    
}


template <class T>
bool BPlusTree<T>::contains(const T& entry) const{
  int i = first_ge(data, data_count, entry);
  bool found = (i<data_count && data[i]==entry);
  if (is_leaf())
      if (found){
          return true;
      }
      else{
          return false;
      }
  if (found) //inner node
      return subset[i+1]->contains(entry);
      //or just return true?
  else //not found yet...
      return subset[i]->contains(entry);
}              //true if entry can be found in
                                        //                  the array
template <class T>
T& BPlusTree<T>::get(const T& entry){
    if(!contains(entry)){
        insert(entry);
    }
    return get_existing(entry);
}                     //return a reference to entry
                                        //                  in the tree

template <class T>
const T& BPlusTree<T>::get(const T& entry) const{
  return get_existing(entry);
}


template <class T>
T& BPlusTree<T>::get_existing(const T& entry){
  const bool debug = false;
    int i = first_ge(data, data_count, entry);
    bool found = (i<data_count && data[i]==entry);
    if (is_leaf())
        if (found){
            return data[i];
        }
        else{
            if (debug) cout<<"get_existing was called with nonexistent entry"<<endl;
            assert(found);
        }
    if (found) //inner node
        return subset[i+1]->get(entry);
        //or just return true?
    else //not found yet...
        return subset[i]->get(entry);
}


template <class T>
typename BPlusTree<T>::Iterator BPlusTree<T>::find(const T& key){
    int i = first_ge(data,data_count,key); 
    bool found = (i< data_count && data[i] == key);
    if(found && is_leaf()){
        T* bruh= &data[i];
        return BPlusTree<T>::Iterator(this,i);
    }  else if(found && !is_leaf()){
        subset[i+1]->find(key);
    } else if(!found && is_leaf()){
        return BPlusTree<T>::Iterator(NULL,0);
    } else if(!found && !is_leaf()){
      return subset[i]->find(key);
    }
  
}                    //return a pointer to this key.
//          NULL if not there.

template <class T>
typename BPlusTree<T>::Iterator BPlusTree<T>::lower_bound(const T& key){
  for(BPlusTree<T>::Iterator it= begin(); it!= end();++it){
    if(*it > key || *it==key){
      return it;
    }
  }
  return NULL;
}  //return first that goes NOT BEFORE
                                      // key entry or next if does not
                                      // exist: >= entry

template <class T>
typename BPlusTree<T>::Iterator BPlusTree<T>::upper_bound(const T& key){
  for(BPlusTree<T>::Iterator it= begin(); it!= end();++it){
    if(*it > key){
      return it;
    }
  }

  return NULL;
}  //return first that goes AFTER key
                                      //exist or not, the next entry  >entry
template <class T>
int BPlusTree<T>::size() const{
    int size = 0;
    if(is_leaf() != true){
        size += subset[0]->size();
    }
    for(int i = 0 ; i < data_count; i++){
        size++;
        if(!is_leaf()&&subset[i+1]){
            size += subset[i+1]->size();
        }
    } 

    return size;
}                           //count the number of elements
                                        //              in the tree
template <class T>
bool BPlusTree<T>::empty() const{
    return (size() == 0);
}                         //true if the tree is empty

template <class T>
bool BPlusTree<T>::is_valid(){
    // if(!is_leaf()){
    //     subset[data_count]->is_valid();
    // }

    // if(is_leaf()){
    //     return true;
    // }

    // for(int i = data_count -1; i > -1;i--){
    //     if( (subset[i+1]->data[0] > data[i]) == false ){
    //         return false;
    //     }
    // }


    // int index_of_sub = subset[0]->data_count-1;
    // if(index_of_sub < 0){
    //     index_of_sub = 0;
    // }  
    // if(data[0] < subset[0]->data[index_of_sub]){
    //     // cout << subset[0]->data_count << endl;
    //     // cout << subset[0]->data[0] << endl;
    //     // cout << subset[0] ->data[subset[0]->data_count] << endl;
    //     return false;
    // }
    // return true;



    //should check that every data[i] < data[i+1]
    for(int i= 0; i< data_count;i++){
        if(i+1 >= data_count){
            break;
        }
        
        if(!(data[i] < data[i+1])){
            return false;
        }
    }
    if (is_leaf()){
      return true;
    }
    

    //data[data_count-1] must be less than equal to 
    //  every subset[child_count-1]->data[ ]
    for(int i=0; i < subset[child_count-1]->data_count;i++){
        if((data[data_count-1]>subset[child_count-1]->data[i])){
            cout << __LINE__<<endl;
            return false;
        }
    }
    //every data[i] is greater than every subset[i]->data[ ]
    
    for(int i =0; i < data_count;i++){
        for(int j =0; j < subset[i]->data_count;j++){
            if((data[i] <= subset[i]->data[j])){
            cout << __LINE__<<endl;

                return false;
            }
        }
    }
    //B+Tree: Every data[i] is equal to subset[i+1]->smallest
    for(int i =0; i <data_count;i++){
        T bruh;
        if(i+1 >= data_count){
            break;
        }
        subset[i+1]->get_smallest(bruh);
        if(!(data[i] == bruh)){
            cout << data[i] << endl;
            cout << bruh << endl;
            cout << __LINE__<<endl;

            return false;
        }
    }


    //Recursively validate every subset[i]
    for(int i=0;i<child_count;i++){
        return subset[i]->is_valid();
    }
    return true;
}

template <class T>
string BPlusTree<T>::in_order(){
    string result = "";
    if(is_leaf() != true){
        result += subset[0]->in_order();
    }

    for(int i = 0 ; i < data_count; i++){

        result+= to_string(data[i]);
        result+="|";
    
        if(!is_leaf()){
            result +=subset[i+1]->in_order();
        }
    } 
    return result;
}                          // traverse the tree in an
                        // inorder fashion, return a 
                        // string of all the data items
                        // with vertical delimiters

template <class T>
string BPlusTree<T>::post_order(){
    string smth;
    if(!is_leaf()){
        smth+=subset[0]->post_order();
    }
    
    for(int i=0; i<data_count; i++){
        if(!is_leaf()){
            // smth += subset [i]->post_order();
            smth+=subset[i+1]->post_order();

        }
        smth += to_string (data[i]);
        smth += "|";
    }
    return smth;
}

template <class T>
string BPlusTree<T>::pre_order(){
    string result = "";
    
    // if(is_leaf() != true){
    //     result += subset[0]->in_order();
    // }
    int i =0;
    for(; i < data_count; i++){

        result+= to_string(data[i]);
        result+="|";
    
        if(!is_leaf()){
            result +=subset[i]->pre_order();
        }

    }

    if(!is_leaf()){
        result+=subset[data_count]->pre_order();
    }
    return result;
}

template <class T>
typename BPlusTree<T>::Iterator BPlusTree<T>::begin(){
  return BPlusTree<T>::Iterator(get_smallest_node());
}

template <class T>
typename BPlusTree<T>::Iterator BPlusTree<T>::end(){
  return BPlusTree<T>::Iterator();
}


//insert element functions
template <class T>
void BPlusTree<T>::loose_insert(const T& entry){
    int i = first_ge(data,data_count,entry);
    bool found = (i< data_count && data[i] == entry);
    // cout << "bruh: " << found << endl;
    // cout << "i: " << i << endl;
    // cout << "is_leaf(): " << is_leaf() << endl;
    if(found && is_leaf()){
        if(dups_ok){
          data[i] + entry;
        }else {
          data[i] = entry;
        }
    } else if(is_leaf() && !found){
        ordered_insert(data,data_count,entry);
    } else if(!is_leaf() && found) {
        subset[i+1]->loose_insert(entry);
        fix_excess(i+1);
    } else if(!is_leaf() && !found){
        subset[i]->loose_insert(entry);
        fix_excess(i);
    }
    return;
}          //allows MAXIMUM+1 data
                                        //      elements in the root

template <class T>
void BPlusTree<T>::fix_excess(int i){
    if(!(subset[i]->data_count > MAXIMUM)){
        return;
    } 
    insert_item(subset,i+1,child_count,new BPlusTree<T>(dups_ok));
    
    split(subset[i]->data,subset[i]->data_count,subset[i+1]->data,subset[i+1]->data_count);

    
    split(subset[i]->subset,subset[i]->child_count,subset[i+1]->subset,subset[i+1]->child_count);

    T bring_to_parent;
    detach_item(subset[i]->data, subset[i]->data_count, bring_to_parent);
    ordered_insert(data,data_count,bring_to_parent);

    if(subset[i]->is_leaf()){
      ordered_insert(subset[i+1]->data,subset[i+1]->data_count,bring_to_parent);
      subset[i+1]->next = subset[i]->next;
      subset[i]->next = subset[i+1];
    }

}                     //fix excess of data elements
                                        //                  in child i

template <class T>
//remove element functions:
void BPlusTree<T>::loose_remove(const T& entry){
    int i = first_ge(data,data_count,entry);
    bool found = (i < data_count && data[i] == entry);
   
    if(is_leaf() && !found){
        return;
    }else if (is_leaf() && found){
        T bruh;
        delete_item(data,i,data_count,bruh);
        return;
    } else if(!is_leaf() && !found){
        subset[i]->loose_remove(entry);
        fix_shortage(i);

    }else if(!is_leaf()&& found){
    
        subset[i+1]->loose_remove(entry);
        fix_shortage(i+1);
        T* data_pointer = find_ptr(entry);
        // cout << "I: " << i << endl;
        // cout << "\n=======================================\n";
        // cout << *this << endl;
        // cout << "\n=======================================\n";
        if(data_pointer){
            int ge = first_ge(data,data_count,entry);
            T smallest_item;
            subset[ge+1]->get_smallest(smallest_item);
            *data_pointer = smallest_item;
        }else {
            int ge_outer = first_ge(data,data_count,entry);
            // print_array(subset[i]->data,subset[i]->data_count);
            // cout << "i: " << i << endl;
            // cout << "ge: " << ge_outer << endl;

            //!previous iteration
            // data_pointer = subset[ge_outer]->find_ptr(entry);
            data_pointer = subset[i]->find_ptr(entry);
            // cout << "ge_outer: " << ge_outer << endl;
            T* data_pointer_ge_outer = subset[ge_outer]->find_ptr(entry);

            // cout << data_pointer << endl;
            // cout << data_pointer_ge_outer << endl;
            // print_array(subset[ge_outer]->data,subset[ge_outer]->data_count);

            if(data_pointer){

                // cout << *this << endl;
                // cout << "ge: " << ge << endl;
                T smallest_item;
                int ge_inner = first_ge(subset[i]->data,subset[i]->data_count,entry);
                subset[i]->subset[ge_inner+1]->get_smallest(smallest_item);
                //! previous iteration
                // T smallest_item;
                // int ge_inner = first_ge(subset[ge_outer]->data,subset[ge_outer]->data_count,entry);


                // print_array(subset[ge_outer]->data,subset[ge_outer]->data_count);
                // cout << "ge_inner: " << ge_inner << endl;

                //!previous iterattion
                // subset[ge_outer]->subset[ge_inner+1]->get_smallest(smallest_item);
                
                *data_pointer = smallest_item;
                // cout << *this << endl;
            }else if(data_pointer_ge_outer){
                T smallest_item;
                // print_array(subset[ge_outer]->data,subset[ge_outer]->data_count);
                int ge_inner = first_ge(subset[ge_outer]->data,subset[ge_outer]->data_count,entry);
                subset[ge_outer]->subset[ge_inner+1]->get_smallest(smallest_item);
                *data_pointer_ge_outer = smallest_item;
                // cout << "\n=======================================\n";
                // cout << *this << endl;
                // cout << "\n=======================================\n";
            } else {
                return;
            }

        }
    }
    // print_array(data,data_count);
    // cout << "child_count: " << child_count << endl;
    // cout << "data_count: " << data_count << endl;
    // cout << "i: " << i << endl;
    // fix_shortage(i);
    // cout << "where is 96\n";
    // print_array(data,data_count);
    // cout << "data_count: " << data_count << endl;
    // print_array(subset[0]->data,subset[0]->data_count);
    // print_array(subset[1]->data,subset[1]->data_count);
    // print_array(subset[2]->data,subset[2]->data_count);
}          //allows MINIMUM-1 data
                                        //      elements in the root

template <class T>
BPlusTree<T>* BPlusTree<T>::fix_shortage(int i){
    if(is_leaf() || (subset[i]->data_count >= MINIMUM)){
        // print_array(subset[i]->data,subset[i]->data_count);
        return nullptr;
    }
    // cout << "WHAT\n";
    // print_array(data,data_count);
    // print_array(subset[i]->data,subset[i]->data_count);
    // cout << "i: " << i << endl;
    // cout << subset[i+1]->data_count << endl;
    // print_array(subset[i+1]->data,subset[i+1]->data_count);

    // cout << "\n\n";
    // cout << endl;
    // cout << (subset[i-1]->data_count > MINIMUM) << endl;
    if(i+1<child_count &&subset[i+1]->data_count > MINIMUM){
        //borrow from right
        // cout << __LINE__ <<endl;
        transfer_left(i);
    }
    else if(i>0 && subset[i-1]->data_count > MINIMUM){
        //borrow from left
        // cout << __LINE__ <<endl; 
        transfer_right(i);
    }else if (i+1<child_count){
        // merge right
        merge_with_next_subset(i);
        // cout << __LINE__ <<endl;

    } else{
        // cout << __LINE__ <<endl;
        //merge left
        merge_with_next_subset(i-1);
    }
    return this;
}                   //fix shortage of data elements
                                        //                  in child i

template <class T>
T* BPlusTree<T>::find_ptr(const T& entry){
  for(int i =0;i <data_count;i++){
    if(entry == data[i]){
      return &data[i];
    }
  }

  return NULL;
}         //return a pointer to this key.
                                         // NULL if not there.

template <class T>
BPlusTree<T>* BPlusTree<T>::get_smallest_node(){
  if(!is_leaf()){
    return subset[0]->get_smallest_node();
  }
  if(data_count == 0){
    return NULL;
  }
  return this;
}

template <class T>
void BPlusTree<T>::get_smallest(T& entry){
    if(!is_leaf()){
        return subset[0]->get_smallest(entry);
    } else {
        entry = data[0];
    }
}      //entry := leftmost leaf

template <class T>
void BPlusTree<T>::get_biggest(T& entry){

}       //entry := rightmost leaf

template <class T>
void BPlusTree<T>::remove_biggest(T& entry){
  if(!is_leaf()){
        subset[data_count]->remove_biggest(entry);
        fix_shortage(data_count);
        return;
  } else {
        detach_item(data,data_count,entry);
  }
}    //remove the biggest child of tree->entry

template <class T>
void BPlusTree<T>::transfer_left(int i){
     //get parent item then put it into the empty node
    T parent_item;

    // print_array(data,data_count);
    delete_item(data,i,data_count,parent_item);
    // print_array(data,data_count);


    // print_array(subset[i]->data,subset[i]->data_count);
    ordered_insert(subset[i]->data,subset[i]->data_count,parent_item);
    // print_array(subset[i]->data,subset[i]->data_count);


    //get the children of the smallest node and put it into the right of the empty node
    BPlusTree<T>* child_node = nullptr;
    
    if(!subset[i+1]->is_leaf()){
        delete_item(subset[i+1]->subset,0,subset[i+1]->child_count,child_node);
        attach_item(subset[i]->subset,subset[i]->child_count,child_node);

    }

    //get the smallest child and put it into the parent
    T child_item;
    // print_array(subset[i+1]->data,subset[i+1]->data_count);
    delete_item(subset[i+1]->data,0,subset[i+1]->data_count,child_item);
    if(!subset[i]->is_leaf()){
        ordered_insert(data,data_count,child_item);
    } else {
        ordered_insert(data,data_count,subset[i+1]->data[0]);
    }
    // print_array(subset[i+1]->data,subset[i+1]->data_count);

    
}       //transfer one element LEFT from child i

template <class T>
void BPlusTree<T>::transfer_right(int i){
    //get parent item then put it into the empty node
     T parent_item;
        // print_array(data,data_count);
        delete_item(data,i-1,data_count,parent_item);
        // print_array(data,data_count);
        ordered_insert(subset[i]->data,subset[i]->data_count,parent_item);
        //get the children of the biggest child node and put it to the left of the empty node

        BPlusTree<T>* child_node = nullptr;
        if(!subset[i-1]->is_leaf()){
            detach_item(subset[i-1]->subset,subset[i-1]->child_count,child_node);
            insert_item(subset[i]->subset,0,subset[i]->child_count,child_node);
        }

        //get the biggest child and put it into parent
        T child_item;
        // print_array(subset[i-1]->data,subset[i-1]->data_count);
        detach_item(subset[i-1]->data,subset[i-1]->data_count,child_item);
        // print_array(subset[i-1]->data,subset[i-1]->data_count);
        
        // print_array(data,data_count);
        ordered_insert(data,data_count,child_item);

        if(!subset[i]->is_leaf()){
            
            // T* temp_pointer = &subset[i+1]->data[0];
            // subset[i+1]->subset[i]->get_smallest(*temp_pointer);
        } else if (subset[i]->is_leaf()){
            subset[i]->data[0] = child_item;
        }
    // if(!subset[i]->is_leaf()){
    //     T parent_item;
    //     // print_array(data,data_count);
    //     delete_item(data,i-1,data_count,parent_item);
    //     // print_array(data,data_count);
    //     ordered_insert(subset[i]->data,subset[i]->data_count,parent_item);
    //     //get the children of the biggest child node and put it to the left of the empty node

    //     BPlusTree<T>* child_node = nullptr;
    //     if(!subset[i-1]->is_leaf()){
    //         detach_item(subset[i-1]->subset,subset[i-1]->child_count,child_node);
    //         insert_item(subset[i]->subset,0,subset[i]->child_count,child_node);
    //     }

    //     //get the biggest child and put it into parent

    //     T child_item;
    //     // print_array(subset[i-1]->data,subset[i-1]->data_count);
    //     detach_item(subset[i-1]->data,subset[i-1]->data_count,child_item);
    //     // print_array(subset[i-1]->data,subset[i-1]->data_count);
        
    //     // print_array(data,data_count);
    //     ordered_insert(data,data_count,child_item);
    //     // print_array(data,data_count);
    //     T* temp_pointer = &subset[i+1]->data[0];
    //     subset[i+1]->subset[i]->get_smallest(*temp_pointer);
    // } else if(subset[i]->is_leaf()){
    //     T child_item;
    //     detach_item(subset[i-1]->data,subset[i-1]->data_count,child_item);
    //     cout << i << endl;
    //     ordered_insert(subset[i]->data,subset[i]->data_count,child_item);
    //     data[i-1] = child_item;
    // }
    

}       //transfer one element RIGHT from child i


template <class T>
BPlusTree<T>* BPlusTree<T>::merge_with_next_subset(int i){
    //! Check for if it a leaf or not
    //!if it not a leaf, you do attached it, if it not you dont
    //get the parent element and putting it into child
    T parent_item;
    // print_array(data,data_count);
    // cout << "data_count: " << data_count << endl;
    delete_item(data,i,data_count,parent_item);
    // print_array(data,data_count);
    // cout << "data_count: " << data_count << endl;
    if(!subset[i]->is_leaf()){
        attach_item(subset[i]->data,subset[i]->data_count,parent_item);
    }
        // attach_item(subset[i]->data,subset[i]->data_count,parent_item);

    //merging the children of subset i+1 with children of sub i
    
    merge(subset[i]->subset,subset[i]->child_count,subset[i+1]->subset,subset[i+1]->child_count);
    merge(subset[i]->data,subset[i]->data_count,subset[i+1]->data,subset[i+1]->data_count);

    if(subset[i]->is_leaf()){
        subset[i]->next =subset[i+1]->next;
    }
    // print_array(subset[i]->data,subset[i]->data_count);
    // subset[i+1]->child_count = 0;
    // subset[i+1]->data_count = 0;

    BPlusTree<T>* temp;
    delete_item(subset,i+1,child_count,temp);
    delete temp;

    
    return this;
}         //merge subset i with subset
                                        //                      i+1
#endif