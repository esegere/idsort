#include <string>
#include <vector>
#include <variant>

#ifndef FIELD_H
#define FIELD_H

namespace field {

  using FieldType = std::variant<float, std::string>;

  class Field{
      private:
        int start;
        int end;
        bool ascending_order;
        unsigned int type; //0:float, 1:string
        bool valid;
        int invalid_specifier_index;
        std::string_view invalid_reason;

        Field(unsigned int start, unsigned int end, bool ascending_order, unsigned int type);
        Field(int invalid_specifier_index, std::string_view reason);
      public:
        bool isValid() const {return this->valid;}
        std::string_view getNonValidReason() const {return this->invalid_reason;}
        int failIndex() const{return this->invalid_specifier_index;}
        int getStart() const {return this->start;}
        int getEnd() const {return this->end;}
        bool isAscending() const {return this->ascending_order;}
        unsigned int getTypeIndex() const {return this->type;}
        friend Field make_field(std::string_view field_string);
  };

  Field make_field(std::string_view field_string);

  class Register{
    private:
      std::vector<FieldType> columns;
      int line_number;
    public:
      int size() const;
      FieldType at(int index) const;
      bool operator<(const Register& reg2) const;
  };

  class FieldExtractor {
    private:
      std::vector<Field> columns;
      void addField(const Field& new_field);
    public:
      friend std::variant<FieldExtractor, std::string> parse_fields(std::string_view string_to_parse);
      Register extract(std::string_view text_line);
  };

  std::variant<FieldExtractor, std::string> parse_fields(std::string_view string_to_parse);
}

#endif
