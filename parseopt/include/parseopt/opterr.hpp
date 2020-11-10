#include <string>

#ifndef OPTERR_H
#define OPTERR_H

namespace opterr{

  class Parseable{
    public:
      virtual bool isValid() const = 0;
      virtual std::string_view getNonValidReason() const = 0;
      virtual int failIndex() const = 0; 
  };

  std::string generate_parse_error(std::string_view string_to_parse, char field_delimiter, char specifier_delimiter, int field_index, const Parseable& invalid_field);
}
#endif
