#include "GameManager.h"

GameManager::GameManager():running(true) {}

void GameManager::run()
{
	ifstream fileToRead("initiate.txt");
	string dataToPrint;

	if (running)
	{
		cout << "Game running...\n";
		cout << "Successfully loaded from \"include\" folder\n";
		while (!fileToRead.eof())
		{
			getline(fileToRead, dataToPrint);
			cout << dataToPrint << endl;
		}
	} else
	{
		cout << "Loading failed\n";
	}
}
