#include "GameMode.h"

//In der Initialisierungsfuntion werden Variablen der GameMode-Klasse übergeben
GameMode::GameMode(){
	//Spieler-Koordinaten
	player.x = 0.0f;
	player.y = 0.0f;

	//Spieler-Geschwindigkeit
	playerVel.x = 0.0f;
	playerVel.y = -1.0f;

	//Vorgerechnete Koordinaten;
	earlyPlayer.x = 0.0f;
	earlyPlayer.y = 0.0f;
}

GameMode::~GameMode() {

}

void GameMode::tick(const Uint8* keyState, int* mouseX, int* mouseY) {
	//Alle SwitchGroundobjekte werden durchgegangen und ihre Tick-Funktion ausgeführt.
	//SwitchGround
	for (int i = 0; i < switchGroundList.size(); i++) {
		switchGroundList[i].tick();
	}

	//Alle NPCs werden durchgegangen und ihre Tick-Funktion ausgeführt.
	//NPCs
	for (int i = 0; i < npcList.size(); i++) {
		npcCollision(i);
		npcList[i].tick();
	}

	//Die keyManager Prozedur regelt die Eingabe der Tastatur
	keyManager(keyState);

	//Player
	//Es wird geguckt, ob der Spieler auf andere Onjekte trifft.
	playerCollison();

	//Die konstante Geschwindigkeit wird dem Spieler angerechnet.
	player.x += playerVel.x;
	player.y += playerVel.y;

	//Die Geschwindigkeit des Spielers wird wieder auf ihren ursprünglichen Wert gesetzt.
	playerVel.x = 0.0f;
	playerVel.y = -1.0f;
}

void GameMode::keyManager(const Uint8* keyState) {
	//Hier wird durch das drücken von Tasten die Bewegung des Spielers beeinflusst. Die konstante Geschwindigkeit wird geändert.
	if (keyState[SDL_SCANCODE_A]) {
		playerVel.x += -1.0f;
	}
	if (keyState[SDL_SCANCODE_D]) {
		playerVel.x += 1.0f;
	}
	if (keyState[SDL_SCANCODE_SPACE]) {
		playerVel.y += 5.0f;
	}
}

vec2d GameMode::getPlayerCoords() {
	return player;
}

vec2d GameMode::getLevelCompleteCoords() {
	return levelComplete;
}

std::vector<vec2d> GameMode::getGround() {
	return groundList;
}

std::vector<SwitchGround> GameMode::getSwitchGround() {
	return switchGroundList;
}

std::vector<SwitchTwoGrounds> GameMode::getSwitchTwoGrounds() {
	return switchTwoGroundsList;
}

std::vector<NPC> GameMode::getNPCs() {
	return npcList;
}

//Das nächste Level wird geladen.
void GameMode::loadNextLevel() {
//Die Koordinaten und Liste der Spielonjekte werden von der LevelLoader-Klasse an die GameMode-Klasse übergeben.
	player = levelLoader.getPlayerCoords();
	originalPlayer = player;
	killAreas = levelLoader.getKillAreas();
	levelComplete = levelLoader.getLevelCompleteCoords();
	groundList = levelLoader.getGround();
	switchGroundList = levelLoader.getSwitchGround();
	switchTwoGroundsList = levelLoader.getSwitchTwoGrounds();
	npcList = levelLoader.getNPCs();

	//Das nächste Level wird vorgeladen.
	levelLoader.loadLevel(level + 1);
	level += 1;
}

//Es kann ein bestimmtes Level geladenWerden
void GameMode::loadLevel(int i) {
	levelLoader.loadLevel(i);
}

//Das erste Level wird geladen und es wird zurückgegeben ob das Level geladen werden konnte.
bool GameMode::loadFirstLevel() {
	level = 1;

	if (levelLoader.loadLevel(level)) {
		player = levelLoader.getPlayerCoords();
		originalPlayer = player;
		killAreas = levelLoader.getKillAreas();
		levelComplete = levelLoader.getLevelCompleteCoords();
		groundList = levelLoader.getGround();
		switchGroundList = levelLoader.getSwitchGround();
		switchTwoGroundsList = levelLoader.getSwitchTwoGrounds();
		npcList = levelLoader.getNPCs();

		levelLoader.loadLevel(level + 1);
		level += 1;

		return true;
	}
	else {
		return false;
	}
}

