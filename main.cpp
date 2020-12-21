#include <iostream>

#include "argh/argh.hpp"
#include "sortm.hpp"

const char* instructions = R"doc(
idsort usage:

    required arguments

        [File]

        -O, --output-file [File]

    flags

        -f, --field=field[/field]...

        defaults to the whole line

        field syntax =>	start:length:type:order

            start		->	the number of column where the field begins, the first column is 1, if omitted defaults to 1

            length		->	the number of characters in the field, if omitted defaults to the end of the line

            type		->	N for numbers or S for strings, if omitted defaults to string

            order		->	A for ascending or D for descending, if omitted defaults to ascending
)doc";

int main(int argc, char* argv[]) {
    argh::parser cli;
    cli.add_params(
            {
                    "-f", "--field",
                    "-O", "--output-file"
            }
    );
    cli.parse(argc, argv, argh::parser::PREFER_PARAM_FOR_UNREG_OPTION);

    if (cli[{"-h", "--help"}]) {
        std::cout << instructions;
        return 0;
    }
    return sortm::execute(cli);
}
