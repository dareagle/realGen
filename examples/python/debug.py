import numpy as np
import matplotlib.pyplot as plt
import matplotlib.cm as cm

import realga as rg


class QuadraticFitness(rg.FitnessFunction):
    def eval(self, g: rg.RealChromosome):
        x = g.gene[0]
        y = g.gene[1]
        return 20 + x**2 + y**2 - 10 * (np.cos(2 * np.pi * x) + np.cos(2 * np.pi * y))


myFitnessFunction = QuadraticFitness()


x = np.arange(-5.0, 5.0, 0.025)
y = np.arange(-5.0, 5.0, 0.025)
X, Y = np.meshgrid(x, y)
Z = np.zeros_like(X)
for i in range(len(y)):
    for j in range(len(x)):
        c = rg.RealChromosome(2)
        c.gene[0] = x[j]
        c.gene[1] = y[i]
        Z[i, j] = myFitnessFunction.eval(c)


options = rg.RealGAOptions()
options.setChromosomeSize(2)
options.setPopulationSize(150)
options.setBounds([-5.0, -5.0], [5.0, 5.0])
options.setVerbose(1)
options.setMutationType("gaussian")
options.setMutationGaussianPerc(0.05, 0.001)

ga = rg.RealGA()
ga.init(options, myFitnessFunction, False)
ga.popInitRandUniform()

# ---- Matplotlib setup ----
plt.ion()  # interactive mode
fig, ax = plt.subplots()
ax.set_xlim(-5, 5)
ax.set_ylim(-5, 5)
ax.set_title("GA population")
ax.set_xlabel("x")

CS = ax.contour(X, Y, Z)

# initial empty scatter
scatter = ax.scatter([], [])

# ---- Evolution loop ----
for gen in range(40):
    ga.evolve()

    pop = ga.getPopulation()
    pop_values = np.array([[c.gene[0], c.gene[1]] for c in pop])

    scatter.set_offsets(pop_values)

    ax.set_title(f"Generation {gen}")
    plt.pause(0.5)  # allows GUI update

plt.ioff()
plt.show()
