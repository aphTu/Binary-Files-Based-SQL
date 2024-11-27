#include "../../includes/container/logical.h"

Logical::Logical (string string_data): _data(string_data),Token(string_data){
  _type = "Logical";
  if(_data == "and"){
    _rpn_prio = 2;
  } else {
    _rpn_prio = 1;
  }
}


vectorlong Logical::eval(ResultSet right, ResultSet left){
  vectorlong right_ve = right.get_data();
  vectorlong left_ve = left.get_data();
  
  sort(right_ve.begin(),right_ve.end());
  sort(left_ve.begin(),left_ve.end());
  vectorlong result;
  if(_data == "and"){
    set_intersection(right_ve.begin(),right_ve.end(),left_ve.begin(),left_ve.end(),back_inserter(result));
  } else if(_data == "or"){
    set_union(right_ve.begin(),right_ve.end(),left_ve.begin(),left_ve.end(),back_inserter(result));
  }

  return result;
}
