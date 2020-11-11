#include <string>
#include <vector>

#ifndef PARSEUTIL_H
#define PARSEUTIL_H

namespace parseutil {

  std::vector<std::string> split(std::string_view string_to_split, char delimitter);

  bool is_valid_number(std::string_view field_num);

}
#endif

