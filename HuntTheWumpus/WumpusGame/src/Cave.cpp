/********************************************************************
FITS1201 – Object-Oriented Programming
OOP Final Project - Hunt the Wumpus Game
Academic Integrity Declaration
Student Name: Gerrard Saint Wu
Student ID: 251103130113
Submission Date: 04/04/2026
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
Student Signature: Gerrard Saint Wu
********************************************************************/

#include "Cave.h"

//constructor
Cave::Cave(GameDifficulty gameDiff) { //weird because of UML error workarounds
	if (gameDiff == ROOKIE_RANDOM || gameDiff == HUNTER_RANDOM || gameDiff == MASTER_HUNTER_RANDOM) {
		randomCave = true;
	}
	else {
		randomCave = false;
	}
	playerPosition = 0; 
	caveLogicVector.assign(10, vector<Tile>(10, Tile::EMPTY));
	cavePositionVector.assign(10, vector<int>(10, -1));
	map.assign(30, string(50, ' '));	
	cavesData.assign(cavePositionVector.size(), CaveProperties());
	generateCaveMap();
}

//destructor
Cave::~Cave() {
	//empty
}

//setters
void Cave::setCaveLogicVector(vector<vector<Tile>> newLogicVector) {
	caveLogicVector = newLogicVector;
}

void Cave::setCavePositionVector(vector<vector<int>> newPositionVector) {
	cavePositionVector = newPositionVector;
}

void Cave::setCavesData(vector<CaveProperties> newCavesData) {
	cavesData = newCavesData;
}

void Cave::setMap(vector<string> newMap) {
	map = newMap;
}

void Cave::setPlayerPosition(int newPlayerPosition) {
	playerPosition = newPlayerPosition;
}

void Cave::setRandomCave(bool newRandomCave) {
	randomCave = newRandomCave;
}

//getters
vector<vector<Tile>> Cave::getCaveLogicVector() {
	return caveLogicVector;
}

vector<vector<int>> Cave::getCavePositionVector() {
	return cavePositionVector;
}

vector<CaveProperties> Cave::getCavesData() {
	return cavesData;
}

vector<string> Cave::getMap() {
	return map;
}

int Cave::getPlayerPosition() {
	return playerPosition;
}

bool Cave::getRandomCave() {
	return randomCave;
}

//member functions
///private funcs
int Cave::countConnections(vector<vector<Tile>>& caveLogicVector, int x, int y) {
	
	int count = 0;
	if (y - 2 >= 0 and caveLogicVector[y - 1][x] == Tile::V_TUNNEL) {
		count++;
	}
	if (x + 2 < 10 and caveLogicVector[y][x + 1] == Tile::H_TUNNEL) {
		count++;
	}
	if (y + 2 < 10 and caveLogicVector[y + 1][x] == Tile::V_TUNNEL) {
		count++;
	}
	if (x - 2 >= 0 and caveLogicVector[y][x - 1] == Tile::H_TUNNEL) {
		count++;
	}
	return count;
}

string Cave::directionToString(int dirIndex) {
	
	if (dirIndex == 0) {
		return "NORTH";
	}
	if (dirIndex == 1) {
		return "EAST";
	}
	if (dirIndex == 2) {
		return "SOUTH";
	}
	if (dirIndex == 3) {
		return "WEST";
	}
	else {
		return "WEST";
	}
}

