#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <vector>
#include <fstream>
#include "Cave.h"    
#include "Player.h"
#include "Hazard.h"  

class FileManager {
private:
    std::string mapFile;
    std::string saveFile;
    std::string scoreFile;
    std::string howToPlayFile;
    std::string storyFile;

public:
    FileManager();

    std::vector<CaveProperties> loadMap();
    void saveGame(Player& player, std::vector<Hazard*>& hazards, int turns);
    std::string loadGame();
    void saveScore(const std::string& name, int score);
    std::string loadScores();
    std::string loadHowToPlay();
    std::string loadStory();
};

#endif