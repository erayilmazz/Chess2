#include <unordered_map>
#include "ChessPiece.hpp"
#include "ChessBoard.hpp"


class MoveValidator{
public:
    MoveValidator();

    bool isValidMove(const ChessPiece& piece, int beforex, int beforey, int afterx, int aftery) const;
    std::vector<std::pair<int,int>> getValidMoves(const ChessPiece& piece, int beforex, int aftery) const;

private:
    const ChessBoard& board;
    const std::unordered_map<std::string, ChessPiece*>& pieces;
};