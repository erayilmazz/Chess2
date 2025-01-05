#include "../include/Portal.hpp"

Portal::Portal(const std::string id, const Position& entry, const Position& exit, const PortalProperties& props)
    : id(id), entry(entry), exit(exit), props(props)  {}


Position Portal::getEntry() const{return entry;}
Position Portal::getExit() const {return exit;}
std::string Portal::getId() const {return id;}

std::string Portal::getPortal() const{
    std::string reset_code = "\033[0m";
    std::string orange_color_code = "\033[38;2;255;165;0m";
    std::string blue_color_code = "\033[38;2;0;0;255m";
    if(getId() == "orange_1" || getId() == "orange_2"){
        return orange_color_code + "0" + reset_code;
    }
    else{
        return blue_color_code + "0" + reset_code;
    }
}



