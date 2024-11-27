#include "../../includes/table/table.h"

Table::Table(){
  _empty = true;
  _last_record = 0;

  // const int size = 7;
  // string arr[size] = {"==", "<=", ">=", ">", "<", "and", "or"};
  // string type[size] = {"Relational", "Relational", "Relational", "Relational", "Relational" , "Logical", "Logical"};

  // for(int i = 0; i < size;i++){
  //   what_token[arr[i]] = type[i];
  // }
}
Table::Table(const string& name): _name(name){
  _empty = true;
  string file_name = _name + ".bin";
  _file_name = file_name;
  _last_record = 0;

  ifstream read;
  read.open(_name+"_fields.text");
  string line;
  int i = 0;
  vector<string> field_name;
  while(getline(read,line)){
    field_name+= line;
  }
  read.close();
  set_fields(field_name);
  //call reindex here
  reindex();
  
  // FileRecord record;
  // for(int i =0; i <field_names.size();i++){
  //   _indices.push_back(MMap<string,long>());
  // }
}

Table::Table(const string& name, const vector<string> &field_names){
  _name = name;
  _field_names = field_names;
  _empty = false;
  string file_name = _name + ".bin";
  _file_name = file_name;
  _last_record = 0;
  ofstream f;
  
  f.open(_name+"_fields.text");
  for(int i =0;i < field_names.size();i++){
    f << field_names[i] << endl;


    _field_map[field_names[i]] = i;
  }

  for(int i =0; i <field_names.size();i++){
    _indices.push_back(MMap<string,long>());
  }
  f.close();
  fstream File;
  open_fileW(File,_file_name);
  File.close();
} //vector<emap 35> indices;

void Table::delete_table(){

}

void Table::set_fields(vector<string> fld_names){
  
  
  for(int i =0 ;i < fld_names.size();i++){
    _field_names.push_back(fld_names[i]);
  }
  
  ofstream f;
  f.open(_name+"_fields.text");
  f.clear();
  for(int i =0;i < _field_names.size();i++){
    f << _field_names[i] << endl;
    _field_map[_field_names[i]] = i;
  }

  f.close();
}
vectorstr Table::get_fields() const{
  return _field_names;
}

bool Table::is_empty(){
  if(_field_names.size() == 0){
    _empty = true;
  } else {
    _empty = false;
  }

  return _empty;
}
int Table::insert_into (vectorstr& fields){
  fstream f;

  open_fileRW(f,_file_name);
  
  bool debug = false;
  
  FileRecord b (fields);
  long recno = b.write(f);

  if(debug){
    cout << "inserted " << fields << " into " << recno << endl;
  }

  // long last = _field_map.get("last");
  // _indices[last][fields[last]].push_back(recno);
  // long first = _field_map.get("first");
  
  // _indices[first][fields[first]].push_back(recno);

  // long age = _field_map.get("age");
  // _indices[age][fields[age]].push_back(recno);
  indices_insert(fields,recno);
  f.close();

  _last_record++;
  return recno;
} //return row number

void Table::indices_insert(vectorstr& fields, int recno){

  // while(_indices.size() < fields.size()){
  //   _indices.push_back(MMap<string,long>());
  // }
  // cout <<"field size: " <<fields.size() << endl;
  for(int i =0; i < fields.size();i++){
    // cout << fields[i] << endl;
    _indices[i][fields[i]].push_back(recno);
  }

}


Table Table::select_all(vectorstr fields){
  FileRecord r2;
  fstream f;
  open_fileRW(f,_file_name);
  vectorlong recnos;
  // cout << "bruhb\n";
  int recno = 0;
  long bytes = r2.read(f, recno);
  while(bytes>0){
    recnos.push_back(recno);
    recno++;
    bytes = r2.read(f,recno);
  }
  // cout <<"here\n";
  Table bruh = vector_to_table(fields,recnos);
  // cout << "it passed\n";
  return bruh ;
}
Table Table::select_all(){
  Table sample("sample", _field_names);
  FileRecord record;

  vectorlong location_of_fields;
  for(int i = 0; i < _field_names.size();i++){
    location_of_fields.push_back(_field_map[_field_names[i]]); 
  }
  fstream f;
  open_fileRW(f,_file_name);
  long _recno = 0;
  long bytes = record.read(f,_recno);
  while(bytes>0){
    _select_recnos.push_back(_recno);
    record.change_record(location_of_fields);
    vectorstr bruh = record.get_record();
    sample.insert_into(bruh);
    // sample.indices_insert(bruh,_recno);
    _recno++;
    bytes = record.read(f,_recno);
  }
  // cout << "og select_recnos: " << _select_recnos << endl;
  sample.select_recnos() = _select_recnos;
  // cout << "sample select_recnos: " << sample.select_recnos() << endl;

  f.close();
  return sample;
}

