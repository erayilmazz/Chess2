#include "../include/ConfigReader.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

ConfigReader::ConfigReader(const std::string& config_path)
    : config_path_(config_path) {}

bool ConfigReader::readConfig() {
  try {
    // Open and read the JSON file
    std::ifstream config_file(config_path_);
    if (!config_file.is_open()) {
      std::cerr << "Failed to open config file: " << config_path_ << std::endl;
      return false;
    }

    // Parse JSON content
    nlohmann::json json_data;
    config_file >> json_data;

    // Parse game settings and piece configurations
    parseGameSettings(json_data["game_settings"]);
    parsePieceConfigs(json_data["pieces"]);

    // Parse portal configurations if they exist
    if (json_data.contains("portals")) {
      parsePortalConfigs(json_data["portals"]);
    }

    return true;
  } catch (const std::exception& e) {
    std::cerr << "Error parsing config file: " << e.what() << std::endl;
    return false;
  }
}

void ConfigReader::parseGameSettings(const nlohmann::json& json) {
  game_settings_.name = json["name"].get<std::string>();
  game_settings_.board_size = json["board_size"].get<int>();
  game_settings_.turn_limit = json["turn_limit"].get<int>();
}

void ConfigReader::parsePieceConfigs(const nlohmann::json& json) {
    piece_configs_.clear();

    for (const auto& piece : json) {
        PieceConfig config;
        config.type = piece.value("type", "");

        if (piece.contains("white_positions")) {
            for (const auto& pos : piece["white_positions"]) {
                Position position;
                position.x = pos.value("x", 0);
                position.y = pos.value("y", 0);
                config.white_positions.push_back(position);
            }
        }

        if (piece.contains("black_positions")) {
            for (const auto& pos : piece["black_positions"]) {
                Position position;
                position.x = pos.value("x", 0);
                position.y = pos.value("y", 0);
                config.black_positions.push_back(position);
            }
        }

        if (piece.contains("movement")) {
            const auto& movement = piece["movement"];
            config.movement.forward = movement.value("forward", 0);
            config.movement.backward = movement.value("backward", 0);
            config.movement.sideways = movement.value("sideways", 0);
            config.movement.diagonal = movement.value("diagonal", 0);
            config.movement.l_shape = movement.value("l_shape", false);
            config.movement.first_move_forward = movement.value("first_move_forward", 0);
            config.movement.diagonal_capture = movement.value("diagonal_capture", 0);
        }

        config.count = piece.value("count", 0);
        piece_configs_.push_back(config);
    }
}

void ConfigReader::parsePortalConfigs(const nlohmann::json& json) {
    portal_configs_.clear();

    for (const auto& portal : json) {
        PortalConfig config;
        config.id = portal.value("id", "");

        if (portal.contains("positions")) {
            config.positions.entry.x = portal["positions"]["entry"].value("x", 0);
            config.positions.entry.y = portal["positions"]["entry"].value("y", 0);
            config.positions.exit.x = portal["positions"]["exit"].value("x", 0);
            config.positions.exit.y = portal["positions"]["exit"].value("y", 0);
        }

        if (portal.contains("properties")) {
            const auto& props = portal["properties"];
            config.properties.preserve_direction = props.value("preserve_direction", true);
            config.properties.allowed_colors = props.value("allowed_colors", std::vector<std::string>());
            config.properties.cooldown = props.value("cooldown", 0);
        }

        portal_configs_.push_back(config);
    }
}

GameSettings ConfigReader::getGameSettings() const { return game_settings_; }

std::vector<PieceConfig> ConfigReader::getPieceConfigs() const { return piece_configs_; }

std::vector<PortalConfig> ConfigReader::getPortalConfigs() const { return portal_configs_; }
