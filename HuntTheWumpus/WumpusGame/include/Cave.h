#ifndef CAVE_H
#define CAVE_H

#include <libraries.h>

enum CaveHazards //unneeded becuz of Hazards class
{
	NONE, BATS, PIT, WUMPUS
};

struct CaveProperties //couldve been made a class or maybe parent class
{
	vector<int> connectedCaves = vector<int>(4, -1);
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
		vector<vector<Tile>> caveLogicVector; //holds the type of tile for rendering and spacing
		vector<vector<int>> cavePositionVector; //holds cave x y positions for map grid
		vector<CaveProperties> cavesData; //holds the cave's insides and relations with other caves
		vector<string> map;
		int playerPosition; //uneeded bcuz of player class
		bool randomCave;

		//private member functions
		int countConnections(vector<vector<Tile>>& caveLogicVector, int x, int y);
		string directionToString(int dirIndex); //just for testing

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
		vector<vector<Tile>> getCaveLogicVector();
		vector<vector<int>> getCavePositionVector();
		vector<CaveProperties> getCavesData();
		vector<string> getMap();
		int getPlayerPosition();
		bool getRandomCave();

		//setters
		void setCaveLogicVector(vector<vector<Tile>> newLogicVector); //what type of Tile the space is, ie cave or tunnel
		void setCavePositionVector(vector<vector<int>> newPositionVector); //used for rendering
		void setCavesData(vector<CaveProperties> newCavesData);
		void setMap(vector<string> newMap);
		void setPlayerPosition(int newPlayerPosition);
		void setRandomCave(bool newRandomCave);

		//member functons
		void generateCaveMap();
		void linkCaves();
		void renderMap(); //shouldve made it return type sstream for game manager to handle
		void updateCaveMap(vector<CaveProperties> newCavesData);



};

#endif