Table Table::select(const vectorstr& fields, const Queue<Token *>& postfix){
  vectorlong after_rpn = cond(postfix);
  _select_recnos = after_rpn;
  Table bruh = vector_to_table(fields,after_rpn);
  return bruh;
} 
Table Table::select(const vectorstr& fields, const vectorstr& condition){
  Stack<Token*> op_stack;

  Queue<Token*> postfix;
  Queue<Token*> infix = string_to_token(condition);

  for(Queue<Token*>::Iterator it = infix.begin();it!= infix.end();it++)
  {
    string type = (*it)->get_type();
    // cout << "it: " << *it << endl;
    // cout << "type: " << type << endl;
    if(type == "LeftParen")
    {
      op_stack.push(*it);
    }else if (type == "RightParen")
    {
      findingLeftParen(postfix,op_stack);
    //   cout << "postfix: "<<postfix << endl;
    // cout << "op_stack: " << op_stack <<endl;

      continue;
    }else if(type == "Relational")
    {
      if(op_stack.size() > 0 &&op_stack.top()->get_type() == "Relational")
      {
        Relational* top = static_cast<Relational*>(op_stack.top());
        Relational* current_iter = static_cast<Relational*>(*it);
        while(top->get_rpn_prio() >= current_iter->get_rpn_prio())
        {
          postfix.push(op_stack.pop());
          if(op_stack.size() > 0){
            top = static_cast<Relational*>(op_stack.top());
          } else break;
        }
      
      } 
      op_stack.push(*it);
    }else if (type == "Logical"){
        if(op_stack.size()> 0 && op_stack.top()->get_type() == "Relational"){
          Relational* top = static_cast<Relational*>(op_stack.top());
          Logical* current_iter = static_cast<Logical*>(*it);
          while(top->get_rpn_prio() >= current_iter->get_rpn_prio()){
            postfix.push(op_stack.pop());

            if(op_stack.size() > 0){
              top = static_cast<Relational*> (op_stack.top());
            } else break;
          }
        } else if (op_stack.size() > 0 && op_stack.top()->get_type() == "Logical"){
          Logical* top = static_cast<Logical*>(op_stack.top());
          Logical* current_iter = static_cast<Logical*>(*it);
          while(top->get_rpn_prio() >= current_iter->get_rpn_prio()){
            postfix.push(op_stack.pop());
            if(op_stack.size() > 0){
              top = static_cast<Logical*> (op_stack.top());
            } else break;
          }
        } 
        op_stack.push(*it);
    }else if(type == "TokenStr"){
        postfix.push(*it);
    }

    // cout << "postfix: "<<postfix << endl;
    // cout << "op_stack: " << op_stack <<endl;
  }

  while(!op_stack.empty()){
    postfix.push(op_stack.pop());
  }

  cout << "final postfix: "<<postfix << endl;
  return select(fields,postfix);
}

Table Table::select(const vectorstr& fields, const string& field, const string& op, const string& value,const mmap_ss& p_tree){
  long search_field = _field_map.at(field);
  _select_recnos.clear();
  vector<long> recnos;
  mmap_sl::Iterator it = _indices[search_field].begin();
  mmap_sl::Iterator end = _indices[search_field].begin();

  if(op == "="){
    recnos= _indices[search_field][value];
    _select_recnos = recnos;
  } else if (op == ">"){
     it =  _indices[search_field].upper_bound(value);
     end = _indices[search_field].end();
  }else if (op == "<"){
     it = _indices[search_field].begin();
     end =  _indices[search_field].lower_bound(value);
  } else if(op == "<="){
     it = _indices[search_field].begin();
     end =  _indices[search_field].upper_bound(value);
  } else if (op == ">="){
     it = _indices[search_field].lower_bound(value);
     end =  _indices[search_field].end();
  }
  for(;it!=end;it++){
    recnos += (*it).value_list;
    _select_recnos+=(*it).value_list;
  }
  Table bruh = vector_to_table(fields,recnos);
  return bruh;
}
Table Table::select(vectorstr& condition){
  // FileRecord record;

  // vectorlong location_of_fields;
  // for(int i = 0; i < _field_names.size();i++){
  //   location_of_fields.push_back(_field_map[_field_names[i]]); 
  // }
  // fstream f;
  // open_fileRW(f,_file_name);
  // long _recno = 0;
  // long bytes = record.read(f,_recno);
  // while(bytes>0){
  //   _recno++;
  //   bytes = record.read(f,_recno);
  // }
  // // cout << "og select_recnos: " << _select_recnos << endl;
  // // cout << "sample select_recnos: " << sample.select_recnos() << endl;
  
  // f.close();
  // ifstream read;
  // read.open(_name+"_fields.text");
  // string line;
  // int i = 0;
  // vector<string> field_name;
  // while(getline(read,line)){
  //   field_name+= line;
  // }
  // read.close();
  // set_fields(field_name);
  return select(_field_names,condition);
}

void build_keyword_list(map_sl &list){
  list.insert("=",1);
}

