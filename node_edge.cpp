#include "graph.h"
#include <utility>

namespace namespace_graph {

// Constructor
Node::Node(std::string label)
    : label_(std::move(label)) {}

// Adding out-edge to node
void Node::add_out_edge(Edge* e) {
    out_edges_.push_back(e);
}
// Adding in-edge to node
void Node::add_in_edge(Edge* e) {
    in_edges_.push_back(e);
}
// Removing out-edge
void Node::remove_out_edge(Edge* e) {
    out_edges_.remove(e);
}
// Removing in-edge
void Node::remove_in_edge(Edge* e) {
    in_edges_.remove(e);
}
// For checking if node is isolated
bool Node::is_isolated() const {
    return out_edges_.empty() && in_edges_.empty();
}

// Constructor
Edge::Edge(std::string label, Node* from, Node* to)
    : label_(std::move(label)), from(from), to(to) {}

}