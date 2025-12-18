// AlphaBetaAI.cpp
#include "ai/AlphaBetaAI.h"
#include <limits>

AlphaBetaAI::AlphaBetaAI(int player, const std::vector<double>& w)
    : aiPlayer(player), weights(w) {}


Move AlphaBetaAI::findBestMove(BoardState board, int depth) {
    int bestScore = std::numeric_limits<int>::min();
    Move best{7,7};

    for (int r = 0; r < BOARD_SIZE; r++) {
        for (int c = 0; c < BOARD_SIZE; c++) {
            if (board[r][c] == EMPTY) {
                board[r][c] = aiPlayer;
                int s = alphabeta(board, depth - 1,
                                  std::numeric_limits<int>::min(),
                                  std::numeric_limits<int>::max(),
                                  false);
                board[r][c] = EMPTY;

                if (s > bestScore) {
                    bestScore = s;
                    best = {r, c};
                }
            }
        }
    }
    return best;
}

int AlphaBetaAI::alphabeta(BoardState& board, int depth,
                           int alpha, int beta, bool maxPlayer) {
    if (depth == 0)
        return Heuristics::evaluate(board, aiPlayer, weights);

    int current = maxPlayer ? aiPlayer : (aiPlayer == BLACK ? WHITE : BLACK);

    if (maxPlayer) {
        int value = std::numeric_limits<int>::min();
        for (int r = 0; r < BOARD_SIZE; r++) {
            for (int c = 0; c < BOARD_SIZE; c++) {
                if (board[r][c] == EMPTY) {
                    board[r][c] = current;
                    value = std::max(value,
                        alphabeta(board, depth - 1, alpha, beta, false));
                    board[r][c] = EMPTY;
                    alpha = std::max(alpha, value);
                    if (alpha >= beta) break;
                }
            }
        }
        return value;
    } else {
        int value = std::numeric_limits<int>::max();
        for (int r = 0; r < BOARD_SIZE; r++) {
            for (int c = 0; c < BOARD_SIZE; c++) {
                if (board[r][c] == EMPTY) {
                    board[r][c] = current;
                    value = std::min(value,
                        alphabeta(board, depth - 1, alpha, beta, true));
                    board[r][c] = EMPTY;
                    beta = std::min(beta, value);
                    if (alpha >= beta) break;
                }
            }
        }
        return value;
    }
}
