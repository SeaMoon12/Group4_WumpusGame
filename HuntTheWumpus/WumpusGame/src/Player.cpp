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

#include "Player.h"
#include <cstdlib>
#include <sstream>

#define RESETCOLOR "\033[0m"
#define RED "\033[31m"
#define YELLOW "\033[33m"
#define LIGHT_BLUE "\033[36m"
#define BRIGHT_YELLOW "\033[1;33m"

using namespace std;

//the constructor will initalise all player attributes to their starting values
Player::Player(const string& name) {
	playerName = name;
	currentCaveID = 0;
	arrows = STARTING_ARROWS;
	magicArrows = 0;
	lanternOil = STARTING_LANTERN_OIL;
	isAlive = true;
	score = 0;
	cavesExplored = 0;
	//inventory is a vector and initalises itself as empty automatically
}

void Player::setCurrentCaveID(int caveID) {
	currentCaveID = caveID;
}

int Player::getCurrentCaveID() {
	return currentCaveID;
}

void Player::addVisitedCave(int caveID) {
	cavesExplored++;
}

int Player::getCavesExplored() {
	return cavesExplored;
}

void Player::consumeLanternOil() {
	int reduction = rand() % 3 + 2; //reduces the lantern oil by a random value between 2 and 4
	lanternOil -= reduction;

	//to make sure that the lantern oil never goes negative
	if (lanternOil < 0) {
		lanternOil = 0;
	}
}

int Player::getLanternOil() {
	return lanternOil;
}

void Player::useArrow() {
	if (arrows > 0) {  //reduce the arrow by 1 when the player shoots
		arrows--;
	}
}

void Player::useMagicArrow() {
	if (magicArrows > 0) { //same thing for magic arrows
		magicArrows--;
	}
}

void Player::setMagicArrows(int amount) {
	magicArrows = amount;
}

int Player::getArrows() {
	return arrows;
}

int Player::getMagicArrows() {
	return magicArrows;
}

bool Player::isOutofOil() {
	return lanternOil <= 0; //returns true if lantern oil has reached 0
}

bool Player::isOutofArrows() {
	return arrows <= 0 && magicArrows <= 0; //returns true if both types of arrows have reached 0
}

void Player::addItem(const string& item) {
	inventory.push_back(item); //add a new item to the player's inventory
}

//find and remove a specific item from the player's inventory
void Player::removeItem(const string& item) {
	for (int i = 0; i < inventory.size(); i++) {
		if (inventory[i] == item) {
			inventory.erase(inventory.begin() + i);
			break;
		}
	}
}

//check whether a specific item exists in the player's inventory
bool Player::hasItem(const string& item) {
	for (int i = 0; i < inventory.size(); i++) {
		if (inventory[i] == item) {
			return true;
		}
	}
	return false;
}

vector<string> Player::getInventory() {
	return inventory;
}

string Player::getPlayerName() {
	return playerName;
}

void Player::setAlive(bool status) {
	isAlive = status;
}

bool Player::getIsAlive() {
	return isAlive;
}

//display the player's current status and inventory to the console
void Player::displayStatus() {
	cout << RED << "================================" << RESETCOLOR << endl;
	cout << LIGHT_BLUE << "        PLAYER STATUS           " << RESETCOLOR << endl;
	cout << RED << "================================" << RESETCOLOR << endl;
	cout << LIGHT_BLUE << " Cave           : " << currentCaveID << RESETCOLOR << endl;
	cout << YELLOW << " Lantern Oil    : " << lanternOil << RESETCOLOR << endl;
	cout << YELLOW << " Normal Arrows  : " << arrows << RESETCOLOR << endl;
	cout << BRIGHT_YELLOW << " Magic Arrows   : " << magicArrows << RESETCOLOR << endl;
	cout << endl;
	cout << RED << "================================" << RESETCOLOR << endl;
	cout << LIGHT_BLUE << "          INVENTORY             " << RESETCOLOR << endl;
	cout << RED << "================================" << RESETCOLOR << endl;

	if (inventory.empty()) {
		cout << YELLOW << " Inventory is empty" << RESETCOLOR << endl;
	}
	else {
		//range based for loop to display each item in the inventory
		//got the idea to use this from: https://www.geeksforgeeks.org/cpp/range-based-loop-c/
		for (string item : inventory) {
			cout << YELLOW << "- " << item << RESETCOLOR << endl;
		}
	}
	cout << RED << "================================" << RESETCOLOR << endl;
}

//calculate the player's score based on their performance in the game, also taking account of the number of turns taken and the difficulty level
void Player::calculateScore(int turns, int diff) {
	int arrowBonus = arrows * 10;
	int magicBonus = magicArrows * 15;
	int exploreBonus = cavesExplored * 5;
	int turnPenalty = turns * 2;
	int baseScore = arrowBonus + magicBonus + exploreBonus - turnPenalty;

	if (baseScore < 0) {
		baseScore = 0;
	}

	//applying a multiplier to the score based on the difficulty level
	//Rookie = x1.0, Hunter = x1.5, Master Hunter = x2.0
	double difficultyMultiplier;
	if (diff == 1) {
		difficultyMultiplier = 1.0; //Rookie
	}
	else if (diff == 2) {
		difficultyMultiplier = 1.5; //Hunter
	}
	else if (diff == 3) {
		difficultyMultiplier = 2.0; //Master Hunter
	}
	//static cast for converting the final score from double to integer.
	score = static_cast<int>(baseScore * difficultyMultiplier);
}

//return the player's final score
int Player::getScore() {
	return score;
}

//convert all player attributes into a single string so FileManager can save it into the save file
string Player::getSaveData() {
	stringstream ss;
	ss << playerName << ","
		<< currentCaveID << ","
		<< arrows << ","
		<< magicArrows << ","
		<< lanternOil << ","
		<< isAlive << ","
		<< score << ","
		<< cavesExplored << ","
		<< inventory.size();

	//append each inventory item after the count
	for (int i = 0; i < inventory.size(); i++) {
		ss << "," << inventory[i];
	}
	return ss.str();
}

//restore all player attributes from the saved string received from FileManager when loading a game
//the order of restoring each attribute must be the same as the order in getSaveData to ensure the correct values are assigned to the correct attributes
void Player::loadSaveData(const string& data) {
	stringstream ss(data);
	string value;

	/* got the idea to use stringstream to seperate the saved data string into smaller values using commas,
	   then used stoi to convert the number values from string to integer from this website:
	   https://stackoverflow.com/questions/48528893/stringstream-parse-comma-separated-integers
	*/
	getline(ss, playerName, ',');
	getline(ss, value, ','); currentCaveID = stoi(value);
	getline(ss, value, ','); arrows = stoi(value);
	getline(ss, value, ','); magicArrows = stoi(value);
	getline(ss, value, ','); lanternOil = stoi(value);
	getline(ss, value, ','); isAlive = stoi(value);
	getline(ss, value, ','); score = stoi(value);
	getline(ss, value, ','); cavesExplored = stoi(value);

	//read the inventory count first then restore each item
	getline(ss, value, ',');
	int inventorySize = stoi(value);

	inventory.clear();

	for (int i = 0; i < inventorySize; i++) {
		getline(ss, value, ',');
		inventory.push_back(value);
	}
}