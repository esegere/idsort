#include <string>
#include <utility>
#include <vector>
#include <variant>
#include <utility>
#include <functional>

#include "parseopt/opterr.hpp"

#ifndef FIELD_H
#define FIELD_H

namespace field {

  using FieldType = std::variant<long double, std::string>;

  class Field : public opterr::Parseable {
      private:
          int start = 0;
          int end = 0;
          bool ascending_order = true;
          unsigned int type = 1; //0:long double, 1:string
          bool valid = true;
          int invalid_specifier_index = 0;
          std::string_view invalid_reason = "";
        
          Field(unsigned int, unsigned int, bool, unsigned int);
        
          Field(int, std::string_view);
    
      public:
          bool isValid() const override { return this->valid; }
        
          std::string_view getNonValidReason() const override { return this->invalid_reason; }
        
          int failIndex() const override { return this->invalid_specifier_index; }
        
          int getStart() const { return this->start; }
        
          int getEnd() const { return this->end; }
        
          bool isAscending() const { return this->ascending_order; }
        unsigned int getTypeIndex() const {return this->type;}
        friend Field make_field(std::string_view);
  };

  Field make_field(std::string_view field_string);

  class Register{
    private:
      std::vector<std::pair<FieldType, bool>> columns;
      std::string line;
    public:
          void setLine(std::string text) { this->line = std::move(text); }

          std::string getLine() const { return line; }

          void addPair(const std::pair<FieldType, bool>&);

          int size() const;
      FieldType at(int index) const;
      bool orderAt(int index) const;
      bool operator<(const Register&) const;
  };
  class FieldExtractor {
    private:
      std::vector<Field> columns;
      void addField(const Field&);
    public:
      friend std::variant<FieldExtractor, std::string> parse_fields_impl(std::string_view);
      Register extract(std::string_view) const;
  };

   std::function<std::variant<FieldExtractor, std::string>()> parse_fields(std::string_view);
}

#endif
