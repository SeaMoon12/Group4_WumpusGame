#include "GameManager.h"

#define RESETCOLOR  "\033[0m"
#define RED         "\033[31m"
#define GREEN       "\033[32m"
#define YELLOW      "\033[33m"
#define LIGHT_BLUE  "\033[36m"

using namespace std;

//constructor using initializer list to provide dummy values since player and cave lack default constructors
GameManager::GameManager() : player("Hunter"), caveMap(Cave::ROOKIE) {
    turnCount = 0;
    cheatMode = false;
    gameState = MENU;
}

//prints text slowly for dramatic effect using std::flush
void GameManager::printSlow(const string& text, int delayMs) {
    for (char letter : text) {
        cout << letter << flush;
        this_thread::sleep_for(chrono::milliseconds(delayMs));
    }
    cout << endl;
}

//main entry point that keeps the program running until the user quits
void GameManager::run() {
    while (true) {
        showMainMenu();
        if (gameState == MENU) {
            break; //exit the program completely if the menu signals a full stop
        }
    }
}

//displays the title screen and handles main menu input
void GameManager::showMainMenu() {
    gameState = MENU;
    bool check = true;
    while (check) {
        string choice;
        system("cls");

        cout << RED << "================================\n";
        cout << "        HUNT THE WUMPUS         \n";
        cout << "================================" << RESETCOLOR << "\n";
        cout << "1. New Game\n";
        cout << "2. Load Game\n";
        cout << "3. High Scores\n";
        cout << "4. How to Play\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == "1") {
            startNewGame();
        }
        else if (choice == "2") {
            loadGame();
        }
        else if (choice == "3") {
            cout << "\n" << YELLOW << "--- HIGH SCORES ---\n" << RESETCOLOR;
            cout << fileManager.loadScores() << "\n";
            system("pause");
        }
        else if (choice == "4") {
            cout << "\n" << LIGHT_BLUE << "--- HOW TO PLAY ---\n" << RESETCOLOR;
            cout << fileManager.loadHowToPlay() << "\n";
            system("pause");
        }
        else if (choice == "5") {
            cout << "Exiting game. Goodbye!\n";
            check = false;
            //leaving gamestate as MENU breaks the run() loop
        }
        else {
            cout << RED << "Invalid choice. Please try again.\n" << RESETCOLOR;
        }
    }
}

//handles the setup of a fresh game session
void GameManager::startNewGame() {
    string customName;
    int diffChoice;

    cout << "\nEnter your hunter's name: ";
    cin >> customName;

    //overwrites the dummy player with the real user name
    player = Player(customName);

    cout << "Select Difficulty (0: Rookie, 1: Hunter, 2: Master, 3: Rookie Random, 4: Hunter Random, 5: Master Random): ";
    cin >> diffChoice;

    if (diffChoice == 0 || diffChoice == 3) player.setMagicArrows(2);
    else if (diffChoice == 1 || diffChoice == 4) player.setMagicArrows(1);
    else player.setMagicArrows(0);

    //cast integer to gerrard's enum and overwrite the dummy map
    Cave::GameDifficulty selectedDiff = static_cast<Cave::GameDifficulty>(diffChoice);
    caveMap = Cave(selectedDiff);

    //generate the layout mathematically
    caveMap.generateCaveMap();

    for (Hazard* h : hazards) delete h;
    hazards.clear();
    vector<CaveProperties> cData = caveMap.getCavesData();
    int totalCaves = cData.size();

    // Place 1 Wumpus
    int wumpusRoom = rand() % (totalCaves - 1) + 1; // 1 to totalCaves-1, avoid 0
    Wumpus* w = new Wumpus(0.75f);
    w->setRoomID(wumpusRoom);
    hazards.push_back(w);
    cData[wumpusRoom].caveHazards = WUMPUS;

    // Place 2 Bottomless Pits
    for (int i = 0; i < 2; i++) {
        int pitRoom;
        do { pitRoom = rand() % (totalCaves - 1) + 1; } while (cData[pitRoom].caveHazards != NONE);
        BottomlessPit* p = new BottomlessPit();
        p->setRoomID(pitRoom);
        hazards.push_back(p);
        cData[pitRoom].caveHazards = PIT;
    }

    // Place 2 Super Bats
    for (int i = 0; i < 2; i++) {
        int batRoom;
        do { batRoom = rand() % (totalCaves - 1) + 1; } while (cData[batRoom].caveHazards != NONE);
        SuperBat* b = new SuperBat(0.0f);
        b->setRoomID(batRoom);
        hazards.push_back(b);
        cData[batRoom].caveHazards = BATS;
    }

    caveMap.updateCaveMap(cData);

    caveMap.setPlayerPosition(0);
    player.setCurrentCaveID(0);
    caveMap.updateCaveMap(caveMap.getCavesData());

    //print john's story text slowly
    cout << "\n";
    /*printSlow(fileManager.loadStory(), 30);*/
    cout << "\nPress ENTER to enter the caves...";
    cin.ignore();
    cin.get();

    turnCount = 0;
    gameState = RUNNING;
    gameLoop();
}

