//Bibliotheken und Header-Dateien werden importiert.
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <chrono>

#include "Structs.h"
#include "Enums.h"
#include "Window.h"
#include "Render.h"
#include "GameMode.h"
#include "StartMode.h"

//Tick-Funktion, die andere Tick-Funktionen von gameMode unsd startMode einmal ausführt.
void tick(const Uint8* keyState, Uint32* mouseState, int* mouseX, int* mouseY, bool* gameRunning, GameModes* mode, GameMode* gameMode, StartMode* startMode) {
	if (*mode == GAME) {
		gameMode->tick(keyState, mouseX, mouseY);
	}
	else if (*mode == START) {
		startMode->tick(keyState, mouseState, mouseX, mouseY, gameRunning, mode);
	}
}

#undef main

//Eingangspunkt des Programms
int main(int argc, char* args[]) {

	//Initialisierung der Bibiliotheken von SDL, SDL_image und SDL_TTF
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		std::cout << "SDL_Init failed! SDL_Error: " << SDL_GetError() << std::endl;
	if (!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "IMG_Init failed! SDL_Error: " << SDL_GetError() << std::endl;
	if(TTF_Init() < 0)
		std::cout << "TTF_Init failed! SDL_Error: " << SDL_GetError() << std::endl;

	// Boolean, die die Taste F5 nur einmal drücken lässt
	bool F5Pressed = false;

	//Boolean, die die Kopfgesteuerte Hauptschleife kontrolliert
	bool gameRunning = true;

	//Angabe des Spielmodus als Enum
	GameModes mode = START;

	//Initalisierung der Klasse GameMode (Der hauptsächliche Code des Spiels) als gameMode
	GameMode gameMode;

	//Das erste Level wird in den Arbeitspeicher geladen. Wenn das Laden mislingt, wird eine Fehlerbox angezeigt und -1 als Endcode angegeben.
	if (!gameMode.loadFirstLevel()) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Level could not load!", "Failed to load Level! \nFiles are probably missing! \n", NULL);
		return -1;
	}

	//Der Startmodus (Startbildschirm) wird initalisiert als startMode.
	StartMode startMode;

	//Integers, die die Position des Maus speichern.
	int mouseX = 0, mouseY = 0;

	//Integers, die die Größe des Bildschirms angeben
	int WIDTH = 1280, HEIGHT = 720;

	//Variable, in der Events (Was der Benutzer für Eingaben tätigt) gespeichert werden
	SDL_Event event;


	//Hier werden die Klassen zum Rendern initalisiert.
	Render render;
	Window window("Liederbock", WIDTH, HEIGHT, &render);


	//Hier werden Variablen mithilfe der chrono Bibliothek initialisiert, die dann das den Spiel-Teil und den Render-Teil zu bestimmten Zeiten ausführen.
	std::chrono::steady_clock::time_point startTimePoint = std::chrono::steady_clock::now();

	double nsRender = 1000000000.0 / 144;
	double nsTick = 1000000000.0 / 300;
	double now = 0;
	double deltaRender = 0;
	double deltaTick = 0;
	double lastTime = std::chrono::duration_cast<std::chrono::nanoseconds>(startTimePoint - startTimePoint).count();

	while (gameRunning) {
		std::chrono::steady_clock::time_point endTimePoint = std::chrono::steady_clock::now();
		now = std::chrono::duration_cast<std::chrono::nanoseconds>(endTimePoint - startTimePoint).count();

		deltaRender += (now - lastTime) / nsRender;
		deltaTick += (now - lastTime) / nsTick;
		lastTime = now;

		//Wenn deltaTick größer als 1 ist, werden alle Funktionen und Klassen des Spiel-Teils einmal augeführt, die von hier erreicht werden.
		if (deltaTick >= 1) {
			while (SDL_PollEvent(&event) > 0) {
				switch (event.type) {
				case SDL_QUIT:
					//settings.save();
					gameRunning = false;
					break;
				}
			}
			//Hier werden die gedrückten Tasten regestriert und gespeichert.
			const Uint8* keyState = SDL_GetKeyboardState(NULL);
			
			//Hier werden die Mausetasten und Mausposition regestriert und gespeichert. Anschließend wird die Position der Maus noch skaliert.
			Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);
			mouseX /= render.ratioX;
			mouseY /= render.ratioY;

			//Es wird geprüft, ob die Taste F5 gedrückt ist. Durch Drücken wird wird der COde nur einmal ausgeführt.
			if (keyState[SDL_SCANCODE_F5]) {
				if (!F5Pressed) {
					render.debug = !render.debug;
					F5Pressed = true;
				}
			}
			else {
				F5Pressed = false;
			}
			
			//Der Rest des Spiel-Teils wird einmal ausgeführt und es werden Variablen bzw. ihre Adresssen weitergegeben
			tick(keyState, &mouseState, &mouseX, &mouseY, &gameRunning, &mode, &gameMode, &startMode);

			//deltaTick wird wieder auf Null definiert, damit wieder aufgezählt wird bis deltaTick größer gleich Eins ist.
			deltaTick = 0;
		}

		//Wenn deltaRender größer gleich 1 ist wird, wird der Render-Teil einmal ausgeführt und das Spiel wird auf dem Bildschirm angezeigt
		if (deltaRender >= 1) {
			//Das Fenster wird leer gemacht (Ausschließlich schwarze Pixel)
			render.clear();
			
			//Die zu anzeigenden Dinge werden in den Arbeitsspeicher geladen.
			render.tick(&mode, &gameMode, &startMode);

			//Die im Arbeitsspeicher enthaltenden Dinge werden auf das Fenster gebracht.
			render.display();

			//deltaRender wird wie oben als Null definiert
			deltaRender = 0;
		}
	}

	//Die SDL- und SDL_image-Bibliothek werden aus dem Arbeitsspeicher gelöcht. 
	IMG_Quit();
	SDL_Quit();

	//Das Programm beendet und gibt den Endcode 0 aus
	return 0;
}