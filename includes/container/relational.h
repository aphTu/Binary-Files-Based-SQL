#ifndef RELATIONAL_H
#define RELATIONAL_H
#include "../../includes/container/token.h"
#include "../../includes/table/typedefs.h"
#include "../../includes/container/tokenstr.h"
#include "../../includes/container/resultset.h"
#include "../../includes/bplustree/multimap.h"
#include "../../includes/bplustree/map.h"
#include <iostream>
#include <string>
#include <cstring>
#include <vector>



using namespace std;

class Relational: public Token{
  public: 
  Relational (string string_data);
  string get_type(){return _type;}
  int get_rpn_prio(){return _rpn_prio;}
  vectorlong eval(TokenStr field, TokenStr value, vector<mmap_sl> indices, map_sl fields);
  string get_data(){return _data;}
  private: 
  string _type;
  string _data;
  int _rpn_prio;
};

#endif