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

    // Check that query_file has at least two lines
    for (int i = 0; i < 2; i++) {
        if (!std::getline(file, line)) {
            std::cerr << "Query file must contain exactly 2 lines\n";
            return label_sequences;
        }

        // istringstream for getting each word in string
        std::istringstream iss(line);
        // Each sequence
        std::vector<std::string> sequence;
        // 
        std::string word;

        while (iss >> word) {
            if (!word.empty() && word.back() == '.') {
                // Removes . of last word
                word.pop_back();
            }
            sequence.push_back(word);
        }

        label_sequences.push_back(sequence);
    }
    // Check that file doesn´t contain any more lines 
    if (std::getline(file, line)) {
        std::cerr << "Query file must contain exactly 2 lines\n";
        return {};
    }

    return label_sequences;
}


std::vector<std::pair<std::string, std::string>>
Diamond::find_diamonds(const namespace_graph::AbstractGraph& graph,
                       const std::string& query_file) {
    diamond_pairs.clear();
    label_sequences = get_label_sequences(query_file);

    if (label_sequences.size() != 2) {
        return diamond_pairs;
    }

    nodes = graph.get_nodes();

    for (const std::string& start_node : nodes) {
        std::vector<std::string> endpoints_seq1;
        std::vector<std::string> endpoints_seq2;

        dfs_follow_sequence(graph, start_node, label_sequences[0], 0, endpoints_seq1);
        dfs_follow_sequence(graph, start_node, label_sequences[1], 0, endpoints_seq2);

        // Remove duplicates from endpoints if needed
        std::sort(endpoints_seq1.begin(), endpoints_seq1.end());
        endpoints_seq1.erase(std::unique(endpoints_seq1.begin(), endpoints_seq1.end()), endpoints_seq1.end());

        std::sort(endpoints_seq2.begin(), endpoints_seq2.end());
        endpoints_seq2.erase(std::unique(endpoints_seq2.begin(), endpoints_seq2.end()), endpoints_seq2.end());

        // Find common endpoints
        for (const std::string& end_node : endpoints_seq1) {
            if (std::find(endpoints_seq2.begin(), endpoints_seq2.end(), end_node) != endpoints_seq2.end()) {
                diamond_pairs.push_back({start_node, end_node});
            }
        }
    }

    return diamond_pairs;
}


void Diamond::dfs_follow_sequence(const namespace_graph::AbstractGraph& graph,
                                  const std::string& current_node,
                                  const std::vector<std::string>& sequence,
                                  int label_index,
                                  std::vector<std::string>& endpoints) {

    if (label_index == static_cast<int>(sequence.size())) {
        endpoints.push_back(current_node);
        return;
    }

    std::string needed_label = sequence[label_index];

    for (const auto& edge : graph.get_labeled_out_edges(current_node)) {
        const std::string& edge_label = edge.first;
        const std::string& next_node = edge.second;

        if (edge_label == needed_label) {
            dfs_follow_sequence(graph, next_node, sequence, label_index + 1, endpoints);
        }
    }
}

}  // namespace diamond_finder