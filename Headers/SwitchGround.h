#pragma once

#include <vector>
#include <iostream>

#include "Structs.h"

class SwitchGround {
public:
	SwitchGround(float x1, float y1, float x2, float y2, float percentTime);
	void tick();

	//activate aktiviert einen momentanen Block und reset löst ihn auch wieder.
	void activate();
	void reset();

	void addArea(float x, float y, float w, float h);

	vec2d getActivateCoords();
	vec2d getResetCoords();
	std::vector<rect> getSwitchAreas();
	int getHighArea();
	bool getActivated();

private:
	//Koordinaten des Reset- und Aktivierungs-Block
	vec2d activateCoords;
	vec2d resetCoords;

	//Index des momentanen Blocks
	int highArea = 0;

	//Boolsche Variable, die zeigt ob ein Block aktiviert ist oder keiner.
	bool activated = false;

	//Eine Liste, die wechselnden Blöcke
	std::vector<rect> switchAreas;

	int time = 0;
	int switchTime = 300;
};

