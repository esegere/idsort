#include "argh/argh.hpp"
#include "sortm.hpp"
#include <iostream>

int main(int argc, char* argv[]){
  argh::parser cli;
  cli.parse(argc, argv, argh::parser::PREFER_PARAM_FOR_UNREG_OPTION);

  if(cli[{"-S", "--sort"}]){
    return sortm::execute(cli);
  } else if (cli[{"-J", "--join"}]){
    std::cout << "join mode\n" ;
  } else {
    std::cout << "no mode selected\n" ;
    return 1 ;
  }
  
  return 0 ;
}