void Cave::generateCaveMap() { //generates the cave positions, has a boolean to contro if its random or not
	
	if (randomCave == true) { //random cave gen using rejection sampling method
		int attempts = 0; //so when making the map, it doesnt explode if it doesnt find one with the requested specs
		while (attempts < 15000) {
			attempts++;

			//inits starting cave
			caveLogicVector.assign(10, vector<Tile>(10, Tile::EMPTY));
			cavePositionVector.clear();

			int startX = rand() % 10;
			int startY = rand() % 10;

			caveLogicVector[startY][startX] = Tile::CAVE;
			cavePositionVector.push_back({ startX, startY });

			//directions and tunnel types for branching
			int directionX[] = { 0, 2, 0, -2 }; //increment by 2 to account for tunnels
			int directionY[] = { -2, 0, 2, 0 };
			Tile tunnelType[] = { Tile::V_TUNNEL, Tile::H_TUNNEL, Tile::V_TUNNEL, Tile::H_TUNNEL };

			while (cavePositionVector.size() < TOTAL_CAVES) { //cave generation loop

				int randomIndex = rand() % cavePositionVector.size(); //picks a random cave to branch off of
				int currentX = cavePositionVector[randomIndex][0];
				int currentY = cavePositionVector[randomIndex][1];

				int direction = rand() % 4; //picks a random direction to branch off of
				int newX = currentX + directionX[direction];
				int newY = currentY + directionY[direction];
				if (newX >= 0 and newX < 10 and newY >= 0 and newY < 10 and caveLogicVector[newY][newX] == Tile::EMPTY) {
					caveLogicVector[newY][newX] = Tile::CAVE;
					caveLogicVector[currentY + (directionY[direction] / 2)][currentX + (directionX[direction] / 2)] = tunnelType[direction];
					cavePositionVector.push_back({ newX, newY });
				}
			}

			for (int i = 0; i < cavePositionVector.size(); i++) { //link caves randomly so not all caves are connected
				int currentX = cavePositionVector[i][0];
				int currentY = cavePositionVector[i][1];
				for (int direction = 0; direction < 4; direction++) {
					int adjX = currentX + directionX[direction];
					int adjY = currentY + directionY[direction];
					if (adjX >= 0 and adjX < 10 and adjY >= 0 and adjY < 10 and caveLogicVector[adjY][adjX] == Tile::CAVE) {
						int tunnelX = currentX + (directionX[direction] / 2);
						int tunnelY = currentY + (directionY[direction] / 2);
						if (caveLogicVector[tunnelY][tunnelX] == Tile::EMPTY) {
							if (rand() % 100 > 30) {
								caveLogicVector[tunnelY][tunnelX] = tunnelType[direction];
							}
						}
					}
				}
			}
			bool isMapPerfect = true;
			int connectionCounts[5] = { 0, 0, 0, 0, 0 };
			for (int i = 0; i < cavePositionVector.size(); i++) {
				int currentX = cavePositionVector[i][0];
				int currentY = cavePositionVector[i][1];
				int connections = countConnections(caveLogicVector, currentX, currentY);
				connectionCounts[connections]++;
			}

			if (connectionCounts[1] >= 3 || connectionCounts[2] <= 3 || connectionCounts[3] <= 5 || connectionCounts[4] <= 5) {
				isMapPerfect = false;
			}

			if (isMapPerfect) {
				cout << "Found a perfectly diverse map in " << attempts << " attempts!\n";
				cout << "[ Dead Ends (1): " << connectionCounts[1]
					<< " | Hallways (2): " << connectionCounts[2]
					<< " | T-Junctions (3): " << connectionCounts[3]
					<< " | Hubs (4): " << connectionCounts[4] << " ]\n\n";
				break;
			}

			if (attempts > 15000) {
				cout << "\nWARNING: Hit 15,000 limit. Spitting out an imperfect map after " << attempts << " attempts.\n";
				cout << "[ Dead Ends (1): " << connectionCounts[1]
					<< " | Hallways (2): " << connectionCounts[2]
					<< " | T-Junctions (3): " << connectionCounts[3]
					<< " | Hubs (4): " << connectionCounts[4] << " ]\n\n";
				break;
			}
		}

	}
	else if (randomCave == false) { //set wumpus map

		caveLogicVector.assign(10, vector<Tile>(10, Tile::EMPTY));
		cavePositionVector.clear();

		int cavesX = TOTAL_CAVES / 5;
		int cavesY = TOTAL_CAVES / cavesX;

		int cavernX = cavesX * 2 - 1;
		int cavernY = cavesY * 2 - 1;

		for (int y = 0; y < cavernX; y++) {
			for (int x = 0; x < cavernY; x++) {
				if (y % 2 == 0) {
					if (x % 2 == 0) {
						caveLogicVector[y][x] = Tile::CAVE;
						cavePositionVector.push_back({ x, y });
					}
					else {
						caveLogicVector[y][x] = Tile::H_TUNNEL;
					}
				}
				else {
					if (x % 2 == 0) {
						caveLogicVector[y][x] = Tile::V_TUNNEL;
					}
				}
			}
		}
	}
	linkCaves();
}

void Cave::linkCaves() { //links caves in cavesData based on the caveLogicVector and cavePositionVector
	
	cavesData.assign(cavePositionVector.size(), CaveProperties());

	//convert to int to store in cavesData.connectedCaves vector, -1 is none
	int const NORTH = static_cast<int>(TunnelDirections::NORTH);
	int const EAST = static_cast<int>(TunnelDirections::EAST);
	int const SOUTH = static_cast<int>(TunnelDirections::SOUTH);
	int const WEST = static_cast<int>(TunnelDirections::WEST);

	vector<vector<int>> idLookupGrid(10, vector<int>(10, -1));

	for (int i = 0; i < cavePositionVector.size(); i++) {
		int cx = cavePositionVector[i][0];
		int cy = cavePositionVector[i][1];
		idLookupGrid[cy][cx] = i;
	}

	for (int i = 0; i < cavePositionVector.size(); i++) {
		cavesData[i].cavePosition = i;
		int currentX = cavePositionVector[i][0];
		int currentY = cavePositionVector[i][1];
		int currentId = i;
		cavesData[currentId].connectedCaves.assign(4, -1);
		if (currentY - 2 >= 0 and caveLogicVector[currentY - 1][currentX] == Tile::V_TUNNEL) {
			cavesData[currentId].connectedCaves[NORTH] = idLookupGrid[currentY - 2][currentX];
		}
		else {
			cavesData[currentId].connectedCaves[NORTH] = -1;
		}
		if (currentX + 2 < 10 and caveLogicVector[currentY][currentX + 1] == Tile::H_TUNNEL) {
			cavesData[currentId].connectedCaves[EAST] = idLookupGrid[currentY][currentX + 2];
		}
		else {
			cavesData[currentId].connectedCaves[EAST] = -1;
		}
		if (currentY + 2 < 10 and caveLogicVector[currentY + 1][currentX] == Tile::V_TUNNEL) {
			cavesData[currentId].connectedCaves[SOUTH] = idLookupGrid[currentY + 2][currentX];
		}
		else {
			cavesData[currentId].connectedCaves[SOUTH] = -1;
		}
		if (currentX - 2 >= 0 and caveLogicVector[currentY][currentX - 1] == Tile::H_TUNNEL) {
			cavesData[currentId].connectedCaves[WEST] = idLookupGrid[currentY][currentX - 2];
		}
		else {
			cavesData[currentId].connectedCaves[WEST] = -1;
		}
		cavesData[currentId].cavePosition = currentId;
	}

	//test to see if it connects

	//for (int i = 0; i < cavesData.size(); i++) {
	//	cout << "Cave ID: " << cavesData[i].cavePosition << " | Exits -> ";
	//	for (int d = 0; d < 4; d++) {
	//		int targetId = cavesData[i].connectedCaves[d];
	//		if (targetId != -1) { // Only print if a tunnel actually exists!
	//			cout << "[" << directionToString(d) << " to Cave " << targetId << "] ";
	//		}
	//	}
	//	cout << "\n";
	//}

}

