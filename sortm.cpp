#include "sortm.hpp"
#include <iostream>

namespace sortm{
  
  int execute(const argh::parser& cli){
    auto extractor_or_error = field::parse_fields(
        cli(
          {"-f", "--field"},
          ""
          ).str()
        );
    if(extractor_or_error.index() == 0){// fieldExtractor
      std::get<0>(extractor_or_error).checkFieldsInfo();
      return 0 ;
    } else { //error
      std::cerr << std::get<1>(extractor_or_error) << "\n";
      return 1 ; 
    }
  }

}
