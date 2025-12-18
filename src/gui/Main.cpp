#include "../core/GameEngine.h"
#include "BoardView.h"
#include "../ai/MinimaxAI.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    GameEngine engine;
    BoardView view(engine);

    // AI 权重
    std::vector<double> weights = {10000, 5000, 500, 50, 10};
    MinimaxAI ai(WHITE, weights); // AI执白

    sf::RenderWindow window(sf::VideoMode(800, 800), "Gomoku AI");
    window.setFramerateLimit(60);

    int currentPlayer = BLACK; // 玩家执黑
    bool gameOver = false;
    sf::Font font;
    if (!font.loadFromFile("assets/STHUPO.TTF")) {
        std::cerr << "Failed to load font!" << std::endl;
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (!gameOver && currentPlayer == BLACK && event.type == sf::Event::MouseButtonPressed) {
                Move m;
                if (view.handleClick(event.mouseButton.x, event.mouseButton.y, m)) {
                    if (engine.applyMove(m, BLACK)) {
                        currentPlayer = WHITE;
                    }
                }
            }
        }

        if (!gameOver && currentPlayer == WHITE) {
            Move aiMove = ai.findBestMove(engine.getBoardState(), 2);
            engine.applyMove(aiMove, WHITE);
            currentPlayer = BLACK;
        }

        // 绘制背景
        window.clear(sf::Color(222, 184, 135)); // 浅木色
        view.draw(window);

        // 检查胜负
        int winner = engine.checkWinner();
        if (winner != EMPTY && !gameOver) {
            gameOver = true;
        }

        // 显示胜负信息
        if (gameOver && font.getInfo().family != "") {
            sf::Text text;
            text.setFont(font);
            text.setCharacterSize(36);
            text.setFillColor(sf::Color::Red);
            text.setStyle(sf::Text::Bold);
            text.setString(winner == BLACK ? "Player (Black) wins!" : "AI (White) wins!");
            text.setPosition(200, 350); // 可根据窗口居中
            window.draw(text);
        }

        window.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    return 0;
}


// #include "../core/GameEngine.h"
// #include "BoardView.h"
// #include "../ai/MinimaxAI.h"
// #include <SFML/Graphics.hpp>
// #include <iostream>
// #include <thread>
// #include <chrono>

// int main() {
//     GameEngine engine;
//     BoardView view(engine);

//     // AI 权重
//     std::vector<double> weights = {10000, 5000, 500, 50, 10};
//     MinimaxAI ai(WHITE, weights); // AI执白

//     sf::RenderWindow window(sf::VideoMode(800, 800), "Gomoku AI");
//     window.setFramerateLimit(60);

//     // 加载字体
//     sf::Font font;
//     if (!font.loadFromFile("F:/Project_GomokuAI-main/GomokuAI/STHUPO.TTF")) { // 确保存在此路径
//         std::cerr << "Failed to load font!" << std::endl;
//         return -1;
//     }
//     sf::Text resultText("", font, 40);
//     resultText.setFillColor(sf::Color::Red);
//     resultText.setPosition(50, 10);

//     int currentPlayer = BLACK;
//     bool gameOver = false;

//     while (window.isOpen()) {
//         sf::Event event;
//         while (window.pollEvent(event)) {
//             if (event.type == sf::Event::Closed)
//                 window.close();

//             if (!gameOver && currentPlayer == BLACK && event.type == sf::Event::MouseButtonPressed) {
//                 Move m;
//                 if (view.handleClick(event.mouseButton.x, event.mouseButton.y, m)) {
//                     if (engine.applyMove(m, BLACK)) {
//                         currentPlayer = WHITE;
//                     }
//                 }
//             }
//         }

//         if (!gameOver && currentPlayer == WHITE) {
//             Move aiMove = ai.findBestMove(engine.getBoardState(), 2);
//             engine.applyMove(aiMove, WHITE);
//             currentPlayer = BLACK;
//         }

//         // 绘制
//         window.clear(sf::Color(34, 139, 34)); // 深绿色背景
//         view.draw(window);

//         // 检查胜负
//         int winner = engine.checkWinner();
//         if (winner != EMPTY && !gameOver) {
//             gameOver = true;
//             std::string msg = (winner == BLACK ? "Player (Black) wins!" : "AI (White) wins!");
//             std::cout << msg << std::endl;
//             resultText.setString(msg);
//         }

//         // 如果游戏结束，显示胜负信息
//         if (gameOver) {
//             window.draw(resultText);
//         }

//         window.display();

//         std::this_thread::sleep_for(std::chrono::milliseconds(50));
//     }

//     return 0;
// }

