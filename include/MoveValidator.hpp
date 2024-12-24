#include <unordered_map>
#include "ChessBoard.hpp"


class MoveValidator{
public:
    MoveValidator();
    std::vector<std::vector<Position>> calculatePossibleMoves(const ChessPiece& piece);
    bool isValidMove(const ChessPiece& piece, Position& cor) const;
    bool isEnemyThere(const ChessPiece& piece, Position& pos) const;

};