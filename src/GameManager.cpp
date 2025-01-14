#include "../third_party/nlohmann/json.hpp"
#include "../include/GameManager.hpp"
#include "../include/ChessBoard.hpp"
#include "../include/MoveValidator.hpp"
#include "../include/ConfigReader.hpp"

GameManager::GameManager(ChessBoard& board): board(board), turn("white"), mv(board){}

void GameManager::startGame(){
    ConfigReader configReader("data/chess_pieces.json");
    configReader.readConfig();
    board.createBoard(configReader.getPieceConfigs(), configReader.getPortalConfigs());
    board.printBoard();
}

bool GameManager::isValidPiece(Position& pos){
    //gelen input olacak
    ChessPiece* piece = board.getPiece(pos); 
    if(piece == nullptr) return false;
    if(piece->getColor()  == turn){
        return true;
    }
    return false;
}
std::vector<Position> GameManager::getPossibleMoves(Position& pos){
    ChessPiece* piece = board.getPiece(pos);
    std::vector<std::vector<Position>> twoVec = mv.calculatePossibleMoves(*piece);
    std::vector<Position> moves;
    for(const auto& move : twoVec){
        for(const auto& m : move){
            moves.push_back(m);
        }
    }
    return moves;
}

bool GameManager::isValidMove(Position& exPos, Position& newPos){
    ChessPiece* piece = board.getPiece(exPos);
    if(mv.isValidMove(*piece, newPos)){
        makeMove(exPos,newPos);
        return true;
   }
   return false;
}

void GameManager::makeMove(Position& exPos, Position& newPos){
    if(board.getPiece(newPos) != nullptr) board.removePiece(newPos); //rakip taş varsa onu yok et
    board.movePiece(exPos, newPos);    
}

bool GameManager::isGameOver(){
    //1. koşul: mevcut turndeki bütün taşları karşı takımın şahına ispossiblemove yaptırt(+)
    //2.koşul: rakip şahını hareket ettirdiğinde is possible move yaptırt bütün taşlara(+)
    //3.koşul: şah yaptırtan bütün yolları bulup o yollara herhangi taş gidebiliyor mu kontrol et
    Position enemyKingPos;
    if (turn == "white"){
        enemyKingPos = board.getKingPos("black");
    }else{
        enemyKingPos = board.getKingPos("white");
    }
    if(isKingInDanger(turn, enemyKingPos)){
        ChessPiece* enemyKing = board.getPiece(enemyKingPos);
        std::vector<std::vector<Position>> kingPosMove = mv.calculatePossibleMoves(*enemyKing);
        for(const auto& position: kingPosMove){
            for(const auto& pos : position){
                if(isKingInDanger(turn, pos) == false){
                    return false;
                }
            }
        }
        return true;
    }
    return false;    
}

bool GameManager::isKingInDanger(std::string turn, Position enemyKingPos){
    for(int row = 0; row < board.getSize(); ++row){
            for(int col = 0; col < board.getSize(); ++col){
                Position pos = {row, col};
                ChessPiece* piece = board.getPiece(pos);
                if(piece == nullptr) continue;
                if(piece->getColor() == turn){
                    std::vector<std::vector<Position>> kingPosMove = mv.calculatePossibleMoves(*piece);
                    for(const auto& position: kingPosMove){
                        for(const auto& pos : position){
                            if(pos == enemyKingPos) return true;
                        }
                    }
                }
            }
    }
    return false;
}

bool GameManager::isShortCastling(){
    if(mv.shortCastling(turn)) return true;
    return false;
}

void GameManager::makeShortCastling(){ board.makeShortCastling(turn);}

bool GameManager::isLongCastling(){
    if(mv.longCastling(turn)) return true;
    return false;
}

void GameManager::makeLongCastling(){ board.makeLongCastling(turn);}



void GameManager::switchPlayer(){
    if(turn == "white"){
        turn = "black";
    }
    else if(turn == "black"){
        turn = "white";
    }
}