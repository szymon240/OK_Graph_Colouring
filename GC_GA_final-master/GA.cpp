#include <queue>
#include <utility>

#include "GA.h"
#include "random.hpp"

GA::GA(unsigned int n_individuals, unsigned int n_genes, unsigned int n_edges,
       std::vector<std::vector<unsigned int>> main_graph) {
    this->n_individuals = n_individuals;
    this->n_genes = n_genes;
    this->n_edges = n_edges;
    this->main_graph = std::move(main_graph);

    for (unsigned int i = 0; i < n_individuals; i++) {
        individual a(n_genes);
        ga_population.push_back(a);
    }
}

GA::GA(unsigned int n_genes, unsigned int n_edges, std::vector<std::vector<unsigned int>> main_graph) {
    this->n_genes = n_genes;
    this->n_edges = n_edges;
    this->main_graph = std::move(main_graph);
    this->n_individuals = 0;
}

void GA::add_individual(const individual& ind_new) {
    this->ga_population.push_back(ind_new);
    n_individuals++;
}

std::vector<individual> GA::find_best_individuals(double percentage) {

    std::vector<individual> best_individuals;

    //pair< Fitness value, index in the ga_population>
    std::priority_queue<std::pair<unsigned int, unsigned int>> best_ind;

    /*  To have the best n_best_individuals, we insert the elements
        into a queue and then pop just what we need.
        (It can be done more efficient, if we don't push the individuals
        smaller than the last element of the queue but back() is not working
        for some reason, I will improve this if I have time)
    */

    for (unsigned int i = 0; i < n_individuals; ++i) best_ind.emplace(fitness_of_individual(i), i);

    //Number of individuals that we will choose
    const auto n_best_individuals = (unsigned int) (percentage * n_individuals);


    /*  Here we pop the elements that we want
    */
    for (int i = 0; i < n_best_individuals; ++i) {
        unsigned int ki = best_ind.top().second;
        best_individuals.push_back(this->ga_population[ki]);
        best_ind.pop();
    }

    return best_individuals;
}

std::vector<individual> GA::reproduce(const std::vector<individual>& population, unsigned int new_ind) const {
    std::vector<individual> new_population;
    unsigned int parent_1, parent_2;
    individual child(n_genes);
    unsigned int individuals = population.size();

    for (unsigned int i = 0; i < new_ind; i++) {
        parent_1 = random::get_random(0, individuals);

        //This way we won't have parent_1 == parent_2
        parent_2 = (parent_1 + (int) random::get_random(1, individuals - 1)) % individuals;
        //cout << "parent 1: " << parent_1 << ", parent 2: " << parent_2 << endl;

        child = std::move(population[parent_1].reproduce(population[parent_2]));
        new_population.push_back(child);

    }
    return new_population;
}

std::vector<individual> GA::mutate(const std::vector<individual>& population, unsigned int new_ind) {
    std::vector<individual> new_population;
    unsigned int random_idx;

    for (unsigned int i = 0; i < new_ind; i++) {
        random_idx = random::get_random(0, population.size());

        individual new_individual = population[random_idx];
        new_individual.mutate();
        new_population.push_back(std::move(new_individual));
    }
    return new_population;
}

void GA::create_population(double p_best, double p_reproduce, double p_mutations) {
    double p_total = p_best + p_reproduce + p_mutations;

    p_best = p_best / p_total;
    double n_reproduce = n_individuals * (p_reproduce / p_total);
    double n_mutations = n_individuals * (p_mutations / p_total);
    std::vector<individual> new_population;

    new_population = find_best_individuals(p_best);

    std::vector<individual> reproduce_v = reproduce(new_population, n_reproduce);
    std::vector<individual> mutate_v = mutate(new_population, n_mutations);

    //Insert the reproduced and mutated std::vector into the new ga_population.

    new_population.insert(end(new_population), begin(reproduce_v), end(reproduce_v));
    new_population.insert(end(new_population), begin(mutate_v), end(mutate_v));

    this->ga_population = new_population;
}

unsigned int GA::fitness_of_individual(unsigned int index) {

    unsigned int fit = 0;
    //If we've calculated it previously we don't need to do it again
    if (ga_population[index].get_fitness() != 0) fit = ga_population[index].get_fitness();
    else {
        for (unsigned int i = 0; i < n_genes; i++) {
            const size_t graph_size = main_graph[i].size();
            for (unsigned int j = 0; j < graph_size; j++) {
                unsigned int cmp_number = ga_population[index].at(main_graph[i][j]);
                if (ga_population[index].at(i) != cmp_number) fit++;
            }
        }
        if (fit == n_edges) fit += (n_genes - ga_population[index].get_n_colors());
        ga_population[index].set_fitness(fit);
    }
    return fit;
}

void GA::print_population() {
    for (unsigned int i = 0; i < n_individuals; i++) {
        std::cout << std::endl;
        ga_population[i].printChromosome();
        std::cout << "Fitness: " << fitness_of_individual(i);
    }
}

bool GA::correct_color(unsigned int n_colors, double percentage) {

    int avg = 0;
    bool finish = false;
    double per = n_individuals * (percentage / 100);

    for (unsigned int i = 0; i < ga_population.size() and !finish; i++) {
        if (ga_population[i].get_n_colors() == n_colors) {
            avg++;
            if (avg == per) finish = true;
        }
    }

    return finish;
}

void GA::main_loop(unsigned int max_iterations, unsigned int& total_iterations,
                   double p_best, double p_cross, double p_mutation, int min_colors) {
    bool cor_color = false;
    std::cout << std::endl;
    for (total_iterations = 0; total_iterations < max_iterations and !cor_color; total_iterations++) {
        this->create_population(p_best, p_cross, p_mutation);
        if (this->correct_color(min_colors, 100.0 - p_mutation)) cor_color = true;
    }
}