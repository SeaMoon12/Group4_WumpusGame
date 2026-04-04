/********************************************************************
FITS1201 – Object-Oriented Programming
UNJI GAMES Assignment – Version 1
Academic Integrity Declaration
Student Name: John Matthew Myers Hamid
Student ID: 251103110113
Submission Date: April 4th, 2026
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
Student Signature: John Matthew Myers Hamid
********************************************************************/

#include "FileManager.h"
#include <iostream>
#include <fstream>
#include <sstream>

#define RESETCOLOR  "\033[0m"
#define RED         "\033[31m"
#define YELLOW      "\033[33m"
#define LIGHT_BLUE  "\033[36m"

using namespace std;

// Initialize all paths pointing strictly to the assets folder
FileManager::FileManager() {
    mapFile = "assets/map.txt";
    saveFile = "assets/save.txt";
    scoreFile = "assets/scores.txt";
    howToPlayFile = "assets/howtoplay.txt";
    storyFile = "assets/story.txt";
}

// Read the static map file and return properties for Gerrard's Cave class
vector<CaveProperties> FileManager::loadMap() {
    vector<CaveProperties> caves;
    ifstream file(mapFile);

    if (!file.is_open()) {
        cout << RED << "Error: Could not open map file." << RESETCOLOR << endl;
        return caves;
    }

    string line;
    getline(file, line);
    int totalCaves = stoi(line);

    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string token;
        CaveProperties cave;

        getline(ss, token, ',');
        cave.cavePosition = stoi(token);

        cave.connectedCaves.resize(4, -1);
        for (int i = 0; i < 4; i++) {
            getline(ss, token, ',');
            cave.connectedCaves[i] = stoi(token);
        }

        cave.caveVisited = false;
        cave.caveHazards = CaveHazards::NONE;

        caves.push_back(cave);
    }

    file.close();
    return caves;
}

// Write the dynamic game state (Player, Turns, Hazards) to the save file
void FileManager::saveGame(Player& player, vector<Hazard*>& hazards, int turns) {
    ofstream file(saveFile);

    if (!file.is_open()) {
        cout << RED << "Error: Could not open save file." << RESETCOLOR << endl;
        return;
    }

    file << player.getSaveData() << "\n";
    file << turns << "\n";

    file << hazards.size() << "\n";
    for (int i = 0; i < hazards.size(); i++) {
        file << hazards[i]->getHazardName() << "," << hazards[i]->getRoomID() << "\n";
    }

    file.close();
    cout << LIGHT_BLUE << "Game saved successfully." << RESETCOLOR << endl;
}

// Return the entire save file content as a single string for GameManager to parse
string FileManager::loadGame() {
    ifstream file(saveFile);
    string result = "";

    if (!file.is_open()) {
        cout << RED << "Error: No save file found." << RESETCOLOR << endl;
        return result;
    }

    string line;
    while (getline(file, line)) {
        result += line + "\n";
    }

    file.close();
    return result;
}

// Append a new winning score securely
void FileManager::saveScore(const string& name, int score) {
    ofstream file(scoreFile, ios::app);

    if (!file.is_open()) {
        cout << RED << "Error: Could not open scores file." << RESETCOLOR << endl;
        return;
    }

    file << name << "," << score << "\n";
    file.close();
}

// Return formatted list of all past scores
string FileManager::loadScores() {
    ifstream file(scoreFile);
    string result = "";

    if (!file.is_open()) {
        cout << YELLOW << "No scores recorded yet." << RESETCOLOR << endl;
        return result;
    }

    string line;
    int rank = 1;

    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string name, scoreStr;

        getline(ss, name, ',');
        getline(ss, scoreStr, ',');

        result += to_string(rank) + ". " + name + " - " + scoreStr + "\n";
        rank++;
    }

    file.close();
    return result;
}

// Return tutorial text
string FileManager::loadHowToPlay() {
    ifstream file(howToPlayFile);
    string result = "";

    if (!file.is_open()) {
        cout << RED << "Error: Could not open How to Play file." << RESETCOLOR << endl;
        return result;
    }

    string line;
    while (getline(file, line)) {
        result += line + "\n";
    }

    file.close();
    return result;
}

// Return story text for dynamic printing
string FileManager::loadStory() {
    ifstream file(storyFile);
    string result = "";

    if (!file.is_open()) {
        cout << RED << "Error: Could not open story file." << RESETCOLOR << endl;
        return result;
    }

    string line;
    while (getline(file, line)) {
        result += line + "\n";
    }

    file.close();
    return result;
}