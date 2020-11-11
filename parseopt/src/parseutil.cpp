#include "parseopt/parseutil.hpp"
#include <algorithm>

namespace parseutil {

  std::vector<std::string> split(std::string_view string_to_split, char delimitter){
    std::vector<std::string> splitted_strings;
    std::string temp_str = "";
    for(auto character : string_to_split){
      if (character == delimitter){
        splitted_strings.push_back(temp_str);
        temp_str.clear();
      } else {
        temp_str += character;
      }
    }
    if (!temp_str.empty()){
    splitted_strings.push_back(temp_str);
    }
    return splitted_strings;
  }


  bool is_valid_number(std::string_view field_num){
    auto check_digit = [](char character, bool include_sign)->bool{
      return std::isdigit(character) || ( include_sign && (character == '-' || character == '+') );
    };
    auto begin = field_num.begin();
    bool first_is_valid = check_digit(*begin, true);
    begin++ ;
    return first_is_valid && std::all_of(
      begin,
      field_num.end(),
      [&check_digit](char character)->bool{return check_digit(character, false);}
    );
  }

}
