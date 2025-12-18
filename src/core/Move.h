#pragma once
#include <iostream>
#include <functional>

namespace Gomoku {

struct Move {
    int row;
    int col;
    
    static constexpr int SIZE = 15;  // 棋盘大小
    
    Move() : row(-1), col(-1) {}
    Move(int r, int c) : row(r), col(c) {}
    
    // 检查移动是否有效
    bool isValid() const {
        return row >= 0 && row < SIZE && col >= 0 && col < SIZE;
    }
    
    // 重载比较运算符
    bool operator==(const Move& other) const {
        return row == other.row && col == other.col;
    }
    
    bool operator!=(const Move& other) const {
        return !(*this == other);
    }
    
    bool operator<(const Move& other) const {
        if (row != other.row) return row < other.row;
        return col < other.col;
    }
    
    // 计算哈希值
    size_t hash() const {
        return static_cast<size_t>(row) * SIZE + col;
    }
    
    // 转换为字符串
    std::string toString() const {
        if (!isValid()) return "Invalid";
        return "(" + std::to_string(row) + ", " + std::to_string(col) + ")";
    }
    
    // 计算曼哈顿距离
    int manhattanDistance(const Move& other) const {
        return std::abs(row - other.row) + std::abs(col - other.col);
    }
    
    // 计算欧几里得距离
    double euclideanDistance(const Move& other) const {
        int dr = row - other.row;
        int dc = col - other.col;
        return std::sqrt(dr * dr + dc * dc);
    }
    
    // 获取所有相邻位置
    static std::vector<Move> getNeighbors(const Move& move, int radius = 1) {
        std::vector<Move> neighbors;
        for (int dr = -radius; dr <= radius; ++dr) {
            for (int dc = -radius; dc <= radius; ++dc) {
                if (dr == 0 && dc == 0) continue;
                Move neighbor(move.row + dr, move.col + dc);
                if (neighbor.isValid()) {
                    neighbors.push_back(neighbor);
                }
            }
        }
        return neighbors;
    }
};

// 输出运算符
inline std::ostream& operator<<(std::ostream& os, const Move& move) {
    os << move.toString();
    return os;
}

} // namespace Gomoku

// 哈希特化
namespace std {
    template<>
    struct hash<Gomoku::Move> {
        size_t operator()(const Gomoku::Move& move) const {
            return move.hash();
        }
    };
}