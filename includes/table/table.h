#ifndef TABLE_H
#define TABLE_H
#include <iostream>
#include <iomanip>
#include <string> 
#include <vector>
#include <queue>
#include <fstream>
#include "../../includes/bplustree/map.h"
#include "../../includes/bplustree/multimap.h"
#include "../../includes/table/typedefs.h"
#include "../../includes/queue/MyQueue.h"
#include "../../includes/binary_files/file_record.h"
#include "../../includes/container/tokenstr.h"
#include "../../includes/container/leftparen.h"
#include "../../includes/container/rightparen.h"
#include "../../includes/stack/MyStack.h"
#include "../../includes/container/logical.h"

using namespace std;

class Table//:public token
{
public:
    Table();
    Table(const string& _name);
    Table(const string& name, const vector<string> &field_names); //vector<emap 35> indices;
    void delete_table();
    void set_fields(vector<string> fld_names);
    vectorstr get_fields() const;
    bool is_empty();
    int insert_into (vectorstr& fields); //return row number
    void indices_insert(vectorstr& fields, int recno);
    int field_col_no(string field_name);
    Table select_all(vectorstr fields);
    Table select_all();
    Table select(const vectorstr& fields, const Queue<Token *>& postfix); 
    Table select(const vectorstr& fields, const vectorstr& condition);

    Table select(const vectorstr& fields, const string& field, 
                const string& op, const string& value,
                const mmap_ss& p_tree = mmap_ss());
    Table select(vectorstr& condition);
    void build_keyword_list(map_sl &list);
    int get_token_type(const string& s); //NOT USED!
    void reindex(); //call this from ctor!
    string Name(){return _name; }
    friend ostream& operator << (ostream& outs, const Table& t); 


    //rpn
    vectorlong cond (const Queue<Token*> &post);

    //shuntingyard
    void findingLeftParen(Queue<Token*>& current_queue, Stack<Token*>& current_stack);
    //string to token for rpn/shuntingyard
    Queue<Token*> string_to_token(vectorstr condition);

    Table vector_to_table(const vectorstr &ftelds,
                        const vectorlong &vector_of_recnos);



vector<long>& select_recnos() { return _select_recnos; }
private:
    vector<long> _select_recnos;
    static int serial;
    enum OPERATORS {EQUAL,
                    LESS_THAN,
                    GREATER_THAN,
                    LESS_EQUAL,
                    GREATER_EQUAL,
                    NOT_EQUAL,
                    AND,
                    OR,
                    NOT
                    };
    enum keys {SELECT, FROM, WHERE, //2
                INSERT, INTO, CREATE, //5
                TABLE, ASTERIK, QUOTE, //8
                COMMA, RELATIONAL_OPERATOR, LOGICAL_OPERATOR, //11?
                SYMBOL, STRING, NUMBER, TK_TABLE}; //14
    
    // map_ss what_token;
    string _name;
    string _file_name;
    map_sl _keywords;
    vector <mmap_sl> _indices;
    bool _empty;
    vectorstr _field_names;
    map_sl _field_map;
    //vector<Record> rows;
    map_sl OPERATOR_CODES;
    map_st OPERATOR_LOGICAL;
    map_st OPERATOR_RELATIONAL;
    long _last_record;
    static const bool DEBUG = false;
};


#endif