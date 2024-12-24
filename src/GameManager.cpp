#include "../include/GameManager.hpp"

GameManager::GameManager(){}

void GameManager::startGame(){
    ConfigReader configReader("config.json");
    board.createBoard(configReader.getPieceConfigs(), configReader.getPortalConfigs());
    board.printBoard();
}

bool GameManager::isValidPiece(Position& pos){
    //gelen input olacak
    ChessPiece* piece = getPiece(pos); 
    if(piece == nullptr) return false;
    if((piece->getColor() == "white" && isWhiteTurn) || (piece.getColor() == "black" && !isWhiteTurn)){
        return true;
    }
    return false;
}

bool GameManager::isValidMove(Position& exPos, Position& newPos){
    if(isValidMove(board.getPiece(exPos), newPos)){
        makeMove();
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
    if (isWhiteTurn == true){
        enemyKingPos = board.getKingPos("black");
        if(isKingInDanger(true, enemyKingPos) == true){
            kingPosMove = board.calculatePossiblemoves();
            for(const auto& pos: kingPosMove){
                if(isKingInDanger(true, pos) == true)
            }
        }
        return false;
    }else{
    }  
}

bool GameManager::isKingInDanger(bool isWhite, ChessPiece& enemyKingPos){
    for(int row = 0; row < board.getSize(); ++row){
            for(int col = 0; col < board.getSize(); ++col){
                if(board.getPiece({row,col}).getColor() == "white"){
                    if (isValidMove(board.getPiece({row, col}), enemyKingPos())) return true;
                }
            }
        }
}

void GameManager::switchPlayer(){
    if(isWhiteTurn) isWhiteTurn = false;
    else isWhiteTurn = true;
}