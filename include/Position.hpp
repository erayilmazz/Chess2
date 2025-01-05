#pragma once

struct Position{
    int x;
    int y;
    bool operator == (const Position& other) const{
        return x == other.x && y == other.y;
    }
};
namespace std{
    template <>
    struct hash<Position> {
        size_t operator() (const Position& pos) const noexcept{
            return std::hash<int>()(pos.x) ^ (std::hash<int>()(pos.y) << 1);
        }
    };
}
