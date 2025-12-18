#pragma once

#include "AIPlayer.h"
#include "../heuristics/Heuristics.h"
#include <vector>

class MinimaxAI : public AIPlayer {
public:
    MinimaxAI(int player, const std::vector<double>& weights);

    Move findBestMove(BoardState board, int depth) override;

private:
    int aiPlayer;
    std::vector<double> weights;

    int minimax(BoardState& board, int depth, bool isMaxPlayer);
};
