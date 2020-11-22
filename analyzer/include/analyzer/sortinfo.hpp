#include <string>
#include <variant>
#include <vector>
#include <functional>

#include "parseopt/field.hpp"

#ifndef SORTINFO_H
#define SORTINFO_H

namespace sortinfo{

  using ret_func = std::function<
    std::variant<std::vector<field::Register>, std::string>(field::FieldExtractor)
  >;

  ret_func proces(const std::string&);  

}
#endif
