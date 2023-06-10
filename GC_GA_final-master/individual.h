#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include <vector>
#include <iostream>
#include <random>
#include <algorithm>
#include <set>

/*
The individual class is used in the Genetic Algorithm and in the Simulated Annealing
algorithm because the implementation and some methods are useful
but the usage is different.
The fitness is for the GA but in SA it is used as the cost
*/
class individual {
private:
    std::vector<unsigned int> chromosome;
    unsigned int n_genes = 0;
    unsigned int N_colors_used = 0;
    unsigned int fitness = 0;

public:

    individual() = default;

    individual(const individual& other) = default;

    individual(individual&& other) noexcept;

    individual& operator=(const individual& other) = default;

    individual& operator=(individual&& other) noexcept;

    /*  Initialize a certain individual with random values,
        and n_genes number of genes
    */
    explicit individual(unsigned int n_genes);

    /*  Create an individual with a given chromosome and the number of colors used
    */
    explicit individual(const std::vector<unsigned int>& chromosome);

    /*  Numer of differents colors used in this result
    */
    [[nodiscard]] unsigned int get_n_colors() const;

    /*  Print the Chromosome and its colors
    */
    void printChromosome() const;

    /*  It will return the value of the chromosome at the i position
    */
    unsigned int at(unsigned int i);

    /*  Assign a value to the f
    */
    void set_fitness(unsigned int f);

    /*  Return the fitness of the individual
    */
    [[nodiscard]] unsigned int get_fitness() const;

    /*  It will mutate the individual
    */
    void mutate();

    /*  Will create a new individual based on his parents
        Parent 1 will be the individual that has been instatiated.
        parent_2: The second parent
        It will create a random number that will be the
            percentage used from the parent 1
            (1-p will be the percentage used from parent_2)
        return: The new individual
    */
    individual reproduce(individual parent_2) const;

    /*  Insert a color c
        in a certain position p
    */
    void insertColor(int p, int c);

};

#endif
