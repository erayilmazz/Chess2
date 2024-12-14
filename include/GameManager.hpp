
class GameManager{
public:
    void startGame();
    bool isValidPiece(); //ekranda seçilen piece input olsun
    bool isValidMove();
    void makeMove();
    bool isGameOver();
private:
    bool isWhiteTurn;
    void switchPlayer();
}
