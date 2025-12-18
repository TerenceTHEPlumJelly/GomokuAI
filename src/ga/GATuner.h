#pragma once
#include <vector>

class GATuner {
public:
    std::vector<double> runTraining(int generations, int popSize);
};
