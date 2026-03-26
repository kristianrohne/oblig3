#include "graph.h"
#include "MatrixGraph.h"
#include "diamond_finder.h"
#include <iostream>
#include <memory>
#include <string>

void print_diamonds(const std::vector<std::pair<std::string, std::string>>& pairs) {
    int i = 1;
    for (const auto& p : pairs) {
        std::cout << "Pair " << i++ << ": " << p.first << " -> " << p.second << "\n";
    }
}

int main(int argc, char** argv) {
    bool verbose = false;
    bool use_matrix = false;
    std::string graph_file;
    std::string query_file;

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
        else if (graph_file.empty()) {
            graph_file = arg;
        }
        else if (query_file.empty()) {
            query_file = arg;
        }
        else {
            std::cerr << "Too many input files given\n";
            return 1;
        }
    }

    if (graph_file.empty() || query_file.empty()) {
        std::cerr << "Usage: ./graph_diamond [--linked|--matrix] [--verbose|--silent] <graph_file> <query_file>\n";
        return 1;
    }

    std::unique_ptr<namespace_graph::AbstractGraph> graph;

    if (use_matrix) {
        graph = std::make_unique<namespace_graph::MatrixGraph>();
    } else {
        graph = std::make_unique<namespace_graph::Graph>();
    }

    graph->load_from_file(graph_file);

    diamond_finder::Diamond diamond;
    auto pairs = diamond.find_diamonds(*graph, query_file);

    if (verbose) {
        print_diamonds(pairs);
    }

    std::cout << "Number of diamond pairs: " << pairs.size() << "\n";
    return 0;
}