//Hier wird die Kollision des Spielers mit anderen errechnet.
//Es wird durch jedes Objekt durchgegangen, deren Koordinaten mit denen des Spielers verglichen und so erkannt, ob Teile des Spielers
//in einen anderen Block ragen. Wenn dies der Fall ist werden die jeweiligen Koordinaten des Spieler auf die vorherigen gesetzt und
//die Geschwindigkeit auf Null. Im Falle von den Aktivierungsblöcken wird dann die jeweilige Funktion ausgeführt.
void GameMode::playerCollison() {
	earlyPlayer.x = player.x + playerVel.x;
	earlyPlayer.y = player.y + playerVel.y;

	int j = 0;
	int l = 0;

	bool bottom = false, top = false, left = false, right = false;

	//Ground
	{
		//Bottom
		{
			for (int i = 0; i < groundList.size(); i++) {
				bottom = collision2RecsBottom(earlyPlayer.x, earlyPlayer.y, player.x, 23.0f, 23.0f, groundList[i].x, groundList[i].y, 31.0f, 31.0f);

				if (bottom) {
					j = i;
					break;
				}
			}

			if (bottom) {
				player.y = groundList[j].y + 32.0f;
				playerVel.y = 0.0f;
			}
		}

		//Top
		{
			for (int i = 0; i < groundList.size(); i++) {
				top = collision2RecsTop(earlyPlayer.x, earlyPlayer.y, player.x, 23.0f, 23.0f, groundList[i].x, groundList[i].y, 31.0f, 31.0f);

				if (top) {
					j = i;
					break;
				}
			}

			if (top) {
				player.y = groundList[j].y - 24.0f;
				playerVel.y = 0.0f;
			}
		}

		//Left
		{
			for (int i = 0; i < groundList.size(); i++) {
				left = collision2RecsLeft(earlyPlayer.x, earlyPlayer.y, player.y, 23.0f, 23.0f, groundList[i].x, groundList[i].y, 31.0f, 31.0f);

				if (left) {
					j = i;
					break;
				}
			}

			if (left) {
				player.x = groundList[j].x + 32.0f;
				playerVel.x = 0.0f;
			}
		}

		//Right
		{
			for (int i = 0; i < groundList.size(); i++) {
				right = collision2RecsRight(earlyPlayer.x, earlyPlayer.y, player.y, 23.0f, 23.0f, groundList[i].x, groundList[i].y, 31.0f, 31.0f);

				if (right) {
					j = i;
					break;
				}
			}

			if (right) {
				player.x = groundList[j].x - 24.0f;
				playerVel.x = 0.0f;
			}
		}
	}

	//LevelComplete
	{
		if (collision2Recs(earlyPlayer.x, earlyPlayer.y, 23.0f, 23.0f,levelComplete.x, levelComplete.y, 31.0f, 31.0f)) {
			loadNextLevel();
		}
	}

	//KillArea
	{
		for (int i = 0; i < killAreas.size(); i++) {
			if (collision2Recs(player.x, player.y, 23.0f, 23.0f, killAreas[i].x, killAreas[i].y, killAreas[i].w - 1.0f, killAreas[i].h - 1.0f)) {
				player.x = originalPlayer.x;
				player.y = originalPlayer.y;
			}
		}
	}

	//SwitchGround Switches Acitvate
	{
		for (int i = 0; i < switchGroundList.size(); i++) {
			if (collision2Recs(earlyPlayer.x, earlyPlayer.y, 23.0f, 23.0f,
				switchGroundList[i].getActivateCoords().x, switchGroundList[i].getActivateCoords().y, 31.0f, 31.0f)) {
				switchGroundList[i].activate();
			}
		}
	}

	//SwitchGround Switches Reset
	{
		for (int i = 0; i < switchGroundList.size(); i++) {
			if (collision2Recs(earlyPlayer.x, earlyPlayer.y, 23.0f, 23.0f,
				switchGroundList[i].getResetCoords().x, switchGroundList[i].getResetCoords().y, 31.0f, 31.0f)) {
				switchGroundList[i].reset();
			}
		}
	}

	bottom = false, top = false, left = false, right = false;

	//SwitchGround AktivatedArea
	{
		//Bottom
		{
			for (int i = 0; i < switchGroundList.size(); i++) {
				if (switchGroundList[i].getActivated()) {
					int k = switchGroundList[i].getHighArea();
					bottom = collision2RecsBottom(earlyPlayer.x, earlyPlayer.y, player.x, 23.0f, 23.0f,
						switchGroundList[i].getSwitchAreas()[k].x, switchGroundList[i].getSwitchAreas()[k].y,
						switchGroundList[i].getSwitchAreas()[k].w - 1.0f, switchGroundList[i].getSwitchAreas()[k].h - 1.0f);

					if (bottom) {
						j = i;
						break;
					}
				}
			}

			if (bottom) {
				int k = switchGroundList[j].getHighArea();
				player.y = switchGroundList[j].getSwitchAreas()[k].y + switchGroundList[j].getSwitchAreas()[k].h;
				playerVel.y = 0.0f;
			}
		}

		//Top
		{
			for (int i = 0; i < switchGroundList.size(); i++) {
				if (switchGroundList[i].getActivated()) {
					int k = switchGroundList[i].getHighArea();
					top = collision2RecsTop(earlyPlayer.x, earlyPlayer.y, player.x, 23.0f, 23.0f,
						switchGroundList[i].getSwitchAreas()[k].x, switchGroundList[i].getSwitchAreas()[k].y,
						switchGroundList[i].getSwitchAreas()[k].w - 1.0f, switchGroundList[i].getSwitchAreas()[k].h - 1.0f);

					if (top) {
						j = i;
						break;
					}
				}
			}

			if (top) {
				int k = switchGroundList[j].getHighArea();
				player.y = switchGroundList[j].getSwitchAreas()[k].y - 24.0f;
				playerVel.y = 0.0f;
			}
		}

		//Left
		{
			for (int i = 0; i < switchGroundList.size(); i++) {
				if (switchGroundList[i].getActivated()) {
					int k = switchGroundList[i].getHighArea();
					left = collision2RecsLeft(earlyPlayer.x, earlyPlayer.y, player.y, 23.0f, 23.0f,
						switchGroundList[i].getSwitchAreas()[k].x, switchGroundList[i].getSwitchAreas()[k].y,
						switchGroundList[i].getSwitchAreas()[k].w - 1.0f, switchGroundList[i].getSwitchAreas()[k].h - 1.0f);

					if (left) {
						j = i;
						break;
					}
				}
			}

			if (left) {
				int k = switchGroundList[j].getHighArea();
				player.x = switchGroundList[j].getSwitchAreas()[k].x + switchGroundList[j].getSwitchAreas()[k].w;
				playerVel.x = 0.0f;
			}
		}

		//Right
		{
			for (int i = 0; i < switchGroundList.size(); i++) {
				if (switchGroundList[i].getActivated()) {
					int k = switchGroundList[i].getHighArea();
					right = collision2RecsRight(earlyPlayer.x, earlyPlayer.y, player.y, 23.0f, 23.0f,
						switchGroundList[i].getSwitchAreas()[k].x, switchGroundList[i].getSwitchAreas()[k].y,
						switchGroundList[i].getSwitchAreas()[k].w - 1.0f, switchGroundList[i].getSwitchAreas()[k].h - 1.0f);

					if (right) {
						j = i;
						break;
					}
				}
			}

			if (right) {
				int k = switchGroundList[j].getHighArea();
				player.x = switchGroundList[j].getSwitchAreas()[k].x - 24.0f;
				playerVel.x = 0.0f;
			}
		}
	}

	//SwitchTwoGrounds Toggle
	{
		for (int i = 0; i < switchTwoGroundsList.size(); i++) {
			if (!switchTwoGroundsList[i].getOnlyNPC()) {
				if (collision2Recs(earlyPlayer.x, earlyPlayer.y, 23.0f, 23.0f,
					switchTwoGroundsList[i].getCoords().x, switchTwoGroundsList[i].getCoords().y, 31.0f, 31.0f)) {
					if (!(switchTwoGroundsList[i].getWasActivatedOnce() && switchTwoGroundsList[i].getOnlyOneTime())) {
						switchTwoGroundsList[i].switchArea();
					}
				}
				else {
					if (switchTwoGroundsList[i].getOneTimeActivasion())
						switchTwoGroundsList[i].setOneTimeActivasionFalse();
				}
			}
		}
	}

	bottom = false, top = false, left = false, right = false;

	//SwitchTwoGrounds AktivatedAreas
	{
		//Bottom
		{
			for (int i = 0; i < switchTwoGroundsList.size(); i++) {
				for (int k = 0; k < switchTwoGroundsList[i].getSwitchAreas().size(); k++) {
					if (switchTwoGroundsList[i].getActivated() == switchTwoGroundsList[i].getSwitchAreas()[k].activated) {
						bottom = collision2RecsBottom(earlyPlayer.x, earlyPlayer.y, player.x, 23.0f, 23.0f,
							switchTwoGroundsList[i].getSwitchAreas()[k].x, switchTwoGroundsList[i].getSwitchAreas()[k].y,
							switchTwoGroundsList[i].getSwitchAreas()[k].w - 1.0f, switchTwoGroundsList[i].getSwitchAreas()[k].h - 1.0f);
					}

					if (bottom) {
						l = i;
						j = k;
						break;
					}
				}
				if (bottom)
					break;

			}

			if (bottom) {
				player.y = switchTwoGroundsList[l].getSwitchAreas()[j].y + switchTwoGroundsList[l].getSwitchAreas()[j].h;
				playerVel.y = 0.0f;
			}
		}

		//Top
		{
			for (int i = 0; i < switchTwoGroundsList.size(); i++) {
				for (int k = 0; k < switchTwoGroundsList[i].getSwitchAreas().size(); k++) {
					if (switchTwoGroundsList[i].getActivated() == switchTwoGroundsList[i].getSwitchAreas()[k].activated) {
						top = collision2RecsTop(earlyPlayer.x, earlyPlayer.y, player.x, 23.0f, 23.0f,
							switchTwoGroundsList[i].getSwitchAreas()[k].x, switchTwoGroundsList[i].getSwitchAreas()[k].y,
							switchTwoGroundsList[i].getSwitchAreas()[k].w - 1.0f, switchTwoGroundsList[i].getSwitchAreas()[k].h - 1.0f);
					}

					if (top) {
						l = i;
						j = k;
						break;
					}
				}
				if (top)
					break;

			}

			if (top) {
				player.y = switchTwoGroundsList[l].getSwitchAreas()[j].y - 24.0f;
				playerVel.y = 0.0f;
			}
		}

		//Left
		{
			for (int i = 0; i < switchTwoGroundsList.size(); i++) {
				for (int k = 0; k < switchTwoGroundsList[i].getSwitchAreas().size(); k++) {
					if (switchTwoGroundsList[i].getActivated() == switchTwoGroundsList[i].getSwitchAreas()[k].activated) {
						left = collision2RecsLeft(earlyPlayer.x, earlyPlayer.y, player.y, 23.0f, 23.0f,
							switchTwoGroundsList[i].getSwitchAreas()[k].x, switchTwoGroundsList[i].getSwitchAreas()[k].y,
							switchTwoGroundsList[i].getSwitchAreas()[k].w - 1.0f, switchTwoGroundsList[i].getSwitchAreas()[k].h - 1.0f);
					}

					if (left) {
						l = i;
						j = k;
						break;
					}
				}
				if (left)
					break;

			}

			if (left) {
				player.x = switchTwoGroundsList[l].getSwitchAreas()[j].x + switchTwoGroundsList[l].getSwitchAreas()[j].w;
				playerVel.x = 0.0f;
			}
		}

		//Right
		{
			for (int i = 0; i < switchTwoGroundsList.size(); i++) {
				for (int k = 0; k < switchTwoGroundsList[i].getSwitchAreas().size(); k++) {
					if (switchTwoGroundsList[i].getActivated() == switchTwoGroundsList[i].getSwitchAreas()[k].activated) {
						right = collision2RecsRight(earlyPlayer.x, earlyPlayer.y, player.y, 23.0f, 23.0f,
							switchTwoGroundsList[i].getSwitchAreas()[k].x, switchTwoGroundsList[i].getSwitchAreas()[k].y,
							switchTwoGroundsList[i].getSwitchAreas()[k].w - 1.0f, switchTwoGroundsList[i].getSwitchAreas()[k].h - 1.0f);
					}

					if (right) {
						l = i;
						j = k;
						break;
					}
				}
				if (right)
					break;

			}

			if (right) {
				player.x = switchTwoGroundsList[l].getSwitchAreas()[j].x - 24.0f;
				playerVel.x = 0.0f;
			}
		}
	}
}

