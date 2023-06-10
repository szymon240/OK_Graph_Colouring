#include "graph.hpp"

void graph::load(const std::string& file_path) {
    std::ifstream file;
    file.open(file_path);

    if (!file) {
        std::cerr << "Error opening file" << std::endl;
        return;
    }
    file >> n_vertices;
    std::cout << n_vertices;
    graph.resize(n_vertices);
    unsigned int v1, v2;
    char e;

    n_edges = 0;
    while (!file.eof()) {
        file >> v1 >> v2;
        graph[v1 - 1].push_back(v2 - 1);
        n_edges++;
    }
    file.close();
}

void graph::print_graph() const {
    if (graph.empty()) std::cout << "The graph is not loaded.";
    else {
        for (size_t i = 0; i < graph.size(); i++) {
            std::cout << std::endl << "[" << i << "]" << "->";
            for (unsigned int j : graph[i]) std::cout << " " << j;
        }
        std::cout << std::endl;
    }
}

[[nodiscard]] unsigned int graph::get_nodes() const {
    return this->n_vertices;
}

[[nodiscard]] unsigned int graph::get_edges() const {
    return this->n_edges;
}

[[nodiscard]] const std::vector<std::vector<unsigned int>>& graph::get_graph() const {
    return this->graph;
}