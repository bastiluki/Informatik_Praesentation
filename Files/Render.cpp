#include "Render.h"

//Die Werte für den Renderer und das Fenster werden aktualisiert, so dass die Klasse das Fenster rendern kann.
void Render::updateValues(SDL_Window* bufferWindow, SDL_Renderer* bufferRenderer, int inputWidth, int inputHeight) {
	window = bufferWindow;
	renderer = bufferRenderer;

	width = (float)inputWidth;
	height = (float)inputHeight;

	//Der Skalierungswert zum Fenster wird hier errechnet.
	ratioX = width / 1280.0;
	ratioY = height / 720.0;

	//Die Schriftart wird in den Arbeitsspeicher geladen.
	font = TTF_OpenFont("font\\Roboto-Regular.ttf", 24);
}

//Der Bilsdchirm wird geleert.
void Render::clear() {
	SDL_RenderClear(renderer);
}

//Alles was im Arbeitsspeicher gerendert werden soll wir hier gerendert.
void Render::display() {
	SDL_RenderPresent(renderer);
}

//Dinge werden hier zum Rendern in den Arbeitsspeicher geladen
void Render::tick(GameModes* mode, GameMode* gameMode, StartMode* startMode) {
	//Game
	if (*mode == GAME) {
		{
			//Ground

			//Die Farbe des Vierecks wird definiert.
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

			//Es wird durch die Ground-Liste gegangen dabei ein Viereck erstellt und dann in den Arbeitsspeicher geladen.
			for (vec2d ground : gameMode->getGround()) {
				SDL_Rect rect;
				rect.x = ground.x * ratioX;
				rect.y = height - (ground.y + 32.0f) * ratioY;
				rect.w = 32.0f * ratioX;
				rect.h = 32.0f * ratioY;

				SDL_RenderDrawRect(renderer, &rect);
			}

			//SwitchGround
			for (SwitchGround switchGround : gameMode->getSwitchGround()) {
				SDL_SetRenderDrawColor(renderer, 72, 0, 255, 255);

				SDL_Rect rect;
				//Activate Block
				rect.x = switchGround.getActivateCoords().x * ratioX;
				rect.y = height - (switchGround.getActivateCoords().y + 32.0f) * ratioY;
				rect.w = 32.0f * ratioX;
				rect.h = 32.0f * ratioY;

				SDL_RenderFillRect(renderer, &rect);


				SDL_SetRenderDrawColor(renderer, 178, 0, 255, 255);
				//Reset Block
				rect.x = switchGround.getResetCoords().x * ratioX;
				rect.y = height - (switchGround.getResetCoords().y + 32.0f) * ratioY;
				rect.w = 32.0f * ratioX;
				rect.h = 32.0f * ratioY;

				SDL_RenderFillRect(renderer, &rect);

				//Activated Area
				//Für jedes SwitchGround-Objekt gibt es eine Area-Liste. Hier werden diese durchgegangen und entsprechend, ob sie aktiviert sind oder nicht angezeigt.
				for (int i = 0; i < switchGround.getSwitchAreas().size(); i++) {
					rect.x = switchGround.getSwitchAreas()[i].x * ratioX;
					rect.y = height - (switchGround.getSwitchAreas()[i].y + switchGround.getSwitchAreas()[i].h) * ratioY;
					rect.w = switchGround.getSwitchAreas()[i].w * ratioX;
					rect.h = switchGround.getSwitchAreas()[i].h * ratioY;

					if (i == switchGround.getHighArea() && !switchGround.getActivated()) {
						SDL_SetRenderDrawColor(renderer, 0, 38, 255, 255);

						SDL_RenderFillRect(renderer, &rect);
					}
					else if (i == switchGround.getHighArea() && switchGround.getActivated()) {
						SDL_SetRenderDrawColor(renderer, 0, 19, 127, 255);

						SDL_RenderFillRect(renderer, &rect);
					}
					else if (i != switchGround.getHighArea() && switchGround.getActivated()) {
						SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

						SDL_RenderFillRect(renderer, &rect);
					}
					else {
						SDL_SetRenderDrawColor(renderer, 64, 64, 64, 255);

						SDL_RenderFillRect(renderer, &rect);
					}
				}
			}

			//SwitchTwoGrounds
			for (SwitchTwoGrounds switchTwoGrounds : gameMode->getSwitchTwoGrounds()) {
				SDL_Rect rect;
				//Toggle Block
				rect.x = switchTwoGrounds.getCoords().x * ratioX;
				rect.y = height - (switchTwoGrounds.getCoords().y + 32.0f) * ratioY;
				rect.w = 32.0f * ratioX;
				rect.h = 32.0f * ratioY;

				if (switchTwoGrounds.getActivated()) {
					SDL_SetRenderDrawColor(renderer, 0, 148, 255, 255);
				}
				else {
					SDL_SetRenderDrawColor(renderer, 255, 0, 110, 255);
				}
				SDL_RenderFillRect(renderer, &rect);

				//Areas
				for (int i = 0; i < switchTwoGrounds.getSwitchAreas().size(); i++) {
					rect.x = switchTwoGrounds.getSwitchAreas()[i].x * ratioX;
					rect.y = height - (switchTwoGrounds.getSwitchAreas()[i].y + switchTwoGrounds.getSwitchAreas()[i].h) * ratioY;
					rect.w = switchTwoGrounds.getSwitchAreas()[i].w * ratioX;
					rect.h = switchTwoGrounds.getSwitchAreas()[i].h * ratioY;

					if (switchTwoGrounds.getSwitchAreas()[i].activated == switchTwoGrounds.getActivated() && switchTwoGrounds.getSwitchAreas()[i].activated) {
						SDL_SetRenderDrawColor(renderer, 255, 0, 110, 255);
						SDL_RenderFillRect(renderer, &rect);
					}
					else if (switchTwoGrounds.getSwitchAreas()[i].activated != switchTwoGrounds.getActivated() && switchTwoGrounds.getSwitchAreas()[i].activated) {
						SDL_SetRenderDrawColor(renderer, 255, 0, 110, 255);
						SDL_RenderDrawRect(renderer, &rect);
					}
					if (switchTwoGrounds.getSwitchAreas()[i].activated == switchTwoGrounds.getActivated() && !switchTwoGrounds.getSwitchAreas()[i].activated) {
						SDL_SetRenderDrawColor(renderer, 0, 148, 255, 255);
						SDL_RenderFillRect(renderer, &rect);
					}
					else if (switchTwoGrounds.getSwitchAreas()[i].activated != switchTwoGrounds.getActivated() && !switchTwoGrounds.getSwitchAreas()[i].activated) {
						SDL_SetRenderDrawColor(renderer, 0, 148, 255, 255);
						SDL_RenderDrawRect(renderer, &rect);
					}
				}
			}

			//NPCs
			SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

			for (NPC npc : gameMode->getNPCs()) {
				SDL_Rect rect;
				rect.x = npc.getCoords().x * ratioX;
				rect.y = height - (npc.getCoords().y + 24.0f) * ratioY;
				rect.w = 24.0f * ratioX;
				rect.h = 24.0f * ratioY;

				SDL_RenderDrawRect(renderer, &rect);

				if (debug) {
					renderTextFromFloat(npc.getCoords().x, npc.getCoords().x + 2.0f,
						npc.getCoords().y + 14.0f, 0.4f, 255, 255, 255, 255);
					renderTextFromFloat(npc.getCoords().y, npc.getCoords().x + 2.0f,
						npc.getCoords().y + 2.0f, 0.5f, 255, 255, 255, 255);
				}
			}

			//LevelComplete
			{
				SDL_SetRenderDrawColor(renderer, 255, 144, 0, 255);

				SDL_Rect rect;
				rect.x = gameMode->getLevelCompleteCoords().x * ratioX;
				rect.y = height - (gameMode->getLevelCompleteCoords().y + 32.0f) * ratioY;
				rect.w = 32.0f * ratioX;
				rect.h = 32.0f * ratioY;

				SDL_RenderFillRect(renderer, &rect);
			}


			//Player
			{
				SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

				SDL_Rect rect;
				rect.x = gameMode->getPlayerCoords().x * ratioX;
				rect.y = height - (gameMode->getPlayerCoords().y + 24.0f) * ratioY;
				rect.w = 24.0f * ratioX;
				rect.h = 24.0f * ratioY;

				SDL_RenderDrawRect(renderer, &rect);

				//Wenn debug wahr ist bzw. F5 gedrückt wurde werden die Koordinaten im Spieler angezeigt.
				if (debug) {
					renderTextFromFloat(gameMode->getPlayerCoords().x, gameMode->getPlayerCoords().x + 2.0f,
						gameMode->getPlayerCoords().y + 14.0f, 0.4f, 255, 255, 255, 255);
					renderTextFromFloat(gameMode->getPlayerCoords().y, gameMode->getPlayerCoords().x + 2.0f,
						gameMode->getPlayerCoords().y + 2.0f, 0.4f, 255, 255, 255, 255);
				}
			}
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	}
	//Start
	else if (*mode == START) {
		//Das StartMenü wird hier in den Arbeitsspeicher geladen. Wenn der Zeiger über einem Button ist werden die Ränder nicht angezeigt
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

		SDL_RenderDrawLine(renderer, 340 * ratioX, 50 * ratioY, 939 * ratioX, 50 * ratioY);
		SDL_RenderDrawLine(renderer, 340 * ratioX, 250 * ratioY, 939 * ratioX, 250 * ratioY);

		SDL_RenderDrawLine(renderer, 339 * ratioX, 50 * ratioY, 339 * ratioX, 250 * ratioY);
		SDL_RenderDrawLine(renderer, 940 * ratioX, 50 * ratioY, 940 * ratioX, 250 * ratioY);

		SDL_RenderDrawLine(renderer, 339 * ratioX, 50 * ratioY, 940 * ratioX, 250 * ratioY);
		SDL_RenderDrawLine(renderer, 339 * ratioX, 250 * ratioY, 940 * ratioX, 50 * ratioY);

		if (!(startMode->newHover)) {
			SDL_RenderDrawLine(renderer, 440 * ratioX, 350 * ratioY, 839 * ratioX, 350 * ratioY);
			SDL_RenderDrawLine(renderer, 440 * ratioX, 390 * ratioY, 839 * ratioX, 390 * ratioY);

			SDL_RenderDrawLine(renderer, 439 * ratioX, 350 * ratioY, 439 * ratioX, 390 * ratioY);
			SDL_RenderDrawLine(renderer, 840 * ratioX, 350 * ratioY, 840 * ratioX, 390 * ratioY);
		}

		SDL_RenderDrawLine(renderer, 439 * ratioX, 350 * ratioY, 840 * ratioX, 390 * ratioY);
		SDL_RenderDrawLine(renderer, 439 * ratioX, 390 * ratioY, 840 * ratioX, 350 * ratioY);

		if (!(startMode->savesHover)) {
			SDL_RenderDrawLine(renderer, 440 * ratioX, 440 * ratioY, 839 * ratioX, 440 * ratioY);
			SDL_RenderDrawLine(renderer, 440 * ratioX, 480 * ratioY, 839 * ratioX, 480 * ratioY);

			SDL_RenderDrawLine(renderer, 439 * ratioX, 440 * ratioY, 439 * ratioX, 480 * ratioY);
			SDL_RenderDrawLine(renderer, 840 * ratioX, 440 * ratioY, 840 * ratioX, 480 * ratioY);
		}

		SDL_RenderDrawLine(renderer, 439 * ratioX, 440 * ratioY, 840 * ratioX, 480 * ratioY);
		SDL_RenderDrawLine(renderer, 439 * ratioX, 480 * ratioY, 840 * ratioX, 440 * ratioY);

		if (!(startMode->quitHover)) {
			SDL_RenderDrawLine(renderer, 440 * ratioX, 530 * ratioY, 839 * ratioX, 530 * ratioY);
			SDL_RenderDrawLine(renderer, 440 * ratioX, 570 * ratioY, 839 * ratioX, 570 * ratioY);

			SDL_RenderDrawLine(renderer, 439 * ratioX, 530 * ratioY, 439 * ratioX, 570 * ratioY);
			SDL_RenderDrawLine(renderer, 840 * ratioX, 530 * ratioY, 840 * ratioX, 570 * ratioY);
		}

		SDL_RenderDrawLine(renderer, 439 * ratioX, 530 * ratioY, 840 * ratioX, 570 * ratioY);
		SDL_RenderDrawLine(renderer, 439 * ratioX, 570 * ratioY, 840 * ratioX, 530 * ratioY);

		if (!(startMode->settingsHover)) {
			SDL_RenderDrawLine(renderer, 1210 * ratioX, 20 * ratioY, 1259 * ratioX, 20 * ratioY);
			SDL_RenderDrawLine(renderer, 1210 * ratioX, 70 * ratioY, 1259 * ratioX, 70 * ratioY);

			SDL_RenderDrawLine(renderer, 1209 * ratioX, 20 * ratioY, 1209 * ratioX, 70 * ratioY);
			SDL_RenderDrawLine(renderer, 1260 * ratioX, 20 * ratioY, 1260 * ratioX, 70 * ratioY);
		}

		SDL_RenderDrawLine(renderer, 1209 * ratioX, 20 * ratioY, 1260 * ratioX, 70 * ratioY);
		SDL_RenderDrawLine(renderer, 1209 * ratioX, 70 * ratioY, 1260 * ratioX, 20 * ratioY);

		if (!(startMode->creditsHover)) {
			SDL_RenderDrawLine(renderer, 20 * ratioX, 20 * ratioY, 69 * ratioX, 20 * ratioY);
			SDL_RenderDrawLine(renderer, 20 * ratioX, 70 * ratioY, 69 * ratioX, 70 * ratioY);

			SDL_RenderDrawLine(renderer, 19 * ratioX, 20 * ratioY, 19 * ratioX, 70 * ratioY);
			SDL_RenderDrawLine(renderer, 70 * ratioX, 20 * ratioY, 70 * ratioX, 70 * ratioY);
		}

		SDL_RenderDrawLine(renderer, 19 * ratioX, 20 * ratioY, 70 * ratioX, 70 * ratioY);
		SDL_RenderDrawLine(renderer, 19 * ratioX, 70 * ratioY, 70 * ratioX, 20 * ratioY);


		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	}
}

//In der Funtion wird der Text erst in eine Oberfläche, dann in eine Textur umgewandelt und dann in den Arbeitsspeicher geladen.
void Render::renderText(const char* text, float x, float y, float scale, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	SDL_Color color = { r, g, b, a };

	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, color);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_Rect rectangle;
	rectangle.x = x;
	rectangle.y = y;
	TTF_SizeText(font, text, &rectangle.w, &rectangle.h);
	rectangle.w *= scale;
	rectangle.h *= scale;

	SDL_RenderCopy(renderer, textTexture, NULL, &rectangle);

	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);
}

//Hier wird noch eine Zahl in einen String umgewandelt.
void Render::renderTextFromFloat(float number, float x, float y, float scale, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	SDL_Color color = { r, g, b, a };

	std::string buffText = std::to_string(number);
	buffText.erase(buffText.find_last_not_of('0') + 1, std::string::npos);
	buffText.erase(buffText.find_last_not_of('.') + 1, std::string::npos);

	const char* text = buffText.c_str();

	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, color);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_Rect rectangle;
	rectangle.x = x * ratioX;
	rectangle.y = height - (y + 24.0f * scale) * ratioY;
	TTF_SizeText(font, text, &rectangle.w, &rectangle.h);
	rectangle.w *= scale * ratioX;
	rectangle.h *= scale * ratioY;

	SDL_RenderCopy(renderer, textTexture, NULL, &rectangle);

	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);
}
