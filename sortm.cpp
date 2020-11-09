#include "sortm.hpp"
#include <iostream>

namespace sortm{
  
  int execute(const argh::parser& cli){
    std::cout << "sort mode\n" ;
    auto extractor_or_error = field::parse_fields(
        cli(
          {"-f", "--field"},
          ""
          ).str()
        );
    if(extractor_or_error.index() == 0){
      return 0 ;
    } else {
      std::cout << std::get<1>(extractor_or_error) << "\n";
      return 1 ; 
    }
  }

}
