#include <vector>
#include <string>
#include <functional>
#include <variant>

#include "parseopt/field.hpp"

#ifndef WRITESORT_H
#define WRITESORT_H

namespace writesort{
    
    using ret_func = std::function<
        std::variant<int, std::string>(std::vector<field::Register>)
    >;

    ret_func write_to(const std::string&);
}
#endif