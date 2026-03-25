#include "graph.h"
#include <iostream>
#include <fstream>
#include <utility>
#include <unordered_map>

namespace namespace_graph {

// Destructor
Graph::~Graph() {
    for (Edge* e : edges) {
        delete e;
    }
    edges.clear();

    for (Node* n : nodes) {
        delete n;
    }
    nodes.clear();
}

// Copy constructor
Graph::Graph(const Graph& other) {
    // Map between old nodes and new nodes
    std::unordered_map<const Node*, Node*> node_map;
    // Reserve space as old nodes´s size
    node_map.reserve(other.nodes.size());
    // Try and catch in case program crashes, for avoiding memory leak
    try {
        // Iterate through old nodes
        for (Node* old_node : other.nodes) {
            // In case of nullptr, skip
            if(!old_node) {
                continue;
            }
            // Make new node from old node, for deep copy
            Node* new_node = new Node(old_node->label());
            nodes.push_back(new_node);
            // Map betwen old node and new node
            node_map[old_node] = new_node;
        }
        // Iterate through old edges
        for (Edge* old_edge : other.edges) {
            // In case of nullptr
            if(!old_edge) {
                continue;
            }
            // Make new from and to from node_map 
            Node* new_from = node_map.at(old_edge->from);
            Node* new_to   = node_map.at(old_edge->to);
            // Make new edge, use label from old_edge and new from and to 
            Edge* new_edge = new Edge(old_edge->label(), new_from, new_to);
            edges.push_back(new_edge);
            // Add new edge to nodes new_from and new_to
            new_from->add_out_edge(new_edge);
            new_to->add_in_edge(new_edge);
        }
    }
    // In case program crashes, delete newly implemented edges and nodes 
    catch (...) {
        for (Edge* e : edges) delete e;
        edges.clear();
        for (Node* n : nodes) delete n;
        nodes.clear();
        throw;
    }
}

Graph& Graph::operator=(const Graph& other) {
    // If assigning to itself, do nothing
    if (this == &other) {
        return *this;
    }

    // Create a copy
    Graph tmp(other);
    // Swap data between the two graphs 
    nodes.swap(tmp.nodes);
    edges.swap(tmp.edges);
    // Return object itself
    return *this;
}


Graph::Graph(Graph&& other) noexcept :
// Moving other´s nodes and edges to new graph 
nodes(std::move(other.nodes)), edges(std::move(other.edges)) {}

Graph& Graph::operator=(Graph&& other) noexcept {
    // Return object if this and other is the same 
    if (this == &other) {
        return *this;
    }

    // Delete existing edges and nodes 
    for (Edge* e : edges) delete e;
    edges.clear();
    for (Node* n : nodes) delete n;
    nodes.clear();

    // Move nodes and edges from other into this graph
    nodes = std::move(other.nodes);
    edges = std::move(other.edges);

    return *this;
}

// 
Node* Graph::find_node(const std::string& label) const {
    for (Node* node : nodes) {
        if (node && node->label() == label) {
            return node;
        }
    }
    return nullptr;
}

Node* Graph::get_or_create_node(const std::string& label) {
    // Get node from find_node
    Node* n = find_node(label);
    // If node not in find_node, create node
    if (!n) {
        n = new Node(label);
        nodes.push_back(n);
    }
    return n;
}

void Graph::insert_edge(const std::string& node_a_label, const std::string& edge_label, const std::string& node_b_label) {
    // Get nodes or create new ones if they don´t exist
    Node* a = get_or_create_node(node_a_label);
    Node* b = get_or_create_node(node_b_label);

    // Create new edge, add to edges
    Edge* e = new Edge(edge_label, a, b);
    edges.push_back(e);

    // Add edge to nodes 
    a->add_out_edge(e);
    b->add_in_edge(e);
}

void Graph::load_from_file(const std::string& text_file) {
    // Open file
    std::ifstream file(text_file);
    // If error happens
    if (!file) {
        std::cerr << "Could not open textfile in load_from_file" << "\n";
        return;
    }
    // Initialize node labels and edge label
    std::string node_a_label, edge_label, node_b_label;
    // Get labels from each line, and use them in function
    while (file >> node_a_label >> edge_label >> node_b_label) {
        if (!node_b_label.empty() && node_b_label.back() == '.') {
            node_b_label.pop_back();
        }
        insert_edge(node_a_label, edge_label, node_b_label);
    }
}

void Graph::write_to_file(const std::string& text_file) const {
    // Open or create file
    std::ofstream file(text_file);
    // If error happens
    if (!file) {
        std::cerr << "Could not create textfile in write_to_file" << "\n";
        return;
    }
    // iterate through each edge in graph, add to new line in file
    for (Edge* e : edges) {
        file << e->from->label() << ' ' << e->label() << ' ' << e->to->label()<< '\n';
    }
}

void Graph::delete_if_disconnected(Node* n) {
    // If n is a nullptr, do nothing
    if (!n) {
        return;
    }
    // If node is not isolated, do nothing
    if (!n->is_isolated()) {
        return;
    }

    // remove node from list if isolated
    nodes.remove(n);
    // Delete node also
    delete n;
}


void Graph::disconnect(std::string node_a_label, std::string node_b_label) {
    // Get nodes from list
    Node* a = find_node(node_a_label);
    Node* b = find_node(node_b_label);
    // If on of them doens´t exist
    if (!a or !b) return;

    // Safe for loop since we may delete edge
    for (auto iterator = edges.begin(); iterator != edges.end(); ) {
        // Get edge
        Edge* e = *iterator;

        // If edge goes from a to b
        if (e && e->from == a && e->to == b) {
            // remove out and in edge in nodes
            a->remove_out_edge(e);
            b->remove_in_edge(e);
            // Delete edge
            delete e;
            // Set new iterator
            iterator = edges.erase(iterator);
        } else {
            // Add 1 to iterator if edge doesn´t go from a to b
            ++iterator;
        }
    }
    // Check if nodes are disconnencted
    delete_if_disconnected(a);
    delete_if_disconnected(b);
}

void Graph::remove_node(std::string node_label) {
    // Get node in list
    Node* n = find_node(node_label);
    // If nullptr, do nothing
    if (!n) return;

    // Create list for checking isolated nodes
    std::list<Node*> maybe_isolated;
    // Safe for loop since we may delete edge 
    for (auto iterator = edges.begin(); iterator != edges.end(); ) {
        // Get edge
        Edge* e = *iterator;

        // Check if edge goes in or out from node
        if (e && (e->from == n or e->to == n)) {
            // Get from and to from edge
            Node* from = e->from;
            Node* to   = e->to;

            // Add nodes to maybe_isolated list before deleting edge
            if (from != n) {
                maybe_isolated.push_back(from);
            }
            if (to   != n) {
                maybe_isolated.push_back(to);
            }
            // Remove edge from nodes
            from->remove_out_edge(e);
            to->remove_in_edge(e);
            // Delete edge
            delete e;
            // Set new iterator
            iterator = edges.erase(iterator);
        } else {
            // Add 1 to iterator
            ++iterator;
        }
    }
    // remove node n from nodes
    nodes.remove(n);
    // Delete node
    delete n;

    // Sort list before making each entry unique 
    maybe_isolated.sort();
    maybe_isolated.unique();
    // Check if every node in list is isolated, delete if so
    for (Node* x : maybe_isolated) {
        delete_if_disconnected(x);
    }
}

std::vector<std::string> Graph::get_nodes() const {
    std::vector<std::string> nodelist;
    for (Node* node : nodes) {
        if (node) {
            nodelist.push_back(node->label());
        }
    }
    return nodelist;
}

std::vector<std::string> Graph::get_out_neighbors(const std::string& label) const {
    std::vector<std::string> neighbors;

    Node* node = find_node(label);
    if (!node) {
        return neighbors;
    }

    for (Edge* edge : node->out_edges()) {
        if (edge && edge->to) {
            neighbors.push_back(edge->to->label());
        }
    }

    return neighbors;
}


}