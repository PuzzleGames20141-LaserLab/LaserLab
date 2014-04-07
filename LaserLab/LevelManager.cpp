#include "LevelManager.h"
#include "LevelInfo.h"
#include "GameScreen.h"

bool LevelManager::instanceFlag = false;
LevelManager* LevelManager::level_manager = NULL;

LevelManager* LevelManager::getInstance()
{
    if(! instanceFlag)
    {
        level_manager = new LevelManager();
        instanceFlag = true;
        return level_manager;
    }
    else
    {
		delete level_manager;
		level_manager = new LevelManager();
        return level_manager;
    }
}

void LevelManager::saveLevelInfo(int levelLabel, int currScore)
{
	std::string levelKey = "";
	if(load_mode == 0)
	{
		char numStr[10] = {};
		itoa(levelLabel, numStr, 10);
		std::string num = std::string(numStr);
		levelKey = "level";
		levelKey += num;
	}
	else
	{
		levelKey = "userlevel" + user_curr_level;
	}
	levelMap[levelKey].setScore(currScore);
	levelMap[levelKey].saveToFile();
	if(load_mode == 0 && levelLabel < LEVEL_NUMBER) {
		char nextNumStr[10] = {};
		itoa(levelLabel+1, nextNumStr, 10);
		std::string nextNum = std::string(nextNumStr);
		levelKey = "level";
		levelKey += nextNum;
		levelMap[levelKey].unlock();
		levelMap[levelKey].saveToFile();
	}
}