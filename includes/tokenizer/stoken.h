#ifndef STOKEN_H
#define STOKEN_H
#include <iostream>
#include <string>
#include "cstring"
#include "../../includes/tokenizer/constants.h"
using namespace std;

class SToken
{
public:
    SToken();
    SToken(string str, int type);
    friend ostream& operator <<(ostream& outs, const SToken& t);
    int type() const;
    string type_string() const;
    string& token_str();
private:
    string _token;
    int _type;
};

#endif