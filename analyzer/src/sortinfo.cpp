#include <fstream>
#include <algorithm>

#include "analyzer/sortinfo.hpp"

namespace sortinfo{ 

  std::variant<std::vector<field::Register>, std::string> proces_impl(const std::string& filename, const field::FieldExtractor& extractor){
    std::ifstream file(filename);
    std::string error_string;
    if(filename.empty()){
      error_string = "no input file";
      return error_string;
    }
    if(!file.is_open() || !file.good()){
      error_string = "error opening ";
      error_string += filename;
      return error_string;
    }

    std::vector<field::Register> registers;
    for(std::string line; std::getline(file, line);){
      registers.push_back(extractor.extract(line));
    }
    std::sort(registers.begin(), registers.end());
    return registers;
  }

  ret_func proces(const std::string& filename){
    return [filename](
            const field::FieldExtractor& extractor) -> std::variant<std::vector<field::Register>, std::string> {
        return proces_impl(filename, extractor);
    };
  }

}
