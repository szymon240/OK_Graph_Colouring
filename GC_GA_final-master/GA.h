#ifndef GA_H
#define GA_H

#include <vector>

#include "individual.h"

class GA {
private:
    //current ga_population
    std::vector<individual> ga_population;

    //Number of individuals in the ga_population
    unsigned int n_individuals;
    //Number of genes in the graph
    unsigned int n_genes;
    //Number of edges in the graph
    unsigned int n_edges;
    //The graph being used
    std::vector<std::vector<unsigned int>> main_graph;

public:

    /*  It will initialize the ga_population with a n_individuals number of individuals
        All individuals will be intilized with random values
        n_genes is the number of nodes in the graph
    */
    GA(unsigned int n_individuals, unsigned int n_genes, unsigned int n_edges,
       std::vector<std::vector<unsigned int>> main_graph);

    /*  Initialize a GA without a ga_population
    */
    GA(unsigned int n_genes, unsigned int n_edges, std::vector<std::vector<unsigned int>> main_graph);

    /*  Add a new individual to the ga_population
        ind_new: New individual
    */
    void add_individual(const individual& ind_new);

    /*  It will find the bests Individuals of the current ga_population
        Percentage of Indiviuals that will return:
            From 0 to 1
        return: Bests p% Individuals
    */
    std::vector<individual> find_best_individuals(double percentage);

    /*  Will generate a new ga_population based on a previous one, using the reproduce method
        and the number of individuals that we want
        ga_population: previous ga_population
        new_ind: numbwe of individuals in the new ga_population

        return: the new ga_population
    */
    std::vector<individual> reproduce(const std::vector<individual>& population, unsigned int new_ind) const;

    /*  Will generate a new ga_population based on a previous one, using the mutate method
        and the number of individuals that we want
        ga_population: previous ga_population
        new_ind: numbwe of individuals in the new ga_population

        return: the new ga_population
    */
    static std::vector<individual> mutate(const std::vector<individual>& population, unsigned int new_ind);

    /*  It will create a new ga_population
            p_best: A percentage will remain from the previous ga_population. (Best Individuals)
            p_reproduce: A percentage will be created with 2 parents.
            p_mutatuions: A percentage will be mutations.
    */
    void create_population(double p_best, double p_reproduce, double p_mutations);

    /*  Method that will return a bool if there was a problem running the Genetic Algorithm
        It will write in best_individual, the best result it could find
    */
    bool CalculateGA(individual& best_individual);

    /*  It will return an int with the value of the fitness of the individual
        This value is calcuflated:
            1. Every time a edge is good (both nodes have different colors)
                it will add 1 to the variable, if the node is not correct wilk add 0.

            2. If all the edges are correct (fitnes = N_edges) it will add
                N-N_colors_used to the value.

        Return: Fitness of a specific infividual
    */
    unsigned int fitness_of_individual(unsigned int index);

    /*  Print the ga_population and the values of the Individuals
    */
    void print_population();

    /*  It will check if the "percentage" of the ga_population has found a
        solution with "n_colors"

            n_colors: The number of colors that will use as a reference
            percentage: The percentage of the ga_population that has to found a
                solution with that number of colors
        return: true if all of that individuals have a solution with that n_colors
    */
    bool correct_color(unsigned int n_colors, double percentage);

    /*  Main Loop for the Genetic Algorithm system
            max_iterations: maximum number of iteration before the program stops
            total_iteration: the real total iteration that the program made
            p_best: Percentage of the best individuals that will be used to create a new ga_population
            p_cross: percentage of the new individuals that will be created reproducing other individuals
            p_mutation: Percentage of the new individuals that will be created with mutations
            min_colors: minimum amount of colors needed to solve the problem (if unknown "min_colors = 0" )
    */
    void main_loop(unsigned int max_iterations, unsigned int& total_iterations, double p_best, double p_cross, double p_mutation,
                   int min_colors);

    /*  Test method to mutate all the individuals of a ga_population (just for fun)
    */
    void mutateAll() {
        for (unsigned int i = 0; i < n_individuals; i++) {
            ga_population[i].mutate();
        }
    }

    /*  It will add the number of colors being used in each individual in the ga_population
    */
    void ColorsPerIndividual(std::vector<std::vector<unsigned int>>& old_colors) {

        for (unsigned int i = 0; i < n_individuals; i++) {
            old_colors[i].push_back(ga_population[i].get_n_colors());
        }
    };
};

#endif
