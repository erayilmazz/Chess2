#pragma once
#include <string>
#include "ConfigReader.hpp"


class ChessPiece{
public:
    ChessPiece(const std::string& type, const Position& position, const std::string& color, const MovementRules& rules);

    std::string getType() const;
    Position getPosition() const;
    std::string getColor() const;
    MovementRules getRules() const;
    int getCooldown() const;
    std::string getEmoji() const;

    void setPosition(const Position& newPosition);
    void setType(const std::string& newType);
    void setCooldown(const int& newCooldown);

private:
    std::string type;
    Position position;
    std::string color;
    MovementRules rules;
    int cooldown;
};