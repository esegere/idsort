#include <iostream>

#include "sortm.hpp"
#include "parseopt/field.hpp"
#include "analyzer/sortinfo.hpp"
#include "flow.hpp"

namespace sortm{
  
  int execute(const argh::parser& cli){
    flow::FlowStarter flow_handler;
    
    return flow_handler.first(
      field::parse_fields(
        cli(
          {"-f", "--field"},
          ":"
        ).str()
      )
    ).then(
      sortinfo::proces(
        cli[1]
      )
    );
  }

}
