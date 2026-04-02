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
	caveLogicVector.assign(20, vector<Tile>(20, Tile::EMPTY));
	cavePositionVector.assign(20, vector<int>(20, -1));
	map.assign(60, string(100, ' '));
	generateCaveMap();
	cavesData.assign(cavePositionVector.size(), CaveProperties());
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
	if (x + 2 < 20 and caveLogicVector[y][x + 1] == Tile::H_TUNNEL) {
		count++;
	}
	if (y + 2 < 20 and caveLogicVector[y + 1][x] == Tile::V_TUNNEL) {
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
			caveLogicVector.assign(20, vector<Tile>(20, Tile::EMPTY));
			cavePositionVector.clear();
			
			int startX = rand() % 20;
			int startY = rand() % 20;

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
				if (newX >= 0 and newX < 20 and newY >= 0 and newY < 20 and caveLogicVector[newX][newY] == Tile::EMPTY) {
					caveLogicVector[newY][newX] = Tile::CAVE;
					caveLogicVector[currentX + (directionX[direction] / 2)][currentY + (directionY[direction] / 2)] = tunnelType[direction];
					cavePositionVector.push_back({ newX, newY });
				}	
			}

			for (int i = 0; i < cavePositionVector.size(); i++) { //link caves randomly so not all caves are connected
				int currentX = cavePositionVector[i][0];
				int currentY = cavePositionVector[i][1];
				for (int direction = 0; direction < 4; direction++) {
					int adjX = currentX + directionX[direction];
					int adjY = currentY + directionY[direction];
					if (adjX >= 0 and adjX < 20 and adjY >= 0 and adjY < 20 and caveLogicVector[adjX][adjY] == Tile::CAVE) {
						int tunnelX = currentX + (directionX[direction] / 2);
						int tunnelY = currentY + (directionY[direction] / 2);
						if (caveLogicVector[tunnelX][tunnelY] == Tile::EMPTY) {
							if (rand() % 100 > 30) {
								caveLogicVector[tunnelX][tunnelY] = tunnelType[direction];
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
		int caveIDInc = 1;
		int X = (TOTAL_CAVES / 5) * 2 - 1;
		int Y = (TOTAL_CAVES / X) * 2 - 1;
		for (int i = 0; i < X; i++) {
			for (int j = 0; j < Y; j++) {
				
				caveLogicVector[i][j] = Tile::CAVE;
				cavePositionVector[i][j] = caveIDInc;
				
				caveIDInc++;
				j++; //inc by 2
				if (j < Y) {
					caveLogicVector[i][j] = Tile::H_TUNNEL;
				}
			}
			i++; //inc by 2
			if (i < X) {
				caveLogicVector[i] = vector<Tile>(Y, Tile::V_TUNNEL);
			}
		}
	}
	linkCaves();
}

void Cave::linkCaves() { //links caves in cavesData based on the caveLogicVector and cavePositionVector
	vector<vector<int>>& const CAVE_POS_REF = cavePositionVector; //read only 

	//convert to int to store in cavesData.connectedCaves vector, -1 is none
	int const NORTH = static_cast<int>(TunnelDirections::NORTH);
	int const EAST = static_cast<int>(TunnelDirections::EAST);
	int const SOUTH = static_cast<int>(TunnelDirections::SOUTH);
	int const WEST = static_cast<int>(TunnelDirections::WEST);

	for (int i = 0; i < cavePositionVector.size(); i++) { 
		int currentX = cavePositionVector[i][0];
		int currentY = cavePositionVector[i][1];
		int currentId = CAVE_POS_REF[currentX][currentY];
		if (currentY - 2 >= 0 and caveLogicVector[currentX - 1][currentY] == Tile::V_TUNNEL) {
			cavesData[currentId].connectedCaves[NORTH] = CAVE_POS_REF[currentX - 2][currentY];
		}
		else {
			cavesData[currentId].connectedCaves[NORTH] = -1;
		}
		if (currentX + 2 < 20 and caveLogicVector[currentX][currentY + 1] == Tile::H_TUNNEL) {
			cavesData[currentId].connectedCaves[EAST] = CAVE_POS_REF[currentX][currentY + 2];
		}
		else {
			cavesData[currentId].connectedCaves[EAST] = -1;
		}
		if (currentY + 2 < 20 and caveLogicVector[currentX + 1][currentY] == Tile::V_TUNNEL) {
			cavesData[currentId].connectedCaves[SOUTH] = CAVE_POS_REF[currentX + 2][currentY];
		}
		else {
			cavesData[currentId].connectedCaves[SOUTH] = -1;
		}
		if (currentX - 2 >= 0 and caveLogicVector[currentX][currentY - 1] == Tile::H_TUNNEL) {
			cavesData[currentId].connectedCaves[WEST] = CAVE_POS_REF[currentX][currentY - 2];
		}
		else {
			cavesData[currentId].connectedCaves[WEST] = -1;
		}
		cavesData[currentId].cavePosition = currentId;
	}

	//test to see if it connects
	for (int i = 0; i < cavesData.size(); i++) {
		cout << "Cave ID: " << cavesData[i].cavePosition << " | Exits -> ";
		for (int d = 0; d < 4; d++) {
			int targetId = cavesData[i].connectedCaves[d];
			if (targetId != -1) { // Only print if a tunnel actually exists!
				cout << "[" << directionToString(d) << " to Cave " << targetId << "] ";
			}
		}
		cout << "\n";
	}

}

void Cave::renderMap() { //render the map based on the caveLogicVector, cavePositionVector and cavesData
	int playerX = cavePositionVector[playerPosition][0];
	int playerY = cavePositionVector[playerPosition][1];
	for (int x = 0; x < 20; ++x) {
		for (int y = 0; y < 20; ++y) {
			Tile currentTile = caveLogicVector[x][y];
			if (currentTile == Tile::EMPTY) {
				continue;
			}
			int drawY = y * 3;
			int drawX = x * 5;
			
			if (caveLogicVector[x][y] == CAVE) {
				bool isNorthOpen = (y - 1 >= 0 and caveLogicVector[x][y - 1] == Tile::V_TUNNEL);
				bool isSouthOpen = (y + 1 < 20 and caveLogicVector[x][y + 1] == Tile::V_TUNNEL);
				bool isWestOpen = (x - 1 >= 0 and caveLogicVector[x - 1][y] == Tile::H_TUNNEL);
				bool isEastOpen = (x + 1 < 20 and caveLogicVector[x + 1][y] == Tile::H_TUNNEL);

				string roof, topString, midString, bottomString;
				if (isNorthOpen == false) {
					roof = " ___ ";
				}

				topString = "/   \\";

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
		for (int i = 0; i < 60; ++i) {
			cout << map[i] << "\n";
		}
	}
}

//for gamemanager class, make a CaveProperties vector, assign the index according to player pos or hazard movement, then pass that as an arg here, sorry
void Cave::updateCaveMap(vector<CaveProperties> newCavesData) { //updates caveData such as changing caveHzards or caveVisted, the arg shouldve been a single caveProperties struct
	for (int i = 0; i < cavesData.size(); i++) {
		cavesData[i] = newCavesData[i];
	}
}