//loads a previously saved game state
void GameManager::loadGame() {
    string savedData = fileManager.loadGame();

    if (savedData.empty()) {
        cout << "No save data found, returning to menu.\n";
        return;
    }

    //here liquinha will write the string parsing logic to split savedData
    //and hand the pieces to player.loadSaveData() and caveMap.updateCaveMap()
    cout << LIGHT_BLUE << "Game successfully loaded!\n" << RESETCOLOR;

    gameState = RUNNING;
    gameLoop();
}

//packages the current game state and hands it to john's file manager
void GameManager::saveGame() {
    //grab the live map snapshot from gerrard's class
    vector<CaveProperties> currentMap = caveMap.getCavesData();

    //pass it all to john's class to write to the txt file
    fileManager.saveGame(player, hazards, turnCount, currentMap);
}

//toggles the cheat mode boolean and updates the map visibility
void GameManager::toggleCheat() {
    cheatMode = !cheatMode;
    if (cheatMode) {
        cout << YELLOW << "CHEAT MODE ENABLED: Map fully revealed.\n" << RESETCOLOR;
    }
    else {
        cout << YELLOW << "CHEAT MODE DISABLED: Map hidden.\n" << RESETCOLOR;
    }
}

//the main interactive loop where the player plays the game
void GameManager::gameLoop() {
    string command;

    while (gameState == RUNNING) {
        cout << "\n";
        caveMap.renderMap(cheatMode);
        player.displayStatus();

        int currentCave = caveMap.getPlayerPosition();
        for (int i = 0; i < 4; i++) {
            int adjCave = caveMap.getCavesData()[currentCave].connectedCaves[i];
            if (adjCave != -1) {
                for (Hazard* h : hazards) {
                    if (h->getRoomID() == adjCave) {
                        cout << YELLOW << h->getHazardWarning() << RESETCOLOR;
                    }
                }
            }
        }
        cout << "\nEnter command (MOVE, SHOOT, SAVE, CHEAT, QUIT): ";
        cin >> command;

        //convert command to uppercase for easy matching
        for (auto& c : command) c = toupper(c);

        if (command == "SAVE") {
            saveGame();
        }
        else if (command == "CHEAT") {
            toggleCheat();
            system("pause");
        }
        else if (command == "QUIT") {
            cout << "Returning to Main Menu...\n";
            gameState = MENU;
            break;
        }
        else if (command == "MOVE") {
            cout << "Which direction? W,A,S,D: ";
            char dir;
            cin >> dir;
            dir = toupper(dir);

            int dirIndex = -1;
            if (dir == 'W') dirIndex = 0;
            else if (dir == 'D') dirIndex = 1;
            else if (dir == 'S') dirIndex = 2;
            else if (dir == 'A') dirIndex = 3;

            if (dirIndex != -1) {
                int currentCave = caveMap.getPlayerPosition();
                int nextCave = caveMap.getCavesData()[currentCave].connectedCaves[dirIndex];

                if (nextCave != -1) {
                    caveMap.setPlayerPosition(nextCave);
                    player.setCurrentCaveID(nextCave);
                    caveMap.updateCaveMap(caveMap.getCavesData());

                    cout << GREEN << "You move to Cave " << nextCave << "." << RESETCOLOR << "\n";
                    for (Hazard* h : hazards) {
                        if (h->getRoomID() == nextCave) {
                            h->encounter();
                            if (h->getHazardName() == "Wumpus" || h->getHazardName() == "Bottomless Pit") {
                                player.setAlive(false);
                            }
                            else if (h->getHazardName() == "Super Bat") {
                                int randomCave;
                                do {
                                    randomCave = rand() % caveMap.getCavesData().size();
                                } while (randomCave == nextCave);
                                caveMap.setPlayerPosition(randomCave);
                                player.setCurrentCaveID(randomCave);
                                caveMap.updateCaveMap(caveMap.getCavesData());
                                cout << "You were dropped in Cave " << randomCave << "!\n";
                            }
                        }
                    }
                    processTurn();
                    checkWinLose();
                }
                else {
                    cout << RED << "You bump into a solid rock wall. There is no tunnel there." << RESETCOLOR << "\n";
                }
            }
            else {
                cout << RED << "Invalid direction!" << RESETCOLOR << "\n";
            }
        }
        else if (command == "SHOOT") {
            if (player.getArrows() <= 0 && player.getMagicArrows() <= 0) {
                cout << RED << "You have no arrows left!" << RESETCOLOR << "\n";
                this_thread::sleep_for(chrono::seconds(2)); // FIX: pause before clear
            }
            else {
                cout << "Which direction? W,A,S,D: ";
                char dir;
                cin >> dir;
                dir = toupper(dir);
                int dirIndex = -1;
                if (dir == 'W') dirIndex = 0;
                else if (dir == 'D') dirIndex = 1;
                else if (dir == 'S') dirIndex = 2;
                else if (dir == 'A') dirIndex = 3;

                if (dirIndex != -1) {
                    int targetCave = caveMap.getCavesData()[currentCave].connectedCaves[dirIndex];

                    if (targetCave != -1) {
                        if (player.getArrows() > 0) player.useArrow();
                        else player.useMagicArrow();

                        cout << GREEN << "You shoot an arrow into Cave " << targetCave << "!" << RESETCOLOR << "\n";
                        bool hitWumpus = false;

                        for (Hazard* h : hazards) {
                            if (h->getHazardName() == "Wumpus") {
                                if (h->getRoomID() == targetCave) {
                                    cout << GREEN << "You hear a triumphant roar! The Wumpus is dead!" << RESETCOLOR << "\n";
                                    hitWumpus = true;
                                    gameState = WON;
                                }
                                else {
                                    cout << YELLOW << "The arrow clatters uselessly in the dark." << RESETCOLOR << "\n";
                                    Wumpus* wumpus = static_cast<Wumpus*>(h);
                                    if (wumpus) {
                                        // Pick random adjacent cave for it to flee to
                                        int moveDir = rand() % 4;
                                        int fleeCave = caveMap.getCavesData()[wumpus->getRoomID()].connectedCaves[moveDir];
                                        if (fleeCave != -1) {
                                            int oldWumpusRoom = wumpus->getRoomID();
                                            wumpus->startle(fleeCave);
                                            if (wumpus->getRoomID() == fleeCave) {
                                                vector<CaveProperties> cData = caveMap.getCavesData();
                                                cData[oldWumpusRoom].caveHazards = NONE;
                                                cData[fleeCave].caveHazards = WUMPUS;
                                                caveMap.updateCaveMap(cData);
                                            }
                                        }
                                    }
                                }
                                break;
                            }
                        }

                        this_thread::sleep_for(chrono::seconds(2)); // FIX: pause before clear
                        if (!hitWumpus) {
                            processTurn();
                            checkWinLose();
                        }
                    }
                    else {
                        cout << RED << "You shoot at a solid rock wall. The arrow shatters." << RESETCOLOR << "\n";
                        this_thread::sleep_for(chrono::seconds(2)); // FIX: pause before clear
                    }
                }
                else {
                    cout << RED << "Invalid direction!" << RESETCOLOR << "\n";
                    this_thread::sleep_for(chrono::seconds(1)); // FIX: pause before clear
                }
            }
        }
        else {
            cout << RED << "Unknown command!\n" << RESETCOLOR;
            this_thread::sleep_for(chrono::seconds(1)); // FIX: pause before clear
        }
        system("pause");
    }

    if (gameState == WON || gameState == LOST) {
        endGame();
    }
}

