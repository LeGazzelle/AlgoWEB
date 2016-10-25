//
// Created by Gabriele Santi on 25/10/16.
//

#ifndef ALGOWEB_RANDOMSEQUENCE_HPP
#define ALGOWEB_RANDOMSEQUENCE_HPP

//#include <random>
#include <cstdlib>
#include <iostream>

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

//FIXME WARNING! rand() function returns a value in the range [0,RAND_MAX]
// and RAND_MAX could not be enough to cover the space of 'long long int' type
class FisherYatesSequence {
private:
    long long upLimit;
    long long max;
    long long *numbers;
    //std::random_device rd;
    //std::mt19937 gen;
    //std::uniform_int_distribution<long long> dis;

    void swap(long long what, long long with) {
        long long tmp = this->numbers[what];

        this->numbers[what] = this->numbers[with];
        this->numbers[with] = tmp;
    }

public:
    //FisherYatesSequence() {}

    FisherYatesSequence(long long size) : upLimit(size - 1), max(size - 1) {
        this->numbers = new long long[size];

        std::srand(std::time(0));
        for (long long k = 0; k < size; k++)
            this->numbers[k] = k;
    }

    Vertex next() {
        Vertex ans;

        if (max) {
            this->swap(this->max, std::rand() % this->max);
            ans = (Vertex) this->numbers[this->max];
            this->max--;
            if (!this->max)
                this->max = this->upLimit;
        } else
            ans = (Vertex) this->numbers[0];

        return ans;
    }
};

#endif //ALGOWEB_RANDOMSEQUENCE_HPP
