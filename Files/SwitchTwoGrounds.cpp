#include "SwitchTwoGrounds.h"

//In der Initalisierungsfunktion werden die Werte dem SwitchTwoGrounds-Objekt übergeben.
SwitchTwoGrounds::SwitchTwoGrounds(float x, float y, bool onlyNPCActivate, bool onlyOneTimeColission) {
	//Koordinaten vom Wechsel-Block
	coords.x = x;
	coords.y = y;

	//Boolsche Variable ob der Block nur durch den NPC aktivierbar ist.
	onlyNPC = onlyNPCActivate;

	//Boolsche Variable ob der Block nur einmal aktivierbar ist.
	onlyOneTime = onlyOneTimeColission;
}

//Die Blockfarbe wird gewechselt. Es wird auch geprüft, ob der Blcokj schoneinmal aktiviert worden ist.
void SwitchTwoGrounds::switchArea() {

	if (!oneTimeActivasion) {
		activated = !activated;
		oneTimeActivasion = true;
	}

	if (!wasActivatedOnce) {
		wasActivatedOnce = true;
	}
}

//Hier werden die Blöcke mit entsprechender Farbe einer Liste hinzugefügt.
void SwitchTwoGrounds::addArea(float x, float y, float w, float h, bool isActivated) {
	rect area;
	area.x = x;
	area.y = y;
	area.w = w;
	area.h = h;
	area.activated = isActivated;

	switchAreas.push_back(area);
}

vec2d SwitchTwoGrounds::getCoords() {
	return coords;
}

std::vector<rect> SwitchTwoGrounds::getSwitchAreas() {
	return switchAreas;
}

bool SwitchTwoGrounds::getActivated(){
	return activated;
}

bool SwitchTwoGrounds::getOnlyNPC() {
	return onlyNPC;
}

bool SwitchTwoGrounds::getOnlyOneTime() {
	return onlyOneTime;
}

bool SwitchTwoGrounds::getWasActivatedOnce() {
	return wasActivatedOnce;
}

bool SwitchTwoGrounds::getOneTimeActivasion() {
	return oneTimeActivasion;
}

void SwitchTwoGrounds::setOneTimeActivasionFalse() {
	oneTimeActivasion = false;
}
