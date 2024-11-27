#include "../../includes/tokenizer/get_token.h"
bool get_token_proto(int table[][MAX_COLUMNS],string& input_buffer, int &pos, int &current_state, bool& done){
  if(input_buffer[pos] == '\0'){
    // cout << input_buffer[pos] << endl;
    done = true;
    return false;
  }
  // cout << "\n\n------------------------\n";
  // cout << input_buffer << endl; 
  
  bool debug = false;
  int original_pos = pos;
  int prev_success_state = -1;
  int state = 0;
  int prev_success_state_type = -1;

  while(pos != input_buffer.size()){    
    char input = input_buffer[pos];

    if (debug) cout << "reading [" << input << "]" << endl;
    
    if(input < 0){
      break;
    }
    state = table[state][input];
    current_state = state;
    if (debug) cout << "current_state = " << current_state << " | table state = " << state << endl;
    if(state == -1){
      break;
    }

    
    if(table[state][0] == 1){
      prev_success_state = pos;
      prev_success_state_type = state; 
      if(debug) cout << "this was a winning state" << endl;     
    }
    
    
    
    pos++;
  }

  // if(table[state][0] != 1){
  //   state = -1;
  // }
  string new_string="";

  if(prev_success_state > original_pos){
    // cout <<"original pos: " << original_pos << endl;
    // cout << __LINE__ <<endl;
    pos = prev_success_state+1;
    for(int i = original_pos; i< pos; i++){
      new_string+= input_buffer.at(i);
    }
    input_buffer = new_string;
    current_state=prev_success_state_type;
    return true;
  } else {
    pos = original_pos;
    current_state = table[0][input_buffer.at(pos)];
    new_string = input_buffer.at(pos);
    input_buffer = new_string;
    return false;
  }
}