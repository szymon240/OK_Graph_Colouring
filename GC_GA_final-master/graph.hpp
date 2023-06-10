#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <fstream>
#include <iostream>
#include <vector>

class graph {

private:

    std::vector<std::vector<unsigned int>> graph;
    unsigned int n_vertices, n_edges;

public:

    void load(const std::string& file_path);

    void print_graph() const;

    [[nodiscard]] unsigned int get_nodes() const;

    [[nodiscard]] unsigned int get_edges() const;

    [[nodiscard]] const std::vector<std::vector<unsigned int>>& get_graph() const;
};

#endif //GRAPH_HPP
