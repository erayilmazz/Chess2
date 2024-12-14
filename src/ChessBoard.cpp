#include "../obj/ChessBoard.hpp"

ChessBoard::ChessBoard(int size) : boardSize(size){
    //create board
}

void ChessBoard::createBoard(const std::vector<PieceConfig>& piece, const std::vector<PortalConfig>& portal){

}

void ChessBoard::printBoard() const{

}

void ChessBoard::movePiece(int beforex, int beforey, int afterx, int aftery){
    auto moves = possibleMoves(beforex, beforey);
    for(auto& move : moves){
        if(move.first == afterx && move.second == aftery){
            //change board
            break;
        }
    }
}

std::vector<std::pair<int,int>> ChessBoard::possibleMoves(int x, int y){
    std::vector<std::pair<int,int>> moves;
    for(int i = 0; i < boardSize; ++i){
        for(int j = 0; j < boardSize; ++j){
            if(isValidMove(x, y, i, j)){
                //highlight there
                moves.push_back(i,j);
            }
        }
    }
    return moves;
}

int ChessBoard::getSize() const {return boardSize;}


ChessPiece* ChessBoard::getPiece(int x, int y) const{

}

Portal* ChessBoard::getPortal(int x, int y) const{

}

bool ChessBoard::isValidMove(int beforex, int beforey, int afterx, int aftery) const{

}