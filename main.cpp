// Main for oblig 2. Her er det noen eksempeler av hvordan man kjører koden

#include "graph.h"
#include <iostream>

void print_matrix(const namespace_graph::MatrixGraph& graph) {
    for (size_t i = 0; i <  graph.matrix.size(); ++i) {
        for (size_t j = 0; j <  graph.matrix[i].size(); ++j) {

            std::cout << "[";
            for (const auto& label :  graph.matrix[i][j]) {
                std::cout << label << ",";
            }
            std::cout << "] ";
        }
        std::cout << "\n";
    }
}


int main() {
    namespace_graph::Graph my_graph;

    my_graph.insert_edge("A", "A-B", "B");
    my_graph.insert_edge("A", "A-C", "C");

    my_graph.write_to_file("data.txt");

    namespace_graph::MatrixGraph matrix_graph;
    matrix_graph.load_from_file("data.txt");

    matrix_graph.insert_edge("B", "B-A", "A");

    print_matrix(matrix_graph);
    
    matrix_graph.write_to_file("data2.txt");

    my_graph.disconnect("A", "B");
    my_graph.remove_node("A");

    matrix_graph.disconnect("A", "B");
    matrix_graph.remove_node("B");
    

    // Copy assignment
    namespace_graph::Graph graph_2;
    graph_2 = my_graph;

    // Self-copy assignment
    graph_2 = graph_2;

    // Move constructor
    namespace_graph::Graph graph3(std::move(graph_2));

    graph3.insert_edge("D", "D-E", "E");

    // Move assignment
    namespace_graph::Graph graph4;
    graph4.insert_edge("E", "E-B", "B");
    graph4 = std::move(graph3);

    // Self-move assignment
    graph4 = std::move(graph4);

    // Copy constructor
    namespace_graph::MatrixGraph matrix_graph2(matrix_graph);

    // Copy assignment
    namespace_graph::MatrixGraph matrix_graph3;
    matrix_graph3 = matrix_graph;
    matrix_graph3 = matrix_graph3;

    // Move constructor
    namespace_graph::MatrixGraph matric_graph4(std::move(matrix_graph3));
    matrix_graph3.insert_edge("K", "K-E", "E"); 

    // Move assignment
    namespace_graph::MatrixGraph matrix_graph5;
    matrix_graph5 = std::move(matrix_graph3);
    matrix_graph5 = std::move(matrix_graph5);
    return 0;
}