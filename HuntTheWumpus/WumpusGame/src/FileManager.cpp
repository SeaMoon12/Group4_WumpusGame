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

#include "FileManager.h"
#include <fstream>
#include <iostream>

FileManager::FileManager() {
	mapFile = "map.txt";
	saveFile = "saveGame.txt";
	scoreFile = "scores.txt";
	howToPlayFile = "howToPlay.txt";
	storyFile = "story.txt"
}

string FileManager::loadHowToPlay() {
    ifstream file(howToPlayFile);
    string text, line;

    if (!file) {
        return "ERROR: FILE CAN'T BE FOUND";
    }

    while (getline(file, line)) {
        text += line + "\n";
    }

    file.close();
    return text;
}

string FileManager::loadStory() {
    ifstream file(storyFile);
    string text, line;

    if (!file) {
        return "ERROR: FILE CAN'T BE FOUND";
    }

    while (getline(file, line)) {
        text += line + "\n";
    }

    file.close();
    return text;
}