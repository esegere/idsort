#include <iostream>

#include "flow.hpp"
#include "sortm.hpp"
#include "parseopt/field.hpp"
#include "analyzer/sortinfo.hpp"
#include "analyzer/writesort.hpp"

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
    ).then(
      writesort::write_to(
        cli(
          {"-O", "--output-file"}
          ).str()
      )
    );
  }

}
