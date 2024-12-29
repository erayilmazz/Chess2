#include "../include/ChessPiece.hpp"

ChessPiece::ChessPiece(const std::string& type, const Position& position, const std::string& color, const MovementRules& rules)
    :type(type), position(position), color(color), rules(rules) {}

std::string ChessPiece::getType() const {return type;}
Position ChessPiece::getPosition() const {return position;}
std::string ChessPiece::getColor() const {return color;}
MovementRules ChessPiece::getRules() const {return rules;}
int ChessPiece::getCooldown() const {return cooldown;}

void ChessPiece::setPosition(const Position& newPosition) {position = newPosition;}
void ChessPiece::setType(const std::string& newType) {type = newType;}
void ChessPiece::setCooldown(const int& newCooldown) {cooldown = newCooldown;}
