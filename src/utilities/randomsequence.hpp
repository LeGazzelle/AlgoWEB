//
// Created by Gabriele Santi on 25/10/16.
//

#ifndef ALGOWEB_RANDOMSEQUENCE_HPP
#define ALGOWEB_RANDOMSEQUENCE_HPP

#include <ctime>
#include <random>
#include "../AlgoWEB.hpp"


//WARNING! rand() function returns a value in the range [0,RAND_MAX]
// and RAND_MAX could not be enough to cover the space of 'long long int' type
//     [FIXED with std::uniform_int_distribution<long long int>]
class FisherYatesSequence {
private:
    vertex_index_t upLimit;
    vertex_index_t max;
    std::vector<vertex_index_t> numbers;
    std::mt19937 gen;
    std::uniform_int_distribution<vertex_index_t> dis;

    void swap(vertex_index_t what, vertex_index_t with) {
        vertex_index_t tmp = this->numbers[what];

        this->numbers[what] = this->numbers[with];
        this->numbers[with] = tmp;
    }

public:
    FisherYatesSequence() {}

    FisherYatesSequence(vertex_index_t size) : upLimit(size - 1), max(size - 1) {
        this->numbers = std::vector<vertex_index_t>(size);
        std::random_device rd;

        //std::srand(std::time(0));
        this->gen = std::mt19937(rd());
        this->dis = std::uniform_int_distribution<vertex_index_t>();
        for (vertex_index_t k = 0; k < size; k++)
            this->numbers[k] = k;
        this->gen.seed((unsigned long) std::time(0));
    }

    void seed(vertex_index_t seed) {
        this->gen.seed(seed);
    }

    Vertex next() {
        Vertex ans;

        if (this->max) {
            this->swap(this->max, this->dis(this->gen) % this->max);
            ans = (Vertex) this->numbers[this->max];
            this->max--;
        } else {
            ans = (Vertex) this->numbers[0];
            this->max = this->upLimit;
        }

        return ans;
    }

    ~FisherYatesSequence() {}
};

#endif //ALGOWEB_RANDOMSEQUENCE_HPP
