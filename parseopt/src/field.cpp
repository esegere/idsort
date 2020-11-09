#include "parseopt/field.hpp"
#include <sstream>
#include <string>
#include <algorithm>

namespace field{

  constexpr char FIELD_DELIMITER = '/';
  constexpr char SPECIFIER_DELIMITER = ':';

  std::vector<std::string> split(std::string_view, char);
  
  Field::Field(unsigned int start, unsigned int end, bool ascending_order, unsigned int type){
    this->start = start;
    this->end = end;
    this->ascending_order = ascending_order;
    this->type = type;
    this->valid = true;
    this->invalid_reason = "";
    this->invalid_specifier_index = 0;
  }


  Field::Field(int invalid_specifier_index, std::string_view reason){
    this->start = 0;
    this->end = 0;
    this->ascending_order = true;
    this->type = 1; //string
    this->valid = false;
    this->invalid_reason = reason;
    this->invalid_specifier_index = invalid_specifier_index;
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

  Field make_field(std::string_view field_string){
    auto specifiers = split(field_string, SPECIFIER_DELIMITER);
    if(specifiers.size() > 4){
      return Field(1, "too many arguments"); 
    }
    while(specifiers.size() < 4){
      specifiers.push_back("");
    }
    std::string start = specifiers[0];
    std::string end = specifiers[1];
    std::string field_type = specifiers[2];
    std::string order = specifiers[3];
    //defaults begin
    if(start.empty()){
      start += '0';
    }
    if(end.empty()){
      end += "-1" ;
    }
    if(field_type.empty()){
      field_type += 'S';
    }
    if(order.empty()){
      order += 'A';
    }
    //defaults end
    if(!is_valid_number(start)){
      return Field(1, "invalid start position");
    }
    if(!is_valid_number(end)){
      return Field(2, "invalid length");
    }
    if( field_type != "N" && field_type != "S" ){
      return Field(3, "invalid field type");
    }
    if( order != "A" && order != "D"){
      return Field(4, "invalid sort order");
    }
    int start_n;
    int end_n;
    unsigned int type_n = ( (field_type == "S") ? 1 : 0 ); //0:float 1:string
    bool ascending_order =  (order == "A") ;
    std::istringstream(start) >> start_n;
    std::istringstream(end) >> end_n;
    return Field(start_n, end_n, ascending_order, type_n);
  }


  int Register::size() const{
    return columns.size();
  }  


  FieldType Register::at(int index) const{
    return columns.at(index);
  }


  template <int NUM_OF_TYPES>
  bool compare(FieldType variant1, FieldType variant2){
    constexpr int VARIANT_INDEX = NUM_OF_TYPES - 1 ;
    bool result = false ;
    try{
      std::get<VARIANT_INDEX>(variant1) <  std::get<VARIANT_INDEX>(variant2) ;
    } catch (const std::bad_variant_access& e){
      if constexpr (VARIANT_INDEX > 0) {
        result = compare<VARIANT_INDEX>(variant1, variant2);
      }
    }
    return result;
  }


  bool Register::operator<(const Register& reg2) const{
    bool is_lower = false;
    int reg_size = this->size();
    for (int i=0; i<reg_size; i++){
      is_lower |= compare<std::variant_size_v<FieldType>>(this->at(i),reg2.at(i));
    }
    return is_lower;
  }


  Register extract(std::string_view text_line){
    return Register{};
  }


  std::vector<std::string> split(std::string_view complete_string, char division){
    std::vector<std::string> splitted_strings;
    std::string temp_str = "";
    for(auto character : complete_string){
      if (character == division){
        splitted_strings.push_back(temp_str);
        temp_str.clear();
      } else {
        temp_str += character ; 
      }
    }
    if (!temp_str.empty()){
      splitted_strings.push_back(temp_str);
    }
    return splitted_strings ;
  }


  void FieldExtractor::addField(const Field& new_field){
    this->columns.push_back(new_field);
  }

  std::string generate_parse_error(std::string_view string_to_parse, int field_index, const Field& invalid_field){
    std::string message = std::string(string_to_parse);
    std::string indication_line;
    int specifier_index = invalid_field.failIndex();
    int curr_specifier_index = 1;
    int curr_field_index = 1;
    for(auto character : string_to_parse){
      if(character == FIELD_DELIMITER){
        curr_field_index ++;
        curr_specifier_index = 1;
      } else if (character == SPECIFIER_DELIMITER){
        curr_specifier_index ++;
      }
      if(curr_specifier_index == specifier_index && curr_field_index == field_index){
        indication_line += " ^ ";
        indication_line += invalid_field.getNonValidReason();
        break;
      } else {
        indication_line += ' ';
      }
    }
    message += '\n';
    message.append(std::move(indication_line));
    return message;
  }

  std::variant<FieldExtractor, std::string> parse_fields(std::string_view string_to_parse){
    bool all_correct = true;
    auto splitted = split(string_to_parse, FIELD_DELIMITER);
    int num_of_fields = splitted.size();
    FieldExtractor grouped_fields;
    std::string parse_error;
    for(int i=0; i < num_of_fields; i++){
      auto curr_field = make_field(splitted[i]);
      if(curr_field.isValid()){
        grouped_fields.addField(curr_field);
      } else {
        all_correct = false;
        parse_error = generate_parse_error(string_to_parse, i+1, curr_field);
        break;
      }
    }
    if(all_correct){
      return grouped_fields;
    } else {
      return parse_error;
    }
  }

}
