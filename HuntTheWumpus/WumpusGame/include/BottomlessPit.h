#ifndef BOTTOMLESS_PIT_H
#define BOTTOMLESS_PIT_H

#include "libraries.h"
#include "Hazard.h"

class BottomlessPit : public Hazard
{
	BottomlessPit();
	void encounter() override;

	// GETTERS
	string getHazardName() override;
	string getHazardWarning() override;

	~BottomlessPit() override;
};

#endif