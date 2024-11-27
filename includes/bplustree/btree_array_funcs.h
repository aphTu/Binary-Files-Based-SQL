#ifndef BTREE_ARRAY_FUNCTIONS_H
#define BTREE_ARRAY_FUNCTIONS_H
#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <random>
#include <iomanip>



using namespace std;

template <class T>
T maximal(const T& a, const T& b);                   //return the larger of the two items

template <class T>
void swap(T& a, T& b); //swap the two items

template <class T>
int index_of_maximal(T data[ ], int n);              //return index of the largest item in data

template <class T>
void ordered_insert(T data[ ], int& n, T entry);        //insert entry into the sorted array
                                                        //data with length n

template <class T>
int first_ge(const T data[ ], int n, const T& entry);   //return the first element in data that is
                                                        //not less than entry

template <class T>
void attach_item(T data[ ], int& n, const T& entry);   //append entry to the right of data

template <class T>
void insert_item(T data[ ], int i, int& n, T entry);    //insert entry at index i in data

template <class T>
void detach_item(T data[ ], int& n, T& entry);          //remove the last element in data and place
                                                        //it in entry

template <class T>
void delete_item(T data[ ], int i, int& n, T& entry);   //delete item at index i and place it in entry

template <class T>
void merge(T data1[ ], int& n1, T data2[ ], int& n2);   //append data2 to the right of data1

template <class T>
void split(T data1[ ], int& n1, T data2[ ], int& n2);   //move n/2 elements from the right of data1
                                                        //and move to data2

template <class T>
void copy_array(T dest[], const T src[],
                int& dest_size, int src_size);              //copy src[] into dest[]

template <class T>
void print_array(const T data[], int n, int pos = -1);  //print array data

template <class T>
bool is_gt(const T data[], int n, const T& item);       //item > all data[i]

template <class T>
bool is_le(const T data[], int n, const T& item);       //item <= all data[i]

//-------------- Vector Extra operators: ---------------------

template <typename T>
ostream& operator <<(ostream& outs, const vector<T>& list); //print vector list

template <typename T>
vector<T>& operator +=(vector<T>& list, const T& addme); //list.push_back addme

template<typename T>
vector<T>& insert_randNum_vector(vector<T>& list); //adding random number from 1 to 1000 into the vector

template <typename T>
void shuffle_vector(vector<T>& list);

template <typename T>
vector<T>& operator+=(vector<T>& list, vector<T> addme);
//---------------------------------------------------------------------------------------------//
template <class T>
T maximal(const T& a, const T& b){
  if(a > b){
    return a;
  }

  return b;
}                    //return the larger of the two items

template <class T>
void swap(T& a, T& b){
  T temp = b;
  b = a;
  a = temp;
}  //swap the two items

template <class T>
int index_of_maximal(T data[ ], int n){

  
  int l_index = 0;
  for(int i =1; i < n; i++){
    if(data[i] > data[l_index]){
      l_index = i;
    }
  }

  return l_index;
}  


template <class T>
void ordered_insert(T data[ ], int& n, T entry){
  int index_bigger;

  //will give you index of the element bigger than entry
  //or it will be -1, which mean that there was no bigger item
  index_bigger = first_ge(data,n,entry);
  if(index_bigger == n){
    attach_item(data,n,entry);
    return;
  }

  if(index_bigger > -1){
    insert_item(data,index_bigger,n,entry);
    return;
  }
  

  
}        //insert entry into the sorted array
                                                        //data with length n

template <class T>
int first_ge(const T data[ ], int n, const T& entry){
  for(int i = 0; i < n; i++){
    if(data[i] > entry || data[i] == entry){
      return i;
    }
  }

  return n;
}   //return the first index in data that is
   //not less than entry

template <class T>
void attach_item(T data[ ], int& n, const T& entry){
  data[n] = entry;
  n++;

}   //append entry to the right of data

template <class T>
void insert_item(T data[ ], int i, int& n, T entry){
  
  for(int j = n; j > i;j--){
    data[j] = data[j-1];    
  }
  n++;

  data[i] = entry;
}    //insert entry at index i in data

template <class T>
void detach_item(T data[ ], int& n, T& entry){
  if(n <=0){
    return;
  }
  entry = data[n-1];
  n--;
}          //remove the last element in data and place//it in entry

template <class T>
void delete_item(T data[ ], int i, int& n, T& entry){
  if(n<=0){
    return;
  }
  entry = data[i];
  for(int j = i; j < n-1; j++){
    data[j] = data[j+1];
  }

  n--;
}   //delete item at index i and place it in entry

template <class T>
void merge(T data1[ ], int& n1, T data2[ ], int& n2){
  for(int i =0; i < n2;i++){
    data1[n1] = data2[i];
    n1++;
  }

  n2 = 0;
}   //append data2 to the right of data1

template <class T>
void split(T data1[ ], int& n1, T data2[ ], int& n2){
  int half = (n1)/2;
  for(int i = 0; i <half; i++){
    data2[i] = data1[n1-half+i];
    n2++;
  }
  
  n1 = n1 - half;
}   //move n/2 elements from the right of data1
//and move to data2

template <class T>
void copy_array(T dest[], const T src[],int& dest_size, int src_size){
  for(int i =0; i < src_size;i++){
    dest[i] = src[i];
  }
  dest_size = src_size;
}              //copy src[] into dest[]

template <class T>
void print_array(const T data[], int n, int pos){
  bool debug = false;
  for(int i =0; i < n; i++){
    cout << data[i] << " ";
    if(debug){
      cout << setw(2*i) << "^" << endl;
    }
  }
  cout << endl;
}  //print array data

template <class T>
bool is_gt(const T data[], int n, const T& item){
  bool success = true;
  for(int i =0; i < n; i++){
    if(data[i] > item){
      success = false;
    }
  }

  return success;
}       //item > all data[i]

template <class T>
bool is_le(const T data[], int n, const T& item){
  bool success = true;
  for(int i =0; i < n; i++){
    if(item> data[i]){
      success = false;
    }
  }

  return success;
}       //item <= all data[i]

//-------------- Vector Extra operators: ---------------------

template <typename T>
ostream& operator <<(ostream& outs, const vector<T>& list){
    for(int i =0; i < list.size();i++){
        cout << "|";
        cout << list[i];
        // if(i+1 <list.size()){
          cout << "| ";
        // }
    }
    cout << endl;
  return outs;
} //print vector list

template <typename T>
vector<T>& operator +=(vector<T>& list, const T& addme){
    
    list.push_back(addme);
    return list;
} //list.push_back addme

template <typename T>
vector<T>& operator+=(vector<T>& list, vector<T> addme){
  for(int i =0;i < addme.size();i++){
    list+=addme[i];
  }

  return list;
}

template <typename T>
vector<T>& insert_randNum_vector(vector<T>& list){
    for(int i =0; i < 50000;i++){
        list+=(rand() % (1000 + 1 - 1) + 1);
    }
    
    // shuffle_vector(list);
    
    // cout << list << endl;
    return list;
} //adding 1 - 1000 into the vector && then shuffle them


template <typename T>
void shuffle_vector(vector<T>& list){
    // cout << list << endl;
    random_device rd;
    mt19937 g(rd());
    shuffle(list.begin(),list.end(),g);
    // cout << list << endl;

}

#endif