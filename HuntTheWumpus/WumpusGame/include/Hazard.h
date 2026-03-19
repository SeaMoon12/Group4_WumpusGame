#ifndef HAZARD_H
#define HAZARD_H

#include "libraries.h"

class Hazard
{
public:
	Hazard();
	virtual void encounter() = 0;

	// GETTERS
	int getRoomID();
	static int getActiveHazardCount();
	virtual string getHazardName() = 0;
	virtual string getHazardWarning() = 0;

	// SETTERS
	void setRoomID();

	virtual ~Hazard();

protected:
	int roomID;

private:
	static int activeHazardCount;
};

#endif