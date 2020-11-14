#include <string>
#include <vector>

#ifndef PARSEUTIL_H
#define PARSEUTIL_H

namespace parseutil {

  std::vector<std::string> split(std::string_view, char);

  bool is_valid_number(std::string_view);

}
#endif

