#pragma once
#include <vector>

constexpr int BOARD_SIZE = 15;

enum Cell {
    EMPTY = 0,
    BLACK = 1,
    WHITE = 2
};

using BoardState = std::vector<std::vector<int>>;

struct Move {
    int row;
    int col;
};
