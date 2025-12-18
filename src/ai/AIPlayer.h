#pragma once
#include "../core/Board.h"
#include <vector>

class AIPlayer {
public:
    virtual Move findBestMove(BoardState board, int depth) = 0;
    virtual ~AIPlayer() = default;
};
