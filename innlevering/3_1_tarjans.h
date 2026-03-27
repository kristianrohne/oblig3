#pragma once

#include <string>
#include <vector>
#include "2_1_graph.h"

namespace tarjans_algorithm {

class Tarjan {
private:
    // For marking unvisited nodes
    const int UNVISITED = -1;
    // Counter for DFS visit order
    int next_id = 0;

    // For store node labels from graph
    std::vector<std::string> nodes;
    // Stores out edges for node i´s neigbors at index i
    std::vector<std::vector<int>> out_edges;

    // Stores DFS discovery id of each node
    std::vector<int> ids;
    // Stores smallest DFS id reachable from node i
    std::vector<int> low;
    // Keeps track of nodes that is on stack, either true or false
    std::vector<bool> on_stack;
    // The actual stack of active nodes
    std::vector<int> stack;
    // Stores the SCC´s
    std::vector<std::vector<std::string>> sccs;

    // DFS helper
    void dfs(int current);

public:
    // The main function that takes in graph and returns SCC´s 
    std::vector<std::vector<std::string>> findSCCs(const namespace_graph::AbstractGraph& graph);
};

}