#ifndef LEVEL_MANAGER_H
#define LEVEL_MANAGER_H

#include <iostream>
#include <ostream>
#include <map>
#include "Grid.h"
#include "LevelInfo.h"
#include "Macro.h"
#include "MenuScreen.h"

class LevelManager
{
private:
    static bool instanceFlag;
    static LevelManager *level_manager;
    LevelManager()
	{
		if(load_mode == 0)
		{
			for(int i = 1; i <= LEVEL_NUMBER; i++)
			{
				std::string levelName = "Level/level_";
				char numStr[10] = {};
				itoa(i, numStr, 10);
				std::string num = std::string(numStr);
				std::string levelKey = "level";
				levelKey += num;
				levelName += num;
				levelName += "_info.txt";
				const char * fileName = levelName.c_str();
				LevelInfo level_info(fileName);
				levelMap.insert(std::pair<std::string, LevelInfo>(levelKey, level_info));
			}
		}
		else
		{
			const char* level_name_file = "UserLevel/level_names.txt";
			std::string * info = loadTXT(level_name_file);
			for(int i = 0; i < 100; i++)
			{
				std::string it = info[i];
				if(it.size() <= 0)
				{
					break;
				}
				std::string levelName = "UserLevel/" + it;
				std::string levelKey = "userlevel" + it;
				levelName += "_info.txt";
				const char * fileName = levelName.c_str();
				LevelInfo level_info(fileName);
				levelMap.insert(std::pair<std::string, LevelInfo>(levelKey, level_info));
				//std::cout<< levelKey << std::endl;
				
			}
		}
	}
public:
	void saveLevelInfo(int levelLabel, int currScore);
	std::map<std::string, LevelInfo> levelMap;
    static LevelManager* getInstance();
    ~LevelManager()
    {
        instanceFlag = false;
    }
};





#endif