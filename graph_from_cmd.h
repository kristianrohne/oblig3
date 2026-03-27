#pragma once

#include <memory>
#include <string>
#include "AbstractGraph.h"
#include "graph.h"
#include "MatrixGraph.h"

namespace graph_from_cmd {

struct ParsedArgs {
    bool verbose;
    bool use_matrix;
    std::string primary_file;
    std::string secondary_file;  // For diamond finder (query file)
};

/*
Parse command line arguments for graph programs.
argc Number of arguments, 
argv Argument array, 
allow_secondary_file If true, allows a second file argument, 
returns ParsedArgs struct with parsed values
*/
ParsedArgs parse_arguments(int argc, char** argv, bool allow_secondary_file = false);

// Create a graph instance (linked or matrix based on use_matrix flag).
std::unique_ptr<namespace_graph::AbstractGraph> create_graph(bool use_matrix);

}
