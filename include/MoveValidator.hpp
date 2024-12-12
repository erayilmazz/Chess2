#include <unordered_map>


class MoveValidator{
public:
    MoveValidator(const Board& board);

    bool isValidMove(const ChessPiece& piece, int beforex, int beforey, int afterx, int aftery) const;
    std::vector<std::pair<int,int>> getValidMoves(const ChessPiece& piece, int beforex, int aftery) const;

private:
    const ChessBoard& board;
    const std::unordered_map<std::string, ChessPiece*>& pieces;
};