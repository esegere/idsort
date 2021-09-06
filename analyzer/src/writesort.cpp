#include <fstream>
#include <sstream>
#include <iostream>

#include "analyzer/writesort.hpp"

namespace writesort {
    
    std::variant<int, std::string>
    write_to_impl(const std::string& filename, const std::vector<field::Register>& lines) {
        std::ostream* output;
        std::string error_string;
        if (filename.empty()) {
            output = &std::cout;
        } else {
            std::ofstream file(filename);
            if (!file.is_open() || !file.good()) {
                error_string = "error opening ";
                error_string += filename;
                return error_string;
            }
            output = &file;
        }
        std::stringstream ss;
        for (const auto& reg: lines) {
            ss << reg.getLine() << "\n";
        }
        *output << ss.str();
        return 0;
    }
    
    ret_func write_to(const std::string& filename) {
        return [filename](const std::vector<field::Register>& ordered_lines) -> std::variant<int, std::string> {
            return write_to_impl(filename, ordered_lines);
        };
    }
}