#ifndef LEFTPAREN_H
#define LEFTPAREN_H
#include <iostream>
#include "../../includes/container/token.h"

using namespace std;
class LeftParen: public Token{
  public: 
  LeftParen(): _type("LeftParen"), Token("LeftParen"){

  }
  string get_type(){return _type;}
  
  private:
  string _type;

};

#endif