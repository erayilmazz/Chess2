#include "../third_party/nlohmann/json.hpp"
#include "../include/GameManager.hpp"
#include "../include/ChessBoard.hpp"
#include "../include/MoveValidator.hpp"
#include "../include/ConfigReader.hpp"

GameManager::GameManager(ChessBoard& board): board(board), isWhiteTurn(true){}

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
    if((piece->getColor() == "white" && isWhiteTurn) || (piece->getColor() == "black" && !isWhiteTurn)){
        return true;
    }
    return false;
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
    board.printBoard();
    
}

bool GameManager::isGameOver(){
    //1. koşul: mevcut turndeki bütün taşları karşı takımın şahına ispossiblemove yaptırt(+)
    //2.koşul: rakip şahını hareket ettirdiğinde is possible move yaptırt bütün taşlara(+)
    //3.koşul: şah yaptırtan bütün yolları bulup o yollara herhangi taş gidebiliyor mu kontrol et
    /*
    if (isWhiteTurn == true){
        Position enemyKingPos = board.getKingPos("black");
        if(isKingInDanger(true, enemyKingPos) == true){
            ChessPiece* enemyKing = board.getPiece(enemyKingPos);
            std::vector<std::vector<Position>> kingPosMove = mv.calculatePossibleMoves(*enemyKing);
            for(const auto& position: kingPosMove){
                for(const auto& pos : position){
                    if(isKingInDanger(true, pos) == false){
                        return false;
                    }
                }
            }
            mv.getPath(enemyKingPos);
            mv.calculatePossibleMoves();
            
            for(const auto& pos : path){
                if(isKingInDanger(false, pos) == false){
                    return false;
                }
            }
        }
        return false;
    }else{
    }
    */
    return false;
}

bool GameManager::isKingInDanger(bool isWhite, Position enemyKingPos){
    for(int row = 0; row < board.getSize(); ++row){
            for(int col = 0; col < board.getSize(); ++col){
                Position pos = {row, col};
                ChessPiece* piece = board.getPiece(pos);
                if(piece->getColor() == "white"){
                    if (isValidMove(pos, enemyKingPos)) return true;
                }
            }
        }
}

void GameManager::switchPlayer(){
    if(isWhiteTurn) isWhiteTurn = false;
    else isWhiteTurn = true;
}