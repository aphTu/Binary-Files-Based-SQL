#ifndef RESULTSET_H
#define RESULSET_H
#include <iostream>
#include "../../includes/container/token.h"
#include "../../includes/table/typedefs.h"


using namespace std;

class ResultSet: public Token{
  public:
  ResultSet(vectorlong string_data): _data(string_data),Token(vect_to_string(string_data)){
    _type = "ResultSet";
  }
  vectorlong get_data(){return _data;}
  string vect_to_string(vectorlong data){
    string re = "";

    for(int i =0;i< data.size();i++){
      re+= data[i];
    }

    return re;
  }
  string get_type(){return _type;}
  private: 
  string _type;
  vectorlong _data;
  
};

#endif