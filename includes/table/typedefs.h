#ifndef TYPEDEFS_H_
#define TYPEDEFS_H_
#include <iostream>
#include <string>
#include <cstring>
#include "../../includes/bplustree/map.h"
#include "../../includes/bplustree/multimap.h"
#include "../../includes/container/token.h"
using namespace std;
    //* Vector
    typedef vector<string> vectorstr; 
    typedef vector<long> vectorlong; 

    //* MAP
    typedef Map <string, long> map_sl;
    typedef Map <string, Token> map_st;

    //* MultiMap
    typedef MMap <string, string> mmap_ss;
    typedef MMap <string, long> mmap_sl;

    typedef ostream ostreams[];
    typedef string strings [];



 
#endif // TYPEDEFS_H_