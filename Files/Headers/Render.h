#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <cmath>
#include <algorithm>
#include <string>

#include "Enums.h"
#include "Structs.h"
#include "GameMode.h"
#include "StartMode.h"
#include "SwitchGround.h"
#include "SwitchTwoGrounds.h"
#include "NPC.h"

class Render {
public:
	void updateValues(SDL_Window* bufferWindow, SDL_Renderer* bufferRenderer, int inputWidth, int inputHeight);

	void clear();
	void display();

	void tick(GameModes* mode, GameMode* gameMode, StartMode* startMode);

	float ratioX = 0.0;
	float ratioY = 0.0;

	bool debug = false;

private:
	//Die Adressen aus der Window-Klasse werden hier gespeichert
	SDL_Window* window;
	SDL_Renderer* renderer;
	TTF_Font* font;

	float width = 0.0;
	float height = 0.0;

	void renderText(const char* text, float x, float y, float scale, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	void renderTextFromFloat(float number, float x, float y, float scale, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
};