//Das gleiche wie für den Spieler passiert hier für den NPC.
void GameMode::npcCollision(int index) {
	int j = 0;
	int l = 0;

	bool bottom = false, top = false, left = false, right = false;

	//Ground
	{
		//Bottom
		{
			for (int i = 0; i < groundList.size(); i++) {
				bottom = collision2RecsBottom(npcList[index].getEarlyCoords().x, npcList[index].getEarlyCoords().y, npcList[index].getCoords().x,
					23.0f, 23.0f, groundList[i].x, groundList[i].y, 31.0f, 31.0f);

				if (bottom) {
					j = i;
					break;
				}
			}

			if (bottom) {
				if (!npcList[index].getHorizontal()) {
					npcList[index].invertDirection();
				}
				else {
					npcList[index].setY(groundList[j].y + 32.0f);
					npcList[index].setVely(0.0f);
				}
			}
		}

		//Top
		{
			for (int i = 0; i < groundList.size(); i++) {
				top = collision2RecsTop(npcList[index].getEarlyCoords().x, npcList[index].getEarlyCoords().y, npcList[index].getCoords().x,
					23.0f, 23.0f, groundList[i].x, groundList[i].y, 31.0f, 31.0f);

				if (top) {
					j = i;
					break;
				}
			}

			if (top) {
				if (!npcList[index].getHorizontal()) {
					npcList[index].invertDirection();
				}
				else {
					npcList[index].setY(groundList[j].y - 24.0f);
					npcList[index].setVely(0.0f);
				}
			}
		}

		//Left
		{
			for (int i = 0; i < groundList.size(); i++) {
				left = collision2RecsLeft(npcList[index].getEarlyCoords().x, npcList[index].getEarlyCoords().y, npcList[index].getCoords().y,
					23.0f, 23.0f, groundList[i].x, groundList[i].y, 31.0f, 31.0f);

				if (left) {
					j = i;
					break;
				}
			}

			if (left) {
				if (npcList[index].getHorizontal()) {
					npcList[index].invertDirection();
				}
				else {
					npcList[index].setX(groundList[j].x + 32.0f);
					npcList[index].setVelx(0.0f);
				}
			}
		}

		//Right
		{
			for (int i = 0; i < groundList.size(); i++) {
				right = collision2RecsRight(npcList[index].getEarlyCoords().x, npcList[index].getEarlyCoords().y, npcList[index].getCoords().y,
					23.0f, 23.0f, groundList[i].x, groundList[i].y, 31.0f, 31.0f);

				if (right) {
					j = i;
					break;
				}
			}

			if (right) {
				if(npcList[index].getHorizontal()) {
					npcList[index].invertDirection();
				}
				else {
					npcList[index].setX(groundList[j].x - 24.0f);
					npcList[index].setVelx(0.0f);
				}
			}
		}
	}

	bottom = false, top = false, left = false, right = false;

	//SwitchGround AktivatedArea
	{
		//Bottom
		{
			for (int i = 0; i < switchGroundList.size(); i++) {
				if (switchGroundList[i].getActivated()) {
					int k = switchGroundList[i].getHighArea();
					bottom = collision2RecsBottom(npcList[index].getEarlyCoords().x, npcList[index].getEarlyCoords().y, npcList[index].getCoords().x,
						23.0f, 23.0f, switchGroundList[i].getSwitchAreas()[k].x, switchGroundList[i].getSwitchAreas()[k].y,
						switchGroundList[i].getSwitchAreas()[k].w - 1.0f, switchGroundList[i].getSwitchAreas()[k].h - 1.0f);

					if (bottom) {
						j = i;
						break;
					}
				}
			}

			if (bottom) {
				int k = switchGroundList[j].getHighArea();
				if (!npcList[index].getHorizontal()) {
					npcList[index].invertDirection();
				}
				else {
					npcList[index].setY(switchGroundList[j].getSwitchAreas()[k].y + switchGroundList[j].getSwitchAreas()[k].h);
					npcList[index].setVely(0.0f);
				}
			}
		}

		//Top
		{
			for (int i = 0; i < switchGroundList.size(); i++) {
				if (switchGroundList[i].getActivated()) {
					int k = switchGroundList[i].getHighArea();
					top = collision2RecsTop(npcList[index].getEarlyCoords().x, npcList[index].getEarlyCoords().y, npcList[index].getCoords().x,
						23.0f, 23.0f, switchGroundList[i].getSwitchAreas()[k].x, switchGroundList[i].getSwitchAreas()[k].y,
						switchGroundList[i].getSwitchAreas()[k].w - 1.0f, switchGroundList[i].getSwitchAreas()[k].h - 1.0f);

					if (top) {
						j = i;
						break;
					}
				}
			}

			if (top) {
				int k = switchGroundList[j].getHighArea();
				if (!npcList[index].getHorizontal()) {
					npcList[index].invertDirection();
				}
				else {
					npcList[index].setY(switchGroundList[j].getSwitchAreas()[k].y - 24.0f);
					npcList[index].setVely(0.0f);
				}
			}
		}

		//Left
		{
			for (int i = 0; i < switchGroundList.size(); i++) {
				if (switchGroundList[i].getActivated()) {
					int k = switchGroundList[i].getHighArea();
					left = collision2RecsLeft(npcList[index].getEarlyCoords().x, npcList[index].getEarlyCoords().y, npcList[index].getCoords().y,
						23.0f, 23.0f, switchGroundList[i].getSwitchAreas()[k].x, switchGroundList[i].getSwitchAreas()[k].y,
						switchGroundList[i].getSwitchAreas()[k].w - 1.0f, switchGroundList[i].getSwitchAreas()[k].h - 1.0f);

					if (left) {
						j = i;
						break;
					}
				}
			}

			if (left) {
				int k = switchGroundList[j].getHighArea();
				if (npcList[index].getHorizontal()) {
					npcList[index].invertDirection();
				}
				else {
					npcList[index].setX(switchGroundList[j].getSwitchAreas()[k].x + switchGroundList[j].getSwitchAreas()[k].w);
					npcList[index].setVelx(0.0f);
				}
			}
		}

		//Right
		{
			for (int i = 0; i < switchGroundList.size(); i++) {
				if (switchGroundList[i].getActivated()) {
					int k = switchGroundList[i].getHighArea();
					right = collision2RecsRight(npcList[index].getEarlyCoords().x, npcList[index].getEarlyCoords().y, npcList[index].getCoords().y,
						23.0f, 23.0f, switchGroundList[i].getSwitchAreas()[k].x, switchGroundList[i].getSwitchAreas()[k].y,
						switchGroundList[i].getSwitchAreas()[k].w - 1.0f, switchGroundList[i].getSwitchAreas()[k].h - 1.0f);

					if (right) {
						j = i;
						break;
					}
				}
			}

			if (right) {
				int k = switchGroundList[j].getHighArea();
				if (npcList[index].getHorizontal()) {
					npcList[index].invertDirection();
				}
				else {
					npcList[index].setX(switchGroundList[j].getSwitchAreas()[k].x - 24.0f);
					npcList[index].setVelx(0.0f);
				}
			}
		}
	}

	//SwitchTwoGrounds Toggle
	{
		for (int i = 0; i < switchTwoGroundsList.size(); i++) {
			if (switchTwoGroundsList[i].getOnlyNPC()) {
				if (collision2Recs(npcList[index].getCoords().x, npcList[index].getCoords().y, 23.0f, 23.0f,
					switchTwoGroundsList[i].getCoords().x, switchTwoGroundsList[i].getCoords().y, 31.0f, 31.0f)) {
					switchTwoGroundsList[i].switchArea();
				}
				else {
					if (switchTwoGroundsList[i].getOneTimeActivasion())
						switchTwoGroundsList[i].setOneTimeActivasionFalse();
				}
			}
		}
	}

	bottom = false, top = false, left = false, right = false;

	//SwitchTwoGrounds AktivatedAreas
	{
		//Bottom
		{
			for (int i = 0; i < switchTwoGroundsList.size(); i++) {
				for (int k = 0; k < switchTwoGroundsList[i].getSwitchAreas().size(); k++) {
					if (switchTwoGroundsList[i].getActivated() == switchTwoGroundsList[i].getSwitchAreas()[k].activated) {
						bottom = collision2RecsBottom(npcList[index].getEarlyCoords().x, npcList[index].getEarlyCoords().y, npcList[index].getCoords().x,
							23.0f, 23.0f, switchTwoGroundsList[i].getSwitchAreas()[k].x, switchTwoGroundsList[i].getSwitchAreas()[k].y,
							switchTwoGroundsList[i].getSwitchAreas()[k].w - 1.0f, switchTwoGroundsList[i].getSwitchAreas()[k].h - 1.0f);
					}

					if (bottom) {
						l = i;
						j = k;
						break;
					}
				}
				if (bottom)
					break;

			}

			if (bottom) {
				if (!npcList[index].getHorizontal()) {
					npcList[index].invertDirection();
				}
				else {
					npcList[index].setY(switchTwoGroundsList[l].getSwitchAreas()[j].y + switchTwoGroundsList[l].getSwitchAreas()[j].h);
					npcList[index].setVely(0.0f);
				}
			}
		}

		//Top
		{
			for (int i = 0; i < switchTwoGroundsList.size(); i++) {
				for (int k = 0; k < switchTwoGroundsList[i].getSwitchAreas().size(); k++) {
					if (switchTwoGroundsList[i].getActivated() == switchTwoGroundsList[i].getSwitchAreas()[k].activated) {
						top = collision2RecsTop(npcList[index].getEarlyCoords().x, npcList[index].getEarlyCoords().y, npcList[index].getCoords().x,
							23.0f, 23.0f, switchTwoGroundsList[i].getSwitchAreas()[k].x, switchTwoGroundsList[i].getSwitchAreas()[k].y,
							switchTwoGroundsList[i].getSwitchAreas()[k].w - 1.0f, switchTwoGroundsList[i].getSwitchAreas()[k].h - 1.0f);
					}

					if (top) {
						l = i;
						j = k;
						break;
					}
				}
				if (top)
					break;

			}

			if (top) {
				if (!npcList[index].getHorizontal()) {
					npcList[index].invertDirection();
				}
				else {
					npcList[index].setY(switchTwoGroundsList[l].getSwitchAreas()[j].y - 24.0f);
					npcList[index].setVely(0.0f);
				}
			}
		}

		//Left
		{
			for (int i = 0; i < switchTwoGroundsList.size(); i++) {
				for (int k = 0; k < switchTwoGroundsList[i].getSwitchAreas().size(); k++) {
					if (switchTwoGroundsList[i].getActivated() == switchTwoGroundsList[i].getSwitchAreas()[k].activated) {
						left = collision2RecsLeft(npcList[index].getEarlyCoords().x, npcList[index].getEarlyCoords().y, npcList[index].getCoords().y,
							23.0f, 23.0f, switchTwoGroundsList[i].getSwitchAreas()[k].x, switchTwoGroundsList[i].getSwitchAreas()[k].y,
							switchTwoGroundsList[i].getSwitchAreas()[k].w - 1.0f, switchTwoGroundsList[i].getSwitchAreas()[k].h - 1.0f);
					}

					if (left) {
						l = i;
						j = k;
						break;
					}
				}
				if (left)
					break;

			}

			if (left) {
				if (npcList[index].getHorizontal()) {
					npcList[index].invertDirection();
				}
				else {
					npcList[index].setX(switchTwoGroundsList[l].getSwitchAreas()[j].x + switchTwoGroundsList[l].getSwitchAreas()[j].w);
					npcList[index].setVelx(0.0f);
				}
			}
		}

		//Right
		{
			for (int i = 0; i < switchTwoGroundsList.size(); i++) {
				for (int k = 0; k < switchTwoGroundsList[i].getSwitchAreas().size(); k++) {
					if (switchTwoGroundsList[i].getActivated() == switchTwoGroundsList[i].getSwitchAreas()[k].activated) {
						right = collision2RecsRight(npcList[index].getEarlyCoords().x, npcList[index].getEarlyCoords().y, npcList[index].getCoords().y,
							23.0f, 23.0f, switchTwoGroundsList[i].getSwitchAreas()[k].x, switchTwoGroundsList[i].getSwitchAreas()[k].y,
							switchTwoGroundsList[i].getSwitchAreas()[k].w - 1.0f, switchTwoGroundsList[i].getSwitchAreas()[k].h - 1.0f);
					}

					if (right) {
						l = i;
						j = k;
						break;
					}
				}
				if (right)
					break;

			}

			if (right) {
				if (npcList[index].getHorizontal()) {
					npcList[index].invertDirection();
				}
				else {
					npcList[index].setX(switchTwoGroundsList[l].getSwitchAreas()[j].x - 24.0f);
					npcList[index].setVelx(0.0f);
				}
			}
		}
	}

	//KillAreas
	{
		for (int i = 0; i < npcList[index].getKillAreas().size(); i++) {
			if (collision2Recs(npcList[index].getCoords().x, npcList[index].getCoords().y, 23.0f, 23.0f,
				npcList[index].getKillAreas()[i].x, npcList[index].getKillAreas()[i].y,
				npcList[index].getKillAreas()[i].w - 1.0f, npcList[index].getKillAreas()[i].h - 1.0f)) {
				if (npcList[index].getRespawn()) {
					npcList[index].respawning();
					break;
				}
			}
		}
	}
}

