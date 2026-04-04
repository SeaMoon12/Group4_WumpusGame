#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

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

class GameManager {
private:
    Player player;
    vector<Cave> caves;
    vector<Hazard*> hazards;
    FileManager fileManager;

    GameState gameState;
    int turnCount;
    bool cheatMode;

public:
    GameManager() {
        gameState = MENU;
        turnCount = 0;
        cheatMode = false;
        srand(time(0));
    }

    void run() {
        while (true) {
            showMainMenu();
        }
    }

    void showMainMenu() {
        cout << "\n=== HUNT THE WUMPUS ===\n";
        cout << "1. Start Game\n";
        cout << "2. Exit\n";

        int choice;
        cin >> choice;

        if (choice == 1) startNewGame();
        else exit(0);
    }

    void startNewGame() {
        string name;
        cout << "Enter name: ";
        cin >> name;

        player = Player();

        caves.clear();
        for (int i = 0; i < 20; i++) {
            caves.push_back(Cave());
        }

        hazards.clear();

        turnCount = 0;
        gameState = RUNNING;

        gameLoop();
    }

    void gameLoop() {
        while (gameState == RUNNING) {
            processTurn();
        }
        endGame();
    }

    void processTurn() {
        cout << "\nTurn: " << turnCount << endl;

        // player.displayStatus();  

        char input;
        cout << "Command (W/A/S/D, X): ";
        cin >> input;

        input = toupper(input);

        switch (input) {
            case 'W':
            case 'A':
            case 'S':
            case 'D':
                handleMove(input);
                break;

            case 'X':
                showInGameMenu();
                return;

            default:
                cout << "Invalid command\n";
                return;
        }

        // player.consumeLanternOil(); 

        checkWinLose();
        turnCount++;
    }

    void handleMove(char direction) {
        // player.move(direction, caves); 
        cout << "Moved.\n";
    }

    void handleShoot(char direction) {
        cout << "Shooting not implemented yet.\n";
    }

    void checkNearbyWarnings() {}

    void checkHazards() {}

    void checkWinLose() {
       
    }

    void showInGameMenu() {
        cout << "\n1. Exit to Menu\n";
        int choice;
        cin >> choice;

        gameState = MENU;
    }

    void loadGame() {}
    void saveGame() {}

    void endGame() {
        if (gameState == WON) {
            cout << "You win!\n";
        } else {
            cout << "Game Over.\n";
        }
        gameState = MENU;
    }
};

#endif