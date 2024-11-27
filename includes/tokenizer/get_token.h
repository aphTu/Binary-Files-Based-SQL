#ifndef GET_TOKEN_H
#define GET_TOKEN_H

#include "iostream"
#include "cstring"
#include "string"
#include "../../includes/tokenizer/constants.h"
using namespace std;



bool get_token_proto(int table[][MAX_COLUMNS],string& input_buffer, int &pos, int &current_state, bool& done);

#endif