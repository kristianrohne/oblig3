// Demo for problem 2.5: MatrixGraph - insert, disconnect, remove, copy/move semantics

#include "MatrixGraph.h"
#include <iostream>

void print_matrix(const namespace_graph::MatrixGraph& g) {
    const auto& labels = g.node_labels;
    // Header row
    std::cout << "     ";
    for (const auto& l : labels) std::cout << l << "    ";
    std::cout << "\n";
    for (size_t i = 0; i < g.matrix.size(); ++i) {
        std::cout << labels[i] << "  ";
        for (size_t j = 0; j < g.matrix[i].size(); ++j) {
            std::cout << "[";
            for (const auto& lbl : g.matrix[i][j]) std::cout << lbl;
            std::cout << "]  ";
        }
        std::cout << "\n";
    }
}

int main() {
    std::cout << "=== 2.5: Matrix Graph ===\n\n";

    // --- insert_edge ---
    namespace_graph::MatrixGraph g;
    g.insert_edge("A", "e1", "B");
    g.insert_edge("A", "e2", "C");
    g.insert_edge("B", "e3", "C");
    std::cout << "[insert_edge] A->B, A->C, B->C\n";
    print_matrix(g);

    // --- get_out_neighbors ---
    std::cout << "\n[get_out_neighbors] A -> ";
    for (const auto& nb : g.get_out_neighbors("A")) std::cout << nb << " ";
    std::cout << "\n";

    // --- get_labeled_out_edges ---
    std::cout << "[get_labeled_out_edges] A -> ";
    for (const auto& [lbl, nb] : g.get_labeled_out_edges("A"))
        std::cout << "(" << lbl << "," << nb << ") ";
    std::cout << "\n";

    // --- write / load ---
    g.write_to_file("data_matrix.txt");
    namespace_graph::MatrixGraph g2;
    g2.load_from_file("data_matrix.txt");
    std::cout << "\n[write_to_file / load_from_file]\n";
    print_matrix(g2);

    // --- disconnect ---
    g.disconnect("A", "B");
    std::cout << "\n[disconnect] removed A->B\n";
    print_matrix(g);

    // --- remove_node ---
    g.remove_node("A");
    std::cout << "\n[remove_node] removed A\n";
    print_matrix(g);

    // --- copy constructor ---
    namespace_graph::MatrixGraph copy1(g2);
    copy1.insert_edge("D", "e4", "E");
    std::cout << "\n[copy constructor] copy1 (added D->E)\n";
    print_matrix(copy1);

    // --- copy assignment + self-assignment ---
    namespace_graph::MatrixGraph copy2;
    copy2 = g2;
    copy2 = copy2;
    std::cout << "\n[copy assignment + self-assignment] copy2\n";
    print_matrix(copy2);

    // --- move constructor ---
    namespace_graph::MatrixGraph moved1(std::move(copy1));
    std::cout << "\n[move constructor] moved1\n";
    print_matrix(moved1);

    // --- move assignment + self-move ---
    namespace_graph::MatrixGraph moved2;
    moved2 = std::move(moved1);
    moved2 = std::move(moved2);
    std::cout << "\n[move assignment + self-move] moved2\n";
    print_matrix(moved2);

    std::cout << "\n=== Done ===\n";
    return 0;
}
