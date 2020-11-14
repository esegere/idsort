#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "analyzer/sortinfo.hpp"

namespace sortinfo{

  std::variant<std::vector<field::Register>, std::string> proces(const std::string& filename, const field::FieldExtractor& extractor){
    std::ifstream file(filename);
    std::string error_string;
    if(!file.is_open()){
      error_string += "error opening ";
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

}
