#include "../../includes/tokenizer/stoken.h"
SToken::SToken(){
  _token = "";
  _type=-1;
}

SToken::SToken(string str, int type){
  _type = type;
  _token = str;
}

ostream& operator <<(ostream& outs, const SToken& t){
  cout << "|" << t._token <<"|";
  return outs;
}




int SToken::type() const{
  return _type;
}

string SToken::type_string() const{
  switch(_type){
    case TOKEN_NUMBER:
      return "NUMBER";
    case TOKEN_ALPHA:
      return "ALPHA";
    case TOKEN_SPACE:
      return "SPACE";
    case TOKEN_OPERATOR:
      return "OPERATOR";
    case TOKEN_PUNC:  
      return "PUNC";
    case TOKEN_UNKNOWN:
      return "UNKNOWN";
    case TOKEN_END:
      return "END";
    case 12:
    case 13:
      return "QUOTATION";
    case 70: 
      return "ASTERISK";
    case 71:
      return "LEFTPAREN";
    case 72:
      return "RIGHTPAREN";
  }
}

string& SToken::token_str(){
  return _token;
}
