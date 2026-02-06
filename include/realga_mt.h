/*
---------------------------------------------
    author: Alessandro Nicolosi
    website: https://github.com/alenic
    license: MIT

    file description:
        This is the RealGA multithreading implementation.
        Threads are used to compute the fitness function
        in parallel.
---------------------------------------------
*/
#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include "realga.h"

class RealGAMultithread : public RealGA
{
private:
    unsigned int mNthread;

public:
    RealGAMultithread(unsigned int nThread);
    ~RealGAMultithread();

    void evolve() override;
};
