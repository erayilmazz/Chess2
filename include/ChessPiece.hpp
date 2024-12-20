#include <string>
#include "ConfigReader.hpp"


struct Position{
    int x;
    int y;
};

class ChessPiece{
public:
    ChessPiece(const std::string& type, const Position& position, const std::string& color, const MovementRules& rules);

    std::string getType() const;
    Position getPosition() const;
    std::string getColor() const;
    MovementRules getRules() const;

    void setPosition(const Position& newPosition);
    void setType(const std::string& newType);

private:
    std::string type;
    Position position;
    std::string color;
    MovementRules rules;
};