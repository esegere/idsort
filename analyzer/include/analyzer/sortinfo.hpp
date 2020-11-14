#include <string>
#include <variant>
#include <vector>

#include "parseopt/field.hpp"

#ifndef SORTINFO_H
#define SORTINFO_H

namespace sortinfo{

  std::variant<std::vector<field::Register>, std::string>proces(const std::string&, const field::FieldExtractor&);

}
#endif
