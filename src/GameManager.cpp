#include "../include/GameManager.hpp"

GameManager::GameManager(){}

void GameManager::startGame(){
    //boardı kur
    //portalı ve taşları yerine koy chessboard fonksiyon
    isWhiteTurn = true;
}

bool GameManager::isValidPiece(){
    //gelen input olacak
    if((piece.getColor() == "white" && isWhiteTurn) || (piece.getColor() == "black" && !isWhiteTurn)){
        return true;
    }
    return false;
}

bool GameManager::isValidMove(){
    //gelen kordinat inputu
    for(const auto& cor : cors){
        if(cordinat == cor) return true;
    }
    return false;
}

void GameManager::makeMove(){
    //input olarak kordinat ve taş gelecek
    // if ile o kardinatta taş olup olmadığına bak
    //varsa o taşı sil ve taşı hareket ettir
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