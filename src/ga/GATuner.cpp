#include "GATuner.h"
#include <random>
#include <algorithm>

struct Chromosome {
    std::vector<double> weights;
    double fitness;
};

std::vector<double> GATuner::runTraining(int generations, int popSize) {
    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<double> dist(0.5, 2.0);

    std::vector<Chromosome> pop(popSize);
    for (auto& c : pop) {
        c.weights = {10000,3000,1000,300,100};
        for (auto& w : c.weights) w *= dist(rng);
        c.fitness = 0;
    }

    for (int g = 0; g < generations; g++) {
        std::sort(pop.begin(), pop.end(),
                  [](auto& a, auto& b){return a.fitness > b.fitness;});
        pop.resize(popSize / 2);

        while ((int)pop.size() < popSize) {
            Chromosome c = pop[rng() % pop.size()];
            int idx = rng() % c.weights.size();
            c.weights[idx] *= dist(rng);
            pop.push_back(c);
        }
    }
    return pop.front().weights;
}
