// Demo for problem 2.2: Graph (linked-list) - insert, disconnect, remove, copy/move semantics

#include "2_1_graph.h"
#include <iostream>

void print_nodes(const std::string& label, const namespace_graph::Graph& g) {
    std::cout << label << ": ";
    for (const auto& n : g.get_nodes()) std::cout << n << " ";
    std::cout << "\n";
}

int main() {
    std::cout << "=== 2.2: Linked-list Graph ===\n\n";

    // --- insert_edge ---
    namespace_graph::Graph g;
    g.insert_edge("A", "e1", "B");
    g.insert_edge("A", "e2", "C");
    g.insert_edge("B", "e3", "C");
    std::cout << "[insert_edge] A->B, A->C, B->C\n";
    print_nodes("Nodes", g);

    // --- get_out_neighbors ---
    std::cout << "\n[get_out_neighbors] A -> ";
    for (const auto& nb : g.get_out_neighbors("A")) std::cout << nb << " ";
    std::cout << "\n";

    // --- write / load ---
    g.write_to_file("data.txt");
    namespace_graph::Graph g2;
    g2.load_from_file("data.txt");
    std::cout << "\n[write_to_file / load_from_file]\n";
    print_nodes("Loaded graph nodes", g2);

    // --- disconnect ---
    g.disconnect("A", "B");
    std::cout << "\n[disconnect] removed A->B\n";
    std::cout << "A neighbors: ";
    for (const auto& nb : g.get_out_neighbors("A")) std::cout << nb << " ";
    std::cout << "\n";

    // --- remove_node ---
    g.remove_node("A");
    std::cout << "\n[remove_node] removed A\n";
    print_nodes("Remaining nodes", g);

    // --- copy constructor ---
    namespace_graph::Graph copy1(g2);
    copy1.insert_edge("D", "e4", "E");
    std::cout << "\n[copy constructor] original nodes: ";
    print_nodes("g2", g2);
    print_nodes("copy1 (added D->E)", copy1);

    // --- copy assignment ---
    namespace_graph::Graph copy2;
    copy2 = g2;
    copy2 = copy2; // self-assignment
    std::cout << "\n[copy assignment + self-assignment]\n";
    print_nodes("copy2", copy2);

    // --- move constructor ---
    namespace_graph::Graph moved1(std::move(copy1));
    std::cout << "\n[move constructor]\n";
    print_nodes("moved1", moved1);

    // --- move assignment ---
    namespace_graph::Graph moved2;
    moved2 = std::move(moved1);
    moved2 = std::move(moved2); // self-move
    std::cout << "\n[move assignment + self-move]\n";
    print_nodes("moved2", moved2);

    std::cout << "\n=== Done ===\n";
    return 0;
}
