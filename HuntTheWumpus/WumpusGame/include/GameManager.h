#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Player.h"
#include "Cave.h"
#include "FileManager.h"
#include "Hazard.h"
#include "Wumpus.h"
#include "BottomlessPit.h"
#include "SuperBat.h"
#include "libraries.h"

//enumeration exactly as defined in the uml
enum GameState {
    RUNNING, WON, LOST, MENU
};

class GameManager {
private:
    Player player;
    Cave caveMap;
    std::vector<Hazard*> hazards;
    FileManager fileManager;
    GameState gameState;
    int turnCount;
    bool cheatMode;

    //helper function to print narrative text character by character
    void printSlow(const std::string& text, int delayMs);

public:
    //constructor
    GameManager();

    //core execution
    void run();

    //menu operations
    void showMainMenu();
    void startNewGame();
    void loadGame();
    void saveGame();

    //gameplay operations
    void gameLoop();
    void processTurn();
    void checkWinLose();
    void endGame();
    void toggleCheat();
};

#endif