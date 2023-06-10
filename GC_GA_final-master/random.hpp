#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <random>

class random {
    inline static std::random_device rd;
    inline static std::mt19937 mt{rd()};
public:
    static double get_random(double start, double end);
};
// w linijce 6 i 7 zostal zparametryzowany silnik losowy ktory raz zostal stworzony, a wczesniej byl tworzony przy
// kazdym wywolaniu funkcji get random
#endif //RANDOM_HPP
