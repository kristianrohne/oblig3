#include "graph.h"
#include "tarjans.h"
#include <iostream>
#include <memory>
#include <string>

void print_sccs(const std::vector<std::vector<std::string>>& sccs) {
    int i = 1;
    for (const auto& scc : sccs) {
        std::cout << "SCC " << i++ << ": ";
        for (const auto& node : scc) {
            std::cout << node << " ";
        }
        std::cout << "\n";
    }
}


int main(int argc, char** argv) {
    bool verbose = false;
    bool use_matrix = false;
    std::string filename;

    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];

        if (arg == "--verbose") {
            verbose = true;
        }
        else if (arg == "--silent") {
            verbose = false;
        }
        else if (arg == "--matrix") {
            use_matrix = true;
        }
        else if (arg == "--linked") {
            use_matrix = false;
        }
        else if (!arg.empty() && arg[0] == '-') {
            std::cerr << "Unknown flag: " << arg << "\n";
            return 1;
        }
        else {
            filename = arg;
        }
    }

    if (filename.empty()) {
        std::cerr << "No input file given\n";
        return 1;
    }

    std::unique_ptr<namespace_graph::AbstractGraph> graph;

    if (use_matrix) {
        graph = std::make_unique<namespace_graph::MatrixGraph>();
    }
    else {
        graph = std::make_unique<namespace_graph::Graph>();
    }

    graph->load_from_file(filename);

    tarjans_algorithm::Tarjan tarjan;
    auto sccs_from_graph = tarjan.findSCCs(*graph);

    if (verbose) {
        print_sccs(sccs_from_graph);
    }

    std::cout << "Number of SCCs: " << sccs_from_graph.size() << "\n";

    return 0;
}