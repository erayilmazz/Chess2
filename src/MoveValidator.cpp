#include "MoveValidator.hpp"

MoveValidator::MoveValidator(const Board& board)
    :board(board){}


std::vector<Position> MoveValidator::calculatePossibleMoves(const ChessPiece& piece){
    if(piece.cooldown != 0) return; //empty vector
    MovementRules movement = piece.getRules();
    for(int i = 0; i < movement.forward; ++i){
        Position tempPos = piece.getPosition();
        tempPos.y += 1;
        if(isValidMove(piece, tempPos))
    }
    for(int i = 0; i < movement.backward; ++i){
        Position tempPos = piece.getPosition();
        tempPos.y -= 1;
        if(isValidMove(piece, tempPos))
    }
    





}



bool MoveValidator::isValidMove(const ChessPiece& piece, Position& cor) const{
    if(piece.cooldown || afterx >= board.getSize() || aftery >= board.getSize() || afterx < 0 || aftery < 0) return false;
    

}