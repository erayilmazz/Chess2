#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>
#include "ChessPiece.hpp"
#include "Portal.hpp"
//#include "Position.hpp"
#include "ConfigReader.hpp"



class ChessBoard{
public:
    ChessBoard(int size);
    void createBoard(const std::vector<PieceConfig>& piece, const std::vector<PortalConfig>& portal);
    void printBoard() const;
    void movePiece(Position& exPos, Position& newPos);
    void removePiece(Position& pos);
    int getSize() const;

    Position getKingPos(const std::string color);
    ChessPiece* getPiece(Position& pos) const;
    Portal* getPortal(Position& pos) const;

private:
    int boardSize;
    std::unordered_map <Position, std::pair<ChessPiece*, Portal*>> board;
};
