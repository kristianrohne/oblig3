#include "3_1_graph_from_cmd.h"
#include <iostream>

namespace graph_from_cmd {

// For reading arguments from cmd line, argc- number of arguments, argv- array of argument, allow_secondary_file for diamond algorithm
ParsedArgs parse_arguments(int argc, char** argv, bool allow_secondary_file) {
    ParsedArgs args{false, false, "", ""};

    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];

        if (arg == "--verbose") {
            args.verbose = true;
        }
        else if (arg == "--silent") {
            args.verbose = false;
        }
        else if (arg == "--matrix") {
            args.use_matrix = true;
        }
        else if (arg == "--linked") {
            args.use_matrix = false;
        }
        // If unknown argument
        else if (!arg.empty() && arg[0] == '-') {
            std::cerr << "Unknown flag: " << arg << "\n";
            std::exit(1);
        }
        else if (args.primary_file.empty()) {
            args.primary_file = arg;
        }
        // If diamond, read two files
        else if (allow_secondary_file && args.secondary_file.empty()) {
            args.secondary_file = arg;
        }
        else {
            std::cerr << "Too many input files given\n";
            std::exit(1);
        }
    }

    return args;
}

// Helper method that creates either linked or matrix graph
std::unique_ptr<namespace_graph::AbstractGraph> create_graph(bool use_matrix) {
    if (use_matrix) {
        return std::make_unique<namespace_graph::MatrixGraph>();
    } else {
        return std::make_unique<namespace_graph::Graph>();
    }
}

}
