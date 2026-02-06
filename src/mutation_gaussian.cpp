#include "mutation.h"

GaussianMutation::GaussianMutation() : Mutation()
{
}

GaussianMutation::GaussianMutation(float mutationRate, float mutationPerc) : Mutation(mutationRate, mutationPerc)
{
}

GaussianMutation::~GaussianMutation() {}

void GaussianMutation::mutate(RealChromosome &x, const vector<float> &lb, const vector<float> &ub)
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

            // 2 * sigma is 95% of values in delta = delta
            float sigma = mMutationPerc * (delta / 2.0f);

            // Mutate
            float mutGene = Stat::randGaussian(gene, sigma);

            if (mutGene < lower)
                mutGene = lower;
            if (mutGene > upper)
                mutGene = upper;

            x.gene[i] = mutGene;
        }
    }
}
