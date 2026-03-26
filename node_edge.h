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
}