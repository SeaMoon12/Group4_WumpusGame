#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include "libraries.h"
#include "Location.h"
#include "Player.h"
#include "Hazard.h"

class FileManager{
private:
    string mapFile;
    string saveFile;
    string scoreFile;
    string howToPlayFile;

public:
    FileManager();

    vector<Location> loadMap();

    string loadHowToPlay();

    void saveGame(Player& player, vector<Hazard>& hazards, int turns);

    SaveData loadGame();

    void saveScore(string name, int score);

    string loadScores();
};

#endif