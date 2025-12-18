#include "GameEngine.h"

GameEngine::GameEngine() {
    board = BoardState(BOARD_SIZE, std::vector<int>(BOARD_SIZE, EMPTY));
}

const BoardState& GameEngine::getBoardState() const {
    return board;
}

bool GameEngine::applyMove(const Move& m, int player) {
    if (board[m.row][m.col] != EMPTY) return false;
    board[m.row][m.col] = player;
    return true;
}

void GameEngine::undoMove(const Move& m) {
    board[m.row][m.col] = EMPTY;
}

bool GameEngine::inBounds(int r, int c) const {
    return r >= 0 && r < BOARD_SIZE && c >= 0 && c < BOARD_SIZE;
}

std::vector<Move> GameEngine::getLegalMoves() const {
    std::vector<Move> moves;
    static const int D = 2;

    for (int r = 0; r < BOARD_SIZE; r++) {
        for (int c = 0; c < BOARD_SIZE; c++) {
            if (board[r][c] != EMPTY) {
                for (int dr = -D; dr <= D; dr++) {
                    for (int dc = -D; dc <= D; dc++) {
                        int nr = r + dr;
                        int nc = c + dc;
                        if (inBounds(nr, nc) && board[nr][nc] == EMPTY) {
                            moves.push_back({nr, nc});
                        }
                    }
                }
            }
        }
    }

    if (moves.empty()) {
        moves.push_back({BOARD_SIZE / 2, BOARD_SIZE / 2});
    }

    return moves;
}

int GameEngine::checkWinner() const {
    const int dirs[4][2] = {{1,0},{0,1},{1,1},{1,-1}};

    for (int r = 0; r < BOARD_SIZE; r++) {
        for (int c = 0; c < BOARD_SIZE; c++) {
            int p = board[r][c];
            if (p == EMPTY) continue;

            for (auto& d : dirs) {
                int cnt = 1;
                int nr = r + d[0], nc = c + d[1];
                while (inBounds(nr, nc) && board[nr][nc] == p) {
                    cnt++;
                    nr += d[0];
                    nc += d[1];
                }
                if (cnt >= 5) return p;
            }
        }
    }
    return EMPTY;
}
