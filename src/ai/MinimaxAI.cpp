#include "MinimaxAI.h"
#include <limits>

MinimaxAI::MinimaxAI(int player, const std::vector<double>& w)
    : aiPlayer(player), weights(w) {}

Move MinimaxAI::findBestMove(BoardState board, int depth) {
    int bestScore = std::numeric_limits<int>::min();
    Move bestMove{BOARD_SIZE / 2, BOARD_SIZE / 2};

    for (int r = 0; r < BOARD_SIZE; r++) {
        for (int c = 0; c < BOARD_SIZE; c++) {
            if (board[r][c] == EMPTY) {
                board[r][c] = aiPlayer;
                int score = minimax(board, depth - 1, false);
                board[r][c] = EMPTY;

                if (score > bestScore) {
                    bestScore = score;
                    bestMove = {r, c};
                }
            }
        }
    }
    return bestMove;
}

int MinimaxAI::minimax(BoardState& board, int depth, bool isMaxPlayer) {
    if (depth == 0) {
        return Heuristics::evaluate(board, aiPlayer, weights);
    }

    int currentPlayer = isMaxPlayer ? aiPlayer :
        (aiPlayer == BLACK ? WHITE : BLACK);

    if (isMaxPlayer) {
        int best = std::numeric_limits<int>::min();
        for (int r = 0; r < BOARD_SIZE; r++) {
            for (int c = 0; c < BOARD_SIZE; c++) {
                if (board[r][c] == EMPTY) {
                    board[r][c] = currentPlayer;
                    best = std::max(best,
                        minimax(board, depth - 1, false));
                    board[r][c] = EMPTY;
                }
            }
        }
        return best;
    } else {
        int best = std::numeric_limits<int>::max();
        for (int r = 0; r < BOARD_SIZE; r++) {
            for (int c = 0; c < BOARD_SIZE; c++) {
                if (board[r][c] == EMPTY) {
                    board[r][c] = currentPlayer;
                    best = std::min(best,
                        minimax(board, depth - 1, true));
                    board[r][c] = EMPTY;
                }
            }
        }
        return best;
    }
}
