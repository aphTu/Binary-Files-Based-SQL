#include "../../includes/parser/parser.h"
#include <cstring>
int Parser::_adjacency_table[MAX_ROWS][MAX_COLUMNS];
Parser::Parser(){
  build_keyword_list();   
  make_table();
  buffer = nullptr;
  fail_state = false;
}
Parser::Parser(char* s){
  build_keyword_list();
  make_table();
  set_string(s);
}
MMap<string,string>& Parser::parse_tree(){
  return ptree;
}


void Parser::set_string(char* s){
  buffer = s;
  while(!input_q.empty()){
    input_q.pop();
  }
  STokenizer stk(buffer);
  SToken t;
  stk>> t;
  bool debug = false;
  string quotation ="";
  bool q_mode = false;
  while(stk.more()){
    
    if (debug) cout<<setw(10)<<t.type_string()<<setw(10)<<t<<endl;
    if (t.type_string() == "QUOTATION"){
      if(!q_mode){
        q_mode = true;
      }else {
        q_mode= false;
        input_q.push(quotation);
        quotation = "";
      }
      // t.token_str() =t.token_str().substr(1,t.token_str().size()-2);
      // // cout << t.token_str() << endl;
      // input_q.push(t.token_str());
    }else if(q_mode){
      quotation+=t.token_str();
    }else if(!q_mode&&t.type_string() != "SPACE" && t.type_string()!="PUNC"){
      input_q.push(t.token_str());
    } 
    t = SToken();
    stk >> t;
  }
  // cout << "huh\n";
  bool bruh = get_parse_tree();
  if(bruh == false){
    fail_state = true;
  } else {
    fail_state = false;
  }
  // cout << "fail_state: " << fail_state << endl;
}
long Parser::get_columns(string token){
  string lower;
  for(int i =0; i < token.size();i++){
    lower+= tolower(token[i]);
  }
  if(keywords.at(lower)){
    return keywords.at(lower);
  } else {
    return SYMBOL;
  }
} //maps tokens to keyword constants like SELECT, FROM, or SYMBOL
bool Parser::get_parse_tree(){
  ptree.clear();
  // ptree.print_lookup();
  // const int table_symbol = TABLE+SYMBOL+10;//starting creating table but did not finish it
  // const int field_symbol = FIELD+SYMBOL+10; // success state of creating table
  
  // const int into_symbol = INTO+SYMBOL+10; //starting inserting into table but did not finish

  // const int value_symbol = VALUE+SYMBOL+10; // success state of inserting into table
  // //command

  // const int select_symbol = SELECT+SYMBOL+10; //starting selecting into table

  // const int from_symbol = FROM+SYMBOL+10;  //success state of selecting without where

  // const int where_symbol = WHERE+SYMBOL+10; // success state of selecting with where 
  // const int relational_symbol = RELATIONAL_OPERATOR+SYMBOL + 10;  //36 ending state of selecting with where

  // const int logical_symbol = LOGICAL_OPERATOR+SYMBOL+10; //37 beginning thing with logical, not a success state

  // const int left_paren_symbol = LEFTPAREN+SYMBOL+10; //41 begining left paren state with where

  // const int paren_relational = LEFTPAREN+RELATIONAL_OPERATOR+ COMMA + 10; //50 paren with relational

  // const int paren_relational_symbol = LEFTPAREN+RELATIONAL_OPERATOR+SYMBOL+10; //53 symbol relational parenthese success

  // const int paren_logical = LEFTPAREN + LOGICAL_OPERATOR + COMMA + 10; // 51 paren with logical
  int state = 0;
  bool success = false;
  // cout << input_q << endl;
  bool debug = false;
  bool quotation_mode = false;
  string yes = "yes";
  while(!(input_q.empty())){
    string item = input_q.pop();
   if(debug){ 
    cout << "state before: " << state << endl;
    cout << "item: " << item << endl << endl;
    cout << get_columns(item) << endl;
   }

    state = _adjacency_table[state][get_columns(item)];
    // cout << "state: " << state << endl << endl;
    // cout << boolalpha;
    // cout << "state_failing: " << (state!=-1) << endl;
    // cout << "input_q is empty: " << !(input_q.empty()) << endl;
    // cout << noboolalpha;
    switch (state)
    {

    case SELECT:
    case MAKE:
    case CREATE:
    case INSERT:
      ptree["command"]+= item;
      break;
    case table_symbol:
    case into_symbol:
    case from_symbol:
      ptree["table_name"]+= item;
      break;
    case field_symbol:
      ptree["col"]+= item;
      break;
    case value_symbol:
      ptree["values"] += item;
      break;
    case ASTERIK:
    case select_symbol:
      ptree["fields"] += item;
      break;
    case WHERE:
      ptree["where"]+= yes;
      break;
    case where_symbol:
    case RELATIONAL_OPERATOR:
    case relational_symbol:
    case logical_symbol:
    case LOGICAL_OPERATOR:
    // case paren_logical:
    // case left_paren_symbol:
    // case paren_relational:
    // case paren_relational_symbol:
    // case RIGHTPAREN:
    // case LEFTPAREN:
      ptree["condition"]+=item;
      break;
    default:
      break;
    }
  }
  // ptree.print_lookup();
  if(!input_q.empty()){
    cout << "this shit failed\n";
    exit(1);
  }
  // cout << input_q << endl;
  if (_adjacency_table[state][0] == 1){
    // cout << "this happen success\n";
    return true;
  } else {
    ptree.clear();
    return false;
  }
}// set  ptree, return true if end at a success state, false otherwise
void Parser::build_keyword_list(){
  string key_word[20] ={"select", "from", "where", "insert", "into", "create","make", "table", "*", "\"", ","}; 
  int i = 1;
  int j = 0;
  for(; i<=COMMA;i++){

    // cout << "key_word: " << key_word[i] << endl;
    // cout << "i: " << i << endl;
    keywords[key_word[j]] = i;
    j++;
  }

  string relational[20] = {"<", ">" , "<=", ">=", "=", "=>"};
  for(int i =0; i < 5;i++){
    keywords[relational[i]] = RELATIONAL_OPERATOR;
  }
  string logical[20] = {"and", "or"};
  for(int i = 0; i < 2; i++){
    keywords[logical[i]] = LOGICAL_OPERATOR;
  }

  keywords["field"] = FIELD;
  keywords["fields"] = FIELD;
  keywords["value"] = VALUE;
  keywords["values"] = VALUE;
  keywords[" "] = SPACE;
  // keywords["("] = LEFTPAREN;
  // keywords[")"] = RIGHTPAREN;
} //build keyword map used to map keyword strings to adjacency matrix column numbers
void Parser::make_table(){
  init_table(_adjacency_table);
  //*SELECT = 1
  //*FROM = 2
  //*WHERE = 3
  //*INSERT = 4
  //*INTO = 5
  //*CREATE = 6
  //*MAKE = 7
  //*TABLE = 8
  //*ASTERISK = 9
  //* QUOTE = 10
  //* COMMA = 11
  //* RELATIONAL = 12
  //* LOGICAL = 13
  //* SYMBOL = 14
  //* FIELD = 15
  //* VALUE = 16
  // * LEFTPAREN = 17
  // * RIGHTPAREN = 18

  // int table_symbol = TABLE+SYMBOL+10;//32 starting creating table but did not finish it 
  // int field_symbol = FIELD+SYMBOL+10; //39 success state of creating table
  
  // int into_symbol = INTO+SYMBOL+10; //29 starting inserting into table but did not finish

  // int value_symbol = VALUE+SYMBOL+10; //40 success state of inserting into table
  // //command

  // int select_symbol = SELECT+SYMBOL+10; //25 starting selecting into table

  // int from_symbol = FROM+SYMBOL+10;  //26 success state of selecting without where

  // int where_symbol = WHERE+SYMBOL+10; //27 beginning state of selecting with where 


  // int relational_symbol = RELATIONAL_OPERATOR+SYMBOL + 10;  //36 ending state of selecting with where

  // int logical_symbol = LOGICAL_OPERATOR+SYMBOL+10; //37 beginning thing with logical, not a success state

  // int left_paren_symbol = LEFTPAREN+SYMBOL+10; //41 begining left paren state with where

  // int paren_relational = LEFTPAREN+RELATIONAL_OPERATOR+ COMMA + 10; //50 paren with relational

  // int paren_relational_symbol = LEFTPAREN+RELATIONAL_OPERATOR+SYMBOL+10; //53 symbol relational parenthese success

  // int paren_logical = LEFTPAREN + LOGICAL_OPERATOR + COMMA + 10; // 51 paren with logical

  mark_cell(0,_adjacency_table,SELECT,SELECT);
  mark_cell(0,_adjacency_table,MAKE,CREATE);
  mark_cell(0,_adjacency_table,CREATE,CREATE);
  mark_cell(0,_adjacency_table,INSERT,INSERT);

  //*---------------------creating/making table-----------------//
  mark_cell(CREATE,_adjacency_table,TABLE,TABLE);
  // mark_cell(TABLE,_adjacency_table,FIELD,FIELD);
  mark_cell(TABLE,_adjacency_table,SYMBOL,table_symbol);

  mark_cell(table_symbol,_adjacency_table, FIELD,FIELD);
  mark_cell(FIELD,_adjacency_table,SYMBOL,field_symbol);
  mark_cell(field_symbol,_adjacency_table,SYMBOL,field_symbol);
  // mark_cell(field_symbol,_adjacency_table,COMMA,COMMA);
  // mark_cell(COMMA,_adjacency_table,SYMBOL,field_symbol);

  mark_success(_adjacency_table,field_symbol);

  mark_fail(_adjacency_table,CREATE);
  mark_fail(_adjacency_table,MAKE);
  mark_fail(_adjacency_table,FIELD);
  mark_fail(_adjacency_table,INSERT);
  mark_fail(_adjacency_table,SYMBOL);
  mark_fail(_adjacency_table,COMMA);
  mark_fail(_adjacency_table,table_symbol);

  //*--------------------------------------------------------//

  //*--------------------inserting into table----------------//
  mark_cell(INSERT,_adjacency_table,INTO,INTO);
  mark_cell(INTO,_adjacency_table,SYMBOL,into_symbol);
  mark_cell(into_symbol,_adjacency_table,VALUE,VALUE);
  mark_cell(VALUE,_adjacency_table,SYMBOL,value_symbol);
  mark_cell(value_symbol,_adjacency_table,SYMBOL,value_symbol);
  // mark_cell(value_symbol,_adjacency_table,COMMA,COMMA);
  // mark_cell(COMMA,_adjacency_table,SYMBOL,value_symbol);
  // mark_cell(SYMBOL+VALUE,_adjacency_table,QUOTE,QUOTE);
  // mark_cell(QUOTE,_adjacency_table,SYMBOL,SYMBOL+VALUE);

  mark_fail(_adjacency_table,INSERT);
  mark_fail(_adjacency_table,INTO);
  mark_fail(_adjacency_table,VALUE);
  mark_fail(_adjacency_table,into_symbol);
  // mark_fail(_adjacency_table,QUOTE);

  mark_success(_adjacency_table,value_symbol);
  //*--------------------------------------------------------//


  //*--------------------selecting into table---------------------//
  mark_cell(SELECT,_adjacency_table,SYMBOL,select_symbol);
  mark_cell(select_symbol,_adjacency_table,FROM,FROM);
  mark_cell(select_symbol,_adjacency_table,SYMBOL,select_symbol);

                //?having multiple field//
  // mark_cell(select_symbol,_adjacency_table,COMMA,COMMA);
  // mark_cell(COMMA,_adjacency_table,SYMBOL,select_symbol);
                //? --------------------//


  mark_cell(SELECT,_adjacency_table,ASTERIK,ASTERIK);
  mark_cell(ASTERIK,_adjacency_table,FROM,FROM);
  mark_cell(FROM,_adjacency_table,SYMBOL,from_symbol);

  

                  //? where condition//
  mark_cell(from_symbol,_adjacency_table,WHERE,WHERE);
  mark_cell(WHERE,_adjacency_table,SYMBOL,where_symbol);
  mark_cell(where_symbol,_adjacency_table,SYMBOL,where_symbol);
  mark_cell(where_symbol,_adjacency_table,LOGICAL_OPERATOR,where_symbol);
  mark_cell(where_symbol,_adjacency_table,RELATIONAL_OPERATOR,where_symbol);
  // mark_cell(where_symbol,_adjacency_table,RELATIONAL_OPERATOR,RELATIONAL_OPERATOR);
  // mark_cell(RELATIONAL_OPERATOR,_adjacency_table,SYMBOL,relational_symbol);
  // mark_cell(relational_symbol,_adjacency_table,LOGICAL_OPERATOR,LOGICAL_OPERATOR);
  // mark_cell(LOGICAL_OPERATOR,_adjacency_table,SYMBOL,where_symbol); 


                //?parenthese condition//
  // mark_cell(WHERE,_adjacency_table,LEFTPAREN,LEFTPAREN);
  // mark_cell(LEFTPAREN,_adjacency_table,SYMBOL,left_paren_symbol);
  // mark_cell(left_paren_symbol,_adjacency_table,RELATIONAL_OPERATOR,paren_relational);
  // mark_cell(paren_relational,_adjacency_table,SYMBOL,paren_relational_symbol);
  // mark_cell(paren_relational_symbol,_adjacency_table,LOGICAL_OPERATOR,paren_logical);
  // mark_cell(paren_logical,_adjacency_table,SYMBOL,left_paren_symbol);
  // mark_cell(paren_relational_symbol,_adjacency_table,RIGHTPAREN,RIGHTPAREN);
  // mark_cell(RIGHTPAREN,_adjacency_table,LOGICAL_OPERATOR,LOGICAL_OPERATOR);
  // mark_cell(LOGICAL_OPERATOR,_adjacency_table,LEFTPAREN,LEFTPAREN);
                //?====================//
  // mark_cell(where_symbol,_adjacency_table,LOGICAL_OPERATOR,LOGICAL_OPERATOR);

  // mark_cell(LOGICAL_OPERATOR,_adjacency_table,SYMBOL,end_symbol);
  // mark_cell(end_symbol,_adjacency_table,SYMBOL,end_symbol);
                  //?---------------//
  // cout << "bruh: " << _adjacency_table[from_symbol][RELATIONAL_OPERATOR] << endl;
  // cout << "bruh3: " << get_columns("=");
  // cout << "bruh2: " << _adjacency_table[12][get_columns("=")] << endl;
  mark_fail(_adjacency_table,SELECT);
  mark_fail(_adjacency_table,FROM);
  mark_fail(_adjacency_table,select_symbol);
  mark_fail(_adjacency_table,logical_symbol);
  // mark_fail(_adjacency_table,paren_relational);
  // mark_fail(_adjacency_table,paren_relational_symbol);
  // mark_fail(_adjacency_table,left_paren_symbol);
  mark_fail(_adjacency_table,WHERE);
  mark_fail(_adjacency_table,ASTERIK);
  mark_fail(_adjacency_table,RELATIONAL_OPERATOR);
  mark_fail(_adjacency_table,LOGICAL_OPERATOR);
  
  mark_success(_adjacency_table,from_symbol);
  mark_success(_adjacency_table,relational_symbol);
  mark_success(_adjacency_table,RIGHTPAREN);
  mark_success(_adjacency_table,where_symbol);

  //*-----------------------------------------------------------//
  
  
  


}






