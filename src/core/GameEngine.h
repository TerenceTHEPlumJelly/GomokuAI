#pragma once
#include "Board.h"
#include <vector>

class GameEngine {
public:
    GameEngine();

    const BoardState& getBoardState() const;
    bool applyMove(const Move& m, int player);
    void undoMove(const Move& m);

    int checkWinner() const;
    std::vector<Move> getLegalMoves() const;

private:
    BoardState board;

    bool inBounds(int r, int c) const;
};
