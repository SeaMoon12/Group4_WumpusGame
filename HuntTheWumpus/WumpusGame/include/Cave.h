#ifndef CAVE_H
#define CAVE_H

#include <libraries.h>

enum CaveHazards //unneeded becuz of Hazards class
{
	NONE, BATS, PIT, WUMPUS
};

struct CaveProperties //couldve been made a class or maybe parent class
{
	std::vector<int> connectedCaves = std::vector<int>(4, -1);
	int cavePosition; //cave ID, wrong naming convention.
	CaveHazards caveHazards;
	bool caveVisited;
};

enum TunnelDirections
{
	NORTH, EAST, SOUTH, WEST
};

enum Tile
{
	EMPTY, CAVE, H_TUNNEL, V_TUNNEL
};

class Cave
{
private:

	//instance variables
	std::vector<vector<Tile>> caveLogicVector; //holds the type of tile for rendering and spacing
	std::vector<vector<int>> cavePositionVector; //holds cave x y positions for map grid
	std::vector<CaveProperties> cavesData; //holds the cave's insides and relations with other caves
	std::vector<string> map;
	int playerPosition; //uneeded bcuz of player class
	bool randomCave;

	//private member functions
	int countConnections(std::vector<vector<Tile>>& caveLogicVector, int x, int y);
	std::string directionToString(int dirIndex); //just for testing

public:

	//static variables
	static enum GameDifficulty { //shouldve been an instance var
		ROOKIE, HUNTER, MASTER_HUNTER, ROOKIE_RANDOM, HUNTER_RANDOM, MASTER_HUNTER_RANDOM
	};
	static const int TOTAL_CAVES = 20;

	//constructor & destructtor
	Cave(GameDifficulty gameDiff); //gameDiff is useless here, shouldve been bool randomCave. also wrong name in UML(update, got it to work yipee)
	~Cave();

	//getters
	std::vector<vector<Tile>> getCaveLogicVector();
	std::vector<vector<int>> getCavePositionVector();
	std::vector<CaveProperties> getCavesData();
	std::vector<string> getMap();
	int getPlayerPosition();
	bool getRandomCave();

	//setters
	void setCaveLogicVector(std::vector<vector<Tile>> newLogicVector); //what type of Tile the space is, ie cave or tunnel
	void setCavePositionVector(std::vector<vector<int>> newPositionVector); //used for rendering
	void setCavesData(std::vector<CaveProperties> newCavesData);
	void setMap(std::vector<string> newMap);
	void setPlayerPosition(int newPlayerPosition);
	void setRandomCave(bool newRandomCave);

	//member functons
	void generateCaveMap();
	void linkCaves();
	void renderMap(bool cheatMode = false); //shouldve made it return type sstream for game manager to handle
	void updateCaveMap(std::vector<CaveProperties> newCavesData);



};

#endif