void Table::reindex(){

    
  // for(int i = 0; i <r.get_record().size();i++){
  //   _indices[i].insert(r.get_record()[i],recno);
  // }
  FileRecord record;

  for(int i = 0; i < _field_names.size();i++){
    _indices.push_back(MMap<string,long>());
  }

  vectorlong location_of_fields;
  for(int i = 0; i < _field_names.size();i++){
    location_of_fields.push_back(_field_map[_field_names[i]]); 
  }
  fstream f;
  open_fileRW(f,_file_name);
  long _recno = 0;
  long bytes = record.read(f,_recno);
  while(bytes>0){
    record.change_record(location_of_fields);
    vectorstr bruh = record.get_record();
    indices_insert(bruh,_recno);
    _recno++;
    bytes = record.read(f,_recno);
    _last_record++;
  }
  f.close();
} //call this from ctor!


ostream& operator << (ostream& outs,  const Table& t){
  cout << "Table name: " << t._name << ", records: " << t._last_record << endl;

  // cout << setw(7) << "record" << setw(4) << "fname" << endl;
  // cout << setw(7) << "lname" << setw(4) << "age" << endl;
  // long last = t._field_map.at("last");
  // long first = t._field_map.at("first");
  // long age = t._field_map.at("age");
  ifstream text;
  text.open(t._name+"_fields.text");
  cout << "record " << setw(8);
  string line;
  int i = 0;
  while(getline(text,line)){
    if(i != 0){
      cout << setw(12);
    }
    cout << line;
    i++;
  }
  cout << endl;
  text.close();


  FileRecord r2;
  fstream f;
  open_fileRW(f,t._file_name);
  int recno = 0;
  long bytes = r2.read(f, recno);
  // cout <<"location of field size: " <<location_of_fields.size() << endl;
  while(bytes>0){
    cout << "     ";
    cout << recno << setw(12) << r2 << endl;
    recno++;
    bytes = r2.read(f,recno);
  }
  f.close();
  return outs;
}

vectorlong Table::cond (const Queue<Token*> &post){
  Stack<Token*> result;

  Queue<Token*>::Iterator begin = post.begin();
  
  while(begin!=post.end()){
    string type = (*begin)->get_type();
    // cout << "type: " << type << endl;
    // (*begin)->print();  
    if(type == "TokenStr"){
      result.push(*begin);
    } else if( type == "Relational"){
      if(result.size() > 1){
        Relational* relational = static_cast<Relational*>(*begin);
        TokenStr* value = static_cast<TokenStr*>(result.pop());
        TokenStr* field = static_cast<TokenStr*>(result.pop());
        vectorlong temp_result = relational->eval(*field,*value,_indices,_field_map);
        result.push(new ResultSet(temp_result));
      }
    } else if (type == "Logical"){
      if(result.size() > 1){
        Logical* logical = static_cast<Logical*>(*begin);
        ResultSet* left = static_cast<ResultSet*>(result.pop());
        ResultSet* right = static_cast<ResultSet*>(result.pop());

        vectorlong temp_result = logical->eval(right->get_data(),left->get_data());
        result.push(new ResultSet(temp_result));
      }
    }
    begin++;
  }


  return static_cast<ResultSet*>(result.pop())->get_data();
}

void Table::findingLeftParen(Queue<Token*>& current_queue, Stack<Token*>& current_stack){
  Stack<Token*> looping_stack = current_stack;
  for(Stack<Token*>::Iterator it = looping_stack.begin();it!= looping_stack.end();it++){
    Token* item = *it;

    if(item->get_type()!= "LeftParen"){
      current_queue.push(current_stack.pop());
    } else {
      current_stack.pop();
      break;
    }
  }
}

Queue<Token*> Table::string_to_token(vectorstr condition){
  Queue<Token*> infix;


  for(int i = 0;i < condition.size();i++){
    if(condition[i] == "<" || condition[i] == ">" || condition[i] == "<=" || condition[i] == ">=" || condition[i] == "="){
      infix.push(new Relational(condition[i]));
    } else if (condition[i] == "and"||condition[i]=="or"){
      infix.push(new Logical (condition[i]));
    } else if (condition[i] == "("){
      infix.push(new LeftParen());
    } else if (condition[i] == ")"){
      infix.push(new RightParen());
    } else {
      infix.push(new TokenStr(condition[i]));
    }
  }

  return infix;
}

Table Table::vector_to_table(const vectorstr &ftelds,const vectorlong &vector_of_recnos){
  Table re_table("temp",ftelds);
  re_table.select_recnos() = vector_of_recnos;
  fstream f;
  FileRecord r2;
  vectorlong location_of_fields;
  for(int i = 0; i < ftelds.size();i++){
    location_of_fields.push_back(_field_map[ftelds[i]]); 
  }
  // cout << "location_of_fields: " << location_of_fields << endl; 
  open_fileRW(f,_file_name);

  for(int i =0;i < vector_of_recnos.size();i++){
    r2.read(f,vector_of_recnos[i]);
    r2.change_record(location_of_fields);
    vectorstr bruh = r2.get_record();
    re_table.insert_into(bruh);
  }
  f.close();
  return re_table;
}

