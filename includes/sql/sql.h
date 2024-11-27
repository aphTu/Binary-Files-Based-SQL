#ifndef SQL_H
#define SQL_H
#include <iostream>
#include "../../includes/parser/parser.h"
#include "../../includes/table/table.h"
#include "algorithm"
#include <string>

using namespace std;
class SQL{
  public:
  SQL(){
    _table_name =  "";
  }
  SQL(string file){
    batch_run(file);
    // Parser parser(file);
    
    // mmap_ss ptree = parser.parse_tree();

  }
  Table command(string command){
    char s[300];
    strcpy(s,command.c_str());
    Parser parser(s);
    _ptree = parser.parse_tree();

    _table_name = _ptree["table_name"][0];
    Table re;
    if(_ptree["command"][0] == "make" || _ptree["command"][0] == "create")
    {
      re = make_table(_ptree);
      // _select_recnos = re._select_recnos;
    } else if(_ptree["command"][0] == "insert" )
    {
      re = insert_table(_ptree);
    } else if (_ptree["command"][0] == "select"){
      re = select_table(_ptree);
      _select_recnos = re.select_recnos();
    }
    
    return re;
  }
  vectorlong select_recnos(){return _select_recnos;}
  Table make_table(mmap_ss ptree)
  {
    Table re(_table_name,ptree["col"]);
    return re;
  }

  Table insert_table(mmap_ss ptree){
    Table re(_table_name);
    vectorstr values = ptree["values"];
    re.insert_into(values);
    return re;
  }
  Table select_table(mmap_ss ptree){
    Table re(_table_name);
    bool where = ptree.contains("where");
    if(ptree["fields"][0] == "*" && !where){
      return re.select_all();
    } else if (!where && ptree["fields"][0]!= "*"){
      return re.select_all(ptree["fields"]);
    } else if (ptree["fields"][0] == "*"){
      return re.select(ptree["condition"]);
    } else {
      return re.select(ptree["fields"],ptree["condition"]);
    }

  }

  void batch_run(string file){
    ifstream _if(file);

     if (!_if.is_open()) {
        cout << "\nError opening the file!\n";
        exit(1);
    }

    string s;
    int i =0;
    while(getline(_if,s)){
      if(s[0] == '/' && s[1] == '/'){
        cout << s.substr(2,s.size()) << endl << endl;
      } else if(s != ""){
        cout << "[" << i << "] " << s << endl;
        Table t = command(s);
        
        if(_ptree["command"][0] == "select"){
          cout << t << endl;
        }
        i++;
      }
    }

    cout << "SQL: DONE" << endl;
    _if.close();
  }
  private:
  vector<long> _select_recnos;
  string _table_name;
  mmap_ss _ptree;
};

#endif