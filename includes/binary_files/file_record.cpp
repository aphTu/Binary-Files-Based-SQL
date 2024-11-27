#include "../../includes/binary_files/file_record.h"
#include <cstdlib>
#include "iomanip"

long FileRecord::write(fstream &outs){
    //r.write(f); //take the Record r and write it into file f
    //  and return the record number of this Record

    //write to the end of the file.
    outs.seekg(0, outs.end);


    long pos = outs.tellp();    //retrieves the current position of the
                                //      file pointer

    //outs.write(&record[0], sizeof(record));
    // int row = 0;
    // for(; row<_num_of_fields();row++){
      outs.write(&_record[0][0], sizeof(_record));
    // }
    // cout << "row: " << row << endl;
    // cout <<"sizeof(_record[row]): " <<sizeof(_record[row]) << endl;
    // cout << "sizeof: " << sizeof(_record) << endl;
    return pos/(sizeof(_record));  //record number
}

long FileRecord::read(fstream &ins, long recno){
  if(ins.eof() || recno < 0 || recno > MAX){
    return 0;
  }
    //returns the number of bytes read.
    //    r.read(f, 6);
    //    cout<<r<<endl;
    long pos= recno *sizeof(_record);
    ins.seekg(pos, ios_base::beg);
    //ins.read(&_record[0], sizeof(_record))

    ins.read(&_record[0][0],sizeof(_record));
    //don't you want to mark the end of  the cstring with null?
    //_record[] => [zero'\0'trash trash trash trash]
    //don't need the null character, but for those of us with OCD and PTSD:


    // if(ins.gcount() <= MAX){
    //   _record[recno][ins.gcount()] = '\0';
    // } else {
    //   _record[recno][MAX] = '\0';
    // }
    return ins.gcount();

}

vector<string> FileRecord::get_record(){
      vector<string> re_vec;
      for(int i = 0; i < _num_of_fields();i++){
        string str(_record[i]);
        re_vec.push_back(str);
      }

      return re_vec;
  }

const int FileRecord::_num_of_fields() const{
      int i = 0;
      for(; i < MAX+1;i++){
        if(_record[i][0]!= '\0'){
        }else {
          break;
        }
      }
      return i;
      // return _num_of_field;
}

vector<string> FileRecord::operator[](const int& i){
  vector<string> re_vec;
  re_vec.push_back(_record[i]);
  return re_vec;
}

ostream& operator<<(ostream& outs,
                    const FileRecord& r){
    for(int i=0;i <r._num_of_fields();i++){
      cout << r._record[i];
      if(i+1 != r._num_of_fields()){
       cout << setw(12);
      }
    }

    // for(int i =0; i<101;i++){
    //   if(*(r._record[i]) != '\0'){
    //     cout << r._record[i] << " ";
    //   }
    // }
    return outs;
}
vector<string> FileRecord::get_specific_record(vector<long> location){
  vector<string> re_vec;
  // cout << "location: " << location.size() << endl;
  for(int i = 0; i < location.size();i++){
    if(location[i] >=  _num_of_fields()){
      break;
    }
    string str = (_record[location[i]]);
    // cout << "str: " << str << endl;
    re_vec.push_back(str);
  }

  return re_vec;
}

void FileRecord::change_record(vector<long>location){
  vector<string> need = get_specific_record(location);

  for(int i = 0 ;i < MAX+1;i++){
    for(int j = 0; j < MAX+1;j++){
      _record[i][j] = '\0';
    }
  }
  for(int i =0; i < need.size();i++){
    strcpy(_record[i],need[i].c_str());
    // cout << _record[i] << endl;
  }
  
}

