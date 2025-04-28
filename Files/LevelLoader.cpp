#include "LevelLoader.h"

bool LevelLoader::loadLevel(int i) {
	killAreas.clear();
	groundList.clear();
	switchGroundList.clear();
	switchTwoGroundsList.clear();
	npcList.clear();

    std::string filePath = "level\\level" + std::to_string(i) + ".lev";

    std::ifstream levelFile(filePath);

    if (!levelFile.good()) {
		levelFile.close();
        return false;
    }
    else {
        std::string readLine;

        while (std::getline(levelFile, readLine)) {
            if (readLine.size() > 2) {
                if (readLine[0] == 'p' && readLine[1] == 'l') {
                    //Player
                    int middleSpace;

                    for (int i = 3; i < readLine.size(); i++) {
                        if (readLine[i] == ' ') {
                            middleSpace = i;
                            break;
                        }
                    }

					playerBool = true;

                    player.x = std::stof(readLine.substr(3, middleSpace - 3));
                    player.y = std::stof(readLine.substr(middleSpace + 1, readLine.size() - middleSpace));
                }
                else if (readLine[0] == 'l' && readLine[1] == 'c') {
                    //LevelComplete
                    int middleSpace;

                    for (int i = 3; i < readLine.size(); i++) {
                        if (readLine[i] == ' ') {
                            middleSpace = i;
                            break;
                        }
                    }

                    levelComplete.x = std::stof(readLine.substr(3, middleSpace - 3));
                    levelComplete.y = std::stof(readLine.substr(middleSpace + 1, readLine.size() - middleSpace));
                }
                else if (readLine[0] == 'g' && readLine[1] == 'r') {
                    //Ground
                    int middleSpace;

                    for (int i = 3; i < readLine.size(); i++) {
                        if (readLine[i] == ' ') {
                            middleSpace = i;
                            break;
                        }
                    }

                    vec2d ground;
                    ground.x = std::stof(readLine.substr(3, middleSpace - 3));
                    ground.y = std::stof(readLine.substr(middleSpace + 1, readLine.size() - middleSpace));

                    groundList.push_back(ground);
                }
                else if (readLine[0] == 's' && readLine[1] == 'g') {
                    //SwitchGround
                    switchGroundBool = true;
                    int lastSpace = 3;
                    int count = 0;
                    readLine += ' ';

                    for (int i = 3; i < readLine.size(); i++) {
                        if (readLine[i] == ' ') {
                            switch (count) {
                            case 0:                             
                                switchGroundStruct.activate.x = std::stof(readLine.substr(lastSpace, i - lastSpace));
                                lastSpace = i + 1;
                                break;
                            case 1:
                                switchGroundStruct.activate.y = std::stof(readLine.substr(lastSpace, i - lastSpace));
                                lastSpace = i + 1;
                                break;
                            case 2:
                                switchGroundStruct.reset.x = std::stof(readLine.substr(lastSpace, i - lastSpace));
                                lastSpace = i + 1;
                                break;
                            case 3:
                                switchGroundStruct.reset.y = std::stof(readLine.substr(lastSpace, i - lastSpace));
                                lastSpace = i + 1;
                                break;
                            case 4:
                                switchGroundStruct.percent = std::stof(readLine.substr(lastSpace, readLine.size() - lastSpace));
                                break;
                            }
                            count++;
                        }
                    }
                }
                else if (readLine[0] == 's' && readLine[1] == 't') {
                    //SwitchTwoGrounds
                    switchTwoGroundsBool = true;
                    int lastSpace = 3;
                    int count = 0;
                    readLine += ' ';

                    for (int i = 3; i < readLine.size(); i++) {
                        if (readLine[i] == ' ') {
                            switch (count) {
                            case 0:
								switchTwoGroundsStruct.coords.x = std::stof(readLine.substr(lastSpace, i - lastSpace));
                                lastSpace = i + 1;
                                break;
                            case 1:
								switchTwoGroundsStruct.coords.y = std::stof(readLine.substr(lastSpace, i - lastSpace));
                                lastSpace = i + 1;
                                break;
							case 2:
								switchTwoGroundsStruct.onlyNPCActivate = std::stoi(readLine.substr(lastSpace, i - lastSpace));
								lastSpace = i + 1;
								break;
		                    case 3:
								switchTwoGroundsStruct.onlyOneTime = std::stoi(readLine.substr(lastSpace, readLine.size() - lastSpace));
                                break;
                            }
                            count++;
                        }
                    }
                }
                else if (readLine[0] == 'n' && readLine[1] == 'p') {
					//NPC
					npcBool = true;
					int lastSpace = 3;
					int count = 0;
					readLine += ' ';

					for (int i = 3; i < readLine.size(); i++) {
						if (readLine[i] == ' ') {
							switch (count) {
							case 0:
								npcStruct.coords.x = std::stof(readLine.substr(lastSpace, i - lastSpace));
								lastSpace = i + 1;
								break;
							case 1:
								npcStruct.coords.y = std::stof(readLine.substr(lastSpace, i - lastSpace));
								lastSpace = i + 1;
								break;
							case 2:
								npcStruct.horizontal = std::stoi(readLine.substr(lastSpace, i - lastSpace));
								lastSpace = i + 1;
								break;
							case 3:
								npcStruct.upRight = std::stoi(readLine.substr(lastSpace, i - lastSpace));
								lastSpace = i + 1;
								break;
							case 4:
								npcStruct.gravity = std::stoi(readLine.substr(lastSpace, i - lastSpace));
								lastSpace = i + 1;
								break;
							case 5:
								npcStruct.willRespawn = std::stoi(readLine.substr(lastSpace, readLine.size() - lastSpace));
								break;
							}
							count++;
						}
					}
                }
                else if (readLine[0] == 'a' && readLine[1] == 'r') {
					//Areas
					rect rectangle;
					if (switchGroundBool || npcBool || playerBool) {
						int lastSpace = 3;
						int count = 0;
						readLine += ' ';

						for (int i = 3; i < readLine.size(); i++) {
							if (readLine[i] == ' ') {
								switch (count) {
								case 0:
									rectangle.x = std::stof(readLine.substr(lastSpace, i - lastSpace));
									lastSpace = i + 1;
									break;
								case 1:
									rectangle.y = std::stof(readLine.substr(lastSpace, i - lastSpace));
									lastSpace = i + 1;
									break;
								case 2:
									rectangle.w = std::stof(readLine.substr(lastSpace, i - lastSpace));
									lastSpace = i + 1;
									break;
								case 3:
									rectangle.h = std::stof(readLine.substr(lastSpace, readLine.size() - lastSpace));
									break;
								}
								count++;
							}
						}

						if (switchGroundBool) {
							switchGroundStruct.areaList.push_back(rectangle);
						}
						else if (npcBool){
							npcStruct.areaList.push_back(rectangle);
						}
						else {
							killAreas.push_back(rectangle);
						}
					}
					else if (switchTwoGroundsBool) {
						int lastSpace = 3;
						int count = 0;
						readLine += ' ';

						for (int i = 3; i < readLine.size(); i++) {
							if (readLine[i] == ' ') {
								switch (count) {
								case 0:
									rectangle.x = std::stof(readLine.substr(lastSpace, i - lastSpace));
									lastSpace = i + 1;
									break;
								case 1:
									rectangle.y = std::stof(readLine.substr(lastSpace, i - lastSpace));
									lastSpace = i + 1;
									break;
								case 2:
									rectangle.w = std::stof(readLine.substr(lastSpace, i - lastSpace));
									lastSpace = i + 1;
									break;
								case 3:
									rectangle.h = std::stof(readLine.substr(lastSpace, i - lastSpace));
									lastSpace = i + 1;
									break;
								case 4:
									rectangle.activated = std::stoi(readLine.substr(lastSpace, readLine.size() - lastSpace));
									break;
								}
								count++;
							}
						}

						switchTwoGroundsStruct.areaList.push_back(rectangle);
					}
                }
                else if (readLine[0] == ';' && readLine[1] == ';') {
					if (switchGroundBool) {
						SwitchGround switchGround(switchGroundStruct.activate.x, switchGroundStruct.activate.y, 
							switchGroundStruct.reset.x, switchGroundStruct.reset.y, switchGroundStruct.percent);
						for (int i = 0; i < switchGroundStruct.areaList.size(); i++) {
							switchGround.addArea(switchGroundStruct.areaList[i].x, switchGroundStruct.areaList[i].y,
								switchGroundStruct.areaList[i].w, switchGroundStruct.areaList[i].h);
						}

						switchGroundList.push_back(switchGround);

						switchGroundStruct.areaList.clear();
				    }
					else if (switchTwoGroundsBool) {
						SwitchTwoGrounds switchTwoGrounds(switchTwoGroundsStruct.coords.x, switchTwoGroundsStruct.coords.y,
							switchTwoGroundsStruct.onlyNPCActivate, switchTwoGroundsStruct.onlyOneTime);
						for (int i = 0; i < switchTwoGroundsStruct.areaList.size(); i++) {
							switchTwoGrounds.addArea(switchTwoGroundsStruct.areaList[i].x, switchTwoGroundsStruct.areaList[i].y,
								switchTwoGroundsStruct.areaList[i].w, switchTwoGroundsStruct.areaList[i].h,
								switchTwoGroundsStruct.areaList[i].activated);
						}

						switchTwoGroundsList.push_back(switchTwoGrounds);

						switchTwoGroundsStruct.areaList.clear();
					}
					else if (npcBool) {
						NPC npc(npcStruct.coords.x, npcStruct.coords.y,
							npcStruct.horizontal, npcStruct.upRight, npcStruct.gravity, npcStruct.willRespawn);
						for (int i = 0; i < npcStruct.areaList.size(); i++) {
							npc.addKillArea(npcStruct.areaList[i].x, npcStruct.areaList[i].y,
								npcStruct.areaList[i].w, npcStruct.areaList[i].h);
						}

						npcList.push_back(npc);

						npcStruct.areaList.clear();
					}

					playerBool = false;
					switchGroundBool = false;
					switchTwoGroundsBool = false;
					npcBool = false;
                }
            }
        }

		levelFile.close();
		return true;
    }
}

vec2d LevelLoader::getPlayerCoords() {
    return player;
}

std::vector<rect> LevelLoader::getKillAreas() {
	return killAreas;
}

vec2d LevelLoader::getLevelCompleteCoords() {
    return levelComplete;
}

std::vector<vec2d> LevelLoader::getGround() {
    return groundList;
}

std::vector<SwitchGround> LevelLoader::getSwitchGround() {
    return switchGroundList;
}

std::vector<SwitchTwoGrounds> LevelLoader::getSwitchTwoGrounds()
{
    return switchTwoGroundsList;
}

std::vector<NPC> LevelLoader::getNPCs() {
	return npcList;
}
