#include "MoveValidator.hpp"

MoveValidator::MoveValidator(const Board& board)
    :board(board){}

bool MoveValidator::isValidMove(const ChessPiece& piece, int beforex, int beforey, int afterx, int aftery) const{
    if(piece.cooldown || afterx >= board.getSize() || aftery >= board.getSize() || afterx < 0 || aftery < 0) return false;
    

}