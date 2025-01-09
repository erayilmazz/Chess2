#pragma once
#include "ConfigReader.hpp"

class Portal{
public:
    Portal(const std::string id, const Position& entry, const Position& exit, const PortalProperties& props);
    Position getEntry() const;
    Position getExit() const;
    std::string getId() const;
    std::string getPortal() const;

private:
    std::string id;
    Position entry;
    Position exit;
    PortalProperties props;
};
