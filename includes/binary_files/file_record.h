#ifndef FILE_RECORD_H
#define FILE_RECORD_H
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include "../../includes/binary_files/utilities.h"
using namespace std;

//----------------------------------------------------------------------------
//                      C L A S S   R E C O R D
//----------------------------------------------------------------------------

struct FileRecord{
public:
    //when you construct a Record, it's either empty or it
    //  contains a word
    FileRecord(){
        recno = -1;
        _num_of_field = 0;
    }

    FileRecord(char str[]){
      strcpy(_record[0], str);
      _num_of_field = 1;
    }
    FileRecord(string s){
      strcpy(_record[0], s.c_str());
      _num_of_field = 1;
    }
    FileRecord(vector<string> vec){
      for(int i =0; i < MAX+1;i++){
        _record[i][0] = '\0';
      }
      _num_of_field = 0;

      for(int i =0; i < vec.size();i++){
        strcpy(_record[i],vec[i].c_str());
        _num_of_field++;
      }
    }
    
    long write(fstream& outs);              //returns the record number
    long read(fstream& ins, long recno);    //returns the number of bytes
                                            //      read = MAX, or zero if
                                            //      read passed the end of file
    vector<string> get_record();
    vector<string> get_specific_record(vector<long> location);
    void change_record(vector<long> location);
    const int _num_of_fields() const;
    vector<string> operator[](const int& i);
    friend ostream& operator<<(ostream& outs,
                               const FileRecord& r);
    static const int MAX = 100;

    char _record[MAX+1][MAX+1] = {};
    int recno;
    int _num_of_field;
};






#endif