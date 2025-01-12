#include "../include/MoveValidator.hpp"
MoveValidator::MoveValidator(ChessBoard& board) : board(&board){}
std::vector<std::vector<Position>> MoveValidator::calculatePossibleMoves(const ChessPiece& piece){
    std::vector <std::vector <Position>> cordinates;
    if(piece.getCooldown() != 0) return cordinates; //empty vector
    MovementRules movement = piece.getRules();
    Position currPos = piece.getPosition();
    std::vector<Position> path;
    Position tempPos = currPos;
    if(piece.getColor() == "black"){
        int temp = movement.forward;
        movement.forward = movement.backward;
        movement.backward = temp;
    }
    for(int i = 0; i < movement.forward; ++i){
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
    tempPos = currPos;
    for(int i = 0; i < movement.backward; ++i){
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
    if(movement.sideways != 0){
        tempPos = currPos;
        for(int i = 0; i < movement.sideways; ++i){
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
        tempPos = currPos;
        for(int i = 0; i < movement.sideways; ++i){
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
        tempPos = currPos;
        for(int i = 0; i < movement.diagonal; ++ i){
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
        tempPos = currPos; 
        for(int i = 0; i < movement.diagonal; ++ i){
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
        tempPos = currPos;
        for(int i = 0; i < movement.diagonal; ++ i){
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
        tempPos = currPos;
        for(int i = 0; i < movement.diagonal; ++ i){
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
        tempPos = currPos;
        std::vector<Position> lMoves{
            {tempPos.x + 2, tempPos.y +1},
            {tempPos.x + 2, tempPos.y -1},
            {tempPos.x - 2, tempPos.y +1},
            {tempPos.x - 2, tempPos.y -1},
            {tempPos.x + 1, tempPos.y +2},
            {tempPos.x + 1, tempPos.y -2},
            {tempPos.x - 1, tempPos.y +2},
            {tempPos.x - 1, tempPos.y -2},
            {tempPos.x + 4, tempPos.y +2},
            {tempPos.x + 4, tempPos.y -2},
            {tempPos.x - 4, tempPos.y +2},
            {tempPos.x - 4, tempPos.y -2},
            {tempPos.x + 2, tempPos.y +4},
            {tempPos.x + 2, tempPos.y -4},
            {tempPos.x - 2, tempPos.y +4},
            {tempPos.x - 2, tempPos.y -4}
        };
        for(auto& move : lMoves){
            if(isValidMove(piece, move)){
                path.push_back(move);
                cordinates.push_back(path);
                path.clear();
            }
        }
    }
    return cordinates;
}

std::vector<Position> MoveValidator::getPath(const Position pos, std::vector<std::vector<Position>>& positions) const{
    for(const auto& position: positions){
        for(const auto& p : position){
            if(p == pos){
                return position;
            }
        }
    }
    return std::vector<Position>();//boş vector
}

bool MoveValidator::isValidMove(const ChessPiece& piece, Position& cor) const{
    if(piece.getCooldown() != 0 || cor.x >= board->getSize() || cor.y >= board->getSize() || cor.x < 0 || cor.y < 0) return false;
    if(board->getPiece(cor) == nullptr && board->getPortal(cor) == nullptr){
        return true;
    }
    return false;

}

bool MoveValidator::isEnemyThere(const ChessPiece& piece, Position& pos) const{
    if(pos.x >= board->getSize() || pos.y >= board->getSize() || pos.x < 0 || pos.y < 0) return false;
    if(board->getPiece(pos)->getColor() != piece.getColor()){
        //highlight et burda
        return true;
    }
    return false;
}