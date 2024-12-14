#include <vector>
#include <unordered_map>
#include <string>
#include "ChessPiece.hpp"
//#include "Portal.hpp"
#include "ConfigReader.hpp"


class ChessBoard{
public:
    ChessBoard(int size);
    void createBoard(const std::vector<PieceConfig>& piece, const std::vector<PortalConfig>& portal);
    void printBoard() const;
    void movePiece(int beforex, int beforey, int afterx, int aftery);
    std::vector<std::pair<int,int>> possibleMoves(int x, int y);
    int getSize() const;

    ChessPiece* getPiece(int x, int y) const;
    Portal* getPortal(int x, int y) const;

private:
    int boardSize;
    std::unordered_map <std::string, ChessPiece*> board;
    std::unordered_map <std:: string, Portal> portals;

    bool isValidMove(int beforex, int beforey, int afterx, int aftery) const;
}
