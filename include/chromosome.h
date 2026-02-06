/*
---------------------------------------------
    author: Alessandro Nicolosi
    website: https://github.com/alenic
    license: MIT

    file description:
        RealChromosome is the solution x of the
        optimization problem of type real (float)
---------------------------------------------
*/
#pragma once

#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include "stat.h"
#include "messages.h"

using namespace std;

class RealChromosome
{
public:
    vector<float> gene;
    float fitness;

    RealChromosome();
    RealChromosome(size_t n);

    // Move constructor for high-performance sorting/selection
    RealChromosome(RealChromosome &&other) noexcept;
    // Copy constructor
    RealChromosome(const RealChromosome &c);
    ~RealChromosome();

    string toString() const;

    float distanceTo(const RealChromosome &g) const;

    RealChromosome &operator=(const RealChromosome &c);
    // Assignment by move
    RealChromosome &operator=(RealChromosome &&other) noexcept;

    bool operator<(const RealChromosome &c) const;
    bool operator==(const RealChromosome &other) const;
};
