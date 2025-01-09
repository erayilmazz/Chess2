#include "../include/ChessPiece.hpp"
#include <iomanip>
ChessPiece::ChessPiece(const std::string& type, const Position& position, const std::string& color, const MovementRules& rules)
    :type(type), position(position), color(color), rules(rules), cooldown(0) {}

std::string ChessPiece::getType() const {return type;}
Position ChessPiece::getPosition() const {return position;}
std::string ChessPiece::getColor() const {return color;}
MovementRules ChessPiece::getRules() const {return rules;}
int ChessPiece::getCooldown() const {return cooldown;}
std::string ChessPiece::getEmoji() const{
    std::string black_color_code = "\033[1;30m";
    std::string reset_code = "\033[0m";
    if(getType() == "pawn"){
        if(getColor() == "white") return "♙";
        else return black_color_code + "♟" + reset_code;
    } 
    if(getType() == "rook"){
        if(getColor() == "white") return "♖";
        else return black_color_code + "♜" + reset_code;
    } 
    if(getType() == "knight"){
        if(getColor() == "white") return "♘";
        else return black_color_code +"♞" + reset_code;
    } 
    if(getType() == "bishop"){
        if(getColor() == "white") return "♗";
        else return black_color_code + "♝" + reset_code;
    }
    if(getType() == "queen"){
        if(getColor() == "white") return "♕";
        else return black_color_code + "♛" + reset_code;
    } 
    if(getType() == "king"){
        if(getColor() == "white") return "♔";
        else return black_color_code +  "♚" + reset_code;
    } 
    return "";
}

void ChessPiece::setPosition(const Position& newPosition) {position = newPosition;}
void ChessPiece::setType(const std::string& newType) {type = newType;}
void ChessPiece::setCooldown(const int& newCooldown) {cooldown = newCooldown;}
