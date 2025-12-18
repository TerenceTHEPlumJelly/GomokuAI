#include "Heuristics.h"
#include <limits>

static int scoreLine(int count, int openEnds,
                     const std::vector<double>& w) {
    if (count >= 5) return std::numeric_limits<int>::max();
    if (count == 4 && openEnds == 2) return w[0];
    if (count == 4 && openEnds == 1) return w[1];
    if (count == 3 && openEnds == 2) return w[2];
    if (count == 3 && openEnds == 1) return w[3];
    if (count == 2 && openEnds == 2) return w[4];
    return 0;
}

int Heuristics::evaluate(const BoardState& board,
                         int aiPlayer,
                         const std::vector<double>& w) {
    int opponent = (aiPlayer == BLACK) ? WHITE : BLACK;
    int score = 0;
    const int dirs[4][2] = {{1,0},{0,1},{1,1},{1,-1}};

    auto evalPlayer = [&](int p) {
        int s = 0;
        for (int r = 0; r < BOARD_SIZE; r++) {
            for (int c = 0; c < BOARD_SIZE; c++) {
                if (board[r][c] != p) continue;
                for (auto& d : dirs) {
                    int cnt = 1;
                    int open = 0;
                    int nr = r + d[0], nc = c + d[1];
                    while (nr >= 0 && nr < BOARD_SIZE &&
                           nc >= 0 && nc < BOARD_SIZE &&
                           board[nr][nc] == p) {
                        cnt++;
                        nr += d[0];
                        nc += d[1];
                    }
                    if (nr >= 0 && nr < BOARD_SIZE &&
                        nc >= 0 && nc < BOARD_SIZE &&
                        board[nr][nc] == EMPTY) open++;

                    int br = r - d[0], bc = c - d[1];
                    if (br >= 0 && br < BOARD_SIZE &&
                        bc >= 0 && bc < BOARD_SIZE &&
                        board[br][bc] == EMPTY) open++;

                    s += scoreLine(cnt, open, w);
                }
            }
        }
        return s;
    };

    score += evalPlayer(aiPlayer);
    score -= evalPlayer(opponent);
    return score;
}
