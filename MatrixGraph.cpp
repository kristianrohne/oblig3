#include "graph.h"
#include <iostream>
#include <fstream>
namespace namespace_graph {
    
int MatrixGraph::get_or_create_index(const std::string& label) {
    // CHeck if label is in map 
    auto iterator = index_of.find(label);

    // If label is in map, return index
    if (iterator != index_of.end()) {
        return iterator->second;
    } 
    // if not, add label to node_labels and create map between label and index
    else {
        // Add label to node_labels
        node_labels.push_back(label);

        // create new index, force to be int
        int new_index = static_cast<int>(node_labels.size()) - 1;
        // Create map between label and index
        index_of[label] = new_index;


        int n = node_labels.size();
        // Resize number of rows in matrix
        matrix.resize(n);
        // Resize each column also
        for (auto& row : matrix) {
            row.resize(n);
        }
        return new_index;
    }
}

void MatrixGraph::insert_edge(const std::string& node_a_label, const std::string& edge_label, const std::string& node_b_label) {
    // Get or create index i
    int i = get_or_create_index(node_a_label);
    // Get or create index j
    int j = get_or_create_index(node_b_label);
    // Add edge between nodes with index i and j in matrix
    matrix[i][j].push_back(edge_label);
}

void MatrixGraph::load_from_file(const std::string& text_file) {
    // Open file
    std::ifstream file(text_file);
    // If error
    if (!file) {
        std::cerr << "Could not open textfile in load_from_file" << "\n";
        return;
    }
    // Initialize entries for insert_edge function
    std::string node_a_label, edge_label, node_b_label;
    // Get entries from each line and insert to function
    while (file >> node_a_label >> edge_label >> node_b_label) {
        if (!node_b_label.empty() && node_b_label.back() == '.') {
            node_b_label.pop_back();
        }
        insert_edge(node_a_label, edge_label, node_b_label);
    }
}

void MatrixGraph::write_to_file(const std::string& text_file) const {
    // Open file 
    std::ofstream file(text_file);

    if (!file) {
        std::cerr << "Could not create textfile in write_to_file\n";
        return;
    }
    // For each row in matrix
    for (size_t i = 0; i < matrix.size(); ++i) {
        // For each column in matrix
        for (size_t j = 0; j < matrix[i].size(); ++j) {
            // the entry for matrix[i][j]
            const auto& entry = matrix[i][j];
            // For each edge in entry, add edge and nodes in file
            for (const std::string& edge_label : entry) {
                file << node_labels[i] << ' ' << edge_label << ' ' << node_labels[j] << '\n';
            }
        }
    }
}

void MatrixGraph::remove_index(int i) {
    // Remove row i 
    matrix.erase(matrix.begin() + i);

    // Remove column i
    for (auto& row : matrix) {
        row.erase(row.begin() + i);
    }

    // Remove label i (have add 1 for indexing in vector)
    node_labels.erase(node_labels.begin() + i);

    // Rebuild the map
    index_of.clear();
    for (int k = 0; k < static_cast<int>(node_labels.size()); ++k) {
        index_of[node_labels[k]] = k;
    }
}


void MatrixGraph::delete_if_disconnected(const std::string& node_label) {
    // Check if label is in map 
    auto iterator = index_of.find(node_label);
    if (iterator == index_of.end()) {
        return;
    }

    // Get index
    int i = iterator->second;
    // Get size of node_labels
    int n = static_cast<int>(node_labels.size());

    // Check if node has out_edge
    bool has_out_edge = false;
    // Check every entry in row i
    for (int j = 0; j < n; ++j) {
        if (!matrix[i][j].empty()) { 
            has_out_edge = true; break; 
        }
    }

    // Check if node has in_edge
    bool has_in_edge = false;
    // Check every entry in column i 
    for (int k = 0; k < n; ++k) {
        if (!matrix[k][i].empty()) { 
            has_in_edge = true; break; 
        }
    }
    // Delete node if it has no out/in edge
    if (!has_out_edge && !has_in_edge) {
        remove_index(i);
    }
}

void MatrixGraph::disconnect(const std::string node_a_label, const std::string node_b_label) {
    // Check if node a and b is in map
    auto iterator_A = index_of.find(node_a_label);
    auto iterator_B = index_of.find(node_b_label);
    // Finish function if one of the nodes isn´t in map
    if (iterator_A == index_of.end() or iterator_B == index_of.end()) {
        return;
    }

    // get indexes of nodes
    int i = iterator_A->second;
    int j = iterator_B->second;

    // Clear edge in matrix
    matrix[i][j].clear();

    // Check if one of the nodes are disconnencted, delete if so
    delete_if_disconnected(node_a_label);
    delete_if_disconnected(node_b_label);
}

void MatrixGraph::remove_node(std::string node_label) {
    // check if node is in map
    auto iterator = index_of.find(node_label);
    if (iterator == index_of.end()) return;

    // Remove node
    remove_index(iterator->second);

    // Check for disconnencted nodes, check every node
    // Backward iteration since we may delete nodes in node_labels
    for (int k = static_cast<int>(node_labels.size()) - 1; k >= 0; --k) {
        delete_if_disconnected(node_labels[k]);
    }
}

std::vector<std::string> MatrixGraph::get_nodes() const {
    return node_labels;
}

std::vector<std::string> MatrixGraph::get_out_neighbors(const std::string& label) const {
    std::vector<std::string> neighbors;

    auto iterator = index_of.find(label);
    if (iterator == index_of.end()) {
        return neighbors;
    }

    int i = iterator->second;

    for (size_t j = 0; j < matrix[i].size(); ++j) {
        if (!matrix[i][j].empty()) {
            neighbors.push_back(node_labels[j]);
        }
    }

    return neighbors;
}

std::vector<std::pair<std::string, std::string>>
MatrixGraph::get_labeled_out_edges(const std::string& label) const {
    std::vector<std::pair<std::string, std::string>> neighbors;

    auto iterator = index_of.find(label);
    if (iterator == index_of.end()) {
        return neighbors;
    }

    int i = iterator->second;

    for (size_t j = 0; j < matrix[i].size(); ++j) {
        for (const std::string& edge_label : matrix[i][j]) {
            neighbors.push_back({edge_label, node_labels[j]});
        }
    }

    return neighbors;
}

}