// 3.2

#include "diamond_finder.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <algorithm>

namespace diamond_finder {

std::vector<std::vector<std::string>> Diamond::get_label_sequences(const std::string& query_file) {
    std::vector<std::vector<std::string>> label_sequences;

    std::ifstream file(query_file);
    if (!file) {
        std::cerr << "Could not open query file\n";
        return label_sequences;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::vector<std::string> sequence;
        std::string token;

        while (iss >> token) {
            if (!token.empty() && token.back() == '.') {
                token.pop_back();
            }
            sequence.push_back(token);
        }

        if (!sequence.empty()) {
            label_sequences.push_back(sequence);
        }
    }

    if (label_sequences.size() != 2) {
        std::cerr << "Query file must contain exactly 2 lines\n";
    }

    return label_sequences;
}

std::vector<std::vector<std::string>> Diamond::find_diamonds(const namespace_graph::AbstractGraph& graph, std::string query_file) {
    // Reset state in case the same Tarjan object is reused
    next_id = 0;
    nodes.clear();
    out_edges.clear();
    ids.clear();
    low.clear();
    on_stack.clear();
    stack.clear();
    diamond_pairs.clear();
    label_sequences.clear();

    label_sequences = get_label_sequences(query_file);

    // Get all node labels from graph
    nodes = graph.get_nodes();
    int n = static_cast<int>(nodes.size());

    // Temporary mapping from node label to integer index
    std::unordered_map<std::string, int> index_of;
    for (int i = 0; i < n; i++) {
        index_of[nodes[i]] = i;
    }

    // Prepare vectors with correct size
    out_edges.resize(n);
    ids.resize(n, UNVISITED);
    low.resize(n, UNVISITED);
    on_stack.resize(n, false);

    // Build adjacency list using integer indices
    for (int i = 0; i < n; i++) {
        std::vector<std::string> neighbors = graph.get_out_neighbors(nodes[i]);

        for (const std::string& neighbor : neighbors) {
            out_edges[i].push_back(index_of[neighbor]);
        }
    }

    // Run DFS from each unvisited node
    for (int i = 0; i < n; i++) {
        if (ids[i] == UNVISITED) {
            dfs(i);
        }
    }

    return sccs;
}

void Tarjan::dfs(int current) {
    stack.push_back(current);
    on_stack[current] = true;
    ids[current] = next_id;
    low[current] = next_id;
    next_id++;

    for (int to : out_edges[current]) {
        if (ids[to] == UNVISITED) {
            dfs(to);
            low[current] = std::min(low[current], low[to]);
        } else if (on_stack[to]) {
            low[current] = std::min(low[current], ids[to]);
        }
    }

    // current is the root of an SCC
    if (ids[current] == low[current]) {
        std::vector<std::string> component;

        while (true) {
            int node = stack.back();
            stack.pop_back();
            on_stack[node] = false;

            component.push_back(nodes[node]);

            if (node == current) {
                break;
            }
        }

        sccs.push_back(component);
    }
}

}