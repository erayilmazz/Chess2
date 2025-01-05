#include <fstream>
#include <iomanip>
#include <iostream>
#include <cctype>
#include <string>


#include "../third_party/nlohmann/json.hpp"
#include "../include/GameManager.hpp"
#include "../include/ChessBoard.hpp"
bool isValidCor(std::string cor);
Position convertToPosition(std::string cor);
//taşları çek onları yarat ve board'a ekle
int main(){
  ChessBoard board(10);
  GameManager gm(board);
  gm.startGame();
  while (true){
    Position piecePos;
    while(true){
      std::cout<< "Type coordinant of which piece you want to play" << std::endl;
      std::string cor;
      std:: cin >> cor;
      if (isValidCor(cor)){
        piecePos = convertToPosition(cor);
      }else{
        std::cout << "Invalid coordinant." << std::endl;
        continue;
      }
      if (!gm.isValidPiece(piecePos)){
        std::cout << "Invalid piece." << std:: endl;
      }else break;
    }
    Position nPos;
    while(true){
      std::cout << "Type coordinant of where do you want to go" << std::endl;
      std::string ncor;
      std:: cin >> ncor;
      if(isValidCor(ncor)){
        nPos = convertToPosition(ncor);
      }else{
        std::cout << "Invalid coordinant." << std::endl;
        continue;
      }
      if(!gm.isValidMove(piecePos, nPos)){
        std::cout << "Invalid move." << std::endl;
        continue;
      }else break;
    }
    std::cout << "Looplar bitti." << std::endl;
    gm.makeMove(piecePos, nPos);
    board.printBoard();
    if(gm.isGameOver()) break;
    gm.switchPlayer();
  }   
}

bool isValidCor(std::string cor){
  //burda şey gibi düşün a1 c0 d4 gibi bir cor değeri gelecek o değer geçerli mi diye bakacak
  if(cor.length() != 2) return false;
  if(!std::isalpha(cor[0]) || cor[0] < 'a' || cor[0] > 'j') return false;
  if(!std::isdigit(cor[1]) || cor[1] < '0' || cor[1] > '9') return false;
  return true;
}

Position convertToPosition(std::string cor){
  std::vector<char> letters = {'a','b','c','d','e','f','g','h','i','j'};
  size_t i = 0;
  for(i = 0; cor[0] != letters[i]; ++i);
  int x = i;
  int y = cor[1] - '0';
  Position pos = {x, y};
  return pos;
}
/*
// Helper function to print positions
void printPosition(const Position& pos) {
  std::cout << "(" << pos.x << "," << pos.y << ")";
}

// Helper function to print movement rules
void printMovementRules(const MovementRules& rules) {
  std::cout << "Movement Rules:\n";
  std::cout << "  Forward: " << rules.forward << "\n";
  std::cout << "  Sideways: " << rules.sideways << "\n";
  std::cout << "  Diagonal: " << rules.diagonal << "\n";
  std::cout << "  L-Shape: " << (rules.l_shape ? "true" : "false") << "\n";
  std::cout << "  First Move Forward: " << rules.first_move_forward << "\n";
  std::cout << "  Diagonal Capture: " << rules.diagonal_capture << "\n";
}

// Helper function to print piece configurations
void printPieceConfig(const PieceConfig& piece) {
  std::cout << "\nPiece Type: " << piece.type << "\n";

  std::cout << "White Positions: ";
  for (const auto& pos : piece.white_positions) {
    printPosition(pos);
    std::cout << " ";
  }
  std::cout << "\n";

  std::cout << "Black Positions: ";
  for (const auto& pos : piece.black_positions) {
    printPosition(pos);
    std::cout << " ";
  }
  std::cout << "\n";

  printMovementRules(piece.movement);
  std::cout << "Count: " << piece.count << "\n";
}

// Helper function to print portal configurations
void printPortalConfig(const PortalConfig& portal) {
  std::cout << "\nPortal ID: " << portal.id << "\n";
  std::cout << "Entry: ";
  printPosition(portal.positions.entry);
  std::cout << "\nExit: ";
  printPosition(portal.positions.exit);

  std::cout << "\nProperties:\n";
  std::cout << "  Preserve Direction: "
            << (portal.properties.preserve_direction ? "true" : "false")
            << "\n";
  std::cout << "  Allowed Colors: ";
  for (const auto& color : portal.properties.allowed_colors) {
    std::cout << color << " ";
  }
  std::cout << "\n  Cooldown: " << portal.properties.cooldown << "\n";
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <config_file>\n";
    return 1;
  }

  // Check if file exists
  std::ifstream file(argv[1]);
  if (!file.good()) {
    std::cerr << "Error: Could not open config file: " << argv[1] << "\n";
    return 1;
  }
  file.close();

  ConfigReader reader(argv[1]);
  if (!reader.readConfig()) {
    std::cerr << "Failed to read configuration file\n";
    return 1;
  }

  // Print game settings
  auto settings = reader.getGameSettings();
  std::cout << "\n=== Game Settings ===\n";
  std::cout << "Name: " << settings.name << "\n";
  std::cout << "Board Size: " << settings.board_size << "\n";
  std::cout << "Turn Limit: " << settings.turn_limit << "\n";

  // Print piece configurations
  std::cout << "\n=== Piece Configurations ===\n";
  for (const auto& piece : reader.getPieceConfigs()) {
    printPieceConfig(piece);
  }

  // Print portal configurations
  std::cout << "\n=== Portal Configurations ===\n";
  for (const auto& portal : reader.getPortalConfigs()) {
    printPortalConfig(portal);
  }

  return 0;
}
*/