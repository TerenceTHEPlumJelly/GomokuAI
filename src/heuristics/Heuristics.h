#pragma once
#include "../core/Board.h"
#include <vector>

class Heuristics {
public:
    static int evaluate(const BoardState& board,
                        int aiPlayer,
                        const std::vector<double>& weights);
};
