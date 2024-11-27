#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <iomanip>
#include <string>
#include "../../includes/bplustree/bplustree.h"

using namespace std;

template <typename K, typename V>
struct Pair{
    K key;
    V value;

    Pair(const K& k=K(), const V& v=V()){
      value = v;
      key = k;
    }
    friend ostream& operator <<(ostream& outs, const Pair<K, V>& print_me){
       cout << print_me.key << ":" << print_me.value;
      return outs;
    }
    friend bool operator ==(const Pair<K, V>& lhs, const Pair<K, V>& rhs){
      return (lhs.key == rhs.key);
    }
    friend bool operator < (const Pair<K, V>& lhs, const Pair<K, V>& rhs){
      return (lhs.key < rhs.key);
    }
    friend bool operator > (const Pair<K, V>& lhs, const Pair<K, V>& rhs){
      return (lhs.key>rhs.key);
    }
    friend bool operator <= (const Pair<K, V>& lhs, const Pair<K, V>& rhs){
      return (lhs.key<=rhs.key);
    }
    friend Pair<K, V> operator + (const Pair<K, V>& lhs, const Pair<K, V>& rhs){
      assert(lhs.key==rhs.key);
      return Pair<K,V> (lhs.key,rhs.value);
    }
};


//-----------------------------------------------------------------//

template <typename K, typename V>
struct Map
{
public:
    typedef BPlusTree<Pair<K, V> > map_base;
    class Iterator{
    public:
        friend class Map;
        Iterator(){
          _it = NULL;
        }
        Iterator(typename map_base::Iterator it):_it(it){
          
        }
        Iterator operator ++(int unused){
          return _it++;
        }
        Iterator operator ++(){
          return ++_it;
        }
        Pair<K, V> operator *(){
          return *_it;
        }
        friend bool operator ==(const Iterator& lhs, const Iterator& rhs){
          return (lhs._it ==rhs._it);
        }
        friend bool operator !=(const Iterator& lhs, const Iterator& rhs){
          return !(lhs._it==rhs._it);
        }
    private:
        typename map_base::Iterator _it;

    };

    Map();
//  Iterators
    Iterator begin();
    Iterator end();

//  Capacity
    int size() const;
    bool empty() const;

//  Element Access
    V& operator[](const K& key);
    V& at(const K& key);
    const V& at(const K& key) const;


//  Modifiers
    void insert(const K& k, const V& v);
    void erase(const K& key);
    void clear();
    V get(const K& key);

//  Operations:
    Iterator find(const K& key);
    bool contains(const Pair<K, V>& target) const;

    // I have not writtent hese yet, but we will need them:
    //    int count(const K& key);
    //    lower_bound
    //    upper_bound
    //    equal_range:

    Iterator lower_bound(const K& key){return Map<K,V>::Iterator(map.lower_bound(key));}
    Iterator upper_bound (const K& key){return Map<K,V>::Iterator(map.upper_bound(key));}
    int count(const K& key){
      return -1;
    }

    bool is_valid(){return map.is_valid();}

    friend ostream& operator<<(ostream& outs, const Map<K, V>& print_me){
        outs<<print_me.map<<endl;
        return outs;
    }
private:
    int key_count;
    BPlusTree<Pair<K, V> > map{true};
};

template <typename K, typename V>
Map<K,V>::Map() : key_count(0) {}
//  Iterators
template <typename K, typename V>
typename Map<K,V>::Iterator Map<K,V>::begin(){
  return Map<K,V>::Iterator(map.begin());
}

template <typename K, typename V>
typename Map<K,V>::Iterator Map<K,V>::end(){
  return Map<K,V>::Iterator(map.end());
}

//  Capacity
template <typename K, typename V>
int Map<K,V>::size() const{
  return map.size();
}
template <typename K, typename V>
bool Map<K,V>::empty() const{
  return map.empty();
}

//  Element Access
template <typename K, typename V>
V& Map<K,V>::operator[](const K& key){
  return map.get(Pair<K,V>(key)).value;
}
template <typename K, typename V>
V& Map<K,V>::at(const K& key){
  return map.get_existing(Pair<K,V>(key)).value;
}

template <typename K, typename V>
const V& Map<K,V>::at(const K& key) const{
  return map.get(Pair<K,V>(key)).value;
}


//  Modifiers
template <typename K, typename V>
void Map<K,V>::insert(const K& k, const V& v){
  map.insert(Pair<K,V>(k,v));
  key_count++;
}
template <typename K, typename V>
void Map<K,V>::erase(const K& key){
  map.remove(key);
}
template <typename K, typename V>
void Map<K,V>::clear(){
  map.clear_tree();
}
template <typename K, typename V>
V Map<K,V>::get(const K& key){
  return map.get(key).value;
}

//  Operations:
template <typename K, typename V>
typename Map<K,V>::Iterator Map<K,V>::find(const K& key){
 return Map<K,V>::Iterator(map.find(key)); 
}
template <typename K, typename V>
bool Map<K,V>::contains(const Pair<K, V>& target) const{
  return map.contains(target);
}

// I have not writtent hese yet, but we will need them:
//    int count(const K& key);
//    lower_bound
//    upper_bound
//    equal_range:




#endif