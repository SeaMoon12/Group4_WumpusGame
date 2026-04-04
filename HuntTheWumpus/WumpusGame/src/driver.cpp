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

#include "BottomlessPit.h"
#include "Wumpus.h"
#include "SuperBat.h"

int main()
{
	vector<Hazard*> hazards = { new Wumpus(0.5f), new SuperBat(0.75f), new BottomlessPit() };
	cout << "Hazard Name: " << hazards[0]->getHazardName() << endl;
	hazards[0]->setRoomID(5);
	cout << hazards[0]->getHazardWarning();
	hazards[0]->encounter();

	cout << endl;

	cout << "Hazard Name: " << hazards[1]->getHazardName() << endl;
	hazards[1]->setRoomID(5);
	cout << hazards[1]->getHazardWarning();
	hazards[1]->encounter();

	cout << endl;

	cout << "Hazard Name: " << hazards[2]->getHazardName() << endl;
	hazards[2]->setRoomID(5);
	cout << hazards[2]->getHazardWarning();
	hazards[2]->encounter();

	return 0;
}