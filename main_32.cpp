// Demo for problem 3.2: Diamond path query on both Graph and MatrixGraph

#include "graph.h"
#include "MatrixGraph.h"
#include "diamond_finder.h"
#include <iostream>
#include <memory>

void print_diamonds(const std::vector<std::pair<std::string, std::string>>& pairs) {
    if (pairs.empty()) {
        std::cout << "  (no diamond pairs found)\n";
        return;
    }
    for (size_t i = 0; i < pairs.size(); ++i) {
        std::cout << "  Pair " << i + 1 << ": " << pairs[i].first << " -> " << pairs[i].second << "\n";
    }
    std::cout << "  Total pairs: " << pairs.size() << "\n";
}

void run(const std::string& label, namespace_graph::AbstractGraph& graph,
         const std::string& graph_file, const std::string& query_file) {
    graph.load_from_file(graph_file);
    diamond_finder::Diamond diamond;
    auto pairs = diamond.find_diamonds(graph, query_file);
    std::cout << "\n[" << label << "] graph=" << graph_file << " query=" << query_file << "\n";
    print_diamonds(pairs);
}

int main() {
    std::cout << "=== 3.2: Diamond Path Query ===\n";

    namespace_graph::Graph linked;
    run("Linked-list Graph", linked, "data/scc02.dat", "data/query.dat");

    namespace_graph::MatrixGraph matrix;
    run("Matrix Graph", matrix, "data/scc02.dat", "data/query.dat");

    std::cout << "\n=== Done ===\n";
    return 0;
}
