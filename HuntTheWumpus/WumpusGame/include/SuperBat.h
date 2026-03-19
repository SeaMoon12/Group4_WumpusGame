#ifndef SUPER_BAT_H
#define SUPER_BAT_H

#include "libraries.h"
#include "Hazard.h"

class SuperBat : public Hazard
{
public:
	SuperBat(float movementChance);
	void encounter() override;

	// GETTERS
	string getHazardName() override;
	string getHazardWarning() override;

	void roam();

	~SuperBat() override;
private:
	float chanceToMove;
};

#endif