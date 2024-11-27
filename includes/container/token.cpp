#include "../../includes/container/token.h"

Token::Token(string string_data): _string_data(string_data){

}

void Token::print(){
  cout << _string_data << endl;
}

string Token::get_type(){
  // return _type;
  return "";
}

ostream& operator<< (ostream& outs, const Token &print_me){
  return outs;
}

ostream& operator<<(ostream& outs, const Token* print_me){
  cout << print_me->_string_data;
  return outs;
}

