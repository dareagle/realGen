#include "mutation.h"

UniformMutation::UniformMutation() : Mutation()
{
}

UniformMutation::UniformMutation(float mutationRate, float mutationPerc) : Mutation(mutationRate, mutationPerc)
{
}

UniformMutation::~UniformMutation() {}

void UniformMutation::mutate(RealChromosome &x, const vector<float> &lb, const vector<float> &ub)
{
    const size_t n = x.gene.size();

    for (size_t i = 0; i < n; i++)
    {
        if (Stat::randUniform() < mMutationRate)
        {
            float lower = lb[i];
            float upper = ub[i];
            float delta = upper - lower;
            float gene = x.gene[i];
            float fraction = mMutationPerc * (Stat::randUniform() - 0.5) * delta;
            // Mutate
            float mutGene = gene + fraction;

            if (mutGene < lower)
                mutGene = lower;
            if (mutGene > upper)
                mutGene = upper;

            x.gene[i] = mutGene;
        }
    }
}