#include "MoveValidator.hpp"

MoveValidator::MoveValidator(){}


std::vector<std::vector<Position>> MoveValidator::calculatePossibleMoves(const ChessPiece& piece){
    std::vector <std::vector <Position>> cordinates;
    if(piece.cooldown != 0) return cordinates; //empty vector
    MovementRules movement = piece.getRules();
    Position currPos = piece.getPosition();
    std::vector<Position> path;
    for(int i = 0; i < movement.forward; ++i){
        Position tempPos = currPos;
        tempPos.y += 1;
        if(isValidMove(piece, tempPos)){
            path.push_back(tempPos);
        }else{
            if(isEnemyThere(piece, tempPos)){
                path.push_back(tempPos);
            }
            break;
        }
    }
    if(!path.empty()){
        cordinates.push_back(path);
        path.clear();
    }
    for(int i = 0; i < movement.backward; ++i){
        Position tempPos = currPos;
        tempPos.y -= 1;
        if(isValidMove(piece, tempPos)){
            path.push_back(tempPos);
        }else{
            if(isEnemyThere(piece, tempPos)){
                path.push_back(tempPos);
            }
            break;
        }
    }
    if(!path.empty()){
        cordinates.push_back(path);
        path.clear();
    }
    if(movement.sideways != 1){
        for(int i = 0; i < movement.sideways; ++i){
            Position tempPos = currPos;
            tempPos.x +=1;
            if(isValidMove(piece, tempPos)){
                path.push_back(tempPos);
            }else{
                if(isEnemyThere(piece, tempPos)){
                path.push_back(tempPos);
                }
                break;
            }
        }
        if(!path.empty()){
            cordinates.push_back(path);
            path.clear();
        }    
        for(int i = 0; i < movement.sideways; ++i){
            Position tempPos = currPos;
            tempPos.x -=1;
            if(isValidMove(piece, tempPos)){
                path.push_back(tempPos);
            }else{
                if(isEnemyThere(piece, tempPos)){
                path.push_back(tempPos);
                }
                break;
            }
        }
        if(!path.empty()){
            cordinates.push_back(path);
            path.clear();
        } 
    }
    if(movement.diagonal != 0){
       for(int i = 0; i < movement.diagonal; ++ i){
            Position tempPos = currPos;
            tempPos.x +=1;
            tempPos.y +=1;
            if(isValidMove(piece, tempPos)){
                path.push_back(tempPos);
            }else{
                if(isEnemyThere(piece, tempPos)){
                path.push_back(tempPos);
                }
                break;
            }
        }
        if(!path.empty()){
            cordinates.push_back(path);
            path.clear();
        } 
        for(int i = 0; i < movement.diagonal; ++ i){
            Position tempPos = currPos;
            tempPos.x +=1;
            tempPos.y -=1;
            if(isValidMove(piece, tempPos)){
                path.push_back(tempPos);
            }else{
                if(isEnemyThere(piece, tempPos)){
                path.push_back(tempPos);
                }
                break;
            }
        }
        if(!path.empty()){
            cordinates.push_back(path);
            path.clear();
        } 
        for(int i = 0; i < movement.diagonal; ++ i){
            Position tempPos = currPos;
            tempPos.x -=1;
            tempPos.y +=1;
            if(isValidMove(piece, tempPos)){
                path.push_back(tempPos);
            }else{
                if(isEnemyThere(piece, tempPos)){
                path.push_back(tempPos);
                }
                break;
            }
        }
        if(!path.empty()){
            cordinates.push_back(path);
            path.clear();
        } 
        for(int i = 0; i < movement.diagonal; ++ i){
            Position tempPos = currPos;
            tempPos.x -=1;
            tempPos.y -=1;
            if(isValidMove(piece, tempPos)){
                path.push_back(tempPos);
            }else{
                if(isEnemyThere(piece, tempPos)){
                path.push_back(tempPos);
                }
                break;
            }
        }
        if(!path.empty()){
            cordinates.push_back(path);
            path.clear();
        } 
    }
    if(movement.l_shape){
        Position tempPos = currPos;
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
    };
    for(const auto& move : lMoves){
        if(isValidMove(piece, move)){
            path.push_back(move);
            cordinates.push_back(path);
            path.clear();
        }
    }
}



bool MoveValidator::isValidMove(const ChessPiece& piece, Position& cor) const{
    if(piece.cooldown || afterx >= board.getSize() || aftery >= board.getSize() || afterx < 0 || aftery < 0) return false;
    if(board.getPiece(cor) != nullptr && board.getPortal(cor) != nullptr){
        //highlight et burda
        return true;
    }
    return false;

}

bool MoveValidator::isEnemyThere(const ChessPiece& piece, Position& pos) const{
    if(board.getPiece(cor)->type != piece.type){
        //highlight et burda
        return true;
    }
    return false;
}