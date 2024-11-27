#ifndef PARSER_H
#define PARSER_H
#include "../../includes/bplustree/map.h"
#include "../../includes/bplustree/multimap.h"
#include "../../includes/queue/MyQueue.h"
#include "../../includes/table/typedefs.h"
#include "../../includes/tokenizer/stokenize.h"
#include "../../includes/tokenizer/constants.h"
#include <iostream>
#include <string>

using namespace std;
class Parser{
public: 
  Parser();
  Parser(char* s);
  void set_string(char* s);
  long get_columns(string token); //maps tokens to keyword constants like SELECT, FROM, or SYMBOL
  bool get_parse_tree();// set  ptree, return true if end at a success state, false otherwise
  MMap<string,string>& parse_tree();
  void build_keyword_list(); //build keyword map used to map keyword strings to adjacency matrix column numbers
  void make_table();
  bool fail(){return fail_state;}
  void print_lookup();
private: 
  MMap<string,string> ptree;
  char* buffer;
  Map<string,long> keywords;
  static int _adjacency_table[MAX_ROWS][MAX_COLUMNS];
  Queue<string> input_q; // hold tokens
  bool fail_state;
  enum keys {NOTHING, SELECT, FROM, WHERE, //2
                INSERT, INTO, CREATE,MAKE, //6
                TABLE, ASTERIK, QUOTE, //9
                COMMA, RELATIONAL_OPERATOR, LOGICAL_OPERATOR, //11?
                SYMBOL, FIELD ,VALUE,LEFTPAREN,RIGHTPAREN,SPACE,STRING, NUMBER, TK_TABLE}; //14


};

#endif