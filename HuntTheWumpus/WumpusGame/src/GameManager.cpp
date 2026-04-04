/********************************************************************
FITS1201 – Object-Oriented Programming
UNJI GAMES Assignment – Version 1
Academic Integrity Declaration
Student Name: ______________________________
Student ID: ______________________________
Submission Date: ___________________________
I declare that:
1. This assignment is entirely my own original work.
2. I have not copied code from other students, websites, AI tools,
 or any external sources without proper acknowledgment.
3. I have not used AI tools (such as ChatGPT, GitHub Copilot, or similar)
 to generate any part of this assignment solution.
4. I have only used AI tools, if any, for learning purposes such as
 understanding concepts, syntax, or debugging, and not for generating
code.
5. Any concepts, syntax, or techniques not taught in this course have been
 properly acknowledged with citations in the comments of my code.
6. I understand that failure to comply with these requirements may result
 in academic misconduct proceedings and penalties, including a mark of
 zero for this assignment.
Student Signature: <mention your full name here>
********************************************************************/

#include "GameManager.h"



GameManager::GameManager() : player("Hunter"), cave(Cave::GameDifficulty::ROOKIE) { 
    gameState = MENU;
    turnCount = 0;
    cheatMode = false;
    srand(time(0));
}

void GameManager::run() {
    string playerName;
    cout << "Enter your name: ";
    cin >> playerName;
    Player player(playerName);
    showMainMenu();
}

void GameManager::showMainMenu() {
    system("cls");
    cout << "\nWelcome " << player.getPlayerName() << ".";
    cout << "=== HUNT THE WUMPUS ===\n";
    cout << "1. Start Game\n";
	cout << "2. Load Game\n";
	cout << "3. How to Play\n";
    cout << "4. Exit\n";

    int choice;
    cin >> choice;
    while (gameState == MENU) {
        if (choice == 1) {
            startNewGame();
        }
        else if (choice == 2) {
            //placeholder
        }
        else if (choice == 3) {
            fileManager.loadHowToPlay();
        }
        else if (choice == 4) {
            gameState = LOST;
        }
    }
    system("cls");
    cout << "\nggs";
}

void GameManager::startNewGame() {
    system("cls");
    int inputRand = 0;
    int inputDiff = 0;
    cout << "RANDOM MAP?\n";
    cout << "1. Yes\n2. No\n";
    cin >> inputRand;
    cout << "DIFFICULTY SELECT\n";
    cout << "1. Rookie\n2. Hunter\n3. Master Hunter\n";
    cin >> inputDiff;
    if (inputRand == 1) {
        if (inputDiff == 1) {
            Cave cave(Cave::GameDifficulty::ROOKIE);
        }
        else if (inputDiff == 2) {
            Cave cave(Cave::GameDifficulty::HUNTER);
        }
        else if (inputDiff == 3) {
            Cave cave(Cave::GameDifficulty::MASTER_HUNTER);
        }
    }
    else if (inputRand == 2) {

    }

    turnCount = 0;
    gameState = RUNNING;

    gameLoop();
}

void GameManager::gameLoop() {
    while (gameState == RUNNING) {
        processTurn();
    }
    endGame();
}

void GameManager::processTurn() {
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

void GameManager::handleMove(char direction) {
    // player.move(direction, caves); 
    cout << "Moved.\n";
}

void GameManager::handleShoot(char direction) {
    cout << "Shooting not implemented yet.\n";
}

void GameManager::checkNearbyWarnings() {}

void GameManager::checkHazards() {}

void GameManager::checkWinLose() {

}

void GameManager::showInGameMenu() {
    cout << "\n1. Exit to Menu\n";
    int choice;
    cin >> choice;

    gameState = MENU;
}

void GameManager::loadGame() {}
void GameManager::saveGame() {}

void GameManager::endGame() {
    if (gameState == WON) {
        cout << "You win!\n";
    }
    else {
        cout << "Game Over.\n";
    }
    gameState = MENU;
}