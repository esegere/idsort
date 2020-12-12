#include <fstream>
#include <sstream>

#include "analyzer/writesort.hpp"

namespace writesort{

    std::variant<int, std::string> write_to_impl(const std::string& filename, const std::vector<field::Register>& lines){
        std::ofstream file(filename);
        std::string error_string;
        if(filename.empty()){
            error_string = "no output file";
            return error_string;
        }
        if(!file.is_open() || !file.good()){
            error_string = "error opening ";
            error_string += filename;
            return error_string;
        }
        std::stringstream ss;
        for (const auto& reg : lines) {
            ss << reg.getLine() << "\n";
        }
        file << ss.str();
        return 0;
    }

    ret_func write_to(const std::string& filename) {
        return [filename](const std::vector<field::Register>& ordered_lines) -> std::variant<int, std::string> {
            return write_to_impl(filename, ordered_lines);
        };
    }
}