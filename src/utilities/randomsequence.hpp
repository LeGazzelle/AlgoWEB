//
// Created by Gabriele Santi on 25/10/16.
//

#ifndef ALGOWEB_RANDOMSEQUENCE_HPP
#define ALGOWEB_RANDOMSEQUENCE_HPP

#include <iostream>
#include <random>
#include "../AlgoWEB.hpp"

/**
 * From an idea of Jeff Preshing of 31/12/12.
 */
class RandomSequenceOfUnique {
private:
    unsigned int m_index;
    unsigned int m_intermediateOffset;

    static unsigned int permuteQPR(unsigned int x) {
        static const unsigned int prime = 4294967291u;
        if (x >= prime)
            return x;  // The 5 integers out of range are mapped to themselves.
        unsigned int residue = ((unsigned long long) x * x) % prime;
        return (x <= prime / 2) ? residue : prime - residue;
    }

public:
    RandomSequenceOfUnique(unsigned int seedBase, unsigned int seedOffset) {
        m_index = permuteQPR(permuteQPR(seedBase) + 0x682f0161);
        m_intermediateOffset = permuteQPR(permuteQPR(seedOffset) + 0x46790905);
    }

    unsigned int next() {
        return permuteQPR((permuteQPR(m_index++) + m_intermediateOffset) ^ 0x5bf03635);
    }
};

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
    FisherYatesSequence(vertex_index_t size) : upLimit(size - 1), max(size - 1) {
        this->numbers = std::vector<vertex_index_t>(size);
        std::random_device rd;

        //std::srand(std::time(0));
        this->gen = std::mt19937(rd());
        this->dis = std::uniform_int_distribution<vertex_index_t>();
        for (vertex_index_t k = 0; k < size; k++)
            this->numbers[k] = k;
    }

    void seed(vertex_index_t seed) {
        this->max = seed;
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
