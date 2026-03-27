#include "3_2_diamond_finder.h"
#include "3_1_graph_from_cmd.h"
#include <iostream>
#include <chrono>

// Helper functions for printing out pairs
void print_diamonds(const std::vector<std::pair<std::string, std::string>>& pairs) {
    int i = 1;
    for (const auto& p : pairs) {
        std::cout << "Pair " << i++ << ": " << p.first << " -> " << p.second << "\n";
    }
}

// Main function, input: arc - n cmd. line arguments, argv - array of argument
int main(int argc, char** argv) {
    // Read arguments from cmd line
    auto args = graph_from_cmd::parse_arguments(argc, argv, true);

    // If argument not recognized, it gets treated as an error
    if (args.primary_file.empty() || args.secondary_file.empty()) {
        std::cerr << "Usage: ./graph_diamond [--linked|--matrix] [--verbose|--silent] <graph_file> <query_file>\n";
        return 1;
    }

    // Create graph instance
    auto graph = graph_from_cmd::create_graph(args.use_matrix);

    // Load nodes and edges for graph from file
    graph->load_from_file(args.primary_file);

    diamond_finder::Diamond diamond;
    
    // Keep track of time for alghorithm
    auto start = std::chrono::high_resolution_clock::now();
    auto pairs = diamond.find_diamonds(*graph, args.secondary_file);
    auto end = std::chrono::high_resolution_clock::now();

    // Time it takes for algorithm to ifnish
    double ms = std::chrono::duration<double, std::milli>(end - start).count();
    std::cout << "Runtime_ms: " << ms << "\n";

    // Print more output if verbose mode
    if (args.verbose) {
        print_diamonds(pairs);
    }

    std::cout << "Number of diamond pairs: " << pairs.size() << "\n";
    return 0;
}