//increments counters and processes background mechanics like oil drain
void GameManager::processTurn() {
    turnCount++;

    //simulate oil burning per your player class logic
    player.consumeLanternOil();

    //liquinha will loop through hazards here to see if the wumpus moves or wakes up
}

//evaluates if the game should end based on player status or wumpus status
void GameManager::checkWinLose() {
    if (!player.getIsAlive()) {
        cout << RED << "You have been slain in the dark...\n" << RESETCOLOR;
        gameState = LOST;
    }
    else if (player.isOutofOil()) {
        cout << RED << "Your lantern flickers and dies. You are lost to the darkness forever.\n" << RESETCOLOR;
        gameState = LOST;
    }

    //liquinha will add the condition to check if the wumpus hazard is dead here
    //if (wumpusIsDead) { gameState = WON; }
}

//handles the post-game summary and score calculation
void GameManager::endGame() {
    if (gameState == WON) {
        cout << GREEN << "\n================================\n";
        cout << "           VICTORY!             \n";
        cout << "================================\n" << RESETCOLOR;

        //use your score calculation logic
        int diffMultiplier = 1; //can be derived from caveMap difficulty
        player.calculateScore(turnCount, diffMultiplier);

        cout << "Final Score: " << player.getScore() << "\n";

        //save the winning score securely
        fileManager.saveScore(player.getPlayerName(), player.getScore());
    }
    else if (gameState == LOST) {
        cout << RED << "\n================================\n";
        cout << "          GAME OVER             \n";
        cout << "================================\n" << RESETCOLOR;
    }

    cout << "\nPress ENTER to return to the main menu.";
    cin.ignore();
    cin.get();

    //reset state to allow running the menu again
    gameState = MENU;
}