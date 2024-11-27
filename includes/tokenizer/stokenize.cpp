#include "../../includes/tokenizer/stokenize.h"
int STokenizer::_table[MAX_ROWS][MAX_COLUMNS];

STokenizer::STokenizer(){
  _buffer[0] = '\0';
  _pos=-1;
  make_table(_table);
  _done = false;
}

STokenizer::STokenizer(char str[]){
  int i =0;
  while(str[i] != '\0'){
    _buffer[i] = str[i];
    i++;
  }
  
  _buffer[i] = '\0';
  _pos = 0;
  make_table(_table);
  _done = false;
}

bool STokenizer::done(){

  
  // int i = strlen(_buffer);
  // if(_buffer[_pos] != '\0' || _pos < i){
  //   return false;
  // } 
  // return true;
  return _done;
  // return _pos >= strlen(_buffer);
}
            //true: there are no more tokens
bool STokenizer::more(){
  return !(_done);
}
            //true: there are more tokens//

//---------------------------------------------------------------//
//extract one token (very similar to the way cin >> works)
STokenizer& operator >> (STokenizer& s, SToken& t){
  int type = 0;
  string token = s._buffer;
  bool found_success = s.get_token(type,token);

  if(s._done == true){
    return s;
  }

  if(found_success== false){
    s._pos++;
  }
  t=SToken(token,type);  
  return s;
}


//set a new string as the input string
void STokenizer::set_string(char str[]){
  _pos = 0;
  int i = 0;
  for(;str[i]!='\0';i++){
    _buffer[i] = str[i];
  }
  _buffer[i] = '\0';
  _done = false;
}


