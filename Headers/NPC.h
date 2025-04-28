#pragma once

#include <iostream>
#include <vector>

#include "Structs.h"

class NPC {
public:
	NPC(float x, float y, bool horizontalMovement, bool upRight, bool gravityExists, bool willRespawn);
	void tick();

	void addKillArea(float x, float y, float w, float h);

	//Funktion, die den NPC an seine originale Position setzt.
	void respawning();

	vec2d getCoords();
	vec2d getEarlyCoords();

	std::vector<rect> getKillAreas();

	bool getHorizontal();
	bool getRespawn();

	void setX(float x);
	void setY(float y);

	void setVelx(float velX);
	void setVely(float velY);

	void invertDirection();

private:
	vec2d npc;
	vec2d npcVel;
	vec2d constNPCVel;
	vec2d earlyNPC;
	vec2d originalCoords;

	std::vector<rect> killAreas;

	bool horizontal;
	bool respawn;
};

