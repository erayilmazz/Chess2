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
    if(movement.sideways != 1){
        for(int i = 0; i < movement.sideways; ++i){
            Position tempPos = piece.getPosition();
            tempPos.x +=1;
            if(isValidMove(piece, tempPos)) 
        }
        for(int i = 0; i < movement.sideways; ++i){
            Position tempPos = piece.getPosition();
            tempPos.x -=1;
            if(isValidMove(piece, tempPos)) 
        }
    }
    if(movement.diagonal != 0){
       for(int i = 0; i < movement.diagonal; ++ i){
            Position tempPos = piece.getPosition();
            tempPos.x +=1;
            tempPos.y +=1;
            if(isValidMove(piece, tempPos))
        }
        for(int i = 0; i < movement.diagonal; ++ i){
            Position tempPos = piece.getPosition();
            tempPos.x +=1;
            tempPos.y -=1;
            if(isValidMove(piece, tempPos))
        }
        for(int i = 0; i < movement.diagonal; ++ i){
            Position tempPos = piece.getPosition();
            tempPos.x -=1;
            tempPos.y +=1;
            if(isValidMove(piece, tempPos))
        } 
        for(int i = 0; i < movement.diagonal; ++ i){
            Position tempPos = piece.getPosition();
            tempPos.x -=1;
            tempPos.y -=1;
            if(isValidMove(piece, tempPos))
        }  
    }
    if(movement.l_shape){
        Position tempPos = piece.getPosition();
        std::vector<Position> lMoves{
            {tempPos.x += 2, tempPos.y +=1},
            {tempPos.x += 2, tempPos.y -=1},
            {tempPos.x -= 2, tempPos.y +=1},
            {tempPos.x -= 2, tempPos.y -=1},
            {tempPos.x += 1, tempPos.y +=2},
            {tempPos.x += 1, tempPos.y -=2},
            {tempPos.x -= 1, tempPos.y +=2},
            {tempPos.x -= 1, tempPos.y -=2},
            {tempPos.x += 4, tempPos.y +=2},
            {tempPos.x += 4, tempPos.y -=2},
            {tempPos.x -= 4, tempPos.y +=2},
            {tempPos.x -= 4, tempPos.y -=2},
            {tempPos.x += 2, tempPos.y +=4},
            {tempPos.x += 2, tempPos.y -=4},
            {tempPos.x -= 2, tempPos.y +=4},
            {tempPos.x -= 2, tempPos.y -=4}
        }
    }


}



bool MoveValidator::isValidMove(const ChessPiece& piece, Position& cor) const{
    if(piece.cooldown || afterx >= board.getSize() || aftery >= board.getSize() || afterx < 0 || aftery < 0) return false;
    

}