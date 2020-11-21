#include <string>
#include <vector>
#include <variant>
#include <sstream>
#include <utility>
#include <functional>

#include "parseopt/opterr.hpp"

#ifndef FIELD_H
#define FIELD_H

namespace field {

  using FieldType = std::variant<float, std::string>;

  class Field: public opterr::Parseable{
    private:
        int start;
        int end;
        bool ascending_order;
        unsigned int type; //0:float, 1:string
        bool valid;
        int invalid_specifier_index;
        std::string_view invalid_reason;

        Field(unsigned int, unsigned int, bool, unsigned int);
        Field(int, std::string_view);
      public:
        bool isValid() const override {return this->valid;}
        std::string_view getNonValidReason() const override {return this->invalid_reason;}
        int failIndex() const override {return this->invalid_specifier_index;}
        int getStart() const {return this->start;}
        int getEnd() const {return this->end;}
        bool isAscending() const {return this->ascending_order;}
        unsigned int getTypeIndex() const {return this->type;}
        friend Field make_field(std::string_view);
  };

  Field make_field(std::string_view field_string);

  class Register{
    private:
      std::vector<std::pair<FieldType, bool>> columns;
      unsigned int line_number;
    public:
      Register(unsigned int number): line_number(number){}
      int getLineNumber() const{return line_number;}
      void addPair(std::pair<FieldType, bool>);
      int size() const;
      FieldType at(int index) const;
      bool orderAt(int index) const;
      bool operator<(const Register&) const;
  };
  class FieldExtractor {
    private:
      std::vector<Field> columns;
      mutable unsigned int current_line = 0;
      void addField(const Field&);
    public:
      friend std::variant<FieldExtractor, std::string> parse_fields_impl(std::string_view);
      Register extract(std::string_view) const;
  };

   std::function<std::variant<FieldExtractor, std::string>()> parse_fields(std::string_view);
}

#endif
