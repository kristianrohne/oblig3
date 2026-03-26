// Demo for problem 3.1: Tarjan's SCC algorithm on both Graph and MatrixGraph

#include "graph.h"
#include "MatrixGraph.h"
#include "tarjans.h"
#include <iostream>
#include <memory>

void print_sccs(const std::vector<std::vector<std::string>>& sccs) {
    for (size_t i = 0; i < sccs.size(); ++i) {
        std::cout << "  SCC " << i + 1 << ": ";
        for (const auto& n : sccs[i]) std::cout << n << " ";
        std::cout << "\n";
    }
    std::cout << "  Total SCCs: " << sccs.size() << "\n";
}

void run(const std::string& label, namespace_graph::AbstractGraph& graph, const std::string& file) {
    graph.load_from_file(file);
    tarjans_algorithm::Tarjan tarjan;
    auto sccs = tarjan.findSCCs(graph);
    std::cout << "\n[" << label << "] on " << file << "\n";
    print_sccs(sccs);
}

int main() {
    std::cout << "=== 3.1: Tarjan's SCC Algorithm ===\n";

    // Run on small dataset with both graph types
    namespace_graph::Graph linked;
    run("Linked-list Graph", linked, "data/scc02.dat");

    namespace_graph::MatrixGraph matrix;
    run("Matrix Graph", matrix, "data/scc02.dat");

    // Run on larger dataset
    namespace_graph::Graph linked2;
    run("Linked-list Graph", linked2, "data/scc04.dat");

    namespace_graph::MatrixGraph matrix2;
    run("Matrix Graph", matrix2, "data/scc04.dat");

    std::cout << "\n=== Done ===\n";
    return 0;
}
