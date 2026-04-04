#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <vector>
#include <fstream>
#include "Cave.h"    //requires caveproperties struct
#include "Player.h"  //requires  player class
#include "Hazard.h"  //requires hazard class

class FileManager {
private:
    std::string saveFile;
    std::string scoreFile;
    std::string howToPlayFile;
    std::string storyFile;

public:
    FileManager();

    //signature includes gerrard's dynamic cave map
    void saveGame(Player& player, std::vector<Hazard*>& hazards, int turns, std::vector<CaveProperties>& cavesData);

    std::string loadGame();
    void saveScore(const std::string& name, int score);
    std::string loadScores();
    std::string loadHowToPlay();
    std::string loadStory();
};

#endif