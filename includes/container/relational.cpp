#include "../../includes/container/relational.h"


Relational::Relational (string string_data): _data(string_data), Token(string_data){
  _type  = "Relational";
  _rpn_prio = 2;
}
vectorlong Relational::eval(TokenStr field, TokenStr value, vector<mmap_sl> indices, map_sl fields){
  long search = fields.at(field.get_data());
  vectorlong result;

  mmap_sl::Iterator begin = indices[search].begin();
  mmap_sl::Iterator end = indices[search].begin();


  if(_data == "="){
    result = indices[search][value.get_data()];
  } else if (_data == ">"){
    begin = indices[search].upper_bound(value.get_data());
    end = indices[search].end();
  } else if (_data == "<"){
     begin = indices[search].begin();
     end =  indices[search].lower_bound(value.get_data());
  } else if(_data == "<="){
     begin = indices[search].begin();
     end =  indices[search].upper_bound(value.get_data());
  } else if (_data == ">="){
     begin = indices[search].lower_bound(value.get_data());
     end =  indices[search].end();
  }
    for(;begin!=end;begin++){
      result += (*begin).value_list;
    }
  return (result);
}

