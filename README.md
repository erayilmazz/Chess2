# Chess2 ♟️

Chess2 is a terminal-based chess variant developed as a school project.  
It extends the rules of traditional chess with a **10x10 board**, **portal mechanics**, and **modified piece movements**.  
The game validates moves, manages game flow, and allows two players to play directly in the terminal.

---

## 📖 Project Description
- **Board**: 10x10 chessboard instead of the standard 8x8.  
- **Pawns**: Placed on the sides of the board as well. They cannot move backwards but can move sideways.  
- **Knights**: Two types of moves:  
  - *Small L*: 2 squares in one direction + 1 perpendicular (standard chess move).  
  - *Big L*: 4 squares in one direction + 2 perpendicular.  
- **Portals**:  
  - Double orange and double blue portals exist on the board.  
  - Pieces can enter and exit portals, enabling two-way teleportation.  
- **Game Flow**:  
  - Turn-based, two-player gameplay.  
  - Move validation ensures only legal moves are executed.  
  - The game checks for king safety and game-over conditions.  

---

## 🛠️ Classes Overview
- **ChessBoard**: Manages board state, piece placement, portals, moves, and rendering.  
- **ChessPiece**: Represents pieces with type, color, position, move rules, and cooldown.  
- **MoveValidator**: Calculates valid moves, checks legality, and detects enemy pieces or portals.  
- **GameManager**: Controls game loop, turn switching, move execution, and win conditions.  
- **Portal**: Represents portal entry/exit positions and properties.  

---

## 🚀 Building and Running

### Prerequisites
- [nlohmann/json](https://github.com/nlohmann/json) library  
- GNU Make build system  
- C++17 compatible compiler  

### Build Commands
- **Install dependencies** → `make deps`  
- **Build project** → `make`  
- **Run with configuration (uses chess_pieces.json)** → `make run`  
- **Clean build files** → `make clean`  

---

## 🎮 How to Play
- Run the game in terminal with `make run`.  
- The board will be displayed in a **10x10 grid**.  
- Players take turns entering moves.  
- Moves are validated according to Chess2 rules (pawns sideways, knight big/small L, portals, etc.).  
- The game ends when a king is captured or no valid moves remain.  

---

## 📸 Special Rules in Action

**Extra Pawns on the Sides**  
<img width="587" height="330" alt="image" src="https://github.com/user-attachments/assets/24204702-aacb-44d0-8a4c-b2fdd81cbdd8" />

**Knight’s Extended Big L Move**  
<img width="577" height="331" alt="image" src="https://github.com/user-attachments/assets/83e844c0-a18b-4564-8c14-ce51906f894f" />


---
