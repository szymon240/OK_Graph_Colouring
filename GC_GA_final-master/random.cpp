#include "random.hpp"

double random::get_random(double start, double end) {
    return std::uniform_real_distribution<double>(start, end)(mt);
}
