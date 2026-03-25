#pragma once

#include <string>
#include <vector>
#include "graph.h"
#include <unordered_map>

namespace diamond_finder {

class Diamond {
private:
    const int UNVISITED = -1;

    int next_id = 0;

    std::vector<std::string> nodes;
    std::vector<std::vector<int>> out_edges;

    std::vector<int> ids;
    std::vector<int> low;
    std::vector<bool> on_stack;
    std::vector<int> stack;

    std::vector<std::unordered_map<std::string, std::string>> diamond_pairs;
    std::vector<std::vector<std::string>> label_sequences; 

    void search_diamonds(int current);

    std::vector<std::vector<std::string>> get_label_sequences(const std::string& query_file);

public:
    std::vector<std::unordered_map<std::string, std::string>> find_diamonds(const namespace_graph::AbstractGraph& graph);
};
}