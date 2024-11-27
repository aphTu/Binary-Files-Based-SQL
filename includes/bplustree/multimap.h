#ifndef MULTIMAP_H
#define MULTIMAP_H
#include <iostream>
#include <vector>
#include "../../includes/bplustree/bplustree.h"


using namespace std;

template <typename K, typename V>
struct MPair{
    K key;
    vector<V> value_list;

    //--------------------------------------------------------------------------------
    /*      MPair CTORs:
     *  must have these CTORs:
     *  - default CTOR / CTOR with a key and no value: this will create an empty vector
     *  - CTOR with a key AND a value: pushes the value into the value_list
     *  _ CTOR with a key and a vector of values (to replace value_list)
     */
    //--------------------------------------------------------------------------------
    MPair(const K& k=K()):key(k){}
    MPair(const K& k, const V& v): key(k){
      value_list+=v; 
    }
    MPair(const K& k, const vector<V>& vlist): key(k){
      for(int i = 0; i < vlist.size();i++){
        value_list+=vlist[i];
      }
    }
    //--------------------------------------------------------------------------------

    //You'll need to overlod << for your vector:
    friend ostream& operator <<(ostream& outs, const MPair<K, V>& print_me){
      cout << print_me.key << ":";
      for(int i = 0; i< print_me.value_list.size();i++){
        cout << " [" << print_me.value_list[i] <<"]" << " ";
      }
      return outs;
    }
    
    friend bool operator ==(const MPair<K, V>& lhs, const MPair<K, V>& rhs){
      return (lhs.key == rhs.key);
    }
    friend bool operator < (const MPair<K, V>& lhs, const MPair<K, V>& rhs){
      return (lhs.key < rhs.key);
    }
    friend bool operator <= (const MPair<K, V>& lhs, const MPair<K, V>& rhs){
      return (lhs.key <= rhs.key);
    }
    friend bool operator > (const MPair<K, V>& lhs, const MPair<K, V>& rhs){
      return (lhs.key > rhs.key);
    }
    friend MPair<K, V> operator + (const MPair<K, V>& lhs, const MPair<K, V>& rhs){
      assert(lhs.key == rhs.key);
      MPair<K,V> pair(rhs.key,lhs.value_list);

      for(int j = 0; j < rhs.value_list.size();j++){
        pair.value_list+=rhs.value_list[j];
      }

      return pair;
    }
};


template <typename K, typename V>
struct MMap
{
public:
    typedef BPlusTree<MPair<K, V> > map_base;
    class Iterator{
    public:
        friend class MMap;
        Iterator(){
          _it= NULL;
        }
        Iterator(typename map_base::Iterator it):_it(it){

        }
        Iterator operator ++(int unused){
          return _it++;
        }
        Iterator operator ++(){
          return ++_it;
        }
        MPair<K, V> operator *(){
          return *_it;
        }
        friend bool operator ==(const Iterator& lhs, const Iterator& rhs){
          return (lhs._it == rhs._it);
        }
        friend bool operator !=(const Iterator& lhs, const Iterator& rhs){
          return (lhs._it != rhs._it);
        }

    private:
        typename map_base::Iterator _it;
    };

    MMap();
    MMap<K,V>& operator =(const MMap<K,V>& RHS){
      // RHS.mmap.print_tree();
      mmap = RHS.mmap;
      // mmap.print_tree();
      return *this;
    }
//  Iterators
    Iterator begin();
    Iterator end();

//  Capacity
    int size() const;
    bool empty() const;

//  Element Access
    const vector<V>& operator[](const K& key) const;
    vector<V>& operator[](const K& key);

//  Modifiers
    void insert(const K& k, const V& v);
    void erase(const K& key);
    void clear();

//  Operations:
    bool contains(const K& key) const ;
    vector<V> &get(const K& key);
    vector<V>& at(const K& key);
    Iterator find(const K& key);
    int count(const K& key);
    // I have not writtent hese yet, but we will need them:
    //    int count(const K& key);
    //    lower_bound
    //    upper_bound
    //    equal_range:
    
    Iterator lower_bound(const K& key){return MMap<K,V>::Iterator(mmap.lower_bound(MPair<K,V>(key)));}
    Iterator upper_bound(const K& key){return MMap<K,V>::Iterator(mmap.upper_bound(MPair<K,V>(key)));}

    bool is_valid();
    void print_lookup();
    friend ostream& operator<<(ostream& outs, const MMap<K, V>& print_me){
        outs<<print_me.mmap<<endl;
        return outs;
    }

private:
    BPlusTree<MPair<K, V> > mmap{true};
};



//*------------------------------------------------------------------------//
template <typename K, typename V>
MMap<K,V>::MMap(){
  
}

//  Iterators
template <typename K, typename V>
typename MMap<K,V>::Iterator MMap<K,V>::begin(){
  return MMap<K,V>::Iterator(mmap.begin());
}

template <typename K, typename V>
typename MMap<K,V>::Iterator MMap<K,V>::end(){
  return MMap<K,V>::Iterator(mmap.end());
}

//  Capacity
template <typename K, typename V>
int MMap<K,V>::size() const{
  return mmap.size();
}
template <typename K, typename V>
bool MMap<K,V>::empty() const{
  return mmap.empty();
}

//  Element Access
template <typename K, typename V>
const vector<V>& MMap<K,V>::operator[](const K& key) const{
  return mmap.get(MPair<K,V>(key)).value_list;
}
template <typename K, typename V>
vector<V>& MMap<K,V>::operator[](const K& key){
  return mmap.get(MPair<K,V>(key)).value_list;
}

//  Modifiers
template <typename K, typename V>
void MMap<K,V>::insert(const K& k, const V& v){
  MPair<K,V> bruh(k,v);
  mmap.insert(bruh);
}
template <typename K, typename V>
void MMap<K,V>::erase(const K& key){
  MPair<K,V> bruh(key);

  mmap.remove(bruh);
}
template <typename K, typename V>
void MMap<K,V>::clear(){
  mmap.clear_tree();
}

//  Operations:
template <typename K, typename V>
bool MMap<K,V>::contains(const K& key) const {
  return mmap.contains(MPair<K,V>(key));
}
template <typename K, typename V>
vector<V> &MMap<K,V>::get(const K& key){
  return mmap.get(MPair<K,V>(key)).value_list;
}

template <typename K, typename V>
vector<V>& MMap<K,V>::at(const K& key){
  return mmap.get_existing(MPair<K,V>(key)).value_list;
}

template <typename K, typename V>
typename MMap<K,V>::Iterator MMap<K,V>::find(const K& key){
  return mmap.find(MPair<K,V>(key));
}
template <typename K, typename V>
int MMap<K,V>::count(const K& key){
  return -1;
}
// I have not writtent hese yet, but we will need them:
//    int count(const K& key);
//    lower_bound
//    upper_bound
//    equal_range:
template <typename K, typename V>
void MMap<K,V>::print_lookup(){
  MMap<K,V>::Iterator it = begin();
  for(;it!= end();it++){
    cout << setw(4) <<"|"<< (*it).key<< "|: " << setw(8) << (*it).value_list << endl;
  }

}


template <typename K, typename V>
bool MMap<K,V>::is_valid(){
  return mmap.is_valid();
}
#endif