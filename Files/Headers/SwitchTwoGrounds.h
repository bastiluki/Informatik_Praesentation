#pragma once

#include <vector>
#include <iostream>

#include "Structs.h"

class SwitchTwoGrounds {
public:
	SwitchTwoGrounds(float x, float y, bool onlyNPCActivate, bool onlyOneTimeColission);

	//Die aktivierte Blockfarbe wird gewechselt.
	void switchArea();

	void addArea(float x, float y, float w, float h, bool isActivated);

	vec2d getCoords();
	std::vector<rect> getSwitchAreas();
	bool getActivated();
	bool getOnlyNPC();
	bool getOnlyOneTime();
	bool getWasActivatedOnce();
	bool getOneTimeActivasion();
	void setOneTimeActivasionFalse();

private:
	//Koordinate des Wechselblocks
	vec2d coords;

	//Boolsche Variablen, die zeigen, ob das Objekt schon einmal aktiviert worden ist, welche Farbe aktiviert ist,
	//ob nur NPCs ihn aktivieren können und ob das Objekt nur einmal aktivierbar ist.
	bool activated = true;
	bool oneTimeActivasion = false;

	bool onlyNPC = false;
	bool onlyOneTime = false;

	bool wasActivatedOnce = false;

	//Eine Liste mit den unterschiedlichen Frabblöcken 
	std::vector<rect> switchAreas;
};

