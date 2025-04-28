#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include <iostream>

#include "Structs.h"
#include "SwitchGround.h"
#include "SwitchTwoGrounds.h"
#include "NPC.h"
#include "LevelLoader.h"

class GameMode {
public:
	//Initialisierungs- und Zerstörungsfuntion
	GameMode();
	~GameMode();

	void tick(const Uint8* keyState, int* mouseX, int* mouseY);
	void keyManager(const Uint8* keyState);

	vec2d getPlayerCoords();
	vec2d getLevelCompleteCoords();
	std::vector<vec2d> getGround();
	std::vector<SwitchGround> getSwitchGround();
	std::vector<SwitchTwoGrounds> getSwitchTwoGrounds();

	std::vector<NPC> getNPCs();

	void loadNextLevel();
	void loadLevel(int i);
	bool loadFirstLevel();

private:
	//Spielervariblen
	vec2d player;
	vec2d playerVel;
	vec2d earlyPlayer;
	vec2d originalPlayer;
	//Killareas des Spielers.
	std::vector<rect> killAreas;

	//Koordinate des Ziels
	vec2d levelComplete;

	//Level Variable
	int level = 0;

	//Liste der einzelnen Objekte.
	std::vector<vec2d> groundList;
	std::vector<SwitchGround> switchGroundList;
	std::vector<SwitchTwoGrounds> switchTwoGroundsList;

	std::vector<NPC> npcList;

	//Levelloader-Onjekt
	LevelLoader levelLoader;

	//Kollisionsfunktionen
	void playerCollison();

	void npcCollision(int index);

	bool collision2RecsBottom(float x1, float y1, float orgX1, float w1, float h1, float x2, float y2, float w2, float h2);
	bool collision2RecsTop(float x1, float y1, float orgX1, float w1, float h1, float x2, float y2, float w2, float h2);
	bool collision2RecsLeft(float x1, float y1, float orgY1, float w1, float h1, float x2, float y2, float w2, float h2);
	bool collision2RecsRight(float x1, float y1, float orgY1, float w1, float h1, float x2, float y2, float w2, float h2);

	bool collision2Recs(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2);
};