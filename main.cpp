#include <iostream>
//#include "cxxopts.hpp"
#include "opzioni.h"

using namespace std;

int main(int argc, char *argv[])
{
    Opzioni opzioni;
    opzioni.addOpzione(ARG_SUBCOM,"init","Inizializza il container");
    opzioni.addOpzione(ARG_DOUBLE,"--git-modified","-m","","carica il repository modificato da git");
    opzioni.passArguments(argc, argv);
    for(int i = 0 ; i < opzioni.privateToken.size() ; i++) {
        std::cout << i << "\t" << opzioni.privateToken[i] << std::endl;
    }
}
/*
int _main(int argc, char *argv[])
{
    int MAIN_EXIT_CODE = 0;

    cxxopts::Options option("retouch");

    option.add_options()
        ("n,number", "Show line numbers")
        ("E,show-ends", "Show line endings")
        ("version", "Show the version")
        ("input_files", "Input file(s) to concatenate", cxxopts::value<std::vector<std::string>>()
    );

    option.parse_positional({ "version", "init", "refresh", "pull", "push"});

    cxxopts::ParseResult result;

    try {
        result = option.parse(argc, argv);
        if (result.arguments().empty()) {
            MAIN_EXIT_CODE = EXIT_FAILURE;
        }
    } catch (const exception &x) {
        std::cerr << option.program() << ": " << x.what() << '\n';
        MAIN_EXIT_CODE = EXIT_FAILURE;
    }

    if (MAIN_EXIT_CODE != 0){
        std::cerr << "usage: " << option.program() << " [options] <input_file> ...\n";
        return MAIN_EXIT_CODE;
    }

    cout << "Hello World!" << endl;
    return MAIN_EXIT_CODE;
}
*/
