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

//constructor: initialize file paths securely to assets folder
FileManager::FileManager() {
    saveFile = "save.txt";
    scoreFile = "scores.txt";
    howToPlayFile = "howToPlay.txt";
    storyFile = "story.txt";
}

//savegame: write complete game state to save file
void FileManager::saveGame(Player& player, vector<Hazard*>& hazards, int turns, vector<CaveProperties>& cavesData) {
    ofstream file(saveFile);

    if (!file.is_open()) {
        cout << RED << "Error: Could not open save file." << RESETCOLOR << endl;
        return;
    }

    //save player state
    file << player.getSaveData() << "\n";

    //save turns taken
    file << turns << "\n";

    //save hazards
    file << hazards.size() << "\n";
    for (int i = 0; i < hazards.size(); i++) {
        file << hazards[i]->getHazardName() << "," << hazards[i]->getRoomID() << "\n";
    }

    //save gerrard's dynamically generated cave map
    file << cavesData.size() << "\n";
    for (int i = 0; i < cavesData.size(); i++) {
        file << cavesData[i].cavePosition << ","
            << cavesData[i].connectedCaves[0] << "," //north
            << cavesData[i].connectedCaves[1] << "," //east
            << cavesData[i].connectedCaves[2] << "," //south
            << cavesData[i].connectedCaves[3] << "," //west
            << cavesData[i].caveVisited << "\n";
    }

    file.close();
    cout << LIGHT_BLUE << "Game saved successfully." << RESETCOLOR << endl;
}

//loadgame: read save file and return as string
string FileManager::loadGame() {
    ifstream file(saveFile);
    string result = "";

    if (!file.is_open()) {
        cout << RED << "Error: No save file found." << RESETCOLOR << endl;
        return result;
    }

    //read entire save file into string
    string line;
    while (getline(file, line)) {
        result += line + "\n";
    }

    file.close();
    return result;
}

//savescore: append player's name and score
void FileManager::saveScore(const string& name, int score) {
    ofstream file(scoreFile, ios::app); //ios::app ensures we don't overwrite old scores

    if (!file.is_open()) {
        cout << RED << "Error: Could not open scores file." << RESETCOLOR << endl;
        return;
    }

    file << name << "," << score << "\n";
    file.close();
}

//loadscores: read and format all saved scores
string FileManager::loadScores() {
    ifstream file(scoreFile);
    string result = "";

    if (!file.is_open()) {
        cout << YELLOW << "No scores recorded yet." << RESETCOLOR << endl;
        return result;
    }

    string line;
    int rank = 1;

    //parse and format each score with rank
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

//loadhowtoplay: read how to play text file
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

//loadstory: read story text file for dynamic printing
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