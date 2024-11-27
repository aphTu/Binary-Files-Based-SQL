#include "../../includes/tokenizer/ftokenize.h"
#include <iomanip>
bool FTokenizer::get_new_block(){
  char block[MAX_BUFFER];
  bool debug = false;
   _f.read(block,MAX_BLOCK-1);

  if (_f.gcount() ==0)
      return false;
  block[_f.gcount()]='\0';
  if(debug){
    for(int i = 0; block[i] != '\0';i++){
      cout << block[i] << " ";
    }
  }
  _blockPos += _f.gcount();
  _pos+= _blockPos;
  _stk.set_string(block);
  return true;
 }


FTokenizer::FTokenizer(char* fname){
  _f.open(fname);
  _pos = 0;
  _blockPos= 0;
  _more = true;
  get_new_block();
}

SToken FTokenizer::next_token(){
  SToken t;
  if(!_stk.done()){
    _stk >> t;
  } else if (_more == true){
    bool checker = get_new_block();
    if(checker == true){
      _stk >> t;
    } else {
      _more = false;
    }
  } 


  return t;
}

bool FTokenizer::more(){
  if(_more == false){
    _f.close();
  }
  return _more;
}   
     //returns the current value of _more
int FTokenizer::pos(){
  
  return _pos;
}   
       //returns the value of _pos
int FTokenizer::block_pos(){
  
  return _blockPos;
}   
  //returns the value of _blockPos
FTokenizer& operator >> (FTokenizer& f, SToken& t){
  SToken got = f.next_token();
  t = got;
  return f;
}