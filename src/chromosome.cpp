#include "chromosome.h"
#include <sstream>
#include <math.h>
#include <limits>

RealChromosome::RealChromosome()
{
    fitness = std::numeric_limits<float>::max();
}

RealChromosome::RealChromosome(size_t n) : RealChromosome()
{
    REALGA_ERROR(n <= 0, "Chromosome size must be positive");

    gene.reserve(n); // Reserve capacity to avoid reallocations
    gene.resize(n);
}

RealChromosome::RealChromosome(const RealChromosome &c) : gene(c.gene), fitness(c.fitness)
{
}

RealChromosome::RealChromosome(RealChromosome &&other) noexcept
{
    this->gene = std::move(other.gene);
    this->fitness = other.fitness;
}

RealChromosome::~RealChromosome() = default;

RealChromosome &RealChromosome::operator=(const RealChromosome &c)
{
    if (this != &c)
    {
        gene = c.gene;
        fitness = c.fitness;
    }
    return *this;
}

// Move Assignment Operator
RealChromosome &RealChromosome::operator=(RealChromosome &&other) noexcept
{
    if (this != &other)
    {
        // Release our own resources and take the others
        this->gene = std::move(other.gene);
        this->fitness = other.fitness;
    }
    return *this;
}

bool RealChromosome::operator<(const RealChromosome &c) const
{
    return fitness < c.fitness;
}

bool RealChromosome::operator==(const RealChromosome &other) const
{
    if (gene.size() != other.gene.size())
    {
        return false;
    }

    // Use epsilon for floating point comparison
    constexpr float epsilon = std::numeric_limits<float>::epsilon();
    for (size_t i = 0; i < gene.size(); ++i)
    {
        if (std::abs(gene[i] - other.gene[i]) > epsilon)
        {
            return false;
        }
    }
    return true;
}

std::string RealChromosome::toString() const
{
    if (gene.empty())
    {
        return "[]";
    }

    std::ostringstream os;
    os.precision(10);
    os << "[";

    for (size_t i = 0; i < gene.size() - 1; ++i)
    {
        os << gene[i] << ",";
    }
    os << gene.back() << "]";

    return os.str();
}

float RealChromosome::distanceTo(const RealChromosome &g) const
{
    REALGA_ERROR(gene.size() != g.gene.size(), "Chromosomes must have same size for distance calculation");

    float sse = 0.0f;
    for (size_t i = 0; i < gene.size(); ++i)
    {
        const float dx = gene[i] - g.gene[i];
        sse += dx * dx;
    }
    return std::sqrt(sse);
}
