#include "ChessBoard.hpp"
#include "MoveValidator.hpp"
#include "ConfigReader.hpp"


class GameManager{
public:
    GameManager(ChessBoard& board);
    void startGame();
    bool isValidPiece(Position& pos);
    bool isValidMove(Position& exPos, Position& newPos);
    void makeMove(Position& exPos, Position& newPos);
    bool isGameOver();
    bool isKingInDanger(bool isWhite, Position enemyKingPos);
    void switchPlayer();
private:
    ChessBoard& board;
    bool isWhiteTurn;
    MoveValidator mv;
};
