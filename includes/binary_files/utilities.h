#ifndef UTILITIES_H
#define ULTITILIES_H
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
using namespace std;
//utility functions
bool file_exists(string filename);

void open_fileRW(fstream& f, string filename);
void open_fileW(fstream& f, string filename);
vector<string> read_info(fstream& f,string filename);

#endif