//create table for all the tokens we will recognize (e.g. doubles, words, etc.)
void STokenizer::make_table(int _table[][MAX_COLUMNS]){
 init_table(_table);
  
  // mark_cells(0,_table,SPACES,START_SPACES);

  // //number
  // mark_cells(1,_table,DIGITS,START_DOUBLE);
  // mark_cells(2,_table,DIGITS,START_DOUBLE);
  // mark_cells(3,_table,DIGITS,START_DOUBLE);

  // //spaces
  // mark_cells(4,_table,SPACES,START_SPACES);
  // mark_cells(5,_table,SPACES,START_SPACES);

  // //alphabet
  // for(int i = 6; i < 10; i++){
  //   mark_cells(i,_table,ALFA,START_ALPHA);
  // }

  // //punc
  // for(int i =10; i < 20; i++){
  //   mark_cells(i,_table,PUNC,START_PUNC);
  // }

  // //operator
  // mark_cells(20,_table,OPERATORS,START_OPERATOR);
  
  mark_cells(0, _table, ALFA, TOKEN_ALPHA);
  mark_cells(0, _table, DIGITS, TOKEN_NUMBER);
  mark_cells(0,_table, SPACES, TOKEN_SPACE);
  mark_cells(0, _table, OPERATORS, TOKEN_OPERATOR);
  mark_cells(0, _table, PUNC, TOKEN_PUNC);
  mark_cell(0,_table,'_',TOKEN_ALPHA);
  mark_cell(0,_table,'*',70);
  mark_cell(0,_table,'(',71);
  mark_cell(0,_table,')',72);

  mark_cells(TOKEN_ALPHA,_table,ALFA, TOKEN_ALPHA);
  mark_cell(TOKEN_ALPHA,_table,'_',TOKEN_ALPHA);
  
  mark_cells(TOKEN_NUMBER,_table,DIGITS,TOKEN_NUMBER);
  mark_cells(TOKEN_SPACE,_table,SPACES,TOKEN_SPACE);
  mark_cells(TOKEN_OPERATOR,_table,OPERATORS,TOKEN_OPERATOR);
  // mark_cells(TOKEN_PUNC,_table,PUNC,TOKEN_PUNC);
  mark_cells(TOKEN_NUMBER, _table, '.', '.', TOKEN_PUNC +'.');  //state [1] --- '.' ------> [2] 

  mark_cells(TOKEN_PUNC + '.', _table, DIGITS, TOKEN_NUMBER);    //state [2] --- DIGITS ---> [3]

  // //*QUOTATION


  mark_cell(0,_table,'\"',12);
  // mark_cells(12,_table,PUNC,12);
  // mark_cells(12,_table,OPERATORS,12);
  // mark_cells(12,_table,ALFA,12);
  // mark_cells(12,_table,SPACES,12);
  // mark_cells(12,_table,DIGITS,12);
  // mark_cell(12,_table,'\"',13);
  //state [0] -------------- '\"' -----> state [12] beginning of quotation state

  

  // mark_cell(0,_table,'\"',12);

  // // after beginning quotation, allowing ..., digits, alha, spaces, and underscore
  // mark_cells(12,_table,ALFA,30);
  // mark_cell(12,_table,'_',30);
  // mark_cells(12,_table,SPACES,31);
  // mark_cells(12,_table,DIGITS,30);



  // mark_cell(12,_table,'.',32);

  // //first dot to second dot
  // //state [32] ------'.' ---> state[33]
  // mark_cell(32, _table,'.',33);
  // //second dot to third dot
  // //state [33] ------- '.' ----> state [34]
  // mark_cell(33,_table,'.',34);


  // //third dot has to go to words or digits or underscore or spaces
  // mark_cells(34,_table,SPACES,30);
  // mark_cells(34,_table,ALFA,30);
  // mark_cells(34,_table,DIGITS,30);
  // mark_cell(34,_table,'_',30);

  // //going from 30 back to 30
  // mark_cells(30,_table,DIGITS,30);
  // mark_cells(30,_table,ALFA,30);
  // mark_cell(30,_table,'_',30);
  // mark_cells(30,_table,OPERATORS,30);


  
  
  // //state [30] ----- ' ' --> state [31]
  // mark_cells(30,_table,SPACES,31);
  
  // //state [30] ----- PUNC --- > state[36]
  // mark_cells(30,_table,PUNC,36);
  // mark_cells(36,_table,ALFA,30);


  // //going from spaces back to the other words
  // //state [31] -------> state[30]
  // mark_cells(31,_table,ALFA,30);
  // mark_cells(31,_table,DIGITS,30);
  // mark_cell(31,_table,'_',30);

  // //state [30] -------- "\"" ending quotation  --> state [50] success state
  // mark_cell(30,_table,'\"', 50);
  
  // mark_cell(36,_table,'\"',50);





  // //* end QUOTATION
  
  // //* PAREN
  // mark_cell(0, _table,'(',52);
  // mark_cells(52,_table,PUNC,52);
  // mark_cells(52,_table,ALFA,52);
  // mark_cells(52,_table,DIGITS,52);
  // mark_cell(52,_table,'_',52);
  // mark_cell(52,_table,'\"',12);

  // mark_cells(50,_table, SPACES,52);
  // mark_cells(50,_table, PUNC,52);
  // mark_cells(50,_table, DIGITS,52);
  // mark_cells(50,_table, ALFA,52);
  // mark_cell(50,_table,'_',52);
  // mark_cell(50,_table,')',53);

  // mark_cell(52,_table,')',53);




  // //* END PAREN

  mark_success(_table,TOKEN_NUMBER);
  mark_success(_table,TOKEN_ALPHA);
  mark_success(_table,TOKEN_OPERATOR);
  // mark_success(_table,50);
  mark_success(_table,13);
  mark_success(_table,TOKEN_PUNC);
  mark_success(_table,TOKEN_SPACE);
  // mark_success(_table,TOKEN_PUNC);
  // mark_success(_table,TOKEN_SPACE);

  // mark_fail(_table,TOKEN_PUNC);
  // mark_fail(_table,TOKEN_SPACE);
  mark_fail(_table,0);
  mark_fail(_table,70);
  mark_fail(_table,71);
  mark_fail(_table,72);

  //did not reach the end of a quotation state
  // mark_fail(_table,12);
  // mark_fail(_table,30);
  // mark_fail(_table,31);
  // mark_fail(_table,32);
  // mark_fail(_table,33);
  // mark_fail(_table,34);


  //did not reach end of paren state
  // mark_fail(_table)
}



//extract the longest string that match one of the acceptable token types
bool STokenizer::get_token(int& start_state, string& token){
  bool checker = get_token_proto(_table,token,_pos,start_state, _done);
  return checker;
}
