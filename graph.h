#pragma once

#include <list>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>

namespace namespace_graph {

class Edge;

class Node {
private:
    // label of node
    std::string label_;
    // To store out-edges
    std::list<Edge*> out_edges_;
    // To store in-edges
    std::list<Edge*> in_edges_;

public:
    explicit Node(std::string label);

    const std::string& label() const { return label_; }
    const std::list<Edge*>& out_edges() const { return out_edges_; }
    const std::list<Edge*>& in_edges() const { return in_edges_; }


    void add_out_edge(Edge* e);
    void add_in_edge(Edge* e);

    void remove_out_edge(Edge* e);
    void remove_in_edge(Edge* e);
    bool is_isolated() const;
};

class Edge {
private:
    std::string label_;
public:
    const std::string& label() const { return label_; }
    Node* from;
    Node* to;

    Edge(std::string label, Node* from, Node* to);
};

class AbstractGraph {
public:
    virtual ~AbstractGraph() = default;

    virtual void insert_edge(const std::string&, const std::string&, const std::string&) = 0;
    virtual void load_from_file(const std::string&) = 0;
    virtual void write_to_file(const std::string&) const = 0;

    virtual void disconnect(std::string node_a_label, std::string node_b_label) = 0;
    virtual void remove_node(std::string node_label) = 0;

    virtual std::vector<std::string> get_nodes() const = 0;
    virtual std::vector<std::string> get_out_neighbors(const std::string& label) const = 0;
    virtual std::vector<std::pair<std::string, std::string>> get_labeled_out_edges(const std::string& label) const = 0;
};



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
