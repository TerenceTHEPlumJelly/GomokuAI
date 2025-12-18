#pragma once

#include "AIPlayer.h"
#include "../heuristics/Heuristics.h"
#include <vector>

class AlphaBetaAI : public AIPlayer {
public:
    AlphaBetaAI(int player, const std::vector<double>& weights);

    Move findBestMove(BoardState board, int depth) override;

private:
    int aiPlayer;
    std::vector<double> weights;

    int alphabeta(BoardState& board,
                  int depth,
                  int alpha,
                  int beta,
                  bool isMaxPlayer);
};
