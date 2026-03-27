#include "3_1_tarjans.h"
#include "3_1_graph_from_cmd.h"
#include <iostream>
#include <chrono>

// Helper method that prints each scc in sccs
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

// Main function, input: arc - n cmd. line arguments, argv - array of argument
int main(int argc, char** argv) {
    auto args = graph_from_cmd::parse_arguments(argc, argv, false);

    if (args.primary_file.empty()) {
        std::cerr << "No input file given\n";
        return 1;
    }

    // Create graph instance
    auto graph = graph_from_cmd::create_graph(args.use_matrix);

    // load nodes and edges from file
    graph->load_from_file(args.primary_file);

    // Initialize Tarjan class
    tarjans_algorithm::Tarjan tarjan;
    
    // To keep track of time
    auto start = std::chrono::high_resolution_clock::now();
    // Do Tarjan´s algoritm
    auto sccs_from_graph = tarjan.findSCCs(*graph);
    auto end = std::chrono::high_resolution_clock::now();

    // Time it took for Tarjans Algorithm to finish
    double ms = std::chrono::duration<double, std::milli>(end - start).count();
    
    // Print more output if verbose
    if (args.verbose) {
        print_sccs(sccs_from_graph);
    }

    // Output runtime and number of SCCs
    std::cout << "Runtime_ms: " << ms << "\n";
    std::cout << "Number of SCCs: " << sccs_from_graph.size() << "\n";
    std::cout.flush();

    return 0;
}