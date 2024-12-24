#include "ChessBoard.hpp"


class GameManager{
public:
    GameManager();
    void startGame();
    bool isValidPiece(Position& pos);
    bool isValidMove(Position& exPos, Position& newPos);
    void makeMove(Position& exPos, Position& newPos);
    bool isGameOver();
    bool isKingInDanger(bool isWhite, ChessPiece& enemyKingPos);
    void switchPlayer();
private:
    bool isWhiteTurn;
};