//Hier ist die einzelne Prüfung ob der ein Punkt des Spielers inerhalb eines objekts ist.
bool GameMode::collision2RecsBottom(float x1, float y1, float orgX1, float w1, float h1, float x2, float y2, float w2, float h2) {
	if (y1 <= y2 + h2 && y1 >= y2 && ((orgX1 >= x2 && orgX1 <= x2 + w2) || (orgX1 + w1 >= x2 && orgX1 + w1 <= x2 + w2))) {
		return true;
	}
	return false;
}

bool GameMode::collision2RecsTop(float x1, float y1, float orgX1, float w1, float h1, float x2, float y2, float w2, float h2) {
	if (y1 + h1 >= y2 && y1 + h1 <= y2 + h2 && ((orgX1 >= x2 && orgX1 <= x2 + w2) || (orgX1 + w1 >= x2 && orgX1 + w1 <= x2 + w2))) {
		return true;
	}
	return false;
}

bool GameMode::collision2RecsLeft(float x1, float y1, float orgY1, float w1, float h1, float x2, float y2, float w2, float h2) {
	if (x1 <= x2 + w2 && x1 >= x2 && ((orgY1 >= y2 && orgY1 <= y2 + h2) || (orgY1 + h1 >= y2 && orgY1 + h1 <= y2 + h2))) {
		return true;
	}
	return false;
}

bool GameMode::collision2RecsRight(float x1, float y1, float orgY1, float w1, float h1, float x2, float y2, float w2, float h2) {
	if (x1 + w1 >= x2 && x1 + w1 <= x2 + w2 && ((orgY1 >= y2 && orgY1 <= y2 + h2) || (orgY1 + h1 >= y2 && orgY1 + h1 <= y2 + h2))) {
		return true;
	}
	return false;
}

bool GameMode::collision2Recs(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2) {
	if (x1 + w1 >= x2 && x1 <= x2 + w2 && y1 + h1 >= y2 && y1 <= y2 + h2) {
		return true;
	}
	return false;
}