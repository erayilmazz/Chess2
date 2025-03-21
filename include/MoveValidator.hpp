#pragma once
#include <unordered_map>
#include "ChessBoard.hpp"


class MoveValidator{
public:
    MoveValidator(ChessBoard& board);
    std::vector<std::vector<Position>> calculatePossibleMoves(const ChessPiece& piece);
    std::vector<Position> getPath(const Position pos, std::vector<std::vector<Position>>& positions) const;
    bool isValidMove(const ChessPiece& piece, Position& cor) const;
    bool isEnemyThere(const ChessPiece& piece, Position& pos) const;
    bool isPortalThere(Position& pos) const;
    bool shortCastling(const std::string color) const;
    bool longCastling(const std::string color) const;
private:
    ChessBoard* board;
};