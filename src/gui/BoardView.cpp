#include "BoardView.h"

BoardView::BoardView(GameEngine& e) : engine(e) {}

void BoardView::draw(sf::RenderWindow& window) {
    // 棋盘线颜色
    sf::Color lineColor(139, 69, 19); // 深棕色

    // 绘制棋格
    for (int i = 0; i < BOARD_SIZE; i++) {
        sf::Vertex h[] = {
            {sf::Vector2f(offset, offset + i*cellSize), lineColor},
            {sf::Vector2f(offset + (BOARD_SIZE-1)*cellSize, offset + i*cellSize), lineColor}
        };
        window.draw(h, 2, sf::Lines);

        sf::Vertex v[] = {
            {sf::Vector2f(offset + i*cellSize, offset), lineColor},
            {sf::Vector2f(offset + i*cellSize, offset + (BOARD_SIZE-1)*cellSize), lineColor}
        };
        window.draw(v, 2, sf::Lines);
    }

    // 绘制棋子
    const auto& board = engine.getBoardState();
    for (int r = 0; r < BOARD_SIZE; r++) {
        for (int c = 0; c < BOARD_SIZE; c++) {
            if (board[r][c] == EMPTY) continue;

            sf::CircleShape piece(cellSize/2 - 2);
            piece.setPosition(offset + c*cellSize - cellSize/2 + 2,
                              offset + r*cellSize - cellSize/2 + 2);

            if (board[r][c] == BLACK) {
                piece.setFillColor(sf::Color::Black);
            } else {
                piece.setFillColor(sf::Color::White);
                piece.setOutlineThickness(2.f);
                piece.setOutlineColor(sf::Color::Black);
            }
            window.draw(piece);
        }
    }
}

bool BoardView::handleClick(int x, int y, Move& m) {
    int col = (x - offset + cellSize/2) / cellSize;
    int row = (y - offset + cellSize/2) / cellSize;

    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE)
        return false;

    m = {row, col};
    return true;
}


// #include "BoardView.h"
// #include "../core/Board.h"
// #include "../core/GameEngine.h"
// #include <SFML/Graphics.hpp>
// BoardView::BoardView(GameEngine& e) : engine(e) {}

// void BoardView::draw(sf::RenderWindow& window) {
//     sf::Color lineColor(139, 69, 19);

//     for (int i = 0; i < BOARD_SIZE; i++) {
//         sf::Vertex h[] = {
//             {sf::Vector2f(offset, offset + i*cellSize), lineColor},
//             {sf::Vector2f(offset + (BOARD_SIZE-1)*cellSize, offset + i*cellSize), lineColor}
//         };
//         window.draw(h, 2, sf::Lines);

//         sf::Vertex v[] = {
//             {sf::Vector2f(offset + i*cellSize, offset), lineColor},
//             {sf::Vector2f(offset + i*cellSize, offset + (BOARD_SIZE-1)*cellSize), lineColor}
//         };
//         window.draw(v, 2, sf::Lines);
//     }

//     const auto& board = engine.getBoardState();
//     for (int r = 0; r < BOARD_SIZE; r++) {
//         for (int c = 0; c < BOARD_SIZE; c++) {
//             if (board[r][c] == EMPTY) continue;
//             sf::CircleShape piece(cellSize/2 - 2);
//             piece.setPosition(offset + c*cellSize - cellSize/2 + 2,
//                               offset + r*cellSize - cellSize/2 + 2);
//             piece.setFillColor(board[r][c] == BLACK ? sf::Color::Black : sf::Color::White);
//             window.draw(piece);
//         }
//     }
// }

// bool BoardView::handleClick(int x, int y, Move& m) {
//     int col = (x - offset + cellSize/2) / cellSize;
//     int row = (y - offset + cellSize/2) / cellSize;

//     if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE)
//         return false;

//     m = {row, col};
//     return true;
// }
