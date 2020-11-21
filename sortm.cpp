#include <iostream>

#include "sortm.hpp"
#include "parseopt/field.hpp"
#include "analyzer/sortinfo.hpp"

namespace sortm{
  
  int execute(const argh::parser& cli){
    auto extractor_or_error = field::parse_fields(
        cli(
          {"-f", "--field"},
          ":"
          ).str()
        )();
    if(extractor_or_error.index() == 0){// fieldExtractor
      sortinfo::proces(
          cli[1]
          )(std::get<0>(extractor_or_error));
      return 0 ;
    } else { //error
      std::cerr << std::get<1>(extractor_or_error) << "\n";
      return 1 ; 
    }
  }

}
