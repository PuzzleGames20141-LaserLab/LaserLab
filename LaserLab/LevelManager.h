#ifndef LEVEL_MANAGER_H
#define LEVEL_MANAGER_H

#include <iostream>
#include <ostream>
#include <map>
#include "LevelInfo.h"
#include "Macro.h"

class LevelManager
{
private:
    static bool instanceFlag;
    static LevelManager *level_manager;
    LevelManager()
	{
		for(int i = 1; i <= 30; i++)
		{
			std::string levelName = "Level/level_";
			char numStr[10] = {};
			itoa(i, numStr, 10);
			std::string num = std::string(numStr);
			std::string levelKey = "level";
			levelKey += num;
			levelName += num;
			levelName += "_info.txt";
			std::cout<<levelName<<std::endl;
			const char * fileName = levelName.c_str();
			LevelInfo level_info(fileName);
			levelMap.insert(std::pair<std::string, LevelInfo>(levelKey, level_info));
		}
	}
public:
	std::map<std::string, LevelInfo> levelMap;
    static LevelManager* getInstance();
    ~LevelManager()
    {
        instanceFlag = false;
    }
};
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
        return level_manager;
    }
}

#endif