#ifndef TOKENSTR_H
#define TOKENSTR_H
#include <iostream>
#include "../../includes/container/token.h"


using namespace std;

class TokenStr: public Token{
  public:
  TokenStr(string string_data): _data(string_data),Token(string_data){
    _type = "TokenStr";
  } 
  string get_data(){return _data;}
  string get_type(){return _type;}
  private: 
  string _type;
  string _data;
  
};

#endif