#include <sstream>

#include "parseopt/field.hpp"
#include "parseopt/parseutil.hpp"

namespace field{

  constexpr char FIELD_DELIMITER = '/';
  constexpr char SPECIFIER_DELIMITER = ':';


  Field::Field(unsigned int start, unsigned int end, bool ascending_order, unsigned int type){
    this->start = start;
    this->end = end;
    this->ascending_order = ascending_order;
    this->type = type;
  }


  Field::Field(int invalid_specifier_index, std::string_view reason){
    this->valid = false;
    this->invalid_reason = reason;
    this->invalid_specifier_index = invalid_specifier_index;
  }


  Field make_field(std::string_view field_string){
    auto specifiers = parseutil::split(field_string, SPECIFIER_DELIMITER);
    if(specifiers.size() > 4){
      return Field(5, "too many arguments"); 
    }
    while(specifiers.size() < 4){
      specifiers.emplace_back("");
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
    if(!parseutil::is_valid_number(start)){
      return Field(1, "invalid start position");
    }
      if (!parseutil::is_valid_number(end)) {
          return Field(2, "invalid length");
      }
      if (field_type != "N" && field_type != "S") {
          return Field(3, "invalid field type");
      }
      if (order != "A" && order != "D") {
          return Field(4, "invalid sort order");
      }
      int start_n = 0;
      int end_n = 0;
      unsigned int type_n = ((field_type == "S") ? 1 : 0); //0:long double 1:string
      bool ascending_order = (order == "A");
      std::istringstream(start) >> start_n;
      std::istringstream(end) >> end_n;
      return Field(start_n, end_n, ascending_order, type_n);
  }


    void Register::addPair(const std::pair<FieldType, bool>& new_pair) {
        this->columns.push_back(new_pair);
    }


  int Register::size() const{
    return this->columns.size();
  }  


  FieldType Register::at(int index) const{
    return this->columns.at(index).first;
  }

  bool Register::orderAt(int index) const{
    return this->columns.at(index).second;
  }


  template <int NUM_OF_TYPES>
  int compare(FieldType variant1, FieldType variant2){
      constexpr int VARIANT_INDEX = NUM_OF_TYPES - 1;
      int result = 0;
    if (variant1.index() == VARIANT_INDEX){
      if( std::get<VARIANT_INDEX>(variant1) <  std::get<VARIANT_INDEX>(variant2) ){
        result = -1;
      } else if (std::get<VARIANT_INDEX>(variant1) ==  std::get<VARIANT_INDEX>(variant2)){
        result = 0;
      } else {
        result = 1;
      }
    } else {
      if constexpr (VARIANT_INDEX > 0){
        result = compare<VARIANT_INDEX>(variant1, variant2);
      }
    }
    return result;
  }


  bool Register::operator<(const Register& reg2) const{
    int reg_size = this->size();
    for (int i=0; i<reg_size; i++){
      int compare_result = compare<std::variant_size_v<FieldType>>(this->at(i), reg2.at(i));
      compare_result *= this->orderAt(i) ? 1 : -1 ;
      if (compare_result < 0){
        return true;
      } else if (compare_result > 0){
        return false;
      }
    }
    return false;
  }


  Register FieldExtractor::extract(std::string_view text_line) const{
    Register line_register;
    line_register.setLine(std::string(text_line));
    // positive index lambda
    auto to_positive_index = [size=text_line.size()](int original_index)->unsigned int{
      int position = original_index<0 ? size + original_index + 1 : original_index;
      if(position > size){
        position = size;
      }else if(position < 0){
        position = 0;
      }
      return position;
    };
    //
      long double number = 0;
      std::string word;
      for (const auto& field : this->columns) {
          word = text_line.substr(
                  to_positive_index(field.getStart()),
                  to_positive_index(field.getEnd())
          );
          switch (field.getTypeIndex()) {
              case 0:  //long double
                  std::istringstream(word) >> number;
                  line_register.addPair(
                          std::make_pair(number, field.isAscending())
                  );
          break;
        case 1:  //string
          line_register.addPair(
              std::make_pair(word, field.isAscending())
              );
          break;
      }
    }
    return line_register;
  }


  void FieldExtractor::addField(const Field& new_field){
    this->columns.push_back(new_field);
  }


  std::variant<FieldExtractor, std::string> parse_fields_impl(std::string_view string_to_parse){
    bool all_correct = true;
    auto splitted = parseutil::split(string_to_parse, FIELD_DELIMITER);
    int num_of_fields = splitted.size();
    FieldExtractor grouped_fields;
    std::string parse_error;
    for(int i=0; i < num_of_fields; i++){
      auto curr_field = make_field(splitted[i]);
      if(curr_field.isValid()){
        grouped_fields.addField(curr_field);
      } else {
        all_correct = false;
        parse_error = opterr::generate_parse_error(string_to_parse, FIELD_DELIMITER, SPECIFIER_DELIMITER, i+1, curr_field);
        break;
      }
    }
    if(all_correct){
      return grouped_fields;
    } else {
      return parse_error;
    }
  }

  std::function<std::variant<FieldExtractor, std::string>()> parse_fields(std::string_view string_to_parse){
    return [string_to_parse]() -> std::variant<FieldExtractor, std::string> {
      return parse_fields_impl(string_to_parse);
    };
  }

}
