#pragma once

#include <string>
#include <vector>
#include "graph.h"

namespace tarjans_algorithm {

class Tarjan {
private:
    const int UNVISITED = -1;

    int next_id = 0;

    std::vector<std::string> nodes;
    std::vector<std::vector<int>> out_edges;

    std::vector<int> ids;
    std::vector<int> low;
    std::vector<bool> on_stack;
    std::vector<int> stack;

    std::vector<std::vector<std::string>> sccs;

    void dfs(int current);

public:
    std::vector<std::vector<std::string>> findSCCs(const namespace_graph::AbstractGraph& graph);
};

}