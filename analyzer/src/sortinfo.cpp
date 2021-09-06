#include <fstream>
#include <algorithm>
#include <iostream>

#include "analyzer/sortinfo.hpp"

namespace sortinfo {
    
    std::variant<std::vector<field::Register>, std::string>
    proces_impl(const std::string& filename, const field::FieldExtractor& extractor) {
        std::istream* input;
        std::string error_string;
        if (filename.empty()) {
            input = &std::cin;
        } else {
            std::ifstream file(filename);
            if (!file.is_open() || !file.good()) {
                error_string = "error opening ";
                error_string += filename;
                return error_string;
            }
            input = &file;
        }
        
        std::vector<field::Register> registers;
        for (std::string line; std::getline(*input, line);) {
            registers.push_back(extractor.extract(line));
        }
        std::sort(registers.begin(), registers.end());
        return registers;
    }
    
    ret_func proces(const std::string& filename) {
        return [filename](
            const field::FieldExtractor& extractor
        ) -> std::variant<std::vector<field::Register>, std::string> {
            return proces_impl(filename, extractor);
        };
    }
    
}
