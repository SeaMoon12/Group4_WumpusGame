#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include "libraries.h"
#include "Cave.h"
#include "Player.h"
#include "Hazard.h"

class FileManager{
private:
    string mapFile;
    string saveFile;
    string scoreFile;
    string howToPlayFile;
    string storyFile;

public:
    FileManager();

    vector<CaveProperties> loadMap();

    string loadHowToPlay();

    void saveGame(Player& player, vector<Hazard>& hazards, int turns);

    string loadGame();

    void saveScore(string name, int score);

    string loadScores();

    string loadStory();
};

#endif