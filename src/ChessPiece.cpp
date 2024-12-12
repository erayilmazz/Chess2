#include "../include/ChessPiece.hpp"

ChessPiece::ChessPiece(const std::string& type, const Position& position, const std::string& color)
    :type(type), position(position), color(color) {}

std::string ChessPiece::getType() const {return type;}
Position ChessPiece::getPosition() const {return position;}
std::string ChessPiece::getColor() const {return color;}

void ChessPiece::setPosition(const Position& newPosition) {position = newPosition;}
void ChessPiece::setType(const std::string& newType) {type = newType;}
