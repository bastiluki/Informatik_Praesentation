#include "SwitchGround.h"

//In der Initalisierungsfunktion werden die Werte dem SwitchGround-Objekt übergeben.
SwitchGround::SwitchGround(float x1, float y1, float x2, float y2, float percentTime) {
	//Koordinaten des Activate-Blocks
	activateCoords.x = x1;
	activateCoords.y = y1;

	//Koordinaten des Reset-Blocks
	resetCoords.x = x2;
	resetCoords.y = y2;

	//Errechnung der Zeit, nachdem der Block wechselt.
	switchTime = (int)(300.0f * (percentTime / 100.0f));
}

void SwitchGround::tick() {
	//Wenn kein Block aktiviert ist, wird die Variable time um eins größer.
	if(!activated)
		time += 1;

	//Wenn time gleich switchtime ist wird der momentane Block geändert.
	if (time == switchTime) {
		time = 0;

		if (highArea + 1 == switchAreas.size()) {
			highArea = 0;
		}
		else {
			highArea += 1;
		}
	}
}

void SwitchGround::activate() {
	if (activated == false)
		activated = true;
}

void SwitchGround::reset() {
	if (activated == true)
		activated = false;
}

//Die wechselnden Blöcke werden hier einer Liste hinzugefügt.
void SwitchGround::addArea(float x, float y, float w, float h) {
	rect area;
	area.x = x;
	area.y = y;
	area.w = w;
	area.h = h;
	area.activated = false;

	switchAreas.push_back(area);
}

vec2d SwitchGround::getActivateCoords() {
	return activateCoords;
}

vec2d SwitchGround::getResetCoords() {
	return resetCoords;
}

std::vector<rect> SwitchGround::getSwitchAreas() {
	return switchAreas;
}

int SwitchGround::getHighArea() {
	return highArea;
}

bool SwitchGround::getActivated() {
	return activated;
}
