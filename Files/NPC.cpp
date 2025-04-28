#include "NPC.h"

//In der Initalisierungsfunktion werden die Werte dem NPC-Objekt übergeben.
NPC::NPC(float x, float y, bool horizontalMovement, bool upRight, bool gravityExists, bool willRespawn) {
	//Koordinaten
	npc.x = x;
	npc.y = y;

	//Konstante Startkoordinaten
	originalCoords.x = x;
	originalCoords.y = y;

	//Geschwindigkeitsdefinition je nach Einstellung
	if (horizontalMovement && upRight && gravityExists) {
		constNPCVel.x = 0.25f;
		constNPCVel.y = -0.25f;
	}
	else if (horizontalMovement && upRight && !gravityExists) {
		constNPCVel.x = 0.25f;
		constNPCVel.y = 0.0f;
	}
	else if (horizontalMovement && !upRight && gravityExists) {
		constNPCVel.x = -0.25f;
		constNPCVel.y = -0.25f;
	}
	else if (horizontalMovement && !upRight && !gravityExists) {
		constNPCVel.x = -0.25f;
		constNPCVel.y = 0.0f;
	}
	else if (!horizontalMovement && upRight) {
		constNPCVel.x = 0.0f;
		constNPCVel.y = 0.25f;
	}
	else if (!horizontalMovement && !upRight) {
		constNPCVel.x = 0.0f;
		constNPCVel.y = -0.25f;
	}

	npcVel.x = constNPCVel.x;
	npcVel.y = constNPCVel.y;

	//Neue Koordinaten werden vorgerechnet.
	earlyNPC.x = npc.x + npcVel.x * 4.0f;
	earlyNPC.y = npc.y + npcVel.y * 4.0f;

	horizontal = horizontalMovement;
	respawn = willRespawn;
}


void NPC::tick() {
	//Der NPC wird bewegt mit der bestimmten Geschwindigkeit.
	npc.x += npcVel.x;
	npc.y += npcVel.y;

	npcVel.x = constNPCVel.x;
	npcVel.y = constNPCVel.y;

	earlyNPC.x = npc.x + npcVel.x * 4.0f;
	earlyNPC.y = npc.y + npcVel.y * 4.0f;
}

//Killareas werden hier der Liste hinzugefügt.
void NPC::addKillArea(float x, float y, float w, float h) {
	rect area;
	area.x = x;
	area.y = y;
	area.w = w;
	area.h = h;
	area.activated = false;

	killAreas.push_back(area);
}

//Der NPC wird an seine originalen Koordinaten gesetzt.
void NPC::respawning() {
	npc.x = originalCoords.x;
	npc.y = originalCoords.y;
}

vec2d NPC::getCoords() {
	return npc;
}

vec2d NPC::getEarlyCoords() {
	return earlyNPC;
}

std::vector<rect> NPC::getKillAreas() {
	return killAreas;
}

bool NPC::getHorizontal() {
	return horizontal;
}

bool NPC::getRespawn() {
	return respawn;
}

void NPC::setX(float x) {
	npc.x = x;
}

void NPC::setY(float y) {
	npc.y = y;
}

void NPC::setVelx(float velX){
	npcVel.x = velX;
}
void NPC::setVely(float velY) {
	npcVel.y = velY;
}

//Die Richtung wird mal -1 gerechnet;
void NPC::invertDirection() {
	if (horizontal) {
		npcVel.x *= -1;
		constNPCVel.x *= -1;
	}
	else {
		npcVel.y *= -1;
		constNPCVel.y *= -1;
	}
}
