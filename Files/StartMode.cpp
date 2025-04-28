#include "StartMode.h"

void StartMode::tick(const Uint8* keyStates, Uint32* mouseState, int* mouseX, int* mouseY, bool* gameRunning, GameModes* mode) {
//Die Boolschen-Variablen ob der Zeiger über dem Button ist, werden auf falsch gesetzt.
	settingsHover = false;
	creditsHover = false;
	newHover = false;
	savesHover = false;
	quitHover = false;

	//wenn der Modus des Startbildschirms normal ist wird geprüft, über welchen Buttons der zeiger ist.
	if (screenMode == NORMAL) {
		if (*mouseX >= 19 && *mouseX <= 70 && *mouseY >= 20 && *mouseY <= 70) {
			creditsHover = true;
		}
		if (*mouseX >= 1209 && *mouseX <= 1260 && *mouseY >= 20 && *mouseY <= 70) {
			settingsHover = true;
		}
		if (*mouseX >= 439 && *mouseX <= 840 && *mouseY >= 350 && *mouseY <= 390) {
			newHover = true;

			//Wenn die Linke Maustaste über diesem Button gedrückt wird, ändert sich der Spielmodus zu GAME
			if (*mouseState == SDL_BUTTON_LEFT) {
				*mode = GAME;
			}
		}
		if (*mouseX >= 439 && *mouseX <= 840 && *mouseY >= 440 && *mouseY <= 480) {
			savesHover = true;
		}
		if (*mouseX >= 439 && *mouseX <= 840 && *mouseY >= 530 && *mouseY <= 570) {
			quitHover = true;
			//Wenn die Linke Maustaste über diesem Button gedrückt wird, ändert dsich der Spielmodus zu GAME
			if (*mouseState == SDL_BUTTON_LEFT) {
				*gameRunning = false;
			}
		}
	}
}