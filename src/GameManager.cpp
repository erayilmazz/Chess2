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
    //1. koşul: mevcut turndeki bütün taşları karşı takımın şahına ispossiblemove yaptırt
    //2.koşul: rakip şahını hareket ettirdiğinde is possible move yaptırt bütün taşlara
    //3.koşul: şah yaptırtan bütün yolları bulup o yollara herhangi taş gidebiliyor mu kontrol et
    
}

void GameManager::switchPlayer(){
    if(isWhiteTurn) isWhiteTurn = false;
    else isWhiteTurn = true;
}