#ifndef CONSTANTS_H
#define CONSTANTS_H

enum _const {NOTHING, SELECT, FROM, WHERE, //2
                INSERT, INTO, CREATE,MAKE, //6
                TABLE, ASTERIK, QUOTE, //9
                COMMA, RELATIONAL_OPERATOR, LOGICAL_OPERATOR, //11?
                SYMBOL, FIELD ,VALUE,LEFTPAREN,RIGHTPAREN,SPACE,STRING, NUMBER, TK_TABLE}; //14

const int MAX_COLUMNS = 256;
const int MAX_ROWS = 100;
const int MAX_BUFFER = 200;

const char ALFA[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char DIGITS[] = "0123456789";
const char OPERATORS[] = "><=!+-%&|";
const char SPACES[] = {' ', '\t', '\n'};
const char PUNC[] = "?.,:;'`~!";
const int START_DOUBLE = 0;
const int START_SPACES = 4;
const int START_ALPHA = 6;
const int START_OPERATOR = 20;
const int START_PUNC = 10;

//token types:
const int TOKEN_NUMBER = 1;
const int TOKEN_ALPHA = 2;
const int TOKEN_SPACE = 3;
const int TOKEN_OPERATOR = 4;
const int TOKEN_PUNC = 5;

const int TOKEN_UNKNOWN = -1;
const int TOKEN_END = -2;

const int table_symbol = TABLE+SYMBOL+10;//starting creating table but did not finish it
const int field_symbol = FIELD+SYMBOL+10; // success state of creating table

const int into_symbol = INTO+SYMBOL+10; //starting inserting into table but did not finish

const int value_symbol = VALUE+SYMBOL+10; // success state of inserting into table
//command

const int select_symbol = SELECT+SYMBOL+10; //starting selecting into table

const int from_symbol = FROM+SYMBOL+10;  //success state of selecting without where

const int where_symbol = WHERE+SYMBOL+10; // success state of selecting with where 
const int relational_symbol = RELATIONAL_OPERATOR+SYMBOL + 10;  //36 ending state of selecting with where

const int logical_symbol = LOGICAL_OPERATOR+SYMBOL+10; //37 beginning thing with logical, not a success state


#endif

