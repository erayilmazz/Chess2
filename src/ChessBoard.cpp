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
        for(const auto& pos: piece.white_positions){
            board[pos].first = new ChessPiece(piece.type, pos, "white", piece.movement);
        }
        for(const auto& pos: piece.black_positions){
            board[pos].first = new ChessPiece(piece.type, pos, "black", piece.movement);
        }
    }
    /*
    for(const auto& portal : portalConfigs){
        board[portal.positions.entry].second = new Portal(portal.positions.entry, portal.positions.exit, portal.properties);
    }
    */           
}

Position ChessBoard::getKingPos(const std::string color){
    for(int row = 0; row < boardSize; ++row){
        for(int col = 0; col < boardSize; ++col){
            Position pos = {row, col};
            ChessPiece* piece = getPiece(pos);
            if(piece != nullptr && piece->getType() == "king" && piece->getColor() == color){
                Position kingPos = {row, col};
                return kingPos;
            }
        }
    }
}

void ChessBoard::printBoard() const{
    for(int row = 0; row < boardSize; ++row){
        for(int i = 0; i < boardSize; i++) {std::cout << "-------";}
        for(int col = 0; col < boardSize; ++col){
            std::cout << "\n";
            std::cout << "|";
            std::cout << std::setw(10) << board.at({row,col}).first;
            std::cout << std::setw(10) << board.at({row,col}).second;
        }
        std::cout << "|" << std::endl;
    }
    for(int i = 0; i < boardSize; i++) {std::cout << "-";}
}

void ChessBoard::movePiece(Position& exPos, Position& newPos){
    ChessPiece* piece = board[exPos].first;
    board[newPos].first = piece;
    board[exPos].first = nullptr;
    piece->setPosition(newPos);
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