void Cave::renderMap() { //render the map based on the caveLogicVector, cavePositionVector and cavesData
	
	int playerX = cavePositionVector[playerPosition][0];
	int playerY = cavePositionVector[playerPosition][1];
	for (int y = 0; y < 10; ++y) {
		for (int x = 0; x < 10; ++x) {
			Tile currentTile = caveLogicVector[y][x];
			if (currentTile == Tile::EMPTY) {
				continue;
			}
			int drawY = y * 3;
			int drawX = x * 5;

			if (caveLogicVector[y][x] == CAVE) {
				bool isNorthOpen = (y - 1 >= 0 and caveLogicVector[y - 1][x] == Tile::V_TUNNEL);
				bool isSouthOpen = (y + 1 < 10 and caveLogicVector[y + 1][x] == Tile::V_TUNNEL);
				bool isWestOpen = (x - 1 >= 0 and caveLogicVector[y][x - 1] == Tile::H_TUNNEL);
				bool isEastOpen = (x + 1 < 10 and caveLogicVector[y][x + 1] == Tile::H_TUNNEL);

				string topString, midString, bottomString;
				if (isNorthOpen == false) {
					topString = "/---\\";
				}
				else {
					topString = "/   \\";
				}

				if (playerX == x and playerY == y) {
					midString = "  O  ";
				}
				else {
					midString = "     ";
				}

				if (isWestOpen == true) {
					midString[0] = ' ';
				}
				else {
					midString[0] = '|';
				}

				if (isEastOpen == true) {
					midString[4] = ' ';
				}
				else {
					midString[4] = '|';
				}

				if (isSouthOpen == true) {
					bottomString = "\\   /";
				}
				else {
					bottomString = "\\___/";
				}
				map[drawY].replace(drawX, 5, topString);
				map[drawY + 1].replace(drawX, 5, midString);
				map[drawY + 2].replace(drawX, 5, bottomString);
				continue;
			}
			else if (currentTile == Tile::H_TUNNEL) {
				map[drawY].replace(drawX, 5, "_____");
				map[drawY + 1].replace(drawX, 5, "_____");
				continue;
			}
			else if (currentTile == Tile::V_TUNNEL) {
				map[drawY].replace(drawX, 5, " | | ");
				map[drawY + 1].replace(drawX, 5, " | | ");
				map[drawY + 2].replace(drawX, 5, " | | ");
				continue;
			}

		}
	}

	vector<vector<bool>> visitedGrid(10, vector<bool>(10, false)); //cave visited check
	for (int i = 0; i < cavesData.size(); i++) {
		if (cavesData[i].caveVisited == true) {
			int cx = cavePositionVector[i][0];
			int cy = cavePositionVector[i][1];
			visitedGrid[cy][cx] = true;
		}
	}

	for (int drawY = 0; drawY < 30; ++drawY) {
		for (int drawX = 0; drawX < 50; ++drawX) {

			int gridX = drawX / 5;
			int gridY = drawY / 3;

			if (gridX < 10 and gridY < 10 and visitedGrid[gridY][gridX] == true) { //print red if visited
				cout << "\033[31m" << map[drawY][drawX] << "\033[0m";
			}
			// Otherwise, print normally
			else {
				cout << map[drawY][drawX];
			}
		}
		cout << "\n"; // End of the row
	}
}

//for gameManager class, do getCavesData, update the index of the cave you want updated, then pass the whole vector back to updateCaveMap to update the caveData in Cave class. also updates caveVisited if player is in that cave
void Cave::updateCaveMap(vector<CaveProperties> newCavesData) { //updates caveData such as changing caveHzards or caveVisted, the arg shouldve been a single caveProperties struct
	cavesData = newCavesData;
	if (playerPosition >= 0 and playerPosition < cavesData.size()) {
		cavesData[playerPosition].caveVisited = true;
	}
}