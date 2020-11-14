#include "parseopt/opterr.hpp"

namespace opterr{

  namespace colors{
    constexpr char RESET[]       = "\033[0m";
    constexpr char BLACK[]       = "\033[30m";       
    constexpr char RED[]         = "\033[31m";      
    constexpr char GREEN[]       = "\033[32m";      
    constexpr char YELLOW[]      = "\033[33m";      
    constexpr char BLUE[]        = "\033[34m";      
    constexpr char MAGENTA[]     = "\033[35m";     
    constexpr char CYAN[]        = "\033[36m";    
    constexpr char WHITE[]       = "\033[37m";   
    constexpr char BOLDBLACK[]   = "\033[1m\033[30m";
    constexpr char BOLDRED[]     = "\033[1m\033[31m";
    constexpr char BOLDGREEN[]   = "\033[1m\033[32m";
    constexpr char BOLDYELLOW[]  = "\033[1m\033[33m";
    constexpr char BOLDBLUE[]    = "\033[1m\033[34m";
    constexpr char BOLDMAGENTA[] = "\033[1m\033[35m";
    constexpr char BOLDCYAN[]    = "\033[1m\033[36m";
    constexpr char BOLDWHITE[]   = "\033[1m\033[37m";
  }

  constexpr char INDICATION_SYMBOL[] = "^";
  constexpr char LEADING_SYMBOL[] = " ";
  constexpr char WARNING_SYMBOL[] = "~";

  std::string generate_parse_error(std::string_view string_to_parse, char field_delimiter, char specifier_delimiter, int field_index, const Parseable& invalid_field){
    std::string message = colors::BOLDCYAN;
    std::string indication_line;
    int specifier_index = invalid_field.failIndex();
    int curr_specifier_index = 1;
    int curr_field_index = 1;
    bool in_field = false;
    bool in_specifier = false;
    bool passed_error = false;
    for(auto character : string_to_parse){
      message += character;
      if(character == field_delimiter){
        curr_field_index ++;
        curr_specifier_index = 1;
      } else if (character == specifier_delimiter){
        curr_specifier_index ++;
      }
      in_field = (curr_field_index == field_index);
      in_specifier = (curr_specifier_index == specifier_index);
      passed_error = (in_field && in_specifier) || passed_error;
      if(in_specifier && in_field){
        message += colors::BOLDRED;
        indication_line += colors::BOLDRED;
        indication_line += INDICATION_SYMBOL;
      }else if(in_field){
        message += colors::BOLDYELLOW;
        indication_line += colors::BOLDYELLOW;
        indication_line += WARNING_SYMBOL;
      } else{
        message += colors::BOLDCYAN;
        indication_line += passed_error ? "" : LEADING_SYMBOL;
      }
    }
    indication_line += colors::BOLDRED + std::string(" ") + std::string(invalid_field.getNonValidReason());   
    message += "\n ";
    message.append(std::move(indication_line));
    return message;
  }
}
