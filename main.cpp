#include <iostream>

#include "argh/argh.hpp"
#include "sortm.hpp"

int main(int argc, char* argv[]){
  argh::parser cli;
  cli.add_params(
    {
      "-S", "--sort",
      "-J", "--join",
      "-f", "--field",
      "-O", "--output-file"
    }
  );
  cli.parse(argc, argv, argh::parser::PREFER_PARAM_FOR_UNREG_OPTION);

  if(cli[{"-S", "--sort"}]){
    return sortm::execute(cli);
  } else if (cli[{"-J", "--join"}]){
    std::cout << "join mode\n" ;
  } else {
    std::cerr << "no mode selected\n" ;
    return 1 ;
  }
  
  return 0 ;
}
