#include <iostream>

#include "argh/argh.hpp"
#include "sortm.hpp"

int main(int argc, char* argv[]){
    argh::parser cli;
    cli.add_params(
            {
                    "-f", "--field",
                    "-O", "--output-file"
            }
    );
    cli.parse(argc, argv, argh::parser::PREFER_PARAM_FOR_UNREG_OPTION);


    return sortm::execute(cli);
}
