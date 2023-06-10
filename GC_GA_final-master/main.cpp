#include <chrono>
#include <iostream>

#include "GA.h"
#include "graph.hpp"

int main() {
    graph graph_main;
    graph_main.load("miles250.txt");

    unsigned int total_iterations = 0, max_iterations = 1000;
    auto start = std::chrono::high_resolution_clock::now();
    int n_individuals = 1000, min_colors = 0;
    double p_best = 40.0, p_cross = 40.0, p_mutation = 20.0;

    GA solution(n_individuals, graph_main.get_nodes(), graph_main.get_edges(), graph_main.get_graph());
    solution.main_loop(max_iterations, total_iterations, p_best, p_cross, p_mutation, min_colors);
    solution.print_population();

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = end - start;

    std::cout << "\nSolution found! Time elapsed: " << std::chrono::duration_cast<std::chrono::seconds>(elapsed).count()
              << " seconds." << std::endl;
    return 0;
}
