#ifndef PLAYER_H
#define PLAYER_H

#include "libraries.h"
#include <iostream>
#include <vector>
#include <string>

// not using namespace std in the header file to avoid potential naming conflicts in larger projects.

class Player
{
    // commit first
private:
    // player attributes
    std::string playerName;
    int currentCaveID;
    int arrows;
    int magicArrows;
    int lanternOil;
    bool isAlive;
    int score;
    int cavesExplored;
    std::vector<std::string> inventory;

    // constants for the starting attributes of the player
    static const int STARTING_ARROWS = 5;
    static const int STARTING_LANTERN_OIL = 100;

public:
    // constructor
    Player(const std::string& name);

    // player methods
    void setCurrentCaveID(int caveID);
    int getCurrentCaveID();
    void addVisitedCave(int caveID);
    int getCavesExplored();
    void consumeLanternOil();
    int getLanternOil();
    void useArrow();
    void useMagicArrow();
    int getArrows();
    int getMagicArrows();
    bool isOutofOil();
    bool isOutofArrows();
    void addItem(const std::string& item);
    void removeItem(const std::string& item);
    bool hasItem(const std::string& item);
    std::vector<std::string> getInventory();
    std::string getPlayerName();
    void setAlive(bool status);
    bool getIsAlive();
    void displayStatus();
    void calculateScore(int turns, int diff);
    int getScore();
    std::string getSaveData();
    void loadSaveData(const std::string& data);
};

#endif