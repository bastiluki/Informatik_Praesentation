#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "Render.h"

class Window {
public:
	Window(const char* title, int width, int height, Render* render);
	~Window();

	void changeResolution(int width, int height);

	void makeFullscreen();

	SDL_Renderer* returnRenderer();

private:
	//Fenster und Renderer werden hier gespeichert.
	SDL_Window* window;
	SDL_Renderer* renderer;

	//Die Größe des Bildschirms
	int nativeWidth;
	int nativeHeight;

	//Titel des Fensters
	const char* constTitle;

	//Die Adresse der Render Klasse wird hier gespeichert.
	Render* constRender;
};