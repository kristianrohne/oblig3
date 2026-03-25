#include "tarjans.h"

#include <algorithm>
#include <unordered_map>

namespace tarjans_algorithm {

std::vector<std::vector<std::string>> Tarjan::findSCCs(const namespace_graph::AbstractGraph& graph) {
    // Reset state in case the same Tarjan object is reused
    next_id = 0;
    nodes.clear();
    out_edges.clear();
    ids.clear();
    low.clear();
    on_stack.clear();
    stack.clear();
    sccs.clear();

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