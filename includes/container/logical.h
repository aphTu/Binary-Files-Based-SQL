#ifndef LOGICAL_H
#define LOGICAL_H
#include "../../includes/container/token.h"
#include "../../includes/table/typedefs.h"
#include "../../includes/container/tokenstr.h"
#include "../../includes/bplustree/multimap.h"
#include "../../includes/bplustree/map.h"
#include "../../includes/container/relational.h"
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>


using namespace std;

class Logical: public Token{
  public: 
  Logical (string string_data);
  string get_type(){return _type;}
  int get_rpn_prio(){return _rpn_prio;}
  vectorlong eval(ResultSet right, ResultSet left);
  string get_data(){return _data;}
  private: 
  string _type;
  string _data;
  int _rpn_prio;
};

#endif