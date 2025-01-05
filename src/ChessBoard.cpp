#include "../third_party/nlohmann/json.hpp"
#include "../include/ChessBoard.hpp"
#include "../include/ConfigReader.hpp"


ChessBoard::ChessBoard(int size) : boardSize(size){
    for(int i = 0; i < size; ++i){
        for(int j = 0; j < size; ++j){
            board[{i,j}] = {nullptr, nullptr};
        }
    }
}

void ChessBoard::createBoard(const std::vector<PieceConfig>& pieceConfigs, const std::vector<PortalConfig>& portalConfigs){
    for(const auto& piece : pieceConfigs){
        for(auto pos: piece.white_positions){
            board[pos].first = new ChessPiece(piece.type, pos, "white", piece.movement);
        }
        for(auto pos: piece.black_positions){
            board[pos].first = new ChessPiece(piece.type, pos, "black", piece.movement);
        }
    }
    
    for(const auto& portal : portalConfigs){
        board[portal.positions.entry].second = new Portal(portal.id, portal.positions.entry, portal.positions.exit, portal.properties);
    }
       
}

Position ChessBoard::getKingPos(const std::string color){
    for(int row = boardSize; row > 0; --row){
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
    std::vector<char> letters = {'a','b','c','d','e','f','g','h','i','j'};
    for(int i = 0; i < boardSize; i++) {
            std::cout << "   ";
            std::cout << letters[i];   
            std::cout << "   ";
    }
    std::cout << "\n";
    for(int row = 9; row >= 0; --row){
        std::cout << row;
        for(int i = 0; i < boardSize; i++) {
            std::cout << "-------";
        }
        std::cout << "\n";
        for(int col = 0; col < boardSize; ++col){
            std::cout << "|";
            if(board.at({col,row}).first != nullptr)
                std::cout << "  " << board.at({col,row}).first->getEmoji();
            else std::cout << "   ";
            if(board.at({col,row}).second != nullptr)
                std::cout << "  " << board.at({col,row}).second->getPortal();
            else std::cout << "   ";
        }
        std::cout << "|" << std::endl;
    }
    for(int i = 0; i < boardSize * 7; i++) {std::cout << "-";}
    std::cout << "\n";
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

	