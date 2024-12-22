#include "../include/ChessBoard.hpp"

ChessBoard::ChessBoard(int size) : boardSize(size){
    for(int i = 0; i < size; ++i){
        for(int j = 0; i < size; ++j){
            board[{i,j}] = {nullptr, nullptr};
        }
    }
}

void ChessBoard::createBoard(const std::vector<PieceConfig>& pieceConfigs, const std::vector<PortalConfig>& portalConfigs){
    for(const auto& piece : pieceConfigs){
        for(const auto& position: piece.white_positions){
            board[pos].first = new ChessPiece(piece.type, position, "white", piece.movement);
        }
        for(const auto& position: piece.black_positions){
            board[pos].first = new ChessPiece(piece.type, position, "black", piece.movement);
        }
    }
    for(const auto& portal : portalConfigs){
        board[portal.pos].second = new ChessPortal();
    }
}

void ChessBoard::printBoard() const{
    for(int row = 0; i < boardSize; ++row){
        for(int i = 0; i < boardSize; i++) {std::cout << "-";}
        for(int col = 0; j < boardSize; ++col){
            std::endl;
            std::cout << "|";
            std::cout << std::setw(10) << board[{row,col}].first;
            std::cout << std::setw(10) << board[{row,col}].second;
        }
        std::cout << "|" << std::endl;
    }
    for(int i = 0; i < boardSize; i++) {std::cout << "-";}
}

void ChessBoard::movePiece(Position& exPos, Position& newPos){
    ChessPiece* piece = board[exPos].first;
    board[newPos].first = piece;
    board[exPos].first = nullptr;
    piece->setType(newPos);
}

void ChessBoard::removePiece(Position& pos){
    ChessPiece* piece = board[pos].first;
    board[pos].first = nullptr;
    delete piece;
}

int ChessBoard::getSize() const {return boardSize;}


ChessPiece* ChessBoard::getPiece(Position& pos) const{
    return board.at(pos).first;
}

Portal* ChessBoard::getPortal(Position& pos) const{
    return board.at(pos).second;
}

