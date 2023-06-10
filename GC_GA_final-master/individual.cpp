#include "individual.h"
#include "random.hpp"

individual::individual(individual&& other) noexcept {
    this->chromosome = std::move(other.chromosome);
    this->n_genes = other.n_genes;
    this->N_colors_used = other.N_colors_used;
    this->fitness = other.fitness;
}

individual& individual::operator=(individual&& other) noexcept {
    this->chromosome = std::move(other.chromosome);
    this->n_genes = other.n_genes;
    this->N_colors_used = other.N_colors_used;
    this->fitness = other.fitness;
    return *this;
}

individual::individual(unsigned int n_genes) {
    this->n_genes = n_genes;
    int random;
    unsigned int color = 0;
    for (unsigned int i = 0; i < n_genes; i++) {
        random = random::get_random(0.0, n_genes);
        if (random == 0 or i == 0) chromosome.push_back(color);
        else {
            color++;
            chromosome.push_back(color);
        }
    }
}

individual::individual(const std::vector<unsigned int>& chromosome) {
    this->chromosome = chromosome;
    this->n_genes = chromosome.size();
}

unsigned int individual::get_n_colors() const {
    std::set<unsigned int> distinct_colors;
    for (const auto& curr_int : chromosome) distinct_colors.insert(curr_int);
    return distinct_colors.size();
}

void individual::printChromosome() const {
    std::cout << " N of color used: " << this->get_n_colors() << std::endl;
}

unsigned int individual::at(unsigned int i) {
    return this->chromosome[i];
}

void individual::set_fitness(unsigned int f) {
    this->fitness = f;
}

unsigned int individual::get_fitness() const {
    return this->fitness;
}

void individual::mutate() {
    this->fitness = 0;
    double max_iterations = n_genes / 2;
    unsigned int random_a = random::get_random(1.0, max_iterations);
    unsigned int random_b;
    for (unsigned int i = 0; i < random_a; i++) {
        random_b = random::get_random(0.0, n_genes - 1);
        replace(chromosome.begin(), chromosome.end(), chromosome[random_b], chromosome[(random_b + i + random_a) % n_genes]);
    }
}

individual individual::reproduce(individual parent_2) const {

    double start = n_genes / 3;
    unsigned int random_a = random::get_random(start, n_genes);
    std::vector<unsigned int> new_individual_chr = this->chromosome;
    for (unsigned int i = random_a; i < n_genes; i++) new_individual_chr[i] = parent_2.at(i);

    individual new_ind(new_individual_chr);
    return new_ind;
}

void individual::insertColor(int p, int c) {
    chromosome[p] = c;
}


