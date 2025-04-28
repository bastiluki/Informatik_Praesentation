#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <string>

#include "Structs.h"
#include "SwitchGround.h"
#include "SwitchTwoGrounds.h"
#include "NPC.h"

struct SwitchGroundStruct {
	vec2d activate;
	vec2d reset;
	float percent;
	std::vector<rect> areaList;
};

struct SwitchTwoGroundsStruct {
	vec2d coords;
	bool onlyNPCActivate;
	bool onlyOneTime;
	std::vector<rect> areaList;
};

struct NPCStruct {
	vec2d coords;
	bool horizontal;
	bool upRight;
	bool gravity;
	bool willRespawn;
	std::vector<rect> areaList;
};

class LevelLoader {
public:
	bool loadLevel(int i);

	vec2d getPlayerCoords();
	std::vector<rect> getKillAreas();
	vec2d getLevelCompleteCoords();
	std::vector<vec2d> getGround();
	std::vector<SwitchGround> getSwitchGround();
	std::vector<SwitchTwoGrounds> getSwitchTwoGrounds();
	std::vector<NPC> getNPCs();

private:
	vec2d player;
	vec2d levelComplete;

	std::vector<rect> killAreas;

	SwitchGroundStruct switchGroundStruct;
	SwitchTwoGroundsStruct switchTwoGroundsStruct;
	NPCStruct npcStruct;

	std::vector<vec2d> groundList;
	std::vector<SwitchGround> switchGroundList;
	std::vector<SwitchTwoGrounds> switchTwoGroundsList;
	std::vector<NPC> npcList;

	bool playerBool;
	bool switchGroundBool = false;
	bool switchTwoGroundsBool = false;
	bool npcBool = false;
};

