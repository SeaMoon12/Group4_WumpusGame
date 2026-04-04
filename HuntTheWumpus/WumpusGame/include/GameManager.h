#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <libraries.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include "Player.h"
#include "Cave.h"
#include "Hazard.h"
#include "FileManager.h"
using namespace std;

enum GameState {
    RUNNING,
    WON,
    LOST,
    MENU
};

class GameManager
{
        // hi
    private:
        Player player;
        Cave cave;
        vector<Hazard*> hazards;
        FileManager fileManager;

        GameState gameState;
        int turnCount;
        bool cheatMode;

    public:
        GameManager();

        void run();

        void showMainMenu();

        void startNewGame();

        void gameLoop();

        void processTurn();

        void handleMove(char direction);

        void handleShoot(char direction);

        void checkNearbyWarnings();

        void checkHazards();

        void checkWinLose();

        void showInGameMenu();

        void loadGame();
        void saveGame();

        void endGame();

};

#endif;