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

#include "Wumpus.h"

Wumpus::Wumpus(float movementChance) : isAwake(false) {
	chanceToMove = movementChance;
}

void Wumpus::encounter() {
	cout << "The Wumpus has woken up! You have been eaten.\n";
	// should've killed player, but that's handled in GameManager
}

string Wumpus::getHazardName() {
	return "Wumpus";
}

string Wumpus::getHazardWarning() {
	return "You smell a terrible stench...\n";
}

void Wumpus::startle(int id) {
	isAwake = true;

	// arrow missing handled in GameManager -> if missed, 75% wake up
	int roll = rand() % 100;
	if (roll < (chanceToMove * 100)) {
		roam(id);
	}
}

void Wumpus::roam(int id) {
	setRoomID(id);
}

Wumpus::~Wumpus() {}
