#ifndef TOKEN_H
#define TOKEN_H
#include <iostream>

using namespace std;

class Token{
  public:
  Token(){
    _string_data ="";
  }
  Token(string string_data);
  virtual string get_type();
  void print();
  friend ostream& operator<< (ostream& outs, const Token &print_me);
  friend ostream& operator<<(ostream& outs, const Token* print_me);

  private: 
  string _string_data;
};

#endif