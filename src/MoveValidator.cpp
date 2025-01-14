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
            if(movement.first_move_forward > 0 && piece.getMoveBefore() == 0){
                tempPos = currPos;
                tempPos.y += movement.first_move_forward;
                if(isValidMove(piece, tempPos) || isPortalThere(tempPos)){
                    path.push_back(tempPos);
                    cordinates.push_back(path);
                    path.clear();
                }
            }
        }else{
            if((isEnemyThere(piece, tempPos) && piece.getType() != "pawn")  || isPortalThere(tempPos)){
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
            if(movement.first_move_forward > 0 && piece.getMoveBefore() == 0){
                tempPos = currPos;
                tempPos.y -= movement.first_move_forward;
                if(isValidMove(piece, tempPos) || isPortalThere(tempPos)){
                    path.push_back(tempPos);
                    cordinates.push_back(path);
                    path.clear();
                }
            }
        }else{
            if((isEnemyThere(piece, tempPos) && piece.getType() != "pawn") || isPortalThere(tempPos)){
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
                if((isEnemyThere(piece, tempPos) && piece.getType() != "pawn") || isPortalThere(tempPos)){
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
                if((isEnemyThere(piece, tempPos) && piece.getType() != "pawn") || isPortalThere(tempPos)){
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
                if(isEnemyThere(piece, tempPos) || isPortalThere(tempPos)){
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
                if(isEnemyThere(piece, tempPos) || isPortalThere(tempPos)){
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
                if(isEnemyThere(piece, tempPos) || isPortalThere(tempPos)){
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
                if(isEnemyThere(piece, tempPos) || isPortalThere(tempPos)){
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
            if(isValidMove(piece, move) || isPortalThere(move)){ // AT YİYEMİYOR
                path.push_back(move);
                cordinates.push_back(path);
                path.clear();
            }   
        }
    }
    if(movement.diagonal_capture){
        tempPos = currPos;
        std::vector<Position> dMoves;
        if(piece.getColor() == "white"){
            tempPos.x += 1, tempPos.y += 1;
            if(isEnemyThere(piece, tempPos)){
                path.push_back(tempPos);
                cordinates.push_back(path);
                path.clear();
            }
            tempPos = currPos;
            tempPos.x -= 1, tempPos.y += 1;
            if(isEnemyThere(piece, tempPos)){
                path.push_back(tempPos);
                cordinates.push_back(path);
                path.clear();
            }
        }else{
            tempPos.x += 1, tempPos.y -= 1;
            if(isEnemyThere(piece, tempPos)){
                path.push_back(tempPos);
                cordinates.push_back(path);
                path.clear();
            }
            tempPos = currPos;
            tempPos.x -= 1, tempPos.y -= 1;
            if(isEnemyThere(piece, tempPos)){
                path.push_back(tempPos);
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
    if(board->getPiece(pos) == nullptr) return false;
    if(board->getPiece(pos)->getColor() != piece.getColor()){
        //highlight et burda
        return true;
    }
    return false;
}

bool MoveValidator::isPortalThere(Position& pos) const{
    if(pos.x >= board->getSize() || pos.y >= board->getSize() || pos.x < 0 || pos.y < 0) return false;
    if(board->getPortal(pos) != nullptr){
        return true;
    }
    return false;
}

bool MoveValidator::shortCastling(const std::string color) const{
    Position king, castle, empty1, empty2;
    if(color == "white"){
        king = {5,0};
        castle = {8,0};
        empty1 = {6,0};
        empty2 = {7,0};
    }else{
        king = {5,9};
        castle = {8,9};
        empty1 = {6,9};
        empty2 = {7,9};
    }
    if(board->getPiece(king) == nullptr || board->getPiece(castle) == nullptr) return false;
    if(board->getPiece(king)->getMoveBefore() || board->getPiece(castle)->getMoveBefore()) return false;
    if(board->getPiece(empty1) == nullptr && board->getPiece(empty2) == nullptr) return true;
    return false;
}

bool MoveValidator::longCastling(const std::string color) const{
    Position king, castle, empty1, empty2, empty3;
    if(color == "white"){
        king = {5,0};
        castle = {1,0};
        empty1 = {2,0};
        empty2 = {3,0};
        empty3 = {4,0};
    }else{
        king = {5,9};
        castle = {1,9};
        empty1 = {2,9};
        empty2 = {3,9};
        empty3 = {4,9};
    }
    if(board->getPiece(king) == nullptr || board->getPiece(castle) == nullptr) return false;
    if(board->getPiece(king)->getMoveBefore() || board->getPiece(castle)->getMoveBefore()) return false;
    if(board->getPiece(empty1) == nullptr && board->getPiece(empty2) == nullptr && board->getPiece(empty3) == nullptr) return true;
    return false;
}