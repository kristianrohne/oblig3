#pragma once

#include <list>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>

namespace namespace_graph {


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
}