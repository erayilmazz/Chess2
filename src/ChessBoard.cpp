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
        Position pos = portal.positions.entry;
        board[pos].second = new Portal(portal.id, portal.positions.entry, portal.positions.exit, portal.properties);
    }
       
}

Position ChessBoard::getKingPos(const std::string color){
    for(int row = 0; row < boardSize; ++row){
        for(int col = 0; col < boardSize; ++col){
            Position pos = {row, col};
            if(getPiece(pos) == nullptr) continue;
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

void ChessBoard::setCooldowns(const std::string& color){
    for(int i = 0; i < getSize(); ++i){
        for(int j = 0; j < getSize(); ++j){
            Position pos = {i, j};
            ChessPiece* piece =getPiece(pos);
            if(piece != nullptr && piece->getColor() == color){
                piece->setCooldown(0);
            }
        }
    }
}



void ChessBoard::movePiece(Position& exPos, Position& newPos){
    ChessPiece* piece = board[exPos].first;
    piece->setMoveBefore();
    board[newPos].first = piece;
    board[exPos].first = nullptr;
    piece->setPosition(newPos);
    setCooldowns(piece->getColor());
    if(getPortal(newPos) != nullptr){
        Portal* portal = getPortal(newPos);
        Position portalNewPos = portal->getExit();
        if(getPiece(portalNewPos) != nullptr) removePiece(portalNewPos);
        board[portalNewPos].first = piece;
        board[newPos].first = nullptr;
        piece->setPosition(portalNewPos);
        piece->setCooldown(1);
    }
    pawnPromotion(*piece);
}

void ChessBoard::makeShortCastling(std::string color){
    Position king, castle;
    if(color == "white"){
        king = {5,0};
        castle = {8,0};
    }else{
        king = {5,9};
        castle = {8,9};
    }
    ChessPiece* pieceKing = board[king].first;
    ChessPiece* pieceCastle = board[castle].first;
    board[king].first = pieceCastle;
    board[castle].first = pieceKing;
    pieceKing->setPosition(castle);
    pieceCastle->setPosition(king);
    pieceKing->setMoveBefore();
    pieceCastle->setMoveBefore();
    setCooldowns(pieceKing->getColor());
}

void ChessBoard::makeLongCastling(std::string color){
    Position king, castle;
    if(color == "white"){
        king = {5,0};
        castle = {1,0};
    }else{
        king = {5,9};
        castle = {1,9};
    }
    ChessPiece* pieceKing = board[king].first;
    ChessPiece* pieceCastle = board[castle].first;
    board[king].first = pieceCastle;
    board[castle].first = pieceKing;
    pieceKing->setPosition(castle);
    pieceCastle->setPosition(king);
    pieceKing->setMoveBefore();
    pieceCastle->setMoveBefore();
    setCooldowns(pieceKing->getColor());
}


void ChessBoard::pawnPromotion(ChessPiece& piece){
    if(piece.getType() == "pawn"){
        Position pos = piece.getPosition();
        if((piece.getColor() == "white" && pos.y == 9) || (piece.getColor() == "black" && pos.y == 0)){
            std::string type;
            while(1){
                std::cout << "Which type would you like to promote your piece to? (rook/knight/bishop/queen)" << std::endl;
                std::cin >> type;
                if(type == "rook"  || type == "knight"  || type == "bishop"  || type == "queen"){
                    piece.setType(type);
                    break;
                }
                std::cout << "Choose valid type." << std::endl;
            }
        }
    }
}

void ChessBoard::removePiece(Position& pos){
    ChessPiece* piece = board[pos].first;
    board[pos].first = nullptr;
    delete piece;
}

int ChessBoard::getSize() const {return boardSize;}


ChessPiece* ChessBoard::getPiece(Position& pos) const{
    if(board.at(pos).first){
        return board.at(pos).first;
    }
    return nullptr;
}

Portal* ChessBoard::getPortal(Position& pos) const{
    Portal* portal = board.at(pos).second;
    if(portal){
        return portal;
    }
    return nullptr;
}

	