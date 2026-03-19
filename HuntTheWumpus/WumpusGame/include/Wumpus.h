#ifndef WUMPUS_H
#define WUMPUS_H

#include "libraries.h"
#include "Hazard.h"

class Wumpus : public Hazard
{
public:
	Wumpus(float movementChance);
	void encounter() override;

	// GETTERS
	string getHazardName() override;
	string getHazardWarning() override;

	void startle();
	void roam();

	~Wumpus() override;
private:
};

#endif