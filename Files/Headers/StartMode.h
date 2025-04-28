#pragma once

#include <SDL2/SDL.h>

#include "Enums.h"

class StartMode {
public:
	void tick(const Uint8* keyStates, Uint32* mouseState, int* mouseX, int* mouseY, bool* gameRunning, GameModes* mode);

	bool settingsHover = false;
	bool creditsHover = false;
	bool newHover = false;
	bool savesHover = false;
	bool quitHover = false;
private:
	StartScreenMode screenMode = NORMAL;
};