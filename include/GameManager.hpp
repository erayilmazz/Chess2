#include "ChessBoard.hpp"
#include "MoveValidator.hpp"
#include "ConfigReader.hpp"


class GameManager{
public:
    GameManager(ChessBoard& board);
    void startGame();
    bool isValidPiece(Position& pos);
    std::vector<Position> getPossibleMoves(Position& pos);
    bool isValidMove(Position& exPos, Position& newPos);
    void makeMove(Position& exPos, Position& newPos);
    bool isGameOver();
    bool isKingInDanger(std::string turn, Position enemyKingPos);
    bool isShortCastling();
    void makeShortCastling();
    bool isLongCastling();
    void makeLongCastling();
    void switchPlayer();
private:
    ChessBoard& board;
    std::string turn;
    MoveValidator mv;
};
