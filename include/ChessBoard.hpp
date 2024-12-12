#include <vector>
#include <unordered_map>
#include <string>
#include "ChessPiece.hpp"
#include "Portal.hpp"
#include "ConfigReader.hpp"


class ChessBoard{
public:
    ChessBoard(int size);
    void createBoard(const std::vector<PieceConfig>& piece, const std::vector<PortalConfig>& portal);
    void printBoard() const;
    void movePiece(int beforex, int beforey, int afterx, int aftery);
    void possibleMoves(int x, int y);

private:
    int boardSize;
    std::unordered_map <std::string, ChessPiece*> board;
    std::unordered_map <std:: string, Portal> portals;

    std::string getInfo(int x, int y) const;
    bool isValidMove(int x, int y) const;
}
