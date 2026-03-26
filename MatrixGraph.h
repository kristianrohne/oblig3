#pragma once

#include <list>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include "AbstractGraph.h"

namespace namespace_graph {

class MatrixGraph: public AbstractGraph {
private:
    int get_or_create_index(const std::string& label);
    void delete_if_disconnected(const std::string& node_label);
    void remove_index(int i);
    void remove_isolated_nodes();

public:
    // These should be private, but making them public so we can visualize in main
    std::vector<std::string> node_labels;
    std::unordered_map<std::string,int> index_of;
    std::vector<std::vector<std::vector<std::string>>> matrix;

    // Since we only use data structures from STL, they automatically "clean up" themselves 
    MatrixGraph() = default;
    MatrixGraph(const MatrixGraph&) = default;
    MatrixGraph& operator=(const MatrixGraph&) = default;
    MatrixGraph(MatrixGraph&&) = default;
    MatrixGraph& operator=(MatrixGraph&&) = default;
    ~MatrixGraph() override = default;

    void insert_edge(const std::string& node_a_label, const std::string& edge_label, const std::string& node_b_label) override;
    void load_from_file(const std::string& text_file) override;
    void write_to_file(const std::string& text_file) const override;

    void disconnect(const std::string node_a_label, const std::string node_b_label) override;
    void remove_node(const std::string node_label) override;

    std::vector<std::string> get_nodes() const override;
    std::vector<std::string> get_out_neighbors(const std::string& label) const override;
    std::vector<std::pair<std::string, std::string>> get_labeled_out_edges(const std::string& label) const override;

};
}