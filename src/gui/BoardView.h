#pragma once
#include <SFML/Graphics.hpp>
#include "../core/GameEngine.h"
#include "../core/Board.h"
#include <iostream>

class BoardView {
public:
    BoardView(GameEngine& e);  // 必须传 GameEngine

    void draw(sf::RenderWindow &window);
    bool handleClick(int x, int y, Move& m);

private:
    GameEngine& engine;
    float offset = 50.f;    // float 类型
    float cellSize = 40.f;  // float 类型
};
