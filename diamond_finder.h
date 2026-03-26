#pragma once

#include <string>
#include <utility>
#include <vector>
#include "graph.h"

namespace diamond_finder {

class Diamond {
private:
    std::vector<std::string> nodes;
    std::vector<std::vector<std::string>> label_sequences;
    std::vector<std::pair<std::string, std::string>> diamond_pairs;

    std::vector<std::vector<std::string>> get_label_sequences(const std::string& query_file);

    void dfs_follow_sequence(const namespace_graph::AbstractGraph& graph,
                             const std::string& current_node,
                             const std::vector<std::string>& sequence,
                             int label_index,
                             std::vector<std::string>& endpoints);

public:
    std::vector<std::pair<std::string, std::string>>
    find_diamonds(const namespace_graph::AbstractGraph& graph,
                  const std::string& query_file);
};

}