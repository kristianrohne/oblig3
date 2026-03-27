#pragma once

#include <list>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include "2_3_AbstractGraph.h"
#include "2_1_node_edge.h"


namespace namespace_graph {

class Graph: public AbstractGraph {
private:
    std::list<Node*> nodes;
    std::list<Edge*> edges;
    
    Node* find_node(const std::string& label) const;
    Node* get_or_create_node(const std::string& label);
    
    void delete_if_disconnected(Node* n);

public:

    Graph() = default;
    ~Graph() override;
    Graph(const Graph& other);
    Graph& operator=(const Graph& other);
    Graph(Graph&& other) noexcept;
    Graph& operator=(Graph&& other) noexcept;

    void insert_edge(const std::string& node_a_label, const std::string& edge_label, const std::string& node_b_label) override;
    void load_from_file(const std::string& text_file) override;
    void write_to_file(const std::string& text_file) const override;


    void disconnect(std::string node_a_label, std::string node_b_label) override;
    void remove_node(std::string node_label) override;

    std::vector<std::string> get_nodes() const override;
    std::vector<std::string> get_out_neighbors(const std::string& label) const override;
    std::vector<std::pair<std::string, std::string>> get_labeled_out_edges(const std::string& label) const override